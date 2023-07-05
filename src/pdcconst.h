/*
 * OpenComal -- a free Comal implementation
 *
 * This file is part of the OpenComal package.
 * (c) Copyright 1992-2002 Jos Visser <josv@osp.nl>
 *
 * The OpenComal package is covered by the GNU General Public
 * License. See doc/LICENSE for more information.
 */

/* OpenComal, various not-implementation defined constants */

#define MAX_LINELEN		(256)	/* Max line length for input etc. */
#define MAX_IDLEN		(31)
#define MAX_INDENT		(16)	/* Max nesting of control structures */
#define INDENTION		(2)	/* Indention per nesting */
#define SYS_PI			(acos(-1))
#define DEFAULT_STRLEN		(MAXINT)
#define DEFAULT_DIMBOTTOM	(1)
#define SQASH_BUFSIZE		(32767)	/* For save/load buffer */
#define TEXT_BUFSIZE		(32767)	/* For list/enter buffer */
