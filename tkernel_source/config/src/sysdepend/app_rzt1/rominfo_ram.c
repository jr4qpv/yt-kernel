/*
 *----------------------------------------------------------------------
 *    T-Kernel 2.0 Software Package
 *
 *    Copyright 2011 by Ken Sakamura.
 *    This software is distributed under the latest version of T-License 2.x.
 *----------------------------------------------------------------------
 *
 *    Released by T-Engine Forum(http://www.t-engine.org/) at 2011/05/17.
 *    Modified by T-Engine Forum at 2013/03/02.
 *    Modified by TRON Forum(http://www.tron.org/) at 2015/06/01.
 *
 *----------------------------------------------------------------------
 *
 *    Modified by T.Yokobayashi since 2016/04/20.
 *
 *----------------------------------------------------------------------
 */

/*
 *	@(#)rominfo_ram.c (RZT1) 2019/05/02
 *
 *	ROM information for RAM kernel
 */

#include <basic.h>
#include <sys/rominfo.h>

IMPORT UB SYSCONF[], DEVCONF[];
IMPORT void START();

/* Kernel address */
#define RI_KERNEL_START	(FP)&START	/* Kernel start address */
#define RI_SYSCONF	(UB*)SYSCONF	/* SYSCONF top */
#define RI_DEVCONF	(UB*)DEVCONF	/* DEVCONF top */

/* User definition */
//#define RI_USERAREA_TOP	(void*)0x00080000	/* RAM user area top */
#define RI_USERAREA_TOP	(void*)0x4C800000	/* RAM user area top */
#define RI_USERINIT	(FP)0x20000000	/* User initialization program */
#define RI_RESETINIT	(FP)NULL	/* Reset initialization program */

/* ROM disk */
#define RI_RDSK_TYPE	(UW)0		/* ROM disk type */
#define RI_RDSK_BLOCK	(UW)0		/* ROM disk block size */
#define RI_RDSK_START	(UW)0		/* ROM disk start address */
#define RI_RDSK_END	(UW)0		/* ROM disk end address */


/* ROM information */
RomInfo rominfo = {
	RI_KERNEL_START,	/* Kernel startup address */
	RI_SYSCONF,		/* SYSCONF top */
	RI_DEVCONF,		/* DEVCONF top */
	RI_USERAREA_TOP,	/* RAM user area top */
	RI_USERINIT,		/* User initialization program address */
	RI_RESETINIT,		/* Reset initialization program address */
	{0},			/* Reserved (always 0) */

	RI_RDSK_TYPE,		/* ROM disk type */
	RI_RDSK_BLOCK,		/* ROM disk block size */
	RI_RDSK_START,		/* ROM disk start address */
	RI_RDSK_END,		/* ROM disk end address */
	{0}			/* Reserved (always 0) */
};


/*----------------------------------------------------------------------
#|History of "rominfo_ram.c"
#|--------------------------
#|* 2016/04/20	It's copied from "../tef_em1d/" and it's modified.
#|* 2018/08/24	｢RI_USERAREA_TOP｣を"0x4C800000"に変更(ramend)。
#|
*/