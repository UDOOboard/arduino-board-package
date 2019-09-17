#!/bin/bash

set -e

mkdir -p debian/build/temp
OUT=$(realpath debian/build/temp)

for source in udoo/solox/variants/udooneo/*.c; do
  DEST=$(basename $source)
  /usr/bin/arm-none-eabi-gcc -c -g -Os -Wall -Wextra -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard \
    -mfpu=fpv4-sp-d16 -fmessage-length=0 -ffunction-sections -fdata-sections -D_AEABI_LC_CTYPE=C \
    -D__STRICT_ANSI__=1 -std=gnu11 -MMD -mcpu=cortex-m4 -Iudoo/solox/variants/udooneo/mqx/release/bsp \
    -Iudoo/solox/variants/udooneo/mqx/release/bsp/Sources -Iudoo/solox/variants/udooneo/mqx/release \
    -Iudoo/solox/variants/udooneo/mqx/release/psp -Iudoo/solox/variants/udooneo/mqx/release/open-amp \
    -DARDUINO=123456 -Iudoo/solox/cores/arduino -Iudoo/solox/variants/udooneo $source -o $OUT/$DEST.o
done

for source in udoo/solox/variants/udooneo/*.cpp; do
  DEST=$(basename $source)
  /usr/bin/arm-none-eabi-g++ -c -g -Os -Wall -Wextra -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard \
  -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -ffunction-sections -fdata-sections -g -D_AEABI_LC_CTYPE=C \
  -D__STRICT_ANSI__=1 -std=gnu++11 -fabi-version=0 -MMD -mcpu=cortex-m4 -Iudoo/solox/variants/udooneo/mqx/release/bsp \
  -Iudoo/solox/variants/udooneo/mqx/release/bsp/Sources -Iudoo/solox/variants/udooneo/mqx/release \
  -Iudoo/solox/variants/udooneo/mqx/release/psp -Iudoo/solox/variants/udooneo/mqx/release/open-amp \
  -DARDUINO=123456 -Iudoo/solox/cores/arduino -Iudoo/solox/variants/udooneo $source -o $OUT/$DEST.o
done

/usr/bin/arm-none-eabi-ar rcs debian/build/udooneo.a $OUT/*.o
