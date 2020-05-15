#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"
#include "constants.h"
#include "help_func.h"

LIST *create_list()
/**
 *   @brief Создание двусвязного списка
 */
{
    LIST *temp = NULL;

    temp = malloc(sizeof(LIST));

    if (temp != NULL)
    {
        temp->size = 0;
        temp->head = NULL;
        temp->tail = NULL;
    }
    return temp;
}

void delete_list(LIST **list)
/**
 *    @brief Удаление двусвязного списка
 */
{
    NODE *temp_node = NULL;
    NODE *previous = NULL;

    if (*list != NULL)
    {
        temp_node = (*list)->head;
        while (temp_node)
        {
            previous = temp_node;
            memory_clear(&(previous->data));
            temp_node = temp_node->next;
            free(previous);
        }
        free(*list);
        (*list) = NULL;
    }
}

void soft_delete_list(LIST **list)
/*
    @brief Удаление двусвязного списка
*/
{
    NODE *temp_node = NULL;
    NODE *previous = NULL;

    if (*list != NULL)
    {
        temp_node = (*list)->head;
        while (temp_node)
        {
            previous = temp_node;
            temp_node = temp_node->next;
            free(previous);
        }
        free(*list);
        (*list) = NULL;
    }
}

void push(LIST *list, TRACK data)
/*
    @brief Добаление нового элемента в начало списка. Сложность O(1)
    ---
    @param LIST *list - указатель на список
    @param TRACK data - данные нового элемента
*/
{
    NODE *new_node = NULL;

    new_node = malloc(sizeof(NODE));
    if (new_node != NULL)
    {
        new_node->data = data;
        new_node->next = list->head;
        new_node->previous = NULL;
        if (list->head)
            list->head->previous = new_node;
        list->head = new_node;

        if (list->tail == NULL)
            list->tail = new_node;

        list->size++;
    }
}


void pop(LIST *list, unsigned index)
/**
 *  @brief Удаление элемента из списка. Сложность O(n)
 *  ---
 *  @param LIST *list - список.
 *  @param unsigned index - номер элемента
*/
{
    NODE *node = NULL;
    node = get(list, index);
    if (node != NULL) 
    {
        if (node->previous) 
            node->previous->next = node->next;
        
        if (node->next)
            node->next->previous = node->previous;

        memory_clear(&node->data);
    
        if (!node->previous)
            list->head = node->next;
    
        if (!node->next) {
            list->tail = node->previous;
        }
    
        free(node);
        
        list->size--;
    }
}

void append(LIST *list, TRACK data)
/*
    @brief Добавление нового элемента в конец списка. Сложность O(1)
    ---
    @param LIST *list - указетель на список.
    @param TRACK data - данные нового элемента.
*/
{
    NODE *new_node = NULL;

    new_node = malloc(sizeof(NODE));

    if (new_node != NULL)
    {
        new_node->data = data;
        new_node->next = NULL;
        new_node->previous = list->tail;
        if (list->tail)
            list->tail->next = new_node;
        list->tail = new_node;

        if (list->head == NULL)
            list->head = new_node;
        list->size++;
    }
}


NODE *get(LIST *list, unsigned index)
/*
    @brief Получение элемента списка. Сложность O(n/2) = O(n).
    ---
    @param LIST *list - указатель на список
    @param unsigned index - позиция элемента
    @return NODE - нужный элемент списка
*/
{
    NODE *temp_node = NULL;
    int i;

    // если элемент в первой половине списка,
    // то идем с начала списка
    if (index < list->size/2)
        for (i = 0, temp_node = list->head;
            temp_node && i < index;
            temp_node = temp_node->next, i++);
    else
    // если элемент во второй половине списка,
    // то идем с конца списка
        for (i = list->size - 1, temp_node = list->tail;
             temp_node && i > index;
             temp_node = temp_node->previous, i--);

    return temp_node;
}


void swap(LIST *list, unsigned pos1, unsigned pos2)
/**
 *  @brief Поменять местами два элемента. Сложность O(n)
 *  ---
 *  @param LIST *list - указатель на список
 *  @param unsigned pos1 - позиция первого элемента
 *  @param unsigned pos2 - позиция второго элемента
 */
{
    TRACK tmp;
    NODE *first = NULL,
         *last = NULL;

    first = list->head;
    last = list->head;
    while(pos1--)
        first = first->next;

    if(first == NULL)
        return;

    while(pos2--)
        last = last->next;

    if(last == NULL)
        return;

    tmp = first->data;
    first->data = last->data;
    last->data = tmp;
}


void sort(LIST *head, unsigned type)
/**
 *  @brief Сортировка элементов списка методом пузырька
 *  ---
 *  @param NODE *head - голова списка
 *  @param unsigned type - тип сортируемого значения
 *  @return NODE - отсортированный список
 */
{
    int i, j, n;

    n = length(head);
    for (i = n - 1; i > 0; i--)
        for (j = 0; j < i; j++)
            if (compare(get(head, j), get(head, j+1), type))
                swap(head, j, j+1);
}


char compare(NODE *first, NODE *second, unsigned type)
{
    char res;

    if ((type == 1 && strcmp((first->data).artist, (second->data).artist) > 0)
        ||(type == 2 && strcmp((first->data).title, (second->data).title) > 0)
        ||(type == 3 && strcmp((first->data).album, (second->data).album) > 0)
        ||(type == 4 && (first->data).number > (second->data).number)
        ||(type == 5 && (first->data).year > (second->data).year)
        )
        res = 1;
    else
        res = 0;

    return res;
}

int length(LIST *list)
/*
    @brief Получение длины списка. Сложность O(1)
    ---
    @param LIST *list - указатель на список
    @return int - длина списка
*/
{
    return list->size;
}

void print_list(LIST *list)
/*
    @brief Вывод списка в виде таблицы
    ---
    @param LIST *list - указатель на список
*/
{
    unsigned count;
    NODE *temp_node = NULL;

    system(CLEAR);
    print_header();

    temp_node = list->head;
    count = 1;
    while(temp_node)
    {
        printf("|%6d |%21s |%21s |%21s |%7d |%5d |%10s |\n",
            count, (temp_node->data).artist,
            (temp_node->data).title, (temp_node->data).album,
            (temp_node->data).number,(temp_node->data).year,
            genres_array[(temp_node->data).genre]);

        temp_node = temp_node->next;
        count++;
    }
    pause();
}


void print_list_element(NODE *node)
/**
 *  @brief Вывод элемента списка в виде таблицы
 *  ---
 *  @param LIST *list - указатель на список
 */
{
    system(CLEAR);
    print_header();

    printf("|%6d |%21s |%21s |%21s |%7d |%5d |%10s |\n",
        1, (node->data).artist, (node->data).title, (node->data).album,
        (node->data).number,(node->data).year, genres_array[(node->data).genre]);

    pause();
}


void memory_clear(TRACK *t)
/**
 *  @brief Освобождение памяти из-под полей структуры
 *  ---
 *  @param TRACK t - структура, у которой очищаются поля
 */
{
    if(t->artist != NULL)
        free(t->artist);
    if(t->title != NULL)
        free(t->title);
    if(t->album != NULL)
        free(t->album);

    t->artist = NULL;
    t->title = NULL;
    t->album = NULL;
}
