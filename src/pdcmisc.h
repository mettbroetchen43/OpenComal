/*
 * OpenComal -- a free Comal implementation
 *
 * This file is part of the OpenComal package.
 * (c) Copyright 1992-2002 Jos Visser <josv@osp.nl>
 *
 * The OpenComal package is covered by the GNU General Public
 * License. See doc/LICENSE for more information.
 */

/* Misc routines header file */

extern void my_nl(int stream);
extern void my_put(int stream, char *buf, long len);
extern void my_printf(int stream, int newline, char *s, ...);
extern void fatal(char *s, ...);
extern void *my_reverse(void *root);
extern void free_list(struct my_list *root);
extern int exp_list_of_nums(struct exp_list *root);
extern int check_changed(void);
extern int check_changed_any(void);
extern void puts_line(int stream, struct comal_line *line);
extern int nr_items(struct my_list *list);
extern long d2int(double x, int whole);
extern int type_match1(struct id_rec *id, struct expression *exp);
extern struct id_rec *exp_of_id(struct expression *exp);
extern struct id_rec *exp_of_array(struct expression *exp);
extern int exp_of_string(struct expression *exp);
extern char *exp_cmd(struct expression *exp);
extern long my_write(int h, void *data, long size);
extern long my_read(int h, void *data, long size);
extern struct comal_line *search_line(long l, int exact);
extern int stat_size(int cmd);
extern void give_run_err(struct comal_line *line);
extern int type_size(int t);
extern void data_dump(char *data, int nr, char *title);
extern void check_lval(struct expression *exp);
extern int clean_string_lval(struct expression *exp);
extern int proclevel(struct comal_line *proc);
extern struct comal_line *line_2line(struct comal_line *line);
extern int line_2cmd(struct comal_line *line);
extern struct comal_line *stat_dup(struct comal_line *stat);
extern void trace_add(int *val, char *name);
extern void trace_remove(void);
extern void trace_trace(void);
extern void trace_reset(void);
extern char *ltoa(long num, char *buf, int len);

#ifndef HAS_STRLWR
extern void strupr(char *s);
extern void strlwr(char *s);
#endif

extern void remove_trailing(char *s, char *trailing, char *subst);
extern double my_round(double x);
extern double my_frac(double x);
