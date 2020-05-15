#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "help_func.h"
#include "dlist.h"

// ------------------------- Прототипы функций -------------------------

int get_number();
int get_year();
int get_genre();
char *get_string(unsigned char);

TRACK fill_node(char **);
void clear_str_array(char **, int);
char **simple_split(char *, int, char);
TRACK get_music_data();
void get_database(LIST*, char*, char);

void delete_menu(LIST *);
void edit_info_menu(LIST *);
void sort_menu(LIST *);
void input_menu(LIST *);
void edit_menu(LIST *);
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
        flags[i] = 0;

    flags[EXIT] = 1;

    print_msg(HELLO);
    do
    {

        print_menu(0, flags);
        scanf("%d", &variant);
        clean_stdin();

        switch (variant)
        {
            case HELP:
                help();
            break;
            case INPUT_DATA:
                input_menu(musiclist);
            break;
            case EDIT_DATA:
                edit_menu(musiclist);
            break;
            case PRINT_DATA:
                output_menu(musiclist);
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

    delete_list(&musiclist);
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


void get_database(LIST *list, char* filename, char separator)
{
    int slen,
        flag=1;
    char s1[MAXSTR];
    char **s2 = NULL;
    FILE *df;

    df = fopen(filename, "r");
    if(df != NULL)
    {
        while(fgets(s1,MAXSTR,df) != NULL && flag)
        {
            slen = strlen(s1);
            s1[slen-1] = '\0';
            slen = slen - 1;

            s2 = simple_split(s1,slen,separator);
            if(s2 != NULL)
            {
                push(list, fill_node(s2));
                clear_str_array(s2,6);
                free(s2);
            }
            else
            {
                flag=0;
                puts("Row data not available!");
            }
        }
        fclose(df);
    }
    else
        print_msg(FILE_ERROR);

}


TRACK fill_node(char **s2)
{
    TRACK p;
    int len1, len2, len3;

    len1=strlen(s2[0]);
    len2=strlen(s2[1]);
    len3=strlen(s2[2]);

    p.artist = malloc((len1+1)*sizeof(char));
    p.title = malloc((len2+1)*sizeof(char));
    p.album = malloc((len3+1)*sizeof(char));

    if((p.artist!=NULL)&&(p.title!=NULL)&&(p.album!=NULL))
    {
        strcpy(p.artist, s2[0]);
        strcpy(p.title, s2[1]);
        strcpy(p.album, s2[2]);
        p.number = strtol(s2[3], NULL, 10);
        p.year = strtol(s2[4], NULL, 10);
        p.genre = strtol(s2[5], NULL, 10);
    }
    else
        puts("Out of memory! Program terminated");

    return p;
}


char **simple_split(char *str, int length, char sep)
{
    char **str_array = NULL;
    int i,j,k,m,key,count;
    for(j=0, m=0; j < length; j++)
        if(str[j]==sep) m++;

    key=0;
    str_array = malloc((m+1)*sizeof(char*));
    if(str_array != NULL)
    {
        for(i=0,count=0;i<=m;i++,count++)
        {
            str_array[i] = NULL;
            str_array[i] = malloc(length*sizeof(char));
            if(str_array[i]!=NULL)
                key=1;
            else
            {
                key=0;
                i=m;
            }
        }
        if(key)
        {
            k=0;
            m=0;
            for(j=0;j<length;j++)
            {
                if(str[j]!=sep)
                    str_array[m][j-k] = str[j];
                else
                {
                    str_array[m][j-k] = '\0';
                    k = j+1;
                    m++;
                }
            }
        }
        else
        {
            clear_str_array(str_array, count);
            free(str_array);
        }
     }
     return str_array;
}


void clear_str_array(char **str, int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        free(str[i]);
        str[i]=NULL;
    }
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
    if (menu == 0)
    {
        puts("Main menu");
        if (flags[1])
            puts("1. Help");
        if (flags[2])
            puts("2. Add music list");
        if (flags[3])
            puts("3. Edit music list");
        if (flags[5])
            puts("4. Print music list");
        if (flags[0])
            puts("0. Exit");
    }
    printf(">");
}


void input_menu(LIST *list)
{
    int variant,
        exit_flag;
    char answer;
    char *path = NULL;

    exit_flag = 1;
    do
    {

        system(CLEAR);
        puts("Input menu");
        puts("1. Input from term");
        puts("2. Input from file");
        puts("0. Return to Main Menu");
        printf(">");

        scanf("%d", &variant);
        clean_stdin();
        switch (variant)
        {
            case 1:
                do
                {
                    push(list, get_music_data());
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
                get_database(list, path, ';');
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

    exit_flag = 1;
    do
    {

        system(CLEAR);
        puts("Output menu");
        puts("1. Print all list");
        puts("2. Print one track");
        puts("0. Return to Output Menu");
        printf(">");

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


void edit_menu(LIST *list)
{
    int variant,
        exit_flag;

    exit_flag = 1;
    do
    {

        system(CLEAR);
        puts("Edit menu");
        puts("1. Edit track info");
        puts("2. Sort music list");
        puts("3. Delete track");
        puts("0. Return to Main Menu");
        printf(">");

        scanf("%d", &variant);
        clean_stdin();
        switch (variant)
        {
            case 1:
                edit_info_menu(list);
            break;
            case 2:
                sort_menu(list);
            break;
            case 3:
                delete_menu(list);
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

    system(CLEAR);
    puts("Sort menu");
    printf(">");
    scanf("%u", &type);
    clean_stdin();
    if (type != 0)
        sort(list, type);
}

void delete_menu(LIST *list)
{
    unsigned number;
    system(CLEAR);
    puts("Delete menu");
    printf(">");
    scanf("%u", &number);
    clean_stdin();
    pop(list, number);
}

void help()
{
    system("CLEAR");
    puts("change me!");
    pause();
}

