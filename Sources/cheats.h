#ifndef CHEATS_H
#define CHEATS_H

#include "plugin.h"


#define		ADD16(addr, value)					*(u16 *)addr += value
#define		SUB16(addr, value)					*(u16 *)addr -= value

void	unlock_kokiri_sword();
void	unlock_excalibur_sword();
void	unlock_biggoron_sword();
void	unlock_wood_shield();
void	unlock_hyrule_shield();
void	unlock_mirror_shield();
void	unlock_kokiri_suits();
void	unlock_zora_suits();
void	unlock_goron_suits();

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

void	always_adult_link_voice(void);
void	always_child_link_voice(void);
void	infinite_small_keys_all_dungeons(void);
void	have_map_compass_and_boss_key_all_dunge(void);
void	epona_moon_jump(void); //x + a
void	epona_infinite_carrots_all_areas(void);
void	giants_knife_never_breaks(void);
void	always_raining(void);
void	open_any_chest_in_the_game_as_many_times(void);
void	collect_heart_pieces_in_overworld_as_many(void);
void	always_have_nayrus_love_activated(void);
void	never_take_damage_from_falling(void);
void	use_all_items(void);
void	unlock_all_items(void);
void	timeMod(void);
void	infinite_explosives(void);
void	coloredGaunlet_common(u8 value);
void	purple_gaunlet(void);
void	green_gaunlet(void);
void	blue_gaunlet(void);
void	black_gaunlet(void);

#endif
