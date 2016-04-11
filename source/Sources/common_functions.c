#include "global.h"
#include "configs.h"
#include "cheats.h"

//#define HID_SHAREDMEM_DEFAULT (0x10002000)
extern	u32 threadStack[0x1000];
extern	Handle fsUserHandle;
extern	FS_archive sdmcArchive;
extern	u32 IoBasePad;
extern	enum language langue;
extern	enum MENU		current_menu;
extern	u16  mode;
extern	u8 cheatEnabled[64];
extern	int isNewNtr;
extern	GAME_PLUGIN_MENU gamePluginMenu;
extern	t_menu	menu[8];
vu32 	*hidSharedMem = (u32 *)0x10002000;
static 	u32	kDown;

void	debounceKey() 
{
	vu32 t;

	for (t = 0; t < 0x100000; t++) {}
}

u32		getKey() 
{
	return (*(vu32*)(IoBasePad) ^ 0xFFF) & 0xFFF;
}

u32		waitKey() 
{
	u32 key;
	// wait key to be released
	while (getKey() != 0);
	while (1) 
	{
		key = getKey();
		if (key != 0) 
		{
			break;
		}
	}
	debounceKey();
	return key;
}

void	waitKeyUp()
{
	while (getKey() != 0)
		svc_sleepThread(100000);
}

void	waitKeyChange(int key)
{
	while (getKey() == key) {}
}

void	str_replace(char *str, char a, char b)
{
	while (*str != '\0')
		if (*str++ == a)
			*(str -1) = b;
}

u32 hidCheckSectionUpdateTime(vu32 *sharedmem_section, u32 id)
{
	s64 tick0=0, tick1=0;

	if(id==0)
	{
		tick0 = *((u64*)&sharedmem_section[0]);
		tick1 = *((u64*)&sharedmem_section[2]);

		if(tick0==tick1 || tick0<0 || tick1<0)return 1;
	}

	return 0;
}

void	scanHID()
{
	u32 Id = 0;
	kDown = 0;
	Id = hidSharedMem[4];//PAD / circle-pad
	if(Id > 7)
		Id = 7;
	if(hidCheckSectionUpdateTime(hidSharedMem, Id) == 0)
		kDown = hidSharedMem[10 + Id*4];
}
void	setHID(u32 keys)
{
	u32 Id = 0;
	Id = hidSharedMem[4];//PAD / circle-pad
	if(Id > 7)
		Id = 7;
	if(hidCheckSectionUpdateTime(hidSharedMem, Id) == 0)
		hidSharedMem[10 + Id*4] |= keys;
}

u32		hidKeysDown()
{
	return(kDown);
}

void	str_add_space(char *str, int n)
{
	char	buf[40];
	char	*s = buf;

	while (n-- > 0)
		*s++ = ' ';
	xsprintf(s, "%s", str);
	xsprintf(str, "%s", buf);
}

int		read(int addr, enum TYPE type)
{
	if (type == T8)
		return(READU8(addr));
	if (type == T16)
		return(READU16(addr));
	if (type == T32)
		return(READU32(addr));
}
