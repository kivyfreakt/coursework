#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

void clean_stdin()
/**
 * @brief Замена функции очистки входного потока (fflush)
 */
{
    int c;
    do
    {
        c = getchar();
    }
    while (c != '\n' && c != EOF);
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
