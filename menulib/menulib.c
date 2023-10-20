#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../inputlib/inputlib.h"

typedef struct menu_item_t menu_item_t;
typedef struct menu_t      menu_t;

int     menu_add_option(menu_t *menu, void (*action)(), const char *opt_name);
menu_t *menu_create(const char *name);
void    menu_display(menu_t *menu);
void    menu_free(menu_t *menu);

typedef struct menu_item_t
{
    int   option_id;
    char *option_name;
    void (*action)();
} menu_item_t;

typedef struct menu_t
{
    char        *title;
    int          num_options;
    menu_item_t *options[10];
} menu_t;

/**
 * @brief Adds an option to a menu
 *
 * @param menu A pointer representing the menu
 * @param action A pointer to a function to run when the option is chosen
 * @param opt_name A char array containing the option name for the menu
 * @return int If successful, returns 1, else 0
 */
int
menu_add_option(menu_t *menu, void (*action)(), const char *opt_name)
{
    menu_item_t *item = malloc(sizeof(menu_item_t));

    if (!item)
    {
        return 0;
    }

    if (menu->num_options
        < (int)(sizeof(menu->options) / sizeof(menu->options[0])))
    {
        item->action                     = action;
        item->option_id                  = menu->num_options;
        item->option_name                = strdup(opt_name);
        menu->options[menu->num_options] = item;
        menu->num_options++;
        return 0;
    }

    else
    {
        printf("menu_t full. No more options can be added.\n");
        return 0;
    }
}

/**
 * @brief Create a menu
 *
 * @param menu_name A char array containing the menu name
 * @return menu_t* If successful, returns a pointer to the menu on heap,
 *                 else NULL
 */
menu_t *
menu_create(const char *menu_name)
{
    menu_t *new_menu = malloc(sizeof(menu_t));

    if (!new_menu)
    {
        return NULL;
    }

    new_menu->num_options = 0;
    new_menu->title       = strdup(menu_name);
    return new_menu;
}

/**
 * @brief Frees the menu from the heap
 *
 * @param menu A pointer to the menu
 */
void
menu_free(menu_t *menu)
{
    for (int idx = 0; idx < menu->num_options; idx++)
    {
        free(menu->options[idx]->option_name);
        free(menu->options[idx]);
    }

    free(menu->title);
    free(menu);
}

/**
 * TODO: NEED TO CHANGE THIS FUNCTION TO ONLY DISPLAY THE MENU, NO INPUT HANDLING
 * @brief Displays the menu and runs through the menu
 *
 * @param menu A pointer to the menu
 */
void
menu_display(menu_t *menu)
{
    int choice = 0;

    for (;;)
    {
        printf("\n\nmenu_t: %s\n", menu->title);

        for (int idx = 0; idx < menu->num_options; idx++)
        {
            printf("%d: %s\n",
                   menu->options[idx]->option_id + 1,
                   menu->options[idx]->option_name);
        }

        inputgii("Enter option number (or 0 to exit)", &choice);

        if (choice == 0)
        {
            printf("\nGoodbye!");
            menu_free(menu);
            break;
        }

        int found = 0;

        for (int idx = 0; idx < menu->num_options; idx++)
        {
            if (menu->options[idx]->option_id == choice - 1)
            {
                found = 1;
                menu->options[idx]->action();
                break;
            }
        }

        if (found == 0)
        {
            printf("Invalid choice. Please try again.\n");
        }
    }
}