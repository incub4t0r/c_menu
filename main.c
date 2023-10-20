#include <stdlib.h>
#include <stdio.h>
#include "menulib/menulib.h"

void
action1(void)
{
    printf("Action 1\n");
}

void
action2(void)
{
    printf("Action 2\n");
}

void
action3(void)
{
    printf("Action 3\n");
}

int
main(void)
{
    menu_t * main_menu = menu_create("Main Menu");
    menu_add_option(main_menu, action1, "Act 1");
    menu_add_option(main_menu, action2, "Act 2");
    menu_add_option(main_menu, action3, "Act 3");
    menu_display(main_menu);
}