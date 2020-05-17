/*
    Библиотека для работы с двусвязным списком.
    
    ---
    Доступные операции:
    push - добавление в начало
    append - добавление в конец
    get - получение произвольного элемента
    insert - вставка в произвольную позицию
    pop - удаление элемента из произвольной позиции
    length - длина списка
    is_empty - проверка на пустоту списка
    swap - поменять местами два элемента
    sort - сортирока
    reverse - разворот
    shuffle - рандомное перемешивание
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
void push(LIST* list, TRACK data);
void append(LIST *, TRACK);
NODE *get(LIST *, unsigned);
void insert(LIST *, TRACK, unsigned);
void pop(LIST *, unsigned);
void swap(LIST *, unsigned, unsigned);
char compare(NODE *, NODE *, unsigned);
void sort(LIST *, unsigned);
LIST *search(LIST*, TRACK);
void reverse (LIST *);
void shuffle (LIST *);
int length(LIST *);
char is_empty(LIST *);
void print_list(LIST *);
void print_list_element(NODE *);
void save_list(LIST *, char *);
TRACK fill_node(char **);
char **simple_split(char *, int, char);
void get_list(LIST*, char*, char);

#endif
