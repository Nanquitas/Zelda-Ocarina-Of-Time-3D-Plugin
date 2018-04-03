#include "types.h"
#include "cheats.hpp"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

	static u32	g_basePointer = 0x005A2E3C;

	void	MaxHeart(MenuEntry *entry)
	{
		Process::Write16(0x058799A, 0x140);
	}

	void	MaxMagic(MenuEntry *entry)
	{
		Process::Write8(0x05879A8, 0x00000001);
		Process::Write8(0x058799F, 0x00000060);
	}

	void	RefillHeart(MenuEntry *entry)
	{
		if (Touch::IsDown())
			Process::Write16(0x058799C, 0x140);
	}

	void	RefillLargeMagicbar(MenuEntry *entry)
	{
		if (Touch::IsDown())
		{
            u8  value;
            if (Process::Read8(0x05879A8, value))
            {
                Process::Write8(0x058799F, value ? 0x60 : 0x30);
            }
		}
	}

	void	InfiniteArrows(MenuEntry *entry)
	{
		Process::Write8(0x0587A01, 0x63);
	}

	void	InfiniteNuts(MenuEntry *entry)
	{
		Process::Write8(0x05879FF, 0x63);
	}

	void	InfiniteStick(MenuEntry *entry)
	{
		Process::Write8(0x05879FE, 0x63);
	}

	void	InfiniteBomb(MenuEntry *entry)
	{
		Process::Write8(0x0587A00, 0x63);
		Process::Write8(0x08001AB4, 0x63);
	}

	void	InfiniteBombchu(MenuEntry *entry)
	{
		Process::Write8(0x0587A06, 0x63);
		Process::Write8(0x08001AD0, 0x63);
	}

	void	InfiniteSlingshot(MenuEntry *entry)
	{
		Process::Write8(0x0587A04, 0x63);
	}

	void	Skulltulas(MenuEntry *entry)
	{
		Process::Write8(0x0587A40, 0x64);
		Process::Write8(0x05c2280, 0x64);
	}

	void	MaxRupees(MenuEntry *entry)
	{
		Process::Write16(0x05879A0, 0x3E7);
	}

	void	Sunrise(MenuEntry *entry)
	{
		if (entry->Hotkeys[0].IsDown())
			Process::Write16(0x0587964, 0x8001);
	}

	void	Daytime(MenuEntry *entry)
	{
        if (entry->Hotkeys[0].IsDown())
			Process::Write16(0x0587964, 0x680E);
	}

	void	Sunset(MenuEntry *entry)
	{
        if (entry->Hotkeys[0].IsDown())
			Process::Write16(0x0587964, 0xC001);
	}

	void	Night(MenuEntry *entry)
	{
        if (entry->Hotkeys[0].IsDown())
			Process::Write16(0x0587964, 0x0000);
	}

	void	UnlockLargeMb(MenuEntry *entry)
	{
		Process::Write8(0x05879A8, 0x01);
	}

	void	UnlockMagic(MenuEntry *entry)
	{
		Process::Write8(0x05879A6, 0x60);
	}

	void	UnlockHeartpieces(MenuEntry *entry)
	{
		Process::Write8(0x0587A17, 0x30);
	}

	void	UnlockEnhancedDefense(MenuEntry *entry)
	{
		Process::Write8(0x005879A9, 0x1);
	}

	void	UnlockAllSwords(MenuEntry *entry)
	{
        u8 backup;

	    if (Process::Read8(0x00587A0E, backup))
	    {
            backup = backup & 0xf0;
            backup = backup | 0x7;
            Process::Write8(0x00587A0E, backup);
	    }
	}

	void	TriggerSwords(int x)
	{
        u8 backup;

        if (Process::Read8(0x00587A0E, backup))
        {
            if (x == 0)
                backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b111);
            if (x == 1)
                backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b1);
            if (x == 2)
                backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b10);
            if (x == 3)
                backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b100);
            Process::Write8(0x00587A0E, backup);
        }
	}

	void	TriggerShields(int x)
	{
        u8 backup;

	    if (Process::Read8(0x00587A0E, backup))
	    {
            if (x == 0)
                backup = (backup & 0x0f) | ((backup & 0xf0) ^ (0b111 << 4));
            if (x == 1)
                backup = (backup & 0x0f) | ((backup & 0xf0) ^ (0b1 << 4));
            if (x == 2)
                backup = (backup & 0x0f) | ((backup & 0xf0) ^ (0b10 << 4));
            if (x == 3)
                backup = (backup & 0x0f) | ((backup & 0xf0) ^ (0b100 << 4));
            Process::Write8(0x00587A0E, backup);
	    }
	}

	void	UnlockAllShields(MenuEntry *entry)
	{
        u8 backup;

	    if (Process::Read8(0x00587A0E, backup))
	    {
            backup = backup & 0xf;
            backup = backup | 0x70;
            Process::Write8(0x00587A0E, backup);
	    }
	}

	void	UnlockAllSuits(MenuEntry *entry)
	{
		Process::Write8(0x0587A0F, 0x7);
	}

	void	TriggerSuits(int x)
	{
        u8 backup;

	    if (Process::Read8(0x00587A0F, backup))
	    {
            if (x == 0)
                backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b111);
            if (x == 1)
                backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b1);
            if (x == 2)
                backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b10);
            if (x == 3)
                backup = (backup & 0xf0) | ((backup & 0xf) ^ 0b100);
            Process::Write8(0x00587A0F, backup);
	    }
	}

	void	UnlockAllStones(MenuEntry *entry)
	{
		// 0x04 forest stone
		// 0x08 fire stone
		// 0x10 water stone
		// 0x20 suffering stone ?
		// 0x40 gerudo token
		//
		Process::Write8(0x0587A16, 0x7C);
	}

	void	UnlockAllBest(MenuEntry *entry)
	{
		// 0x587A11 :
		//				0x40 30x seedbag,
		//				0x80 40x seed bag,
		//				0xC0 50x seedbag,
		//				0x02 silver Zora scale,
		//				0x04 gold Zora scale,
		//				0x06 Broken Biggoron,
		//
		Process::Write32(0x0587A10, 0x184D8);
	}

	void	UnlockAllMedallions(MenuEntry *entry)
	{
		Process::Write8(0x0587A14, 0x3F);
	}

	void	GiantLink(MenuEntry *entry)
	{
        u32	pointer;

	    if (Process::Read32(g_basePointer, pointer))
        {
            if (!pointer)
                return;
            pointer += 0x64;
            Process::Write32(pointer, 0x3CA3D70A);
            Process::Write32(pointer + 4, 0x3CA3D70A);
            Process::Write32(pointer + 8, 0x3CA3D70A);
	    }
	}

	void	NormalLink(MenuEntry *entry)
	{
        u32	pointer;

	    if (Process::Read32(g_basePointer, pointer))
	    {
            if (!pointer)
                return;
            pointer += 0x64;
            Process::Write32(pointer, 0x3C23D70A);
            Process::Write32(pointer + 4, 0x3C23D70A);
            Process::Write32(pointer + 8, 0x3C23D70A);
	    }
	}

	void 	MiniLink(MenuEntry *entry)
	{
        u32	pointer;

        if (Process::Read32(g_basePointer, pointer))
        {
            if (!pointer)
                return;
            pointer += 0x64;
            Process::Write32(pointer, 0x3B23D70A);
            Process::Write32(pointer + 4, 0x3B23D70A);
            Process::Write32(pointer + 8, 0x3B23D70A);
        }
	}

	void	PaperLink(MenuEntry *entry)
	{
        u32	pointer;

	    if (Process::Read32(g_basePointer, pointer))
	    {
            if (!pointer)
                return;
            pointer += 0x64;
            Process::Write32(pointer, 0x3AD3D70A);
	    }
	}

	void	MoonJump(MenuEntry *entry)
	{
        u32	pointer;

	    if (Process::Read32(g_basePointer, pointer))
	    {
            if (!pointer)
                return;
            pointer += 0x77;
            if (entry->Hotkeys[0].IsDown())
                Process::Write16(pointer, 0xCB40);
	    }
	}

	void	MoveFast(MenuEntry *entry)
	{
        u32	pointer;

	    if (Process::Read32(g_basePointer, pointer))
	    {
            if (!pointer)
                return;

            static u32 jump = 0;

            u32  jumpPointer = pointer + 0x77;
            pointer += 0x222C;

            if (Controller::IsKeyDown(Key::CPad) && entry->Hotkeys[0].IsDown())
            {
                if (jump < 3)
                {
                    Process::Write16(jumpPointer, 0xCB40);
                    jump++;
                }
                else
                    Process::Write32(pointer, 0x41A00000);
            }
            else
                jump = 0;
	    }
	}

	void	CollectHeart(MenuEntry *entry)
	{
		Process::Write16(0x08720A84, 0x000000000);
	}

	void	OpenChest(MenuEntry *entry)
	{
		Process::Write32(0x08720A78, 0x000000000);
	}

	void	SpinAttack(MenuEntry *entry)
	{
        u32	pointer;

	    if (Process::Read32(g_basePointer, pointer))
	    {
            if (!pointer)
                return;
            pointer += 0x2252;
            Process::Write16(pointer, 0x3F80);
	    }
	}

	void	SwordGlitch(MenuEntry *entry)
	{
        u32	pointer;

	    if (Process::Read32(g_basePointer, pointer))
	    {
            if (!pointer)
                return;
            pointer += 0x2237;
            Process::Write8(pointer, 0x01);
	    }
	}

	void	StickFire(MenuEntry *entry)
	{
        u32	pointer;

	    if (Process::Read32(g_basePointer, pointer))
	    {
            if (!pointer)
                return;
            pointer += 0x2258;
            Process::Write8(pointer, 0xFF);
	    }
	}

	void	EponaMaxCarrots(MenuEntry *entry)
	{
        u32	pointer;

	    if (Process::Read32(g_basePointer, pointer))
	    {
            if (!pointer)
                return;
            pointer += 0x134;
            Process::Write8(pointer, 0x5);
	    }
	}

    void	EponaInfiniteCarrotsAllAreas(MenuEntry *entry)
    {
        u32	offset;

        if (Process::Read32(g_basePointer, offset))
        {
            if (!offset)
                return;

            offset += 0x134;
            if (Process::Read32(offset, offset) && offset)
            {
                Process::Write8(0xE9C + offset, 5);
            }
        }
    }

	void	UnlockKokiriSword(MenuEntry *entry)
	{
		if (entry->IsActivated())
		{
            TriggerSwords(1);
            entry->Disable();
		}

	}

	void	UnlockExcaliburSword(MenuEntry *entry)
	{
        if (entry->IsActivated())
        {
            TriggerSwords(2);
            entry->Disable();
        }
	}

	void 	UnlockBiggoronSword(MenuEntry *entry)
	{
        if (entry->IsActivated())
        {
            TriggerSwords(3);
            entry->Disable();
        }
	}

	void	UnlockWoodShield(MenuEntry *entry)
	{
        if (entry->IsActivated())
        {
            TriggerShields(1);
            entry->Disable();
        }
	}

	void	UnlockHyruleShield(MenuEntry *entry)
	{
        if (entry->IsActivated())
        {
            TriggerShields(2);
            entry->Disable();
        }
	}

	void	UnlockMirrorShield(MenuEntry *entry)
	{
        if (entry->IsActivated())
        {
            TriggerShields(3);
            entry->Disable();
        }
	}

	void	UnlockKokiriSuits(MenuEntry *entry)
	{
        if (entry->IsActivated())
        {
            TriggerSuits(1);
            entry->Disable();
        }
	}

	void	UnlockZoraSuits(MenuEntry *entry)
	{
        if (entry->IsActivated())
        {
            TriggerSuits(3);
            entry->Disable();
        }
	}

	void	UnlockGoronSuits(MenuEntry *entry)
	{
        if (entry->IsActivated())
        {
            TriggerSuits(2);
            entry->Disable();
        }
	}


	void	AlwaysAdultLinkVoice(MenuEntry *entry)
	{
		Process::Write32(0x098F671C, 0x0053A2F0);
	}

	void	AlwaysChildLinkVoice(MenuEntry *entry)
	{
		Process::Write32(0x098F671C, 0x0053A424);
	}

	void	InfiniteSmallKeysAllDungeons(MenuEntry *entry)
	{
		for (int i = 0; i < 0x10; i++)
		{
			Process::Write32(0x00587A2C + i, 0x09090909);
		}
	}

	void	HaveMapCompassAndBossKeyAllDungeon(MenuEntry *entry)
	{
		for (int i = 0; i < 6; i++)
		{
			Process::Write32(0x00587A18 + i, 0x07070707);
		}
	}

	void	EponaMoonJump(MenuEntry *entry)
	{
		u32	offset;

        if (Process::Read32(g_basePointer, offset))
        {
            if (!offset)
                return;

            offset += 0x134;
            if (entry->Hotkeys[0].IsDown())
            {
                if (Process::Read32(offset, offset) && offset)
                {
                    Process::Write16(0x66 + offset, 0x4222);
                }
            }
        }
	}

	void	GiantsKnifeNeverBreaks(MenuEntry *entry)
	{
		Process::Write8(0x005879A2, 0xFF);
	}

	void	AlwaysRaining(MenuEntry *entry)
	{
		Process::Write8(0x08721AAF, 0xFF);
	}

	void	OpenAnyChestInTheGameAsManyTimes(MenuEntry *entry)
	{
		Process::Write32(0x08720A78, 0x00000000);
	}

	void	CollectHeartPiecesInOverworldAsMany(MenuEntry *entry)
	{
		Process::Write16(0x08720A84, 0);
	}

	void	AlwaysHaveNayrusLoveActivated(MenuEntry *entry)
	{
		Process::Write16(0x00588EAA, 0x0000FFFF);
	}

    void	NeverTakeDamageFromFalling(MenuEntry *entry)
	{
		Process::Write32(0x098F7290, 0x00000000);
	}

    void 	UseAllItems(MenuEntry *entry)
    {
        if (!entry->IsActivated())
            return;

        for (int i = 0; i < 0x56; i++)
        {
            Process::Write8(0x506C58 + i, 0x09);
        }

        entry->Disable();
    }

    void	UnlockAllItems(MenuEntry *entry)
    {
        if (!entry->IsActivated())
            return;

        static u8 buffer[] =
        {
            0x00, 0x01, 0x02,
            0x03, 0x04, 0x05,
            0x06, 0x08, 0x09,
            0x0B, 0x0C, 0x0D,
            0x0E, 0x0F, 0x10,
            0x11, 0x12, 0x13,
            0x18, 0x18, 0x18,
            0x18, 0x37, 0x2B,
            0x45, 0x46, 0x1E,
            0x28, 0x28, 0x32
        };

        Process::CopyMemory((void *)0x5879E4, buffer, 0x1E);

        entry->Disable();

    }

    void	TimeModifier(MenuEntry *entry)
    {
        static Clock timer;

        Time delta = timer.Restart();

        if (entry->Hotkeys[0].IsDown())
            *(u16 *)(0x0587964) += (u16)(delta.AsSeconds() * 0x20);
        if (entry->Hotkeys[1].IsDown())
            *(u16 *)(0x0587964) -= (u16)(delta.AsSeconds() * 0x20);
    }

    void    InfiniteExplosives(MenuEntry *entry)
    {
        u32 offset;

        if (Process::Read32(0xFFFE538, offset) && offset != 0)
        {
            Process::Write8(offset + 0x910, 0x0);
        }
    }

    inline void	ColoredGaunlet(u8 value)
    {
        Process::Write16(0x587A10, 0xE500 + value);
    }

    void	PurpleGauntlet(MenuEntry *entry)
    {
        ColoredGaunlet(0x1B);
    }

    void    GreenGauntlet(MenuEntry *entry)
    {
        ColoredGaunlet(0x5B);
    }

    void	BlueGauntlet(MenuEntry *entry)
    {
        ColoredGaunlet(0x9B);
    }

    void	BlackGauntlet(MenuEntry *entry)
    {
        ColoredGaunlet(0xDB);
    }

    struct Item
	{
        const char  *name;
        const u8    id;
	};

    static const std::vector<Item> g_items =
    {
        { "Deku Stick", 0x00 },
        { "Deku Nut", 0x01 },
        { "Bomb", 0x02 },
        { "Fairy Bow", 0x03 },
        { "Fire Arrow", 0x04 },
        { "Din's Fire", 0x05 },
        { "Fairy Slingshot", 0x06 },
        { "Fairy Ocarina", 0x07 },
        { "Ocarina of Time", 0x08 },
        { "Bombchu", 0x09 },
        { "Hookshot", 0x0A },
        { "Longshot", 0x0B },
        { "Ice Arrow", 0x0C },
        { "Farore's Wind", 0x0D },
        { "Boomerang", 0x0E },
        { "Lens of Truth", 0x0F },
        { "Magic Beans", 0x10 },
        { "Megaton Hammer", 0x11 },
        { "Light Arrow", 0x12 },
        { "Nayru's Love", 0x13 },
        //{ "Empty Bottle", 0x14 }, From 0x15 to 0x20 check BottleManager
        { "Weird Egg", 0x21 },
        { "Cucco", 0x22 },
        { "Zelda's Letter", 0x23 },
        { "Keaton Mask", 0x24 },
        { "Skull Mask", 0x25 },
        { "Spooky Mask", 0x26 },
        { "Bunny Hood", 0x27 },
        { "Goron Mask", 0x28 },
        { "Zora Mask", 0x29 },
        { "Gerudo Mask", 0x2A },
        { "Mask of Truth", 0x2B },
        { "No Mask", 0x2C },
        { "Pocket Egg", 0x2D },
        { "Pocket Cucco", 0x2E },
        { "Cojiro", 0x2F },
        { "Odd Mushroom", 0x30 },
        { "Odd Poultice", 0x31 },
        { "Poacher's Saw", 0x32 },
        { "Broken Goron Sword", 0x33 },
        { "Prescription", 0x34 },
        { "Eyeball Frog", 0x35 },
        { "World Finest Eyedrops", 0x36 },
        { "Claim Check", 0x37 },
        { "Fairy Bow (Fire)", 0x38 },
        { "Fairy Bow (Ice)", 0x39 },
        { "Fairy Bow (Light)", 0x3A },
        { "Kokiri Sword", 0x3B },
        { "Master Sword", 0x3C },
        { "Giant's Knife", 0x3D },
        { "Deku Shield", 0x3E },
        { "Hylian Shield", 0x3F },
        { "Mirror Shield", 0x40 },
        { "Kokiri Tunic", 0x41 },
        { "Goron Tunic", 0x42 },
        { "Zora Tunic", 0x43 },
        { "Iron Boots", 0x45 },
        { "Biggoron's Sword", 0x7C },
        // { "Key, What's that", 0xA0, 0xA8, 0xAA },
        // { "Empty bottle, What's that", 0xA1 - 0xA4, 0xA6, 0xA9, 0xAB, 0xAC },
        // { "Rupee bag, What's that", 0xA5, 0xA7, },
        // { "Bottle with soul, What's that", 0xAD, 0xAF },
        // { "Bottle with bug, What's that", 0xAE },
        // { "Key, What's that", 0xA0 },
        { "Empty", 0xFF }
    };
    void	InventoryModifier(MenuEntry *entry)
    {
        static StringVector items;

        if (items.empty())
            for (const Item &i : g_items)
                items.push_back(i.name);

        Keyboard    keyboard("Inventory modifier\n\nSelect which item you'd like to have", items);
        int         choice = keyboard.Open();

        if (choice >= 0)
            Process::Write8(0x5879F8, g_items[choice].id);
    }

    void    Invincible(MenuEntry *entry)
    {
        static u32 original[4] = {0};

        if (entry->WasJustActivated())
        {
            if (original[0] == 0)
            {
                Process::Read32(0x0035D398, original[0]);
                Process::Read32(0x0035D3A8, original[1]);
                Process::Read32(0x00352E24, original[2]);
                Process::Read32(0x00352E28, original[3]);
            }

            Process::Write32(0x0035D398, 0xE3A00000);
            Process::Write32(0x0035D3A8, 0xEA000000);
            Process::Write32(0x00352E24, 0xE1D504B2);
            Process::Write32(0x00352E28, 0xE1A00000);
        }

        if (!entry->IsActivated())
        {
            if (original[0] && original[1])
            {
                Process::Write32(0x0035D398, original[0]);
                Process::Write32(0x0035D3A8, original[1]);
                Process::Write32(0x00352E24, original[2]);
                Process::Write32(0x00352E28, original[3]);
            }
        }
    }

    void    UnlockAllBottles(MenuEntry *entry)
    {
        Process::Write16(0x005879F6, 0x1414);
        Process::Write8(0x005879F8, 0x14);
        entry->Disable();
    }
}
