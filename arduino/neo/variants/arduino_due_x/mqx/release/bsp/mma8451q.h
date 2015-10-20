#ifndef __mma8451q_h__
#define __mma8451q_h__
/**HEADER*******************************************************************
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* FileName: mma8451q.h
* Version :
* Date    : Jun-24-2014
*
* Comments:
*
*   mma8451q driver overall header file
*
*END************************************************************************/

/* mma8451q register definition and bit field masks */
#include "mma8451q_reg.h"

/* mma8451q basic level IO interface */
#include "mma8451q_basic.h"

/* mma8451q functional level generic IO interface */
#include "mma8451q_generic.h"

/* mma8451q motion and freefall detection interface */
#include "mma8451q_ff_mt.h"

/* mma8451q portrait/landscape detection interface */
#include "mma8451q_lapo.h"

/* mma8451q pulse detection interface */
#include "mma8451q_pulse.h"

/* mma8451q transient detection interface */
#include "mma8451q_tran.h"

#endif
