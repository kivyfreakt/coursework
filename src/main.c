#include "menu.h"

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
        SEARCH_DATA,
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
            flags[EDIT_DATA] = flags[SEARCH_DATA] = flags[PRINT_DATA] = 0;
        
        print_menu(MAIN_MENU, flags);
        save_scanf(&variant);

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
                    flags[EDIT_DATA] = flags[SEARCH_DATA] = flags[PRINT_DATA] = 1;
            break;
            case EDIT_DATA:
                if (flags[EDIT_DATA])
                    edit_menu(&musiclist);
                else
                    print_msg(MENU_ERROR);
            break;
            case SEARCH_DATA:
                if (flags[SEARCH_DATA])
                    search_menu(musiclist);
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
    delete_list(&musiclist);
    return 0;
}
