/*
 * OpenComal -- a free Comal implementation
 *
 * This file is part of the OpenComal package.
 * (c) Copyright 1992-2002 Jos Visser <josv@osp.nl>
 *
 * The OpenComal package is covered by the GNU General Public
 * License. See doc/LICENSE for more information.
 */

/* Main file of OpenComal */

#define EXTERN

#include "pdcglob.h"
#include "pdcenv.h"
#include "pdccloop.h"
#include "pdcexp.h"
#include "pdcmisc.h"
#include "version.h"

#include <string.h>

extern int yydebug;

#ifdef TURBOC
unsigned _stklen = 32768;
#endif

PUBLIC int main(int argc, char *argv[])
{
	sys_init();
	copyright = "(c) Copyright 1992-2002  Jos Visser <josv@osp.nl>";

#if defined(OS_WIN32) || defined(OS_MSDOS)
	my_printf(MSG_DIALOG, 1,
		  "OpenComal -- A free Comal implementation (version %s; %s)",
		  OPENCOMAL_VERSION,HOST_OS);
#else
	my_printf(MSG_DIALOG, 1,
		  "OpenComal -- A free Comal implementation (version %s; %s; build %s)",
		  OPENCOMAL_VERSION,HOST_OS,OPENCOMAL_BUILD);
#endif

	my_printf(MSG_DIALOG, 1, "             %s", copyright);
	my_printf(MSG_DIALOG, 1, "             Built on %s at approximately %s", __DATE__, __TIME__);
	my_nl(MSG_DIALOG);
	my_printf(MSG_DIALOG, 1,"OpenComal is licensed under the GNU General Public License (GPL) version 2");
	my_printf(MSG_DIALOG, 1,"(The GPL contains a very nice statement on WARRANTY; you might want to read it)");
	my_nl(MSG_DIALOG);

	comal_debug = (argc == 2 && strcmp(argv[1], "/d") == 0);
	yydebug = (argc == 2 && strcmp(argv[1], "/y") == 0);

	mem_init();

	runfilename = NULL;
	curenv = env_new("nirvana");
	entering = 0;
	sel_infile = NULL;
	sel_outfile = NULL;

	pdc_go(argc, argv);

	if (setjmp(RESTART) == 0) {
		if (sel_infile)
			if (fclose(sel_infile))
				perror
				    ("Error when closing SELECT INPUT file");

		if (sel_outfile)
			if (fclose(sel_outfile))
				perror
				    ("Error when closing SELECT OUTPUT file");

		clear_env(curenv);
		mem_tini();
	}

	sys_tini();

	return 0;
}
