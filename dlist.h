/*
    Библиотека для работы с двусвязным списком.

    ---
    Доступные операции:
    create_list - Создание двусвязного списка
    push - Добавление элемента в начало списка
    pop - Удаление элемента списка
    append - Добаление в конец списка
    pop_back - Удаление из конца списка
    lenght - Длина списка
    get - Получение элемента списка
    delete_list - Удаление списка
*/

#ifndef DLIST_H
#define DLIST_H

// ------------------------- Структуры -------------------------

struct list_info
/*
    Информационная структура списка
*/
{
    char *artist;
    char *title;
    char *album;
    int genre;
    int year;
    int number;
};

struct list_node
/*
    Структура узла списка
*/
{
    struct list_info data;
    struct list_node *next;
    struct list_node *previous;
};

struct list
/*
    Структура списка
*/
{
    int size;
    struct list_node *head;
    struct list_node *tail;
};

typedef struct list LIST;
typedef struct list_node NODE;
typedef struct list_info TRACK;

// ------------------------- Прототипы функций для списка -------------------------

LIST *create_list();
void memory_clear(TRACK *t);
void delete_list(LIST **);
void soft_delete_list(LIST **);
void push(LIST* list, TRACK data);
void append(LIST *, TRACK);
NODE *get(LIST *, unsigned);
void pop(LIST *, unsigned);
void swap(LIST *, unsigned, unsigned);
char compare(NODE *, NODE *, unsigned);
void sort(LIST *, unsigned);

int length(LIST *);
void print_list(LIST *);
void print_list_element(NODE *);

#endif
