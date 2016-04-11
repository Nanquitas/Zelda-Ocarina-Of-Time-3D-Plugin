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

void initMenu()
{
	memset(&gamePluginMenu, 0, sizeof(GAME_PLUGIN_MENU));
}

void addMenuEntry(u8* str)
{
	if (gamePluginMenu.count > 100)
		return;
	u32 pos = gamePluginMenu.count;
	u32 len = strlen(str) + 1;
	gamePluginMenu.offsetInBuffer[pos] = gamePluginMenu.bufOffset;
	strcpy(&(gamePluginMenu.buf[gamePluginMenu.bufOffset]), str);

	gamePluginMenu.count += 1;
	gamePluginMenu.bufOffset += len;
}

u32 updateMenu()
{
	PLGLOADER_INFO *plgLoaderInfo = (void*)0x07000000;
	plgLoaderInfo->gamePluginPid = getCurrentProcessId();
	plgLoaderInfo->gamePluginMenuAddr = (u32)&gamePluginMenu;

	u32 ret = 0;
	u32 hProcess;
	u32 homeMenuPid = plgGetIoBase(5);
	if (homeMenuPid == 0)
		return 1;
	ret = svc_openProcess(&hProcess, homeMenuPid);
	if (ret != 0)
		return ret;
	copyRemoteMemory(hProcess, &(plgLoaderInfo->gamePluginPid), CURRENT_PROCESS_HANDLE, &(plgLoaderInfo->gamePluginPid), 8);
	final:
	svc_closeHandle(hProcess);
	return ret;
}

int scanMenu()
{
	u32 i;
	for (i = 0; i < gamePluginMenu.count; i++)
	{
		if (gamePluginMenu.state[i])
		{
			gamePluginMenu.state[i] = 0;
			return i;
		}
	}
	return -1;
}

void scanCheatMenu()
{
	int ret = scanMenu();
	if (ret != -1)
	{
		onCheatItemChanged(ret, menu[current_menu].state[ret]);
		updateCheatEnableDisplay(ret);
	}
}

void    disableCheat(int index)
{
	menu[current_menu].state[index] = 0;
	updateAllCheatEnableDisplay();
}
/*
**
*/

void init_menu()
{
	int	i;

	i = 0;
	while(i < MENU_COUNT)
		memset(&(menu[i++]), 0, sizeof(t_menu));
}

void	show_menu(enum MENU m)
{
	int i;

	current_menu = m;
	initMenu();
	if(menu[current_menu].status)
		for (i = 0; i < menu[m].count; i++)
		{
			if(menu[m].spoiler[i].visibility)
				addMenuEntry(&(menu[m].text[i][0]));
		}
	else
		addMenuEntry(&(menu[m].text[0][0]));
	updateAllCheatEnableDisplay();
}

void	update_text()
{

}

void	activate_menu()
{
	if (menu[current_menu].status)
		menu[current_menu].status = 0;
	else
		menu[current_menu].status = 1;
	show_menu(current_menu);
	updateAllCheatEnableDisplay();
}

void	change_menu_status(enum MENU m)
{
	if (menu[m].status)
		menu[m].status = 0;
	else
		menu[m].status = 1;
	updateAllCheatEnableDisplay();
}

void	do_action(t_menu *menu_p, int id)
{
	if (id <= menu_p->count)
	{
		if (menu_p->f[id] != NULL && menu_p->args[id] > 0)
			menu_p->f[id](menu_p->args[id]);
		else if(menu_p->f[id] != NULL)
			menu_p->f[id]();
	}
}

void	do_all_action()
{
	int i;

	if (menu[current_menu].status)
	{
		for (i = 0; i <= menu[current_menu].count; i++)
		{
			if (menu[current_menu].state[i])
			{
				if (menu[current_menu].freeze[i] == 0)
					disableCheat(i);
				do_action(&(menu[current_menu]), i);
			}
		}
	}
}

void	change_state(int id)
{
	if (menu[current_menu].state[id] == 1)
		menu[current_menu].state[id] = 0;
	else
		menu[current_menu].state[id] = 1;
	updateAllCheatEnableDisplay();
}



int		find_id(enum MENU me, char *name)
{
	int id;
	t_menu *m = &(menu[me]);
	char	*text; 

	id = 0;
	while (id <= m->count)
	{
		text = m->text[id];
		while (*text == ' ' || *text == '[' || *text == ']' || *text == '#')
			text++;
		if ((strcmp(text, name)) == 0)
			return(id);
		id++;
	}
	return (-1);
}

void	show_base()
{
	show_menu(BASE);
}

void	show_debug()
{
	show_menu(DEBUG);
}

int		get_real_id(int id)
{
	int		i;
	t_menu	*menu_p;

	menu_p = &(menu[current_menu]);
	i = 0;
	for (i = 0; i < menu_p->count; i++)
	{
		if (menu_p->spoiler[i].visibility == 0)
			id++;
		if (id == i && menu_p->spoiler[i].visibility == 1)
			return (id);
	}
	return(id);
}