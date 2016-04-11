#include "global.h"
#include "configs.h"
#include "cheats.h"

extern	u32					threadStack[0x1000];
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

void	spoil(enum MENU m, int id)
{
	t_menu *menu_p = &(menu[m]);
	int i;

	for (i = 0; i < menu_p->count; i++)
	{
		if (menu_p->spoiler[i].parent_id == id)
			str_replace(menu_p->text[i], '-', '+');
		if ( menu_p->spoiler[i].id == id)
		{
			if ( menu_p->spoiler[i].is_spoilable == 1)
				 menu_p->spoiler[i].visibility = 0;
			menu_p->spoiler[i].active = 0;
		}
	}
}

void	spoil_all(enum MENU m)
{
	t_menu *menu_p = &(menu[m]);
	int i;

	for (i = 0; i < menu_p->count; i++)
	{
		if (menu_p->spoiler[i].is_spoilable == 1)
			menu_p->spoiler[i].visibility = 0;
		menu_p->spoiler[i].active = 0;
		if (menu_p->spoiler[i].parent_id != 0)
			str_replace(menu_p->text[i], '-', '+');
	}
}


void	un_spoil(enum MENU m, int id)
{
	t_menu *menu_p = &(menu[m]);
	int i;


	for (i = 0; i < menu_p->count; i++)
	{
		if (menu_p->spoiler[i].parent_id == id)
			str_replace(menu_p->text[i], '+', '-');
		if ( menu_p->spoiler[i].id == id)
		{
			if ( menu_p->spoiler[i].is_spoilable == 1)
				 menu_p->spoiler[i].visibility = 1;
			menu_p->spoiler[i].active = 1;
		}
		if (menu_p->spoiler[i].parent_id == id)
			if(menu_p->spoiler[i].id != -1)
				un_spoil(m, menu_p->spoiler[i].id);
	}
}

void	change_spoiler_state(enum MENU m, int id)
{
	t_menu *menu_p = &(menu[m]);
	int i;

	for (i = 0; i <  menu_p->count; i++)
	{
		if ( menu_p->spoiler[i].id == id)
		{
			if ( menu_p->spoiler[i].active == 1)
				spoil(m, id);
			else
				un_spoil(m, id);
		}
	}
}

void	active_spoiler(int id)
{
	enum MENU	m = current_menu;
	int			i;
	t_menu		*menu_p = &(menu[m]);

	for (i = 0; i < 64; i++)
	{
		if (menu_p->spoiler[i].parent_id == id)
		{
			if (menu_p->spoiler[i + 1].visibility == 1 && menu_p->spoiler[i + 1].id == id)
			{
				if (menu_p->spoiler[i].id == -1)
					spoil_all(m);
				else
					spoil(m, id);
				show_menu(m);
				return;
			}				
		}
	}
	show_only_spoiler(current_menu, id);
	show_menu(current_menu);

}

void	show_only_spoiler(enum MENU m, int id)
{
	spoil_all(m);
	un_spoil(m, id);
}

int		get_next_id(enum MENU m)
{
	int		id;
	int		i;
	t_menu	*menu_p = &(menu[m]);

	id = 1;
	for (i = 0; i < 64; i++)
	{
		if (menu_p->spoiler[i].id != -1)
		{
			if (menu_p->spoiler[i].id >= id)
				id = menu_p->spoiler[i].id + 1;
		}
	}
	return (id);
}