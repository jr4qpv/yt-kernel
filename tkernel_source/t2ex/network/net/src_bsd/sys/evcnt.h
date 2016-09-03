/*	$NetBSD: evcnt.h,v 1.5 2007/12/16 20:45:59 dyoung Exp $	*/

/*
 * Copyright (c) 1996, 2000 Christopher G. Demetriou
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
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * --(license Id: LICENSE.proto,v 1.1 2000/06/13 21:40:26 cgd Exp )--
 */

/*
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _SYS_EVCNT_H_
#define	_SYS_EVCNT_H_

#ifndef T2EX
#include <sys/queue.h>
#else
#include <sys/_queue.h>
#endif
#include <sys/stdint.h>

/*
 * event counters
 */

struct evcnt {
	uint64_t	ev_count;	/* how many have occurred */
	TAILQ_ENTRY(evcnt) ev_list;	/* entry on list of all counters */
	unsigned char	ev_type;	/* counter type; see below */
	unsigned char	ev_grouplen;	/* 'group' len, excluding NUL */
	unsigned char	ev_namelen;	/* 'name' len, excluding NUL */
	char		ev_pad1;	/* reserved (for now); 0 */
	const struct evcnt *ev_parent;	/* parent, for hierarchical ctrs */
	const char	*ev_group;	/* name of group */
	const char	*ev_name;	/* name of specific event */
};
TAILQ_HEAD(evcntlist, evcnt);

/* maximum group/name lengths, including trailing NUL */
#define	EVCNT_STRING_MAX	256

/* ev_type values */
#define	EVCNT_TYPE_MISC		0	/* miscellaneous; catch all */
#define	EVCNT_TYPE_INTR		1	/* interrupt; count with vmstat -i */
#define	EVCNT_TYPE_TRAP		2	/* processor trap/execption */

/*
 * initializer for an event count structure.  the lengths are initted and
 * it is added to the evcnt list at attach time.
 */
#define	EVCNT_INITIALIZER(type, parent, group, name)	\
    {							\
	.ev_type = type,				\
	.ev_parent = parent,				\
	.ev_group = group,				\
	.ev_name = name,				\
    }

/*
 * Attach a static event counter.  This uses a link set to do the work.
 * NOTE: "ev" should not be a pointer to the object, but rather a direct
 * reference to the object itself.
 */
#define	EVCNT_ATTACH_STATIC(ev)		__link_set_add_data(evcnts, ev)
#define	EVCNT_ATTACH_STATIC2(ev, n)	__link_set_add_data2(evcnts, ev, n)

#ifdef _KERNEL

extern struct evcntlist allevents;	/* list of all event counters */

void	evcnt_init(void);
void	evcnt_attach_static(struct evcnt *);
void	evcnt_attach_dynamic(struct evcnt *, int, const struct evcnt *,
	    const char *, const char *);
void	evcnt_detach(struct evcnt *);

#ifdef DDB
void	event_print(int, void (*)(const char *, ...));
#endif
#endif /* _KERNEL */

#endif /* !_SYS_EVCNT_H_ */
