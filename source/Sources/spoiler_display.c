#include "global.h"
#include "configs.h"
#include "cheats.h"

extern	u32					threadStack[0x640];
extern	Handle				fsUserHandle;
extern	FS_archive			sdmcArchive;
extern	u32					IoBasePad;
extern	enum language		langue;
extern	enum MENU			current_menu;
extern	u16					mode;
extern	u8					cheatEnabled[64];
extern	int					isNewNtr;
extern	GAME_PLUGIN_MENU	gamePluginMenu;
extern	t_menu				menu[8];
extern	unsigned int		after;

/*
** Head
*/

t_spoil	add_head_spoiler_menu(enum MENU m, char *text)
{
	t_menu	*menu_p = &(menu[m]);
	t_spoil	ret;

	if (menu_p->count < 64)
	{
		xsprintf(menu_p->text[menu_p->count], "[+ %s +]", text);
		menu_p->f[menu_p->count] = active_spoiler;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 0;
		menu_p->spoiler[menu_p->count].id = -1;
		menu_p->spoiler[menu_p->count].parent_id = get_next_id(m);
		menu_p->args[menu_p->count] = menu_p->spoiler[menu_p->count].parent_id;
		menu_p->spoiler[menu_p->count].visibility = 1;
		menu_p->spoiler[menu_p->count].active = 0;
		menu_p->count++;
	}
	ret.id = menu_p->spoiler[menu_p->count - 1].parent_id;
	ret.space = 1;
	ret.m = m;
	return(ret);
}

t_spoil	add_head_child_spoiler_menu(t_spoil parent, char *text)
{
	t_menu	*menu_p = &(menu[parent.m]);
	t_spoil	ret;

	if (menu_p->count < 64)
	{
		xsprintf(menu_p->text[menu_p->count], "[+ %s +]", text);
		str_add_space(menu_p->text[menu_p->count], parent.space);
		menu_p->f[menu_p->count] = active_spoiler;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 1;
		menu_p->spoiler[menu_p->count].id = parent.id;
		menu_p->spoiler[menu_p->count].parent_id = get_next_id(parent.m);
		menu_p->args[menu_p->count] = menu_p->spoiler[menu_p->count].parent_id;
		menu_p->spoiler[menu_p->count].visibility = 0;
		menu_p->spoiler[menu_p->count].active = 0;
		menu_p->count++;
	}
	ret.id = menu_p->spoiler[menu_p->count - 1].parent_id;
	ret.m = parent.m;
	ret.space = parent.space + 1;
	return(ret);
}

/*
** Child
*/

void	add_child_spoiler_menu(t_spoil parent, char *text, void(*f)())
{
	t_menu *menu_p = &(menu[parent.m]);
	if (menu_p->count < 64)
	{
		xsprintf(menu_p->text[menu_p->count], "[ ]%s", text);
		str_add_space(menu_p->text[menu_p->count], parent.space);
		menu_p->f[menu_p->count] = f;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 1;
		menu_p->spoiler[menu_p->count].is_spoilable = 1;
		menu_p->spoiler[menu_p->count].id = parent.id;
		menu_p->spoiler[menu_p->count].visibility = 0;
		menu_p->spoiler[menu_p->count].active = 0;
		menu_p->count++;
	}
}

void	add_nothing_child_spoiler_menu(t_spoil parent, char *text, void(*f)())
{
	t_menu *menu_p = &(menu[parent.m]);
	if (menu_p->count < 64)
	{
		xsprintf(menu_p->text[menu_p->count], "%s", text);
		str_add_space(menu_p->text[menu_p->count], parent.space);
		menu_p->f[menu_p->count] = f;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 1;
		menu_p->spoiler[menu_p->count].id = parent.id;
		menu_p->spoiler[menu_p->count].visibility = 0;
		menu_p->spoiler[menu_p->count].active = 0;
		menu_p->count++;
	}
}

void	add_activate_child_spoiler_menu(t_spoil parent, char *text)
{
	t_menu *menu_p = &(menu[parent.m]);
	if (menu_p->count < 64)
	{
		xsprintf(menu_p->text[menu_p->count], "[ ]%s", text);
		str_add_space(menu_p->text[menu_p->count], parent.space);
		menu_p->f[menu_p->count] = activate_menu;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->status = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 1;
		menu_p->spoiler[menu_p->count].id = parent.id;
		menu_p->spoiler[menu_p->count].visibility = 0;
		menu_p->spoiler[menu_p->count].active = 0;
		menu_p->count++;
	}
}

void	add_sharp_child_spoiler_menu(t_spoil parent, char *text, void(*f)())
{
	t_menu *menu_p = &(menu[parent.m]);
	if (menu_p->count < 64)
	{
		xsprintf(menu_p->text[menu_p->count], "# %s", text);
		str_add_space(menu_p->text[menu_p->count], parent.space);
		menu_p->f[menu_p->count] = f;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 1;
		menu_p->spoiler[menu_p->count].id = parent.id;
		menu_p->spoiler[menu_p->count].visibility = 0;
		menu_p->spoiler[menu_p->count].active = 0;
		menu_p->count++;
	}
}

void	add_space_child_spoiler_menu(t_spoil parent, char *text, void(*f)())
{
	t_menu *menu_p = &(menu[parent.m]);
	if (menu_p->count < 64)
	{
		xsprintf(menu_p->text[menu_p->count], "  %s", text);
		str_add_space(menu_p->text[menu_p->count], parent.space);
		menu_p->f[menu_p->count] = f;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 1;
		menu_p->spoiler[menu_p->count].id = parent.id;
		menu_p->spoiler[menu_p->count].visibility = 0;
		menu_p->spoiler[menu_p->count].active = 0;
		menu_p->count++;
	}
}

void	add_number_child_spoiler_menu(t_spoil parent, char *text, void(*f)())
{
	t_menu *menu_p = &(menu[parent.m]);
	if (menu_p->count < 64)
	{
		xsprintf(menu_p->text[menu_p->count], "%d. %s", menu_p->count + 1, text);
		str_add_space(menu_p->text[menu_p->count], parent.space);
		menu_p->f[menu_p->count] = f;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 1;
		menu_p->spoiler[menu_p->count].id = parent.id;
		menu_p->spoiler[menu_p->count].visibility = 0;
		menu_p->spoiler[menu_p->count].active = 0;
		menu_p->count++;
	}
}

void	add_separator_child_spoiler_menu(t_spoil parent, char *text)
{
	t_menu *menu_p = &(menu[parent.m]);
	if (menu_p->count < 64)
	{
		xsprintf(menu_p->text[menu_p->count], "----------------------");
		str_add_space(menu_p->text[menu_p->count], parent.space);
		menu_p->f[menu_p->count] = NULL;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 1;
		menu_p->spoiler[menu_p->count].id = parent.id;
		menu_p->spoiler[menu_p->count].visibility = 0;
		menu_p->spoiler[menu_p->count].active = 0;
		menu_p->count++;
	}
}

void	add_line_child_spoiler_menu(t_spoil parent)
{
	t_menu *menu_p = &(menu[parent.m]);
	if (menu_p->count < 64)
	{
		menu_p->text[menu_p->count][0] = '\0';
		menu_p->f[menu_p->count] = NULL;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 1;
		menu_p->spoiler[menu_p->count].id = parent.id;
		menu_p->spoiler[menu_p->count].visibility = 0;
		menu_p->spoiler[menu_p->count].active = 0;
		menu_p->count++;
	}
}