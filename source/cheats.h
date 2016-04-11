#ifndef CHEATS_H
#define CHEATS_H
#include "global.h"
#include "configs.h"

#define MENU_COUNT 2

enum language	{	EN, FR };
enum TYPE		{	T8, T16, T32};
enum MENU		{	BASE, DEBUG };

u32		plgGetIoBase(u32 IoType);
Handle	getCurrentProcessHandle();
u32		getCurrentProcessId();
void	onCheatItemChanged(int id, int enable);

typedef struct	s_offset
{
	enum TYPE	type;
	int			addr;
}				t_offset;

typedef struct	s_spoiler
{
	char		visibility;
	char		is_spoilable;
	int			id;
	int			parent_id;
	char		active;
}				t_spoiler;

typedef struct	s_spoil
{
	int			id;
	int			space;
	enum MENU	m;
}				t_spoil;

typedef struct	s_menu
{
	int			count;
	char		status;
	char		state[64];
	char		freeze[64];
	void		(*f[64])();
	int			args[64];
	char		text[64][40];
	t_spoiler	spoiler[64];
	t_offset	*offset;
}				t_menu;

enum
{
	KEY_A       = BIT(0),       ///< A
	KEY_B       = BIT(1),       ///< B
	KEY_SELECT  = BIT(2),       ///< Select
	KEY_START   = BIT(3),       ///< Start
	KEY_DRIGHT  = BIT(4),       ///< D-Pad Right
	KEY_DLEFT   = BIT(5),       ///< D-Pad Left
	KEY_DUP     = BIT(6),       ///< D-Pad Up
	KEY_DDOWN   = BIT(7),       ///< D-Pad Down
	KEY_R       = BIT(8),       ///< R
	KEY_L       = BIT(9),       ///< L
	KEY_X       = BIT(10),      ///< X
	KEY_Y       = BIT(11),      ///< Y
	KEY_ZL      = BIT(14),      ///< ZL (New 3DS only)
	KEY_ZR      = BIT(15),      ///< ZR (New 3DS only)
	KEY_TOUCH   = BIT(20),      ///< Touch (Not actually provided by HID)
	KEY_CSTICK_RIGHT = BIT(24), ///< C-Stick Right (New 3DS only)
	KEY_CSTICK_LEFT  = BIT(25), ///< C-Stick Left (New 3DS only)
	KEY_CSTICK_UP    = BIT(26), ///< C-Stick Up (New 3DS only)
	KEY_CSTICK_DOWN  = BIT(27), ///< C-Stick Down (New 3DS only)
	KEY_CPAD_RIGHT = BIT(28),   ///< Circle Pad Right
	KEY_CPAD_LEFT  = BIT(29),   ///< Circle Pad Left
	KEY_CPAD_UP    = BIT(30),   ///< Circle Pad Up
	KEY_CPAD_DOWN  = BIT(31),   ///< Circle Pad Down

	// Generic catch-all directions
	KEY_UP    = KEY_DUP    | KEY_CPAD_UP,    ///< D-Pad Up or Circle Pad Up
	KEY_DOWN  = KEY_DDOWN  | KEY_CPAD_DOWN,  ///< D-Pad Down or Circle Pad Down
	KEY_LEFT  = KEY_DLEFT  | KEY_CPAD_LEFT,  ///< D-Pad Left or Circle Pad Left
	KEY_RIGHT = KEY_DRIGHT | KEY_CPAD_RIGHT, ///< D-Pad Right or Circle Pad Right
	KEY_CPAD  = KEY_CPAD_DOWN | KEY_CPAD_UP | KEY_CPAD_LEFT | KEY_CPAD_RIGHT
};

/*
**gameplg.c
*/

void	unlock_kokiri_sword();
void	unlock_excalibur_sword();
void	unlock_biggoron_sword();
void	unlock_wood_shield();
void	unlock_hyrule_shield();
void	unlock_mirror_shield();
void	unlock_kokiri_suits();
void	unlock_zora_suits();
void	unlock_goron_suits();

/*
**cheats.c
*/

void	max_heart();
void	max_magic();
void	refill_heart();
void	refill_large_magicbar();
void	infinite_arrows();
void	infinite_nuts();
void	infinite_stick();
void	infinite_bomb();
void	infinite_bombchu();
void	infinite_slingshot();
void	skulltulas();
void	max_rupees();
void	sunrise();
void	daytime();
void	sunset();
void	night();
void	unlock_large_mb();
void	unlock_magic();
void	unlock_heartpieces();
void	unlock_enhanced_defense();
void	unlock_all_swords();
void	unlock_all_shields();
void	unlock_all_suits();
void	unlock_all_stones();
void	unlock_all_best();
void	unlock_all_medallions();
void	giant_link();
void	normal_link();
void	mini_link();
void	paper_link();
void	moon_jump();
void	move_fast();
void	move_fast_rev();
void	collect_heart();
void	open_chest();
void	spin_attack();
void	sword_glitch();
void	stick_fire();
void	epona_max_carrots(void);

void	trigger_swords(int x);
void	trigger_shields(int x);
void	trigger_suits(int x);

/*
**menu.c
*/

void	create_base_menu();

/*
**common_functions.c
*/

void	waitKeyUp();
void	waitKeyChange(int key);
void	scanHID();
u32		hidKeysDown();
void	setHID(u32 keys);
int		read(int addr, enum TYPE type);
void	str_replace(char *str, char a, char b);
void	str_add_space(char *str, int n);

/*
**menu_display.c
*/

void	updateCheatEnableDisplay(int id);
void	updateAllCheatEnableDisplay();
void	addCheatMenuEntry(u8* str);
void	addSCheatMenuEntry(u8* str);
void	add_menu(enum MENU m, char *text, void(*f)());
void	add_nothing_menu(enum MENU m, char *text, void(*f)());
void	add_activate_menu(enum MENU m, char *text);
void	add_sharp_menu(enum MENU m, char *text, void(*f)());
void	add_space_menu(enum MENU m, char *text, void(*f)());
void	add_number_menu(enum MENU m, char *text, void(*f)());
void	add_separator_menu(enum MENU m);
void	add_line_menu(enum MENU m);
void	change_text(enum MENU m, int line, char	*text);
void	add_text(enum MENU m, int line, char	*text);

/*
**menu_functions.c
*/

void	initMenu();
void    initCheatMenu();
void	addMenuEntry(u8* str);
u32		updateMenu();
int		scanMenu();
void	scanCheatMenu();
void    disableCheat(int index);
void	init_menu();
void	activate_menu();
void	change_menu_status(enum MENU m);
void	show_menu(enum MENU m);
void	show_base();
void	show_debug();
void	do_action(t_menu *menu, int id);
void	do_all_action();
void	change_state(int id);
int		find_id(enum MENU me, char *name);
int		get_real_id(int id);

/*
** spoiler_display.c
*/

t_spoil	add_head_spoiler_menu(enum MENU m, char *text);
t_spoil	add_head_child_spoiler_menu(t_spoil parent, char *text);

void	add_child_spoiler_menu(t_spoil parent, char *text, void(*f)());
void	add_nothing_child_spoiler_menu(t_spoil parent, char *text, void(*f)());
void	add_activate_child_spoiler_menu(t_spoil parent, char *text);
void	add_sharp_child_spoiler_menu(t_spoil parent, char *text, void(*f)());
void	add_space_child_spoiler_menu(t_spoil parent, char *text, void(*f)());
void	add_number_child_spoiler_menu(t_spoil parent, char *text, void(*f)());
void	add_separator_child_spoiler_menu(t_spoil parent, char *text);
void	add_line_child_spoiler_menu(t_spoil parent);

/*
** spoilers_functions.c
*/
void	spoil(enum MENU m, int id);
void	un_spoil(enum MENU m, int id);
void	change_spoiler_state(enum MENU m, int id);
void	active_spoiler(int id);
void	show_only_spoiler(enum MENU m, int id);

int		get_next_id(enum MENU m);

#endif