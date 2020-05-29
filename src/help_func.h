#ifndef HELP_FUNC_H
#define HELP_FUNC_H

void print_array(const char * const *, unsigned);
void clean_stdin();
void pause();
void print_msg(char *);
void print_header();
void clear_str_array(char **, int);
char *get_string(unsigned char);
int get_number();
int get_genre();
int get_year();
char save_scanf(int*);

#endif
