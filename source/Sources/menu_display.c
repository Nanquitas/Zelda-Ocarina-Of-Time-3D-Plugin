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
extern	t_menu				menu[MENU_COUNT];
extern	unsigned int		after;

void updateCheatEnableDisplay(int id)
{
	int		i;
	char	*str;

	str = &gamePluginMenu.buf[gamePluginMenu.offsetInBuffer[id]];
	for (i = 0; i < 40; i++)
	{
		if (*(str + i) == '[' || *(str + i) == '\0' || *(str + i) == '#')
			break;
	}
	str += i;
	if (*str == '[' && *(str + 2) == ']')
		*(str + 1) = menu[current_menu].state[get_real_id(id)] ? 'X' : ' ';	
	if (current_menu == BASE && id == 0)
		if(*str == '[' && *(str + 2) == ']')
			*(str + 1) = menu[current_menu].status ? 'X' : ' ';
}

void updateAllCheatEnableDisplay()
{
	int id;

	for (id = 0; id < gamePluginMenu.count; id++)
	{
		updateCheatEnableDisplay(id);
	}
}

void addCheatMenuEntry(u8* str)
{
	u8 buf[100];
	xsprintf(buf, "[ ] %s", str);
	addMenuEntry(buf);
}

void addSCheatMenuEntry(u8* str)
{
	u8 buf[100];
	xsprintf(buf, " #  %s", str);
	addMenuEntry(buf);
}
/*
**
*/

void	add_menu(enum MENU m, char *text, void(*f)())
{
	t_menu *menu_p = &(menu[m]);

	if (menu_p->count < 100)
	{
		xsprintf(menu_p->text[menu_p->count], "[ ]%s", text);
		menu_p->f[menu_p->count] = f;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 1;
		menu_p->spoiler[menu_p->count].is_spoilable = 0;
		menu_p->spoiler[menu_p->count].id = -1;
		menu_p->spoiler[menu_p->count].visibility = 1;
		menu_p->count++;
	}
}

void	add_nothing_menu(enum MENU m, char *text, void(*f)())
{
	t_menu *menu_p = &(menu[m]);
	if (menu_p->count < 100)
	{
		xsprintf(menu_p->text[menu_p->count], "%s", text);
		menu_p->f[menu_p->count] = f;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 0;
		menu_p->spoiler[menu_p->count].id = -1;
		menu_p->spoiler[menu_p->count].visibility = 1;
		menu_p->count++;
	}
}

void	add_activate_menu(enum MENU m, char *text)
{
	t_menu *menu_p = &(menu[m]);
	if (menu_p->count < 100)
	{
		xsprintf(menu_p->text[menu_p->count], "[ ]%s", text);
		menu_p->f[menu_p->count] = activate_menu;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->status = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 0;
		menu_p->spoiler[menu_p->count].id = -1;
		menu_p->spoiler[menu_p->count].visibility = 1;
		menu_p->count++;
	}
}

void	add_sharp_menu(enum MENU m, char *text, void(*f)())
{
	t_menu *menu_p = &(menu[m]);
	if (menu_p->count < 100)
	{
		xsprintf(menu_p->text[menu_p->count], "# %s", text);
		menu_p->f[menu_p->count] = f;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 0;
		menu_p->spoiler[menu_p->count].id = -1;
		menu_p->spoiler[menu_p->count].visibility = 1;
		menu_p->count++;
	}
}

void	add_space_menu(enum MENU m, char *text, void(*f)())
{
	t_menu *menu_p = &(menu[m]);
	if (menu_p->count < 100)
	{
		xsprintf(menu_p->text[menu_p->count], "  %s", text);
		menu_p->f[menu_p->count] = f;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 0;
		menu_p->spoiler[menu_p->count].id = -1;
		menu_p->spoiler[menu_p->count].visibility = 1;
		menu_p->count++;
	}
}

void	add_number_menu(enum MENU m, char *text, void(*f)())
{
	t_menu *menu_p = &(menu[m]);
	if (menu_p->count < 100)
	{
		xsprintf(menu_p->text[menu_p->count], "%d. %s", menu_p->count + 1, text);
		menu_p->f[menu_p->count] = f;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 0;
		menu_p->spoiler[menu_p->count].id = -1;
		menu_p->spoiler[menu_p->count].visibility = 1;
		menu_p->count++;
	}
}

void	add_separator_menu(enum MENU m)
{
	t_menu *menu_p = &(menu[m]);
	if (menu_p->count < 100)
	{
		xsprintf(menu_p->text[menu_p->count], "----------------------");
		menu_p->f[menu_p->count] = NULL;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 0;
		menu_p->spoiler[menu_p->count].id = -1;
		menu_p->spoiler[menu_p->count].visibility = 1;
		menu_p->count++;
	}
}

void	add_line_menu(enum MENU m)
{
	t_menu *menu_p = &(menu[m]);
	if (menu_p->count < 100)
	{
		menu_p->text[menu_p->count][0] = '\0';
		menu_p->f[menu_p->count] = NULL;
		menu_p->state[menu_p->count] = 0;
		menu_p->freeze[menu_p->count] = 0;
		menu_p->spoiler[menu_p->count].is_spoilable = 0;
		menu_p->spoiler[menu_p->count].id = -1;
		menu_p->spoiler[menu_p->count].visibility = 1;
		menu_p->count++;
	}
}

void	change_text(enum MENU m, int line, char	*text)
{
	memset(&(menu[m].text[line]), '\0', 40);
	xsprintf(menu[m].text[line], text);
}

void	add_text(enum MENU m, int line, char	*text)
{
	char	buf[40];
	int		pos;

	strcpy(buf, menu[m].text[line]);
	pos = 0;
	while (buf[pos] != '\0')
		pos++;
	while (*text != '\0')
	{
		buf[pos++] = *text;
		text++;
	}
	buf[pos] = '\0';
	strcpy(menu[m].text[line], buf);
}