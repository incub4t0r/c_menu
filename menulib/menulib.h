#ifndef MENULIB_H
#define MENULIB_H

typedef struct menu_item_t menu_item_t;
typedef struct menu_t      menu_t;

int     menu_add_option(menu_t *menu, void (*action)(), const char *opt_name);
menu_t *menu_create(const char *name);
void    menu_display(menu_t *menu);
void    menu_free(menu_t *menu);

#endif // MENULIB_H