/*
 * libbinkdec - Bink video decoder
 * Copyright (C) 2011 Barry Duncan
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

 /* This code is based on the Bink decoder from the FFmpeg project which can be obtained from http://www.ffmpeg.org/
  * below is the license from FFmpeg
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

  /*
   * Bink video decoder
   * Copyright (c) 2009 Konstantin Shishkov
   * Copyright (C) 2011 Peter Ross <pross@xvid.org>
   *
   * This file is part of FFmpeg.
   *
   * FFmpeg is free software; you can redistribute it and/or
   * modify it under the terms of the GNU Lesser General Public
   * License as published by the Free Software Foundation; either
   * version 2.1 of the License, or (at your option) any later version.
   *
   * FFmpeg is distributed in the hope that it will be useful,
   * but WITHOUT ANY WARRANTY; without even the implied warranty of
   * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   * Lesser General Public License for more details.
   *
   * You should have received a copy of the GNU Lesser General Public
   * License along with FFmpeg; if not, write to the Free Software
   * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
   */

#ifndef _FFmpeg_includes_h_
#define _FFmpeg_includes_h_

#include <math.h>

#define av_cold

   // taken from FFmpeg - mem.h
   //#define DECLARE_ALIGNED(n,t,v)      __declspec(align(n)) t v

#if defined(__INTEL_COMPILER) && __INTEL_COMPILER < 1110 || defined(__SUNPRO_C)
#define DECLARE_ALIGNED(n,t,v)      t __attribute__ ((aligned (n))) v
#define DECLARE_ASM_ALIGNED(n,t,v)  t __attribute__ ((aligned (n))) v
#define DECLARE_ASM_CONST(n,t,v)    const t __attribute__ ((aligned (n))) v
#elif defined(__DJGPP__)
#define DECLARE_ALIGNED(n,t,v)      t __attribute__ ((aligned (FFMIN(n, 16)))) v
#define DECLARE_ASM_ALIGNED(n,t,v)  t av_used __attribute__ ((aligned (FFMIN(n, 16)))) v
#define DECLARE_ASM_CONST(n,t,v)    static const t av_used __attribute__ ((aligned (FFMIN(n, 16)))) v
#elif defined(__GNUC__) || defined(__clang__)
#define DECLARE_ALIGNED(n,t,v)      t __attribute__ ((aligned (n))) v
#define DECLARE_ASM_ALIGNED(n,t,v)  t av_used __attribute__ ((aligned (n))) v
#define DECLARE_ASM_CONST(n,t,v)    static const t av_used __attribute__ ((aligned (n))) v
#elif defined(_MSC_VER)
#define DECLARE_ALIGNED(n,t,v)      __declspec(align(n)) t v
#define DECLARE_ASM_ALIGNED(n,t,v)  __declspec(align(n)) t v
#define DECLARE_ASM_CONST(n,t,v)    __declspec(align(n)) static const t v
#else
#define DECLARE_ALIGNED(n,t,v)      t v
#define DECLARE_ASM_ALIGNED(n,t,v)  t v
#define DECLARE_ASM_CONST(n,t,v)    static const t v
#endif

#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

#ifndef M_SQRT1_2
#define M_SQRT1_2      0.70710678118654752440  /* 1/sqrt(2) */
#endif

#define HAVE_MMX 0
#define ARCH_ARM 0
#define HAVE_ALTIVEC 0
#define CONFIG_MDCT 1

typedef short DCTELEM;

#endif
