#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
/**
 *  @brief Удаление двусвязного списка
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
/**
 *  @brief Добаление нового элемента в начало списка. Сложность O(1)
 *  ---
 *  @param LIST *list - указатель на список
 *  @param TRACK data - данные нового элемента
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

        memory_clear(&(node->data));
    
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
/**
 *  @brief Добавление нового элемента в конец списка. Сложность O(1)
 *  ---
 *  @param LIST *list - указетель на список.
 *  @param TRACK data - данные нового элемента.
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


void insert(LIST *list, TRACK data, unsigned index)
/**
 *  @brief Добавление нового элемента после определенного элемента списка. Сложность O(n)
 *  ---
 *  @param LIST *list - указетель на список
 *  @param TRACK data - данные нового элемента
 *  @param unsigned index - позиция элемента
 */
{
    NODE *elm = NULL;
    NODE *new_node = NULL;
    elm = get(list, index);
    if (elm != NULL) 
    {
        new_node = malloc(sizeof(NODE));
        new_node->data = data;
        new_node->previous = elm;
        new_node->next = elm->next;
        
        if (elm->next) 
            elm->next->previous = new_node;

        elm->next = new_node;
    
        if (elm->previous == NULL)
            list->head = elm;
        
        if (elm->next == NULL)
            list->tail = elm;

        list->size++;
    }
}   


NODE *get(LIST *list, unsigned index)
/**
 *  @brief Получение элемента списка. Сложность O(n/2) = O(n).
 *  ---
 *  @param LIST *list - указатель на список
 *  @param unsigned index - позиция элемента
 *  @return NODE - нужный элемент списка
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


LIST *search(LIST *list, TRACK search_param, char(*compare)(TRACK, TRACK))
/**
 *  @brief Поиск по элементам списка
 *  ---
 *  @param LIST *list - список
 *  @param TRACK search_param - параметры поиска по списку
 *  @param сhar*()(TRACK, TRACK) - указатель на функцию сравнения
 *  @return LIST* - список
 */
{
    LIST* search_result = NULL;
    NODE* temp_node = NULL;
    
    search_result = create_list();
    if (search_result != NULL)
        for (temp_node = list->head; temp_node; temp_node = temp_node->next)
            if (compare(temp_node->data, search_param))
                append(search_result, temp_node->data);
    
    return search_result;
}


void sort(LIST *head, unsigned type)
/**
 *  @brief Сортировка элементов списка методом пузырька
 *  ---
 *  @param LIST *list - список
 *  @param unsigned type - тип сортируемого значения
 *  @return NODE - отсортированный список
 */
{
    int i, j, n;

    n = length(head);
    for (i = n - 1; i > 0; i--)
        for (j = 0; j < i; j++)
            if (sort_compare(get(head, j), get(head, j+1), type))
                swap(head, j, j+1);
}


char sort_compare(NODE *first, NODE *second, unsigned type)
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


void reverse(LIST *list)
/**
 *  @brief Реверс двусвязного списка. Сложность O(n)
 *  ---
 *  @param LIST *list - указатель на список
 */
{
    NODE *left = NULL,
         *right = NULL;
    TRACK temp;
         
    left = list->head;
    right = list->tail;
    
    while (left != right && left->previous != right)
    {
        temp = left->data;
        left->data = right->data;
        right->data = temp;
        
        left = left->next;
        right = right->previous;
    }
}

void shuffle(LIST *list)
/**
 *  @brief Случайное перемешивание двусвязного списка.
 *  ---
 *  @param LIST *list - указатель на список
 */
{
    int i, j;
    
    srand(time(NULL));
    for (i = length(list) - 1; i >= 1; i--)
    {
        j = rand() % (i+1);
        swap(list, i, j);
    }
}

int length(LIST *list)
/**
 *  @brief Получение длины списка. Сложность O(1)
 *  ---
 *  @param LIST *list - указатель на список
 *  @return int - длина списка
 */
{
    return list->size;
}

char is_empty(LIST *list)
/**
 *  @brief Проверка списка на пустоту. Сложность O(1)
 *  ---
 *  @param LIST *list - указатель на список
 *  @return сhar - 1 - если пустой, 0 - иначе
 */
{
    return (list == NULL || list->head == NULL);
}

void print_list(LIST *list)
/**
 *  @brief Вывод списка в виде таблицы
 *  ---
 *  @param LIST *list - указатель на список
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
        printf("|%6u |%21s |%21s |%21s |%7d |%5d |%10s |\n",
            count, (temp_node->data).artist,
            (temp_node->data).title, (temp_node->data).album,
            (temp_node->data).number,(temp_node->data).year,
            genres_array[(temp_node->data).genre]);

        temp_node = temp_node->next;
        count++;
    }
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
}

void save_list(LIST *list, char *filename)
/**
 *  @brief Сохраниение списка в csv файл
 *  ---
 *  @param LIST *list - указатель на список
 *  @param char *filename - путь до файла
 */
{
    FILE *df;
    NODE *temp_node = NULL;
    
    df = fopen(filename, "w");
    if(df != NULL)
    {
        for (temp_node = list->head; temp_node; temp_node = temp_node->next)
            fprintf(df, "%s;%s;%s;%d;%d;%d\n",temp_node->data.artist, temp_node->data.title,
            temp_node->data.album, temp_node->data.number,
            temp_node->data.year, temp_node->data.genre);
        
        fclose(df);
        print_msg(FILE_SUCCESS);
    }
    else
        print_msg(FILE_ERROR);
}

void get_list(LIST *list, char* filename, char separator)
/**
 *  @brief Получение списка из csv файла
 *  ---
 *  @param LIST *list - указатель на список
 *  @param char *filename - путь до файла
 *  @param char separator - разделитель
 */
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
                append(list, fill_node(s2));
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
/**
 *  @brief Заполнение структуры
 *  ---
 *  @param char **s2 - массив строк
 *  @return TRACK - заполненная структура
 */
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
/**
 *  @brief Разбиение строки на массив строк
 *  ---
 *  @param char *str - строка для разбиения
 *  @param int length - длина строки
 *  @param char sep - разделитель
 *  @return сhar** - массив строк
 */
{
    char **str_array = NULL;
    int i,j,k,m,key,count;
    for(j=0, m=0; j < length; j++)
        if(str[j]==sep) m++;

    key=0;
    str_array = calloc(m+1, sizeof(char*));
    if(str_array != NULL)
    {
        for (i = 0; i <= m; i++)
            str_array[i] = NULL;
        for(i=0,count=0;i<=m;i++,count++)
        {
            str_array[i] = calloc(length, sizeof(char));
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

void memory_clear(TRACK *t)
/**
 *  @brief Освобождение памяти из-под полей структуры
 *  ---
 *  @param TRACK* t - указатель на структуру, у которой очищаются поля
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

char compare_artist(TRACK first, TRACK second)
{
    return strcmp(first.artist, second.artist) == 0;
}

char compare_title(TRACK first, TRACK second)
{
    return strcmp(first.title, second.title) == 0;
}

char compare_album(TRACK first, TRACK second)
{
    return strcmp(first.album, second.album) == 0;
}

char compare_number(TRACK first, TRACK second)
{
    return first.number == second.number;
}

char compare_year(TRACK first, TRACK second)
{
    return first.year == second.year;
}

char compare_genre(TRACK first, TRACK second)
{
    return first.genre == second.genre;
}

