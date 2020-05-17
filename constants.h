/*
    Контанты проекта
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

// константа очистки консоли
#ifdef __linux__
    #define CLEAR "clear"
#else
    #define CLEAR "cls"
#endif

// ------------------------- Константы-Ошибки -------------------------
#define HELLO "Hello, user.\nThis program will help you create your music library."
#define MENU_ERROR "Sorry, but there is no such menu item.\nTry to select another item."
#define FILE_ERROR "Sorry, error of file reading. Try another file."
#define FILE_SUCCESS "Successful file writing!"
#define LIST_DELETE "List of music was successfully delete"
#define SEARCH_ERROR "Sorry, but there are no elements that satisfy these conditions"

// ------------------------- Прочие контанты -------------------------
#define GENRES_NUM 7 // Количество жанров музыки
#define SORT_NUM 6 // Количество видов сортировки музыки
#define MAXLEN 21 // Максимальная длина строки (+ нуль-терминатор)
#define MAXSTR 150 // Максимальная строка файла

extern const char * const genres_array[GENRES_NUM];

#endif
