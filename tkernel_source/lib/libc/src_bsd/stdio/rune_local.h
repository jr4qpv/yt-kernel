/* 	$OpenBSD: rune_local.h,v 1.2 2005/10/10 17:37:44 espie Exp $ */
/*	$NetBSD: rune_local.h,v 1.7 2003/03/02 22:18:15 tshiozak Exp $	*/

/*-
 * Copyright (c) 2000 Citrus Project,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _RUNE_LOCAL_H_
#define _RUNE_LOCAL_H_

/* rune.c */
extern _RuneLocale *_Read_RuneMagi(FILE *fp);
extern void _NukeRune(_RuneLocale *);

/* setrunelocale.c */
extern int _xpg4_setrunelocale(const char *);
extern _RuneLocale *_findrunelocale(const char *);
extern int _newrunelocale(const char *);

/* runeglue.c */
extern int __make_ctype_tabs(_RuneLocale *);
extern void __install_currentrunelocale_ctype();

/* ___runetype_mb.c */
extern _RuneType ___runetype_mb(wint_t);

#endif
