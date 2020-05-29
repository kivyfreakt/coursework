#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

void clean_stdin()
/**
 * @brief Замена функции очистки входного потока (fflush)
 */
{
    char c;
    while ( scanf("%c", &c) == 1 && c != '\n');
}

void print_array(const char * const array[], unsigned len)
/**
 * @brief Вывод массива
 */
{
    int i;

    for (i = 0; i < len; i++)
        printf("%d. %s \n", i, array[i]);
}


void clear_str_array(char **str, int n)
/**
 * @brief Очистка памяти
 */
{
    int i;
    for(i = 0;i < n;i++)
    {
        free(str[i]);
        str[i]=NULL;
    }
}

void pause()
/**
 * @brief Замена системного ожидания
 */
{
    puts("\nPress Enter to continue");
    getchar();
}

void print_msg(char *information)
/**
 * @brief Вывод на экран информации об ошибке/о вспомогательной информации
 * ---
 * @param char *information - текст информации/ошибки
 */
{
    system(CLEAR);
    puts(information);
    pause();
}

void print_header()
/**
 *  @brief Вывод шапки таблицы
 */
{
    puts("");
    printf("|%6s |%21s |%21s |%21s |%7s |%5s |%10s |\n", "#", "artist", "title", "album", "number", "year", "genre");
    printf("+-------+----------------------+----------------------+----------------------+--------+------+-----------+\n");
}

char *get_string(unsigned char type)
/**
 *  @brief Получение строки из терминала
 */
{
    int i, k;
    char *s = NULL;

    if (type == 1)
        printf("Enter artist of track (max string length: %d): ", MAXLEN);
    else if (type == 2)
        printf("Enter title of track (max string length: %d): ", MAXLEN);
    else if (type == 3)
        printf("Enter album (max string length: %d): ", MAXLEN);

    i = 0;
    s = malloc(sizeof(char));
    while(((k = getchar()) != '\n') && (i < MAXLEN))
    {
        s[i] = k;
        s = realloc(s, (1+(++i))*sizeof(char));
    }
    s[i] = '\0';
    
    if (i == MAXLEN)
        clean_stdin();
    return s;
}


int get_year()
/**
 *  @brief Получение года из терминала
 */
{
    int y;
    int good;
    
    good = 1;
    do
    {
        printf("Enter the year of track [1,3000]: ");
        good = scanf("%d", &y);
        clean_stdin();
        if (good != 1)
            puts(INPUT_ERROR);
        else if (y < 0)
            puts("\nSorry, but year should be great than 0");
        else if (y > 3000)
            puts("\nSorry, but year should be less than 3000");
    }
    while(good != 1 || y < 0 || y > 3000);

    return y;
}


int get_number()
/**
 *  @brief Получение номера из терминала
 */
{
    int n;
    int good;
    
    good = 1;
    do
    {
        printf("Enter number of track in album [1, 100]: ");
        good = scanf("%d", &n);
        clean_stdin();
        if (good != 1)
            puts(INPUT_ERROR);
        else if (n < 0)
            puts("\nSorry, but number should be great than 0");
        else if (n > 100)
            puts("\nSorry, but number should be less than 101");
    }
    while(good != 1 || n < 0 || n > 99);

    return n;
}


int get_genre()
/**
 *  @brief Получение номера жанра из терминала
 */
{
    int g;
    int good;
    
    good = 1;
    do
    {
        print_array(genres_array, GENRES_NUM);
        printf("Enter number of genre [0, %d]: ", GENRES_NUM-1);
        good = scanf("%d", &g);
        clean_stdin();
        if (good != 1)
            puts(INPUT_ERROR);
        else if (g < 0)
            puts("\nSorry, but number should be great than 0");
        else if (g > GENRES_NUM-1)
            printf("\nSorry, but number should be less than %d \n", GENRES_NUM);
    }
    while(good!= 1 || g < 0 || g > GENRES_NUM-1);

    return g;
}


void save_scanf(int* number)
{
    char good;
    do
    {
        good = scanf("%d", number);
        if (good != 1)
            puts(INPUT_ERROR);
        clean_stdin();
    }
    while(good != 1);
}
