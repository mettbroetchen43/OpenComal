/*
 * OpenComal -- a free Comal implementation
 *
 * This file is part of the OpenComal package.
 * (c) Copyright 1992-2002 Jos Visser <josv@osp.nl>
 *
 * The OpenComal package is covered by the GNU General Public
 * License. See doc/LICENSE for more information.
 */

/* OpenComal Routines for external OpenComal modules */

#include "pdcglob.h"
#include "pdcmisc.h"
#include "pdclexs.h"
#include "pdcid.h"
#include "pdcseg.h"
#include "pdcexec.h"


/*
 * The root of the loaded module table
 */
PRIVATE struct mod_entry *mod_root;

/*
 * The root of the exported routine table
 */
PRIVATE struct mod_func_entry *mod_func_root;

/*
 * Find a PROC or FUNC in a module
 */
struct comal_line *find_func(struct comal_line *module, struct id_rec *fun)
{
	struct comal_line *walk;

	for (walk=module->lc.pfrec.localproc; walk; walk=walk->lc.pfrec.proclink)
		if (id_eql(walk->lc.pfrec.id,fun))
			return walk;

	return NULL;
}

/*
 * Register an OpenComal module
 */
PRIVATE int mod_register(struct comal_line *line, struct seg_des *seg, char *errtext, struct comal_line **errline)
{
	struct comal_line *walk;
	struct mod_entry *work=GETCORE(RUN_POOL,struct mod_entry);
	struct id_list *idwalk;
	struct comal_line *fun;
	struct mod_func_entry *modfun;

	work->next=mod_root;
	mod_root=work;
	work->id=line->lc.pfrec.id;
	work->line=line;

	if (comal_debug)
		my_printf(MSG_DEBUG,1,"Registering MODULE %s",line->lc.pfrec.id->name);

	/*
	 * Find all the exports in this MODULE and register them
	 */
	for (walk=line; walk->cmd!=endmoduleSYM; walk=walk->ld->next)
		if (walk->cmd==exportSYM)
			for (idwalk=walk->lc.idroot; idwalk; idwalk=idwalk->next) {
				fun=find_func(line,idwalk->id);

				if (!fun) {
					sprintf(errtext,"Can not find PROC/FUNC %s in MODULE %s",
						idwalk->id->name,line->lc.pfrec.id->name);
					*errline=walk;
					return 0;
				}

				if (comal_debug)
					my_printf(MSG_DEBUG,1,"  Exporting %s",fun->lc.pfrec.id->name);

				modfun=GETCORE(RUN_POOL,struct mod_func_entry);
				modfun->next=mod_func_root;
				mod_func_root=modfun;
				modfun->id=idwalk->id;
				modfun->line=fun;
				modfun->module=work;
			}

	return 1;
}

/*
 * Find an OpenComal module
 */
struct mod_entry *mod_find(struct id_rec *id)
{
	struct mod_entry *walk=mod_root;

	while (walk) {
		if (id_eql(walk->id,id))
			return walk;

		walk=walk->next;
	}

	return NULL;
}

/*
 * Find an OpenComal module in a Comal segment
 * Please note the absolutely confusing name of this function :-)
 */
PUBLIC struct comal_line *mod_find_def(struct seg_des *seg, struct id_rec *id)
{
	struct comal_line *walk;

	FOR_EACH_LINE(seg,walk)
		if (walk->cmd==moduleSYM && id_eql(walk->lc.pfrec.id,id))
			return walk;

	return NULL;
}

PRIVATE struct seg_des *mod_load(struct id_rec *id) 
{
	return NULL;
}

/*
 * USE a module
 */
PUBLIC int mod_use(struct seg_des *seg, struct id_rec *id, char *errtxt, struct comal_line **errline)
{
	struct comal_line *defline;
	struct seg_des *modseg=seg;

	/*
	 * If this module has already been 
	 * defined, there is nothing more we need to do
	 */
	if (mod_find(id)) return 1;
        
	/*
	 * Try to find the module inside this segment
	 */
	defline=mod_find_def(seg,id);
                                
	if (!defline) {
		modseg=mod_load(id);

		if (!modseg) {
			sprintf(errtxt,"Module %s can not be found",id->name);
			return 0;
		}
	}

	return mod_register(defline,modseg,errtxt,errline);
}

/*
 * Free the entire environment of loaded OpenComal modules
 */
PUBLIC void mod_freeall()
{
	free_list((struct my_list *)mod_func_root);
	free_list((struct my_list *)mod_root);
	mod_func_root=NULL;
	mod_root=NULL;
}

/*
 * Search a PROC or FUNC in the table of exported routines
 */
PUBLIC struct comal_line *mod_search_routine(struct id_rec *id, int type)
{
	struct mod_func_entry *walk=mod_func_root;

	while (walk) {
		if (id_eql(walk->id,id) && walk->line->cmd==type)
			return walk->line;

		walk=walk->next;
	}

	return NULL;
}

/*
 * Initialize all registered modules
 */
PUBLIC void mod_initall()
{
	struct mod_entry *walk=mod_root;

	while (walk) {
		exec_mod_init(walk->line);
		walk=walk->next;
	}
}
