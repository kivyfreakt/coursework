#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "help_func.h"
#include "dlist.h"

enum
{
    MAIN_MENU,
    INPUT_MENU,
    EDIT_MENU,
    SEARCH_MENU,
    OUTPUT_MENU,
    INPUT_TERM_MENU,
    EDIT_INFO_MENU,
    SORT_MENU1,
    SORT_MENU2,
    DELETE_MENU
};


int get_number();
int get_year();
int get_genre();
char *get_string(unsigned char);
TRACK get_music_data();
void delete_menu(LIST **);
void edit_info_menu(LIST *);
void search_menu(LIST *);
void sort_menu(LIST *);
void input_menu(LIST *);
void edit_menu(LIST **);
void output_menu(LIST *);
void print_menu(unsigned char, unsigned char *);
void help();

#endif
