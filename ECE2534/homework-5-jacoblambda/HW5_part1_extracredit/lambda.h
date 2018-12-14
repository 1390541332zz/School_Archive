/* Copyright (c) 2018, Texas Instruments Incorporated
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

*  Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

*  Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

*  Neither the name of Texas Instruments Incorporated nor the names of
   its contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/


#include <ti/grlib/grlib.h>

static const unsigned char pixel_lambda1BPP_UNCOMP[] =
{
0xc7, 0xc0, 
0xc7, 0xc0, 
0xf3, 0xc0, 
0xf3, 0xc0, 
0xe1, 0xc0, 
0xe1, 0xc0, 
0xcd, 0xc0, 
0x9c, 0xc0, 
0x1c, 0x00, 
0x3e, 0x3e
};

static const unsigned long palette_lambda1BPP_UNCOMP[]=
{
  0x00FFFF00, 0x000000FF
};

static const unsigned long negpalette_lambda1BPP_UNCOMP[]=
{
   0x000000FF,  0x000000FF
};

const tImage  lambda =
{
    IMAGE_FMT_1BPP_UNCOMP,
    10,
    10,
    2,
    palette_lambda1BPP_UNCOMP,
    pixel_lambda1BPP_UNCOMP,
};

const tImage  neglambda =
{
    IMAGE_FMT_1BPP_UNCOMP,
    10,
    10,
    2,
    negpalette_lambda1BPP_UNCOMP,
    pixel_lambda1BPP_UNCOMP,
};
