#!/bin/bash
#
# build_index_packages.sh
# Builds packages and index file for Arduino IDE
#
# Copyright (C) 2015 Aidilab Srl
# Author: Ettore Chimenti <ek5.chimenti@gmail.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

# we need bash 4 for associative arrays
if [ "${BASH_VERSION%%[^0-9]*}" -lt "4" ]; then
  echo "BASH VERSION < 4: ${BASH_VERSION}" >&2
  exit 1
fi

scm_ver()
{
  ## from kernel sources

	# Check for git and a git repo.
	if test -z "$(git rev-parse --show-cdup 2>/dev/null)" &&
	   head=`git rev-parse --verify --short HEAD 2>/dev/null`; then

		# If we are at a tagged commit (like "v2.6.30-rc6"), we ignore
		# it, because this version is defined in the top level Makefile.
		if [ -z "`git describe --exact-match 2>/dev/null`" ]; then

			# If we are past a tagged commit (like
			# "v2.6.30-rc5-302-g72357d5"), we pretty print it.
			if atag="`git describe 2>/dev/null`"; then
      
        #edited by ek5 -> 1.6.6-00001-g0bc4b15% (need plus)
        awk -F- '{printf("%s-%05d-%s", $(NF-2), $(NF-1), $(NF))}' <<< "$atag"

			# If we don't have a tag at all we print -g{commitish}.
			else
				printf '%s%s' -g $head
			fi

    else
      #we do not have Makefiles lol
      printf '%s' "`git describe 2>/dev/null`"
		fi

		# Check for uncommitted changes
		if git diff-index --name-only HEAD | grep -qv "^debian/"; then
			printf '%s' -dirty
		fi

		# All done with git
		return
	fi
}

### VARIABLES

unset DAEMON

# get package script directory
REPO_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
SHA_DIR="${REPO_DIR}/packages"

PACKAGE_INDEX_FILE=`mktemp`
_PACKAGE_INDEX_FILE="$REPO_DIR/build/package_udoo_index.json"

# boards are served via github pages
LOCAL_DOWNLOAD_URL="http://127.0.0.1:8080"
REMOTE_DOWNLOAD_URL="https://udooboard.github.io/arduino-board-package"

declare -a ARCHS
ARCHS=( qdl neo )
declare -A ARCHS_PKG ARCHS_TARGET

ARCHS_TARGET[qdl]="sam"
ARCHS_TARGET[neo]="solox"

declare -a TOOLS
TOOLS=( udooclient gcc-arm-none-eabi bossac-udoo )

declare -a PACKAGEHOST
PACKAGEHOST=( i686-mingw32 i386-apple-darwin11 x86_64-apple-darwin x86_64-pc-linux-gnu i686-pc-linux-gnu )

declare -A PACKAGEVERSION
PACKAGEVERSION[udooclient]="1.0"
PACKAGEVERSION[bossac-udoo]="1.3a-1.0"
PACKAGEVERSION[gcc-arm-none-eabi]="4.9-2014q4-20141203"

declare -A DOWNLOADURL
DOWNLOADURL[udooclient]="https://github.com/UDOOboard/udoofota/releases/download/v${PACKAGEVERSION[udooclient]}"
DOWNLOADURL[bossac-udoo]="https://github.com/UDOOboard/bossac/releases/download/v${PACKAGEVERSION[bossac-udoo]}"
DOWNLOADURL[gcc-arm-none-eabi]="http://www.udoo.org/download/files/crosscompiler"

read -r -d '' PACKAGES_HEADER <<EOF
{
  "packages":[
    {
      "name":"UDOO",
      "maintainer":"UDOO Team",
      "websiteURL":"https://www.udoo.org",
      "email":"social@udoo.org",
      "help":{
        "online":"https://forum.udoo.org"
      },
      "platforms":[
EOF

read -r -d '' JSON <<EOF
      {
          "name":"UDOO NEO (iMX6 SoloX)",
          "architecture":"solox",
          "version":"PACKAGEVERSION",
          "category":"Contributed",
          "url":"DOWNLOADURL",
          "archiveFileName":"PACKAGENAME",
          "checksum":"SHA-256:PACKAGESHA",
          "size":"PACKAGESIZE",
          "help":{
            "online":"https://www.udoo.org"
          },
          "boards":[
            { "name":"UDOO NEO (iMX6 SoloX)" }
          ],
          "toolsDependencies":[
            {
              "packager": "UDOO",
              "name": "udooclient",
              "version": "${PACKAGEVERSION[udooclient]}"
            },
            {
              "packager": "UDOO",
              "name": "gcc-arm-none-eabi",
              "version": "${PACKAGEVERSION[gcc-arm-none-eabi]}"
            }
          ]
       }
EOF

ARCHS_PKG[neo]="$JSON"

read -r -d '' JSON <<EOF
         {
          "name":"UDOO QUAD/DUAL (Arduino Due)",
          "architecture":"sam",
          "version":"PACKAGEVERSION",
          "category":"Contributed",
          "url":"DOWNLOADURL",
          "archiveFileName":"PACKAGENAME",
          "checksum":"SHA-256:PACKAGESHA",
          "size":"PACKAGESIZE",
          "help":{
            "online":"https://www.udoo.org"
          },
          "boards":[
            { "name":"UDOO QUAD/DUAL (Arduino Due)" }
          ],
          "toolsDependencies":[
            {
              "packager": "UDOO",
              "name": "bossac-udoo",
              "version": "${PACKAGEVERSION[bossac-udoo]}"
            },
            {
              "packager": "arduino",
              "name": "arm-none-eabi-gcc",
              "version": "4.8.3-2014q1"
            }
          ]
        }
EOF

ARCHS_PKG[qdl]="$JSON"

read -r -d '' PACKAGES_FOOTER <<EOF
],
EOF

read -r -d '' TOOLS_HEADER <<EOF
      "tools":[
EOF

read -r -d '' TOOLS_FOOTER <<EOF
      ]
    }
  ]
}
EOF

# clean build dir (unless we are debugging)
cd $REPO_DIR
mkdir -p build

GREEN="\e[32m"
RED="\e[31m"
BOLD="\e[1m"
RST="\e[0m"

function log() {

  # args: string
  local EXIT
  local COLOR=${GREEN}${BOLD} 
  local MOD="-e"

  case $1 in
    err) COLOR=${RED}${BOLD}
      shift ;;
    pre) MOD+="n"
      shift ;;
    fat) COLOR=${RED}${BOLD}
      EXIT=1
      shift ;;
    *) ;;
  esac

  echo $MOD "${COLOR}${*}${RST}"

  (( $EXIT )) && exit $EXIT

}

function shasize() {
 
  # args: archive_path sha_return size_return

  local arc=$1
  local  __sha=$2
  local  __size=$3

  local _sha=$(openssl dgst -sha256 $1 | awk '{print $2}')
  local _size=$( du -b $1 | awk '{print $1}')

  eval $__sha="'$_sha'"
  eval $__size="'$_size'"
}


function archive() {

  # args: archive_name source_path sha_return size_return
  local  __sha=$3
  local  __size=$4
  local sha size

  local arc=$1.tar.bz2

  log pre "Building $arc..."

  if [[ ! -f build/$arc ]] 
  then

    #create archive
    tar -jcf "build/$arc" -C "$2" --exclude '*swp' --exclude '*~' --exclude '.git*' .
  else
    log pre "using cache file..."
  fi

  shasize build/$arc sha size

  log "\t\tDone!"
  eval $__sha="'$sha'"
  eval $__size="'$size'"

}

usage() {
# $1 text
# $2 exitcode

  [[ -n $1 ]] && echo $1

  cat <<-EOF
		Usage: ${0##*/} [option]
		
		UDOO Arduino Board Package Index Builder
		Options:
		    -h                   Show this help
		    -d|--daemon          For testing: execute a local http server
		
		EOF
  exit ${2:-0}
}

cd $REPO_DIR

#argument parsing
while (( $# )) 
do 
  case $1 in
    -h|--help) usage ;;
    -d|--daemon) DAEMON=1 ; shift ;;
    *) 
      # many arguments provided
      usage "Too many arguments!" 1 ;;
  esac
done  

#ek5
#create packages

echo "$PACKAGES_HEADER" > $PACKAGE_INDEX_FILE

unset ok_pkg

if (( DAEMON ))
then
  BOARD_DOWNLOAD_URL="$LOCAL_DOWNLOAD_URL"
  TAGS=( $(git tag) boardmanager ) 
else
  BOARD_DOWNLOAD_URL="$REMOTE_DOWNLOAD_URL"
  TAGS=( $(git tag) ) 
fi

#cycle tags
for tags in ${TAGS[*]}
do 

  git checkout -f $tags 

  #cycle every package
  for i in ${ARCHS[*]}
  do

    PACKAGE_VERSION=`scm_ver`


    HARDWARE_FILES="udoo/${ARCHS_TARGET[$i]}"
    BOARD_ARCHIVE_NAME="udoo$i-arduino-${ARCHS_TARGET[$i]}-$PACKAGE_VERSION"
    PACKAGENAME="${BOARD_ARCHIVE_NAME}.tar.bz2"
    DOWNLOADURL="${BOARD_DOWNLOAD_URL}/$PACKAGENAME"

    # create archives and get sha & size
    archive "$BOARD_ARCHIVE_NAME" "$HARDWARE_FILES" PACKAGESHA PACKAGESIZE

    cd $REPO_DIR

    #put a comma on previous snippet
    (( $ok_pkg )) && echo , >> $PACKAGE_INDEX_FILE

    # fill in board json template
    echo -n "${ARCHS_PKG[$i]}" | sed \
      -e "s|PACKAGEVERSION|$PACKAGE_VERSION|g" \
      -e "s|PACKAGENAME|$PACKAGENAME|g" \
      -e "s|DOWNLOADURL|$DOWNLOADURL|g" \
      -e "s|PACKAGESHA|$PACKAGESHA|g" \
      -e "s|PACKAGESIZE|$PACKAGESIZE|g" >> $PACKAGE_INDEX_FILE

    #first snippet ok, next will put comma
    ok_pkg=1

  done
  #end package

done
#end tags

unset ok_pkg

echo "$PACKAGES_FOOTER" >> $PACKAGE_INDEX_FILE

echo "$TOOLS_HEADER" >> $PACKAGE_INDEX_FILE

#cycle for every tool
for i in ${TOOLS[*]}
do

  unset comma
  [ -v ok_tool ] && comma=","

  # fill in board json template
  cat >> $PACKAGE_INDEX_FILE <<EOF
  $comma{
    "name":"${i}",
    "version":"${PACKAGEVERSION[$i]}",
    "systems": [
EOF

    #cycle every host arch
    for host in ${PACKAGEHOST[*]}
    do

      cd build

      unset comma
      (( $ok_host )) && comma=","

      PACKAGENAME="$i-${PACKAGEVERSION[$i]}-${host}.tar.bz2"
      DOWNLOADURL="${DOWNLOADURL[$i]}/$PACKAGENAME"

      #check for a previous shasum
      if [[ -e ${SHA_DIR}/${PACKAGENAME}.sha ]]
      then
        log "Found $i shasum for ${host}..."
        read PACKAGESHA file < "${SHA_DIR}/${PACKAGENAME}.sha"
      elif [[ -e ${PACKAGENAME} ]]
      then
        #if not, check for a predownloaded one
        log "Found $i for ${host} in cache..."
        #get sha and size
        shasize $PACKAGENAME PACKAGESHA PACKAGESIZE
      else
        #download the tools (unless they already exist)
        log pre "Downloading $i for ${host}..."
        wget -q "$DOWNLOADURL"

        #error management
        if (( $? ))
        then
          log err "\t\t ERROR"
          log err "ERROR: Cannot download ${PACKAGENAME}" >&2
          log err "ERROR: Skipping ${host} for ${i}..." >&2
          cd $REPO_DIR
          continue
        else
          log "\t\t Done!"
          #get sha and size
          shasize $PACKAGENAME PACKAGESHA PACKAGESIZE
        fi
      fi

      cat >> $PACKAGE_INDEX_FILE <<EOF
      $comma{
        "host":"$host",
        "url":"$DOWNLOADURL",
        "archiveFileName":"$PACKAGENAME",
        "checksum":"SHA-256:$PACKAGESHA",
        "size":"$PACKAGESIZE"
EOF
      echo -n "}" >> $PACKAGE_INDEX_FILE

      cd $REPO_DIR

      ok_host=1

    done  #end arch host cycle

    (( ok_host )) || log fat "FATAL: Cannot find any architecture for tool $i"

    unset ok_host

    #close end tool bracket
    echo -n "]}" >> $PACKAGE_INDEX_FILE

    ok_tool=1

done  #end tool cycle

unset ok_tool

echo "$TOOLS_FOOTER" >> $PACKAGE_INDEX_FILE

#let's beautify this json
python -m json.tool < $PACKAGE_INDEX_FILE > $_PACKAGE_INDEX_FILE

if (( DAEMON )) 
then 

  cd build
  log "Serving testing board package at $BOARD_DOWNLOAD_URL/${_PACKAGE_INDEX_FILE##*/}"
  ( python -m http.server 8080 ) 
  cd -

fi

exit 0

