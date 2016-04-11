#include "global.h"
#include "configs.h"
#include "cheats.h"
#include "../include/ctr/APT.h"


Handle fsUserHandle;
FS_archive sdmcArchive;
u32 IoBasePad = 0xFFFD4000;
enum language	langue = 0;
enum MENU		current_menu;
u16  mode;
u8 cheatEnabled[64];
int isNewNtr = 0;
GAME_PLUGIN_MENU gamePluginMenu;
t_menu	menu[MENU_COUNT];
unsigned int	after;

// detect language (0: english)
int detectLanguage()
{
	// unimplemented
	return 0;
}

// this function will be called when the state of cheat item changed
void onCheatItemChanged(int id, int enable)
{
	if (current_menu == BASE && id == 0)
		activate_menu();
	else
		change_state(get_real_id(id));
}

/*
** Function needing an arguments
*/

void	unlock_kokiri_sword()
{
	trigger_swords(1);
}

void	unlock_excalibur_sword()
{
	trigger_swords(2);
}

void	unlock_biggoron_sword()
{
	trigger_swords(3);
}

void	unlock_wood_shield()
{
	trigger_shields(1);
}

void	unlock_hyrule_shield()
{
	trigger_shields(2);
}

void	unlock_mirror_shield()
{
	trigger_shields(3);
}

void	unlock_kokiri_suits()
{
	trigger_suits(1);
}

void	unlock_zora_suits()
{
	trigger_suits(3);
}

void	unlock_goron_suits()
{
	trigger_suits(2);
}

/*
**
*/

void key_trigger(unsigned int key)
{
	static int speed = 0;
	scanHID();
	//(key == (ZR + ZL)) ? change_menu_status(BASE), waitKeyChange(key) : key + 0;
	(key == (L + DU)) ? refill_heart(), waitKeyChange(key) : 0;
	(key == (X + DU)) ? daytime(), waitKeyChange(key) : 0;
	(key == (X + DL)) ? sunrise(), waitKeyChange(key) : 0;
	(key == (X + DR)) ? sunset(), waitKeyChange(key) : 0;
	(key == (X + DD)) ? night(), waitKeyChange(key) : 0;
	(hidKeysDown() & KEY_DDOWN) ? speed = !speed, waitKeyChange(key) : 0;
	//(hidKeysDown() & KEY_ZR) ? setHID(KEY_R): 0;
	(hidKeysDown() & KEY_DUP) ? moon_jump() : 0;
	if(speed)
		((hidKeysDown() & KEY_A) &&  (hidKeysDown() & KEY_CPAD)) ? move_fast() : 0;
}


void gamePluginEntry()
{
	u32 ret, key;
	u32 i = 0;
	INIT_SHARED_FUNC(plgGetIoBase, 8);
	INIT_SHARED_FUNC(copyRemoteMemory, 9);
	svc_sleepThread(5000000000);
	
	mode = 0;
	if (((NS_CONFIG*)(NS_CONFIGURE_ADDR))->sharedFunc[8])
	{
		isNewNtr = 1;
	} 
	else
	{
		isNewNtr = 0;
	}
	
	if (isNewNtr)
	{
		IoBasePad = plgGetIoBase(IO_BASE_PAD);
	}
	rtReleaseLock(&((NS_CONFIG*)(NS_CONFIGURE_ADDR))->debugBufferLock);
	plgGetSharedServiceHandle("fs:USER", &fsUserHandle);
	updateMenu();
	current_menu = BASE;
	init_menu();
	create_base_menu();
	show_menu(BASE);
	while (1)
	{
		key = getKey();
	/*	if (key == BUTTON_ST + BUTTON_SE)
		{
			show_menu(BASE);
			waitKeyUp();
		}*/
		key_trigger(key);
		svc_sleepThread(100000);
		scanCheatMenu();
		do_all_action();		
	}
}