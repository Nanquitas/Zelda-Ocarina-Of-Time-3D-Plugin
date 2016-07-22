#include "cheats.h"
#include "hid.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

char	*builder_name = "Nanquitas";


static u32	base_pointer = 0x005A2E3C;

void	max_heart(void)
{
	WRITEU16(0x058799A, 0x140);
}

void	max_magic(void)
{
	
	WRITEU8(0x05879A8, 0x00000001);
	WRITEU8(0x058799F, 0x00000060);
}

void	refill_heart(void)
{
	if (upper_left_touched() || upper_right_touched())
		WRITEU16(0x058799C, 0x140);
}

void	refill_large_magicbar(void)
{
	if (lower_left_touched() || lower_right_touched())
		if (READU8(0x05879A8) == 1)
			WRITEU8(0x058799F, 0x60);
		else
			WRITEU8(0x058799F, 0x30);
}

void	infinite_arrows(void)
{
	WRITEU8(0x0587A01, 0x63);
}

void	infinite_nuts(void)
{
	WRITEU8(0x05879FF, 0x63);
}

void	infinite_stick(void)
{
	WRITEU8(0x05879FE, 0x63);
}

void	infinite_bomb(void)
{
	WRITEU8(0x0587A00, 0x63);
	WRITEU8(0x08001AB4, 0x63);
}

void	infinite_bombchu(void)
{
	WRITEU8(0x0587A06, 0x63);
	WRITEU8(0x08001AD0, 0x63);
}

void	infinite_slingshot(void)
{
	WRITEU8(0x0587A04, 0x63);
}

void	skulltulas(void)
{
	WRITEU8(0x0587A40, 0x64);
	WRITEU8(0x05c2280, 0x64);
}

void	max_rupees(void)
{
	WRITEU16(0x05879A0, 0x3E7);
}

void	sunrise(void)
{
	if (is_pressed(R + DL))
		WRITEU16(0x0587964, 0x8001);
}

void	daytime(void)
{
	if (is_pressed(R + DU))
		WRITEU16(0x0587964, 0x680E);
}

void	sunset(void)
{
	if (is_pressed(R + DR))
		WRITEU16(0x0587964, 0xC001);
}

void	night(void)
{
	if (is_pressed(R + DD))
		WRITEU16(0x0587964, 0x0000);
}

void	unlock_large_mb(void)
{
	WRITEU8(0x05879A8, 0x01);
}

void	unlock_magic(void)
{
	WRITEU8(0x05879A6, 0x60);
}

void	unlock_heartpieces(void)
{
	WRITEU8(0x0587A17, 0x30);
}

void	unlock_enhanced_defense(void)
{
	WRITEU8(0x005879A9, 0x1);
}

void	unlock_all_swords(void)
{
	new_log(INFO, "all_swords | before: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(READU8(0x00587A0E)));
	u32 backup = READU8(0x00587A0E);
	backup = backup & 0xf0;
	backup = backup | 0x7;
	WRITEU8(0x00587A0E, backup);
	new_log(DEBUG, "all_swords | after: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(READU8(0x00587A0E)));
}

void	trigger_swords(int x)
{
	new_log(INFO, "trigger_swords | before: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(READU8(0x00587A0E)));
	u32 backup = READU8(0x00587A0E);
	if(x == 0)
		backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b111);
	if(x == 1)
		backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b1);
	if(x == 2)
		backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b10);
	if(x == 3)
		backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b100);
	WRITEU8(0x00587A0E, backup);
	new_log(INFO, "trigger_swords | after: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(READU8(0x00587A0E)));
}

void	trigger_shields(int x)
{
	u32 backup = READU8(0x00587A0E);
	if(x == 0)
		backup = (backup & 0x0f) | ((backup & 0xf0) ^ (0b111 << 4));
	if(x == 1)
		backup = (backup & 0x0f) | ((backup & 0xf0) ^ ( 0b1 << 4));
	if(x == 2)
		backup = (backup & 0x0f) | ((backup & 0xf0) ^ ( 0b10 << 4));
	if(x == 3)
		backup = (backup & 0x0f) | ((backup & 0xf0) ^ ( 0b100 << 4));
	WRITEU8(0x00587A0E, backup);
}

void	unlock_all_shields(void)
{
	u32 backup = READU8(0x00587A0E);
	backup = backup & 0xf;
	backup = backup | 0x70;
	WRITEU8(0x00587A0E, backup);
}

void	unlock_all_suits(void)
{
	WRITEU8(0x0587A0F, 0x7);
}

void	trigger_suits(int x)
{
	u32 backup = READU8(0x00587A0F);
	if(x == 0)
		backup = (backup & 0xf0)| ((backup & 0xf) ^ 0b111);
	if(x == 1)
		backup = (backup & 0xf0)| ((backup & 0xf) ^ 0b1);
	if(x == 2)
		backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b10);
	if(x == 3)
		backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b100);
	WRITEU8(0x00587A0F, backup);
}

void	unlock_all_stones(void)
{
	// 0x04 pierre foret
	// 0x08 pierre feu
	// 0x10 pierre eau
	// 0x20 pierre souffrrance	
	// 0x40 gerudo token
	// 
	WRITEU8(0x0587A16, 0x7C);
}

void	unlock_all_best(void)
{
	// 0x587A11 : 
	//				0x40 30x seedbag, 
	//				0x80 40x seed bag, 
	//				0xC0 50x seedbag,
	//				0x02 silver Zora scale, 
	//				0x04 gold Zora scale, 
	//				0x06 Broken Biggoron,
	//
	WRITEU32(0x0587A10, 0x184D8);
}

void	unlock_all_medallions(void)
{
	WRITEU8(0x0587A14, 0x3F);
}

void	giant_link(void)
{
	u32	pointer = READU32(base_pointer);

	if (pointer == 0)
		return;
	pointer += 0x64;
	WRITEU32(pointer, 0x3CA3D70A);
	WRITEU32(pointer + 4, 0x3CA3D70A);
	WRITEU32(pointer + 8, 0x3CA3D70A);
}

void	normal_link(void)
{
	u32	pointer = READU32(base_pointer);

	if (pointer == 0)
		return;
	pointer += 0x64;
	WRITEU32(pointer, 0x3C23D70A);
	WRITEU32(pointer + 4, 0x3C23D70A);
	WRITEU32(pointer + 8, 0x3C23D70A);
}

void	mini_link(void)
{
	u32	pointer = READU32(base_pointer);

	if (pointer == 0)
		return;
	pointer += 0x64;
	WRITEU32(pointer, 0x3B23D70A);
	WRITEU32(pointer + 4, 0x3B23D70A);
	WRITEU32(pointer + 8, 0x3B23D70A);
}

void	paper_link(void)
{
	u32	pointer = READU32(base_pointer);

	if (pointer == 0)
		return;
	pointer += 0x64;
	WRITEU32(pointer, 0x3AD3D70A);
}

void	moon_jump(void)
{
	u32	pointer = READU32(base_pointer);
	static u32 active = 1;

	if (pointer == 0)
		return;
	pointer += 0x77;	
	if (is_pressed(DR))
	{
		active = !active;
		wait_keys_released(DR);
	}
	if (active && is_pressed(A))
		WRITEU16(pointer, 0xCB40);
	
}

void	move_fast(void)
{
	u32	pointer = READU32(base_pointer);
	u32 jump_pointer;
	static u32 active = 1;
	static u32 jump = 0;
	
	if (pointer == 0)
		return;
	jump_pointer = pointer + 0x77;
	pointer += 0x222C;
	if (is_pressed(DL))
	{
		active = !active;
		wait_keys_released(DL);
	}
	if (active && any_is_pressed(KEY_CPAD) && is_pressed(X))
	{
		if (jump < 3)
		{
			WRITEU16(jump_pointer, 0xCB40);
			WRITEU16(jump_pointer, 0xCB40);
			jump++;
		}
		else
			WRITEU32(pointer, 0x41A00000);
	}
	else
		jump = 0;
}

void	collect_heart(void)
{
	WRITEU16(0x08720A84, 0x000000000);
}

void	open_chest(void)
{
	WRITEU32(0x08720A78, 0x000000000);
}

void	spin_attack(void)
{
	u32	pointer = READU32(base_pointer);
	
	if (pointer == 0)
		return;
	pointer += 0x2252;
	//new_log(DEBUG, "spin_attack | base_pointer = %08X", base_pointer);
	WRITEU16(pointer, 0x3F80);
}

void	sword_glitch(void)
{
	u32	pointer = READU32(base_pointer);

	if (pointer == 0)
		return;
	pointer += 0x2237;
	WRITEU8(pointer, 0x01);
}

void	stick_fire(void)
{
	u32	pointer = READU32(base_pointer);

	if (pointer == 0)
		return;
	pointer += 0x2258;
	WRITEU8(pointer, 0xFF);
}

void	epona_max_carrots(void)
{
	u32	pointer = READU32(base_pointer);
	
	if (pointer == 0)
		return;
	pointer += 0x134;
	WRITEU8(pointer, 0x5);
}


void	unlock_kokiri_sword()
{
	trigger_swords(1);
	disableCheat(33);
}

void	unlock_excalibur_sword()
{
	trigger_swords(2);
	disableCheat(34);
}

void	unlock_biggoron_sword()
{
	trigger_swords(3);
	disableCheat(35);
}

void	unlock_wood_shield()
{
	trigger_shields(1);
	disableCheat(36);
}

void	unlock_hyrule_shield()
{
	trigger_shields(2);
	disableCheat(37);
}

void	unlock_mirror_shield()
{
	trigger_shields(3);
	disableCheat(38);
}

void	unlock_kokiri_suits()
{
	trigger_suits(1);
	disableCheat(39);
}

void	unlock_zora_suits()
{
	trigger_suits(3);
	disableCheat(41);
}

void	unlock_goron_suits()
{
	trigger_suits(2);
	disableCheat(40);
}


void	always_adult_link_voice(void)
{
	WRITEU32(0x098F671C, 0x0053A2F0);
}

void	always_child_link_voice(void)
{
	WRITEU32(0x098F671C, 0x0053A424);
}

void	infinite_small_keys_all_dungeons(void)
{
	for (int i = 0; i < 0x00000010; i++)
	{
		WRITEU32(0x00587A2C + i, 0x09090909);
	}
}

void	have_map_compass_and_boss_key_all_dunge(void)
{
	for (int i = 0; i < 0x00000006; i++)
	{
		WRITEU32(0x00587A18 + i, 0x07070707);
	}
}

void	epona_moon_jump(void)
{
	u32	offset;

	offset = READU32(base_pointer);
	if (offset == 0)
		return;
	offset += 0x134;
	if (is_pressed( BUTTON_A + BUTTON_X ))
	{
		if ( 0x00000000 != READU32(offset))
		{
			offset = READU32(offset);
			WRITEU16(0x00000066 + offset, 0x00004222 & 0xFFFF);
		}
	}
}

void	epona_infinite_carrots_all_areas(void)
{
	u32	offset;

	offset = READU32(base_pointer);
	if (offset == 0)
		return;
	offset += 0x134;
	if ( 0x00000000 != READU32(offset))
	{
		offset = READU32(offset);
		WRITEU8(0x00000E9C + offset, 0x00000005 & 0xFF);
	}
}

void	giants_knife_never_breaks(void)
{
	WRITEU8(0x005879A2, 0x000000FF & 0xFF);
}

void	always_raining(void)
{
	WRITEU8(0x08721AAF, 0x000000FF & 0xFF);
}

void	open_any_chest_in_the_game_as_many_times(void)
{
	WRITEU32(0x08720A78, 0x00000000);
}

void	collect_heart_pieces_in_overworld_as_many(void)
{
	WRITEU16(0x08720A84, 0x00000000 & 0xFFFF);
}

void	always_have_nayrus_love_activated(void)
{
	WRITEU16(0x00588EAA, 0x0000FFFF & 0xFFFF);
}

void	never_take_damage_from_falling(void)
{
	WRITEU32(0x098F7290, 0x00000000);
}
