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


void	create_base_menu()
{
	t_spoil		spoiler;
	t_spoil		midspoil;

	add_activate_menu(BASE, "Activate Cheat");
	add_separator_menu(BASE);
	spoiler = add_head_spoiler_menu(BASE, "Combat codes");
		//midspoil = add_head_child_spoiler_menu(spoiler, "Refill Codes");
			add_sharp_child_spoiler_menu(spoiler, "Refill Heart (L + UP)", refill_heart);
			add_sharp_child_spoiler_menu(spoiler, "Refill Magicbar", refill_large_magicbar);
			add_child_spoiler_menu(spoiler, "Instant charge spin attack", spin_attack);
			add_child_spoiler_menu(spoiler, "Sword glitch", sword_glitch);
			add_child_spoiler_menu(spoiler, "Stick in fire", stick_fire);
			add_child_spoiler_menu(spoiler, "Epona max carrots", epona_max_carrots);
	spoiler = add_head_spoiler_menu(BASE, "Inventory codes");
		midspoil = add_head_child_spoiler_menu(spoiler, "Misceallenous");
			add_child_spoiler_menu(midspoil, "Infinite Arrows", infinite_arrows);
			add_child_spoiler_menu(midspoil, "Infinite Deku Nuts", infinite_nuts);
			add_child_spoiler_menu(midspoil, "Infinite Deku Sticks", infinite_stick);
			add_child_spoiler_menu(midspoil, "Infinite Bomb", infinite_bomb);
			add_child_spoiler_menu(midspoil, "Infinite Bombchu", infinite_bombchu);
			add_child_spoiler_menu(midspoil, "Infinite slingshot munition", infinite_slingshot);
		add_sharp_child_spoiler_menu(spoiler, "100 Gold Skulltulas", skulltulas);
		add_sharp_child_spoiler_menu(spoiler, "Max rupees", max_rupees);
	spoiler = add_head_spoiler_menu(BASE, "Environment codes"); 
		midspoil = add_head_child_spoiler_menu(spoiler, "Time");
			add_sharp_child_spoiler_menu(midspoil, "Sunrise (R + LEFT)", sunrise);
			add_sharp_child_spoiler_menu(midspoil, "Daytime (R + UP)", daytime);
			add_sharp_child_spoiler_menu(midspoil, "Sunset (R + RIGHT)", sunset);
			add_sharp_child_spoiler_menu(midspoil, "Night (R + DOWN)", night);
		//add_child_spoiler_menu(spoiler, "Collect heartpieces more time", collect_heart);
		//add_child_spoiler_menu(spoiler, "Re-open chest", open_chest);
	spoiler = add_head_spoiler_menu(BASE, "Unlock codes");
		midspoil = add_head_child_spoiler_menu(spoiler, "Combat");
		add_sharp_child_spoiler_menu(midspoil, "Unlock magic", unlock_magic);
			add_sharp_child_spoiler_menu(midspoil, "Unlock large magicbar",unlock_large_mb);			
			add_sharp_child_spoiler_menu(midspoil, "Unlock all heart", max_heart);
			add_sharp_child_spoiler_menu(midspoil, "3 Heartpieces", unlock_heartpieces);
			add_sharp_child_spoiler_menu(midspoil, "Enhanced defense", unlock_enhanced_defense);
		midspoil = add_head_child_spoiler_menu(spoiler, "Equipment");
			add_sharp_child_spoiler_menu(midspoil, "(Un)lock Kokiri's sword", unlock_kokiri_sword);
			add_sharp_child_spoiler_menu(midspoil, "(Un)lock Excalibur's sword", unlock_excalibur_sword);
			add_sharp_child_spoiler_menu(midspoil, "(Un)lock Biggoron's sword", unlock_biggoron_sword);
			add_sharp_child_spoiler_menu(midspoil, "(Un)lock Wood shield", unlock_wood_shield);
			add_sharp_child_spoiler_menu(midspoil, "(Un)lock Hyrule shield", unlock_hyrule_shield);
			add_sharp_child_spoiler_menu(midspoil, "(Un)lock Mirror shield", unlock_mirror_shield);
			add_sharp_child_spoiler_menu(midspoil, "(Un)lock Kokiri's suits", unlock_kokiri_suits);
			add_sharp_child_spoiler_menu(midspoil, "(Un)lock Goron's suits", unlock_goron_suits);
			add_sharp_child_spoiler_menu(midspoil, "(Un)lock Zora's suits", unlock_zora_suits);
		midspoil = add_head_child_spoiler_menu(spoiler, "Unlock All *");
			add_sharp_child_spoiler_menu(midspoil, "Unlock all swords", unlock_all_swords);
			add_sharp_child_spoiler_menu(midspoil, "Unlock all shields", unlock_all_shields);
			add_sharp_child_spoiler_menu(midspoil, "Unlock all suits", unlock_all_suits);
			add_sharp_child_spoiler_menu(midspoil, "Unlock all bests", unlock_all_best);			
		midspoil = add_head_child_spoiler_menu(spoiler, "Story");
			add_sharp_child_spoiler_menu(spoiler, "Unlock all stones", unlock_all_stones);
			add_sharp_child_spoiler_menu(midspoil, "Unlock all medallions", unlock_all_medallions);
	spoiler = add_head_spoiler_menu(BASE, "Fun codes");
		midspoil = add_head_child_spoiler_menu(spoiler, "Link's size");
			add_sharp_child_spoiler_menu(midspoil, "Giant Link", giant_link);
			add_sharp_child_spoiler_menu(midspoil, "Normal Link", normal_link);
			add_sharp_child_spoiler_menu(midspoil, "Mini Link", mini_link);
			add_sharp_child_spoiler_menu(midspoil, "Paper Link", paper_link);
		midspoil = add_head_child_spoiler_menu(spoiler, "Movements codes");
			add_nothing_child_spoiler_menu(midspoil, "Moon Jump (UP)", NULL);
			add_nothing_child_spoiler_menu(midspoil, "Move Fast (A + CPAD)", NULL);
}

/*
** SAMPLE
*/

/*
void	create_base_menu()
{
t_spoil spoiler;
add_activate_menu(BASE, "Activate Cheat");
add_separator_menu(BASE);
add_menu(BASE, "Infinite power meter", infinite_power_meter);
add_menu(BASE, "Infinite heart", full_heart);
add_sharp_menu(BASE, "Max rupees", max_rupees);
spoiler = add_head_spoiler_menu(BASE, "Dungeon's codes");
add_sharp_child_spoiler_menu(spoiler, "5 Dungeon's keys", five_dungeon_keys);
spoiler = add_head_spoiler_menu(BASE, "Inventory's codes");
add_sharp_child_spoiler_menu(spoiler, "Max miamias", max_miamias);
add_sharp_child_spoiler_menu(spoiler, "Max monster horns", max_monster_horns);
add_sharp_child_spoiler_menu(spoiler, "Max monster guts", max_monster_guts);
add_sharp_child_spoiler_menu(spoiler, "Max monster tails", max_monster_tails);

}*/