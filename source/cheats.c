#include "global.h"
#include "configs.h"
#include "cheats.h"

extern	enum language	langue;
extern	enum MENU		current_menu;
extern	t_menu			menu[8];
extern	u16				mode;
extern	unsigned int	after;

void	max_heart()
{
	WRITEU16(0x058799A, 0x140);
}

void	max_magic()
{
	WRITEU8(0x05879A8, 0x00000001);
	WRITEU8(0x058799F, 0x00000060);
}

void	refill_heart()
{
	WRITEU16(0x058799C, 0x140);
}

void	refill_large_magicbar()
{
	WRITEU8(0x058799F, 0x60);
}

void	infinite_arrows()
{
	WRITEU8(0x0587A01, 0x63);
}

void	infinite_nuts()
{
	WRITEU8(0x05879FF, 0x63);
}

void	infinite_stick()
{
	WRITEU8(0x05879FE, 0x63);
}

void	infinite_bomb()
{
	WRITEU8(0x0587A00, 0x63);
	WRITEU8(0x08001AB4, 0x63);
}

void	infinite_bombchu()
{
	WRITEU8(0x0587A06, 0x63);
	WRITEU8(0x08001AD0, 0x63);
}

void	infinite_slingshot()
{
	WRITEU8(0x0587A04, 0x63);
}

void	skulltulas()
{
	WRITEU8(0x0587A40, 0x64);
	WRITEU8(0x05c2280, 0x64);
}

void	max_rupees()
{
	WRITEU16(0x05879A0, 0x3E7);
}

void	sunrise()
{
	WRITEU16(0x0587964, 0x8001);
}

void	daytime()
{
	WRITEU16(0x0587964, 0x680E);
}

void	sunset()
{
	WRITEU16(0x0587964, 0xC001);
}

void	night()
{
	WRITEU16(0x0587964, 0x0000);
}

void	unlock_large_mb()
{
	WRITEU8(0x05879A8, 0x01);
}

void	unlock_magic()
{
	WRITEU8(0x05879A6, 0x60);
}

void	unlock_heartpieces()
{
	WRITEU8(0x0587A17, 0x30);
}

void	unlock_enhanced_defense()
{
	WRITEU8(0x005879A9, 0x1);
}

void	unlock_all_swords()
{
	u32 backup = READU8(0x00587A0E);
	backup = backup & 0xf0;
	backup = backup | 0x7;
	WRITEU8(0x00587A0E, backup);
}

void	trigger_swords(int x)
{
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

void	unlock_all_shields()
{
	u32 backup = READU8(0x00587A0E);
	backup = backup & 0xf;
	backup = backup | 0x70;
	WRITEU8(0x00587A0E, backup);
}

void	unlock_all_suits()
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

void	unlock_all_stones()
{
	// 0x04 pierre foret
	// 0x08 pierre feu
	// 0x10 pierre eau
	// 0x20 pierre souffrrance	
	// 0x40 gerudo token
	// 
	WRITEU8(0x0587A16, 0x7C);
}

void	unlock_all_best()
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

void	unlock_all_medallions()
{
	WRITEU8(0x0587A14, 0x3F);
}

void	giant_link()
{
	u32	pointer = READU32(0x087B18E8) + 0x64;
	WRITEU32(pointer, 0x3CA3D70A);
	WRITEU32(pointer + 4, 0x3CA3D70A);
	WRITEU32(pointer + 8, 0x3CA3D70A);
}

void	normal_link()
{
	u32	pointer = READU32(0x087B18E8) + 0x64;
	WRITEU32(pointer, 0x3C23D70A);
	WRITEU32(pointer + 4, 0x3C23D70A);
	WRITEU32(pointer + 8, 0x3C23D70A);
}

void	mini_link()
{
	u32	pointer = READU32(0x087B18E8) + 0x64;
	WRITEU32(pointer, 0x3B23D70A);
	WRITEU32(pointer + 4, 0x3B23D70A);
	WRITEU32(pointer + 8, 0x3B23D70A);
}

void	paper_link()
{
	u32	pointer = READU32(0x087B18E8) + 0x64;
	WRITEU32(pointer, 0x3AD3D70A);
}

void	moon_jump()
{
	u32	pointer = READU32(0x087B18E8) + 0x77;
	WRITEU16(pointer, 0xCB40);
}

void	move_fast()
{
	u32	pointer = READU32(0x087B18E8) + 0x222C;
	WRITEU32(pointer, 0x41A00000);
}

void	collect_heart()
{
	WRITEU16(0x08720A84, 0x000000000);
}

void	open_chest()
{
	WRITEU32(0x08720A78, 0x000000000);
}

void	spin_attack()
{
	u32	pointer = READU32(0x087B18E8) + 0x2252;
	WRITEU16(pointer, 0x3F80);
}

void	sword_glitch()
{
	u32	pointer = READU32(0x087B18E8) + 0x2237;
	WRITEU8(pointer, 0x01);
}

void	stick_fire()
{
	u32	pointer = READU32(0x087B18E8) + 0x2258;
	WRITEU8(pointer, 0xFF);
}

void	epona_max_carrots(void)
{
	u32	pointer = READU32(0x087B18E8) + 0x134;
	WRITEU8(pointer, 0x5);
}

void	all_items()
{

}