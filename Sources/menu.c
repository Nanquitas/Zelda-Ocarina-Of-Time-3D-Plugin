#include "cheats.h"
#include "notes.h"
#include <string.h>

void	my_menus(void)
{
	int index;
	int i;
	
	set_hid_address(0x10002000);
	new_spoiler("Combat");
		new_entry("Refill hearts (touch)", refill_heart);
		new_entry("Full magic (touch)", refill_large_magicbar);
		new_entry("Instant charge spin attack", spin_attack);
		new_entry("Sword glitch", sword_glitch);
		new_entry("Stick in fire", stick_fire);
		new_entry("MoonJump (Read note)", moon_jump);
		new_entry("Fast moves (Read note)", move_fast);
		new_entry("Epona max carrots", epona_max_carrots);
		new_entry("Epona max carrots all areas", epona_infinite_carrots_all_areas);
		new_entry("Epona moon jump (Read note)", epona_moon_jump);
		new_entry("Never take damage from falling", never_take_damage_from_falling);
		new_entry("Always have nayru's love", always_have_nayrus_love_activated);
	exit_spoiler();
	new_spoiler("Dungeon");
		new_entry("Infinite small keys", infinite_small_keys_all_dungeons);
		new_entry("Unlock Map/Compass/Boss Key", have_map_compass_and_boss_key_all_dunge);
	exit_spoiler();
	new_spoiler("Inventory"); 
		new_spoiler("Misceallenous");
			new_entry("Infinite Arrows", infinite_arrows);
			new_entry("Infinite Deku Nuts", infinite_nuts);
			new_entry("Infinite Deku Sticks", infinite_stick);
			new_entry("Infinite Bomb", infinite_bomb);
			new_entry("Infinite Bombchu", infinite_bombchu);
			new_entry("Infinite slingshot munition", infinite_slingshot);
		exit_spoiler();
		new_entry("100 Gold Skulltulas", skulltulas);
		new_entry("Max rupees", max_rupees);
		new_entry("Giant's knife never breaks", giants_knife_never_breaks);
		new_entry("Open any chest many times", open_any_chest_in_the_game_as_many_times);
		new_entry("Collect hearts many times", collect_heart_pieces_in_overworld_as_many);
	exit_spoiler();
	new_spoiler("Environment"); 
		new_spoiler("Time");
			new_entry("Sunrise (R + LEFT)", sunrise);
			new_entry("Daytime (R + UP)", daytime);
			new_entry("Sunset (R + RIGHT)", sunset);
			new_entry("Night (R + DOWN)", night);
		exit_spoiler();
		new_entry("Always raining", always_raining);
	exit_spoiler();
	new_spoiler("Unlock");
		new_spoiler("Combat");
			new_entry("Unlock magic", unlock_magic);
			new_entry("Unlock large magicbar",unlock_large_mb);			
			new_entry("Unlock all heart", max_heart);
			new_entry("3 Heartpieces", unlock_heartpieces);
			new_entry("Enhanced defense", unlock_enhanced_defense);
		new_spoiler("Equipment");
			new_entry("(Un)lock Kokiri's sword", unlock_kokiri_sword);
			new_entry("(Un)lock Excalibur's sword", unlock_excalibur_sword);
			new_entry("(Un)lock Biggoron's sword", unlock_biggoron_sword);
			new_entry("(Un)lock Wood shield", unlock_wood_shield);
			new_entry("(Un)lock Hyrule shield", unlock_hyrule_shield);
			new_entry("(Un)lock Mirror shield", unlock_mirror_shield);
			new_entry("(Un)lock Kokiri's suits", unlock_kokiri_suits);
			new_entry("(Un)lock Goron's suits", unlock_goron_suits);
			new_entry("(Un)lock Zora's suits", unlock_zora_suits);
		new_spoiler("Unlock All *");
			new_entry("Unlock all swords", unlock_all_swords);
			new_entry("Unlock all shields", unlock_all_shields);
			new_entry("Unlock all suits", unlock_all_suits);
			new_entry("Unlock all bests", unlock_all_best);			
		new_spoiler("Story");
			new_entry("Unlock all stones", unlock_all_stones);
			new_entry("Unlock all medallions", unlock_all_medallions);
		exit_spoiler();
	exit_spoiler();
	new_spoiler("Fun");
		new_spoiler("Link's size");
			new_radio_entry("Giant Link", giant_link);
			new_radio_entry("Normal Link", normal_link);
			new_radio_entry("Mini Link", mini_link);
			new_radio_entry("Paper Link", paper_link);			
		exit_spoiler();
		new_radio_entry("Always have child voice", always_child_link_voice);
		index = new_radio_entry("Always have adult voice", always_adult_link_voice);
	exit_spoiler();
	for (i = 2; i <= index; i++)
		set_note(notes[i - 2], i);
}
