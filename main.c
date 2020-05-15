#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "help_func.h"
#include "dlist.h"

// ------------------------- Прототипы функций -------------------------

enum
{
    MAIN_MENU,
    INPUT_MENU,
    EDIT_MENU,
    OUTPUT_MENU,
    INPUT_TERM_MENU,
    EDIT_INFO_MENU,
    SORT_MENU,
    DELETE_MENU
};

int get_number();
int get_year();
int get_genre();
char *get_string(unsigned char);
TRACK get_music_data();
void delete_menu(LIST **);
void edit_info_menu(LIST *);
void sort_menu(LIST *);
void input_menu(LIST *);
void edit_menu(LIST **);
void output_menu(LIST *);
void print_menu(unsigned char, unsigned char *);
void help();

int main()
{   
    LIST *musiclist = NULL;

    int variant,
        i;

    enum
    /*
        Пункты главного меню
    */
    {
        EXIT,
        HELP,
        INPUT_DATA,
        EDIT_DATA,
        PRINT_DATA,
        MENU_NUM
    };
    
    unsigned char flags[MENU_NUM];

    for (i = 0; i < MENU_NUM; i++)
        flags[i] = 1;

    print_msg(HELLO);
    do
    {
        if (is_empty(musiclist))
            flags[EDIT_DATA] = flags[PRINT_DATA] = 0;
        
        print_menu(MAIN_MENU, flags);
        scanf("%d", &variant);
        clean_stdin();

        switch (variant)
        {
            case HELP:
                help();
            break;
            case INPUT_DATA:
                if (musiclist == NULL)
                    musiclist = create_list();
                
                input_menu(musiclist);
                
                if (musiclist->head != NULL)
                    flags[EDIT_DATA] = flags[PRINT_DATA] = 1;
            break;
            case EDIT_DATA:
                if (flags[EDIT_DATA])
                    edit_menu(&musiclist);
                else
                    print_msg(MENU_ERROR);
            break;
            case PRINT_DATA:
                if (flags[PRINT_DATA])
                    output_menu(musiclist);
                else
                    print_msg(MENU_ERROR);
            break;
            case EXIT:
                flags[EXIT] = 0;
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }

    }
    while(flags[EXIT]);
    
    return 0;
}


TRACK get_music_data()
{
    TRACK music;

    system(CLEAR);
    music.artist = get_string(1);
    music.title = get_string(2);
    music.album = get_string(3);
    music.number = get_number();
    music.year = get_year();
    music.genre = get_genre();

    return music;
}


char *get_string(unsigned char type)
{
    int i, k;
    char *s = NULL;

    if (type == 1)
        printf("Enter artist of track: ");
    else if (type == 2)
        printf("Enter title of track: ");
    else if (type == 3)
        printf("Enter album: ");

    i = 0;
    s = malloc(sizeof(char));
    while(((k = getchar()) != '\n') && (i < MAXLEN))
    {
        s[i] = k;
        s = realloc(s, (1+(++i))*sizeof(char));
    }
    s[i] = '\0';

    return s;
}


int get_year()
{
    int y;

    do
    {
        printf("Enter the year of track: ");
        scanf("%d", &y);
        clean_stdin();
        if (y < 0)
            puts("\nSorry, but year should be great than 0");
        else if (y > 9999)
            puts("\nSorry, but year should be less than 10000");
    }
    while(y < 0 || y > 9999);

    return y;
}


int get_number()
{
    int n;

    do
    {
        printf("Enter number of track in album: ");
        scanf("%d", &n);
        clean_stdin();
        if (n < 0)
            puts("\nSorry, but number should be great than 0");
        else if (n > 99)
            puts("\nSorry, but number should be less than 100");
    }
    while(n < 0 || n > 99);

    return n;
}


int get_genre()
{
    int g;
    print_array(genres_array, GENRES_NUM);
    do
    {
        printf("Enter number of genre: ");
        scanf("%d", &g);
        clean_stdin();
        if (g < 0)
            puts("\nSorry, but number should be great than 0");
        else if (g > GENRES_NUM-1)
            printf("\nSorry, but number should be less than %d \n", GENRES_NUM);
    }
    while(g < 0 || g > GENRES_NUM-1);

    return g;
}


void print_menu(unsigned char menu, unsigned char *flags)
/*
    Вывод пунктов меню на экран
    ---
    @param char *flags - одномерный массив флагов, для вывода
                         только доступных пунктов меню
*/
{
    system(CLEAR);
    switch (menu)
    {
        case MAIN_MENU:
            puts("Main menu");
            if (flags[1])
                puts("1. Help");
            if (flags[2])
                puts("2. Add music list");
            if (flags[3])
                puts("3. Edit music list");
            if (flags[4])
                puts("4. Print music list");
            if (flags[0])
                puts("0. Exit");
        break;
        case INPUT_MENU:
            puts("Input menu");
            puts("1. Input from term");
            puts("2. Input from file");
            puts("0. Return to Main Menu");
        break;
        case EDIT_MENU:
            puts("Edit menu");
            puts("1. Edit track info");
            puts("2. Sort music list");
            puts("3. Reverse list");
            puts("4. Random shuffle");
            puts("5. Delete track");
            puts("0. Return to Main Menu");
        break;
        case OUTPUT_MENU:
            puts("Output menu");
            puts("1. Print all list");
            puts("2. Print one track");
            puts("3. Save list in file");
            puts("0. Return to Main Menu");
        break;
        case INPUT_TERM_MENU:
            puts("Add??");
            puts("1. Add to head");
            puts("2. Add to tail");
            puts("3. Add after n-th element");
        break;
        case EDIT_INFO_MENU:
            puts("Edit info menu");
            puts("1. Edit artist");
            puts("2. Edit title");
            puts("3. Edit album");
            puts("4. Edit number in album");
            puts("5. Edit year");
            puts("0. Return to Edit Menu");
        break;
        case SORT_MENU:
            puts("Sort menu");
            puts("1. Sort by artists");
            puts("2. Sort by title");
            puts("3. Sort by album");
            puts("4. Sort by number in album");
            puts("5. Sort by year");
            puts("0. Return to Edit Menu");
        break;
        case DELETE_MENU:
            puts("Delete menu");
            puts("1. Delete track by number");
            puts("2. Delete all music list");
            puts("0. Return to Edit Menu");
        break;
    }
    printf(">");
}


void input_menu(LIST *list)
{
    unsigned variant,
        exit_flag;
    char answer;
    char *path = NULL;

    exit_flag = 1;
    do
    {

        print_menu(INPUT_MENU, NULL);
        scanf("%d", &variant);
        clean_stdin();
        switch (variant)
        {
            case 1:
                do
                {
                    do
                    {
                        print_menu(INPUT_TERM_MENU, NULL);
                        scanf("%d", &variant);
                        clean_stdin();
                    }
                    while (variant < 1 || variant > 3);
                    if (variant == 1)
                        push(list, get_music_data());
                    else if (variant == 2)
                        append(list, get_music_data());
                    else
                    {
                        system(CLEAR);
                        puts("Enter index");
                        printf(">");
                        scanf("%d", &variant);
                        clean_stdin();
                        insert(list, get_music_data(), variant);
                    }
                    puts("\nDo you want to continue? (y/n)");
                    printf(">");
                    scanf("%c", &answer);
                    clean_stdin();
                }
                while(answer == 'y' || answer == 'Y');
            break;
            case 2:
                system(CLEAR);
                puts("Input filename");
                printf(">");
                path = get_string(0);
                get_list(list, path, ';');
                if (list->head != NULL)
                    print_list(list);
                free(path);
                path = NULL;
            break;
            case 0:
                exit_flag = 0;
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }

    }
    while(exit_flag);
}

void output_menu(LIST *list)
{
    int variant,
        exit_flag,
        n, len;
    char *path;
    
    exit_flag = 1;
    do
    {
        print_menu(OUTPUT_MENU, NULL);

        scanf("%d", &variant);
        clean_stdin();
        switch (variant)
        {
            case 1:
                print_list(list);
            break;
            case 2:
                system(CLEAR);
                len = length(list);
                do
                {
                    puts("Input number of list element");
                    printf("Length of you list is: %d\n", len);
                    printf(">");
                    scanf("%d", &n);
                    clean_stdin();
                    if (n > len)
                        puts("Number can't be greater than length");
                }
                while(n > len);
                print_list_element(get(list, n-1));
            break;
            case 3:
                system(CLEAR);
                puts("Input filename");
                printf(">");
                path = get_string(0);
                save_list(list, path);
                free(path);
                path = NULL;
            break;
            case 0:
                exit_flag = 0;
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }

    }
    while(exit_flag);
}


void edit_menu(LIST **list)
{
    int variant,
        exit_flag;

    exit_flag = 1;
    do
    {
        print_menu(EDIT_MENU, NULL);

        scanf("%d", &variant);
        clean_stdin();
        switch (variant)
        {
            case 1:
                edit_info_menu(*list);
            break;
            case 2:
                sort_menu(*list);
            break;
            case 3:
                reverse(*list);
                print_list(*list);
            break;
            case 4:
                shuffle(*list);
                print_list(*list);
            break;
            case 5:
                delete_menu(list);
                
                if (is_empty(*list))
                    exit_flag = 0;
            break;
            case 0:
                exit_flag = 0;
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }

    }
    while(exit_flag);
}

void edit_info_menu(LIST *list)
{
    print_list(list);
    puts("change me!");
}

void sort_menu(LIST *list)
{
    unsigned type;
    
    do 
    {
        print_menu(SORT_MENU, NULL);
        scanf("%u", &type);
        clean_stdin();
    
        if (type != 0)
        {
            sort(list, type);
            print_list(list);
            type = 0;
        }
    }
    while (type != 0);
}

void delete_menu(LIST **list)
{
    unsigned number;
    
    int variant,
        exit_flag;

    exit_flag = 1;
    do
    {
        
        print_menu(DELETE_MENU, NULL);

        scanf("%d", &variant);
        clean_stdin();
        switch (variant)
        {
            case 1:
                scanf("%u", &number);
                clean_stdin();
                pop(*list, number);
                if (is_empty(*list))
                    exit_flag = 0;
            break;
            case 2:
                delete_list(list);
                print_msg("List of music was successfully delete");
                exit_flag = 0;
            break;
            case 0:
                exit_flag = 0;
            break;
            default:
                print_msg(MENU_ERROR);
            break;
        }

    }
    while(exit_flag);
}

void help()
{
    system(CLEAR);
    puts("change me!");
    pause();
}

