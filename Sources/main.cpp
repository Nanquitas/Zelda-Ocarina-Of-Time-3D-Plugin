#include "cheats.hpp"
#include "BottleManager.hpp"
#include "3DS.h"

namespace CTRPluginFramework
{
    // This function is called on the plugin starts, before main
    void    PatchProcess(FwkSettings &settings)
    {
    }

    #define MAJOR_VERSION       3
    #define MINOR_VERSION       3
    #define REVISION_VERSION    0
    #define STRINGIFY(x)        #x
    #define TOSTRING(x)         STRINGIFY(x)
    #define STRING_VERSION      "[" TOSTRING(MAJOR_VERSION) "." TOSTRING(MINOR_VERSION) "." TOSTRING(REVISION_VERSION) "]"

    const std::string about = u8"\n" \
        u8"Plugin for Zelda Ocarina Of Time    " STRING_VERSION "\n\n"
        u8"Most of these codes comes from Fort42 so a huge thanks to their original creator !!\n\n" \
        u8"GBATemp's release thread: goo.gl/Rz1uhj";

    static MenuEntry *AddArg(void *arg, MenuEntry *entry)
    {
        if(entry != nullptr)
            entry->SetArg(arg);
        return (entry);
    }

    static MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey)
    {
        if (entry != nullptr)
        {
            entry->Hotkeys += hotkey;
            entry->SetArg(new std::string(entry->Name()));
            entry->Name() += " " + hotkey.ToString();
            entry->Hotkeys.OnHotkeyChangeCallback([](MenuEntry *entry, int index)
            {
                std::string *name = reinterpret_cast<std::string *>(entry->GetArg());

                entry->Name() = *name + " " + entry->Hotkeys[0].ToString();
            });
        }

        return (entry);
    }

    static MenuEntry *EntryWithHotkey(MenuEntry *entry, const std::vector<Hotkey> &hotkeys)
    {
        if (entry != nullptr)
        {
            for (const Hotkey &hotkey : hotkeys)
                entry->Hotkeys += hotkey;
        }

        return (entry);
    }

    static void    CreateMenu(PluginMenu &menu)
    {
        std::string     note;

        /*
        ** Movements codes
        ********************/

        note = "Use \uE077 while pressing the hotkey(s) to move very fast.\n"
               << Color::Orange << "Be careful of the loading zone, it might put you out of bound.\n"
               << ResetColor() << "You can change the hotkey by touching the controller icon on the bottom screen.";

        menu += new MenuFolder("Movement", "",
        {
            EntryWithHotkey(new MenuEntry("MoonJump", MoonJump, "Press the hotkey to be free of the gravity."), Hotkey(Key::A, "Moonjump")),
            EntryWithHotkey(new MenuEntry("Fast Move \uE077 +", MoveFast, note), Hotkey(Key::L, "Run faster")),
            new MenuEntry("Epona have max carrots", EponaMaxCarrots),
            new MenuEntry("Epona have max carrots", EponaInfiniteCarrotsAllAreas),
            EntryWithHotkey(new MenuEntry("Epona MoonJump", EponaMoonJump, "Press the hotkey to be free of the gravity."), Hotkey(Key::L | Key::A, "Epona Moonjump"))
        });

        /*
        ** Battle codes
        ******************/

        menu += new MenuFolder("Battle", "Need some boosters for your fights ?",
        {
            new MenuEntry("Invincible", Invincible, "With this code you'll be invincible !"),
            new MenuEntry("Refill Heart (\uE058)", RefillHeart, "Running low on heart ?\nThen touch the screen to fill you in."),
            new MenuEntry("Refill Magic (\uE058)", RefillLargeMagicbar, "Running low on magic ?\nThen touch the screen to refill the magic bar."),
            new MenuEntry("Unlock Heart", MaxHeart),
            new MenuEntry("Unlock Magic", UnlockMagic),
            new MenuEntry("Unlock Large Magic", UnlockLargeMb),
            new MenuEntry("Spin Attack", SpinAttack),
            new MenuEntry("Sword Glitch", SwordGlitch),
            new MenuEntry("Sticks are in fire", StickFire)
        });

        /*
        ** Inventory codes
        *******************/

        MenuFolder *inventory = new MenuFolder("Inventory");
        {
            *inventory += new MenuFolder("Swords", "",
            {
                new MenuEntry("Unlock Kokiri Sword", UnlockKokiriSword),
                new MenuEntry("Unlock Excalibur Sword", UnlockExcaliburSword),
                new MenuEntry("Unlock Biggoron Sword", UnlockBiggoronSword),
                new MenuEntry("Unlock All Swords", UnlockAllSwords)
            });

            *inventory += new MenuFolder("Shield", "",
            {
                new MenuEntry("Unlock Wood Shield", UnlockWoodShield),
                new MenuEntry("Unlock Hyrule Shield", UnlockHyruleShield),
                new MenuEntry("Unlock Mirror Shield", UnlockMirrorShield),
                new MenuEntry("Unlock All Shields", UnlockAllShields)
            });

            *inventory += new MenuFolder("Suits", "",
            {
                new MenuEntry("Unlock Kokiri Suits", UnlockKokiriSuits),
                new MenuEntry("Unlock Zora Suits", UnlockZoraSuits),
                new MenuEntry("Unlock Goron Suits", UnlockGoronSuits),
                new MenuEntry("Unlock All Suits", UnlockAllSuits)
            });

            MenuFolder *items = new MenuFolder("Items");
            {
                std::string     name = " : " << Color::Red << " Read the note !";

                note = "Touch the keyboard icon to set the bottle's content then activate the entry.\n\n"
                    << Color::Red << "Warning:\n"
                    << Color::Orange
                    << "don't set the Locked value when the bottle is attributed to a key or it'll create a duplicate in your inventory and you'll lose an inventory slot.";

                *items += new MenuFolder("Bottles", "",
                {
                    AddArg(new Bottle(1, 0x005879F6), new MenuEntry("Bottle #1" + name, nullptr, BottleSettings, note)),
                    AddArg(new Bottle(2, 0x005879F7), new MenuEntry("Bottle #2" + name, nullptr, BottleSettings, note)),
                    AddArg(new Bottle(3, 0x005879F8), new MenuEntry("Bottle #3" + name, nullptr, BottleSettings, note))
                });

                *items += new MenuFolder("Gauntlet color editor", "",
                {
                    new MenuEntry(1, "Black Gauntlet", BlackGauntlet),
                    new MenuEntry(1, "Blue Gauntlet", BlueGauntlet),
                    new MenuEntry(1, "Green Gauntlet", GreenGauntlet),
                    new MenuEntry(1, "Purple Gauntlet", PurpleGauntlet)
                });

                *items += new MenuEntry("Infinite Arrows", InfiniteArrows);
                *items += new MenuEntry("Infinite Nuts", InfiniteNuts);
                *items += new MenuEntry("Infinite Sticks", InfiniteStick);
                *items += new MenuEntry("Infinite Bomb", InfiniteBomb);
                *items += new MenuEntry("Infinite Bombchu", InfiniteBombchu);
                *items += new MenuEntry("Infinite Slingshot", InfiniteSlingshot);
                *items += new MenuEntry("Infinite Explosives", InfiniteExplosives);
            }

            *inventory += items;
            *inventory += new MenuEntry("Inventory Modifier", nullptr, InventoryModifier);
            *inventory += new MenuEntry("100 Skulltulas", Skulltulas);
            *inventory += new MenuEntry("Max Rupees", MaxRupees);
            *inventory += new MenuEntry("Can use all items", UseAllItems);
            *inventory += new MenuEntry("Unlock all items", UnlockAllItems);
        }

        menu += inventory;

        /*
        Time codes
        ***********/
        menu += new MenuFolder("Time", "",
        {
            EntryWithHotkey(new MenuEntry("Sunrise", Sunrise), Hotkey(Key::R | Key::DPadLeft, "Sunrise")),
            EntryWithHotkey(new MenuEntry("Daytime", Daytime), Hotkey(Key::R | Key::DPadUp, "Daytime")),
            EntryWithHotkey(new MenuEntry("Sunset", Sunset), Hotkey(Key::R | Key::DPadRight, "Sunset")),
            EntryWithHotkey(new MenuEntry("Night", Night), Hotkey(Key::R | Key::DPadDown, "Night")),
            EntryWithHotkey(new MenuEntry("Time modifier", TimeModifier),{ Hotkey(Key::L | Key::DPadUp, "Advance time"), Hotkey(Key::L | Key::DPadDown, "Go back in time") }),
            new MenuEntry("Sky is always raining", AlwaysRaining)
        });

        /*
        ** Quest
        ************/

        menu += new MenuFolder("Quest", "",
        {
            new MenuEntry("Unlock All Best Equipment", UnlockAllBest),
            new MenuEntry("Unlock All Stones", UnlockAllStones),
            new MenuEntry("Unlock All Medallions", UnlockAllMedallions),
            new MenuEntry("Unlock Enhanced Defense", UnlockEnhancedDefense),
            new MenuEntry("Unlock Heart Pieces", UnlockHeartpieces),
            new MenuEntry("Infinite Small Dungeon Keys", InfiniteSmallKeysAllDungeons),
            new MenuEntry("Unlock Map and Boss Key of all Dungeons", HaveMapCompassAndBossKeyAllDungeon)
        });

        /*
        ** Misc codes
        *************/

        menu += new MenuFolder("Misc.", "",
        {
            new MenuEntry("Giant Link", GiantLink),
            new MenuEntry("Normal Link", NormalLink),
            new MenuEntry("Mini Link", MiniLink),
            new MenuEntry("Paper Link", PaperLink),
            new MenuEntry("Link always have his child voice", AlwaysChildLinkVoice),
            new MenuEntry("Link always have his adult voice", AlwaysAdultLinkVoice),
            new MenuEntry("Open Chest Many Times", OpenAnyChestInTheGameAsManyTimes),
            new MenuEntry("Collect Heart Piece Many Times", CollectHeartPiecesInOverworldAsMany),
            new MenuEntry("No Damage From Falling", NeverTakeDamageFromFalling),
            new MenuEntry("Giant knife won't break", GiantsKnifeNeverBreaks)
        });
    }

    int    main(void)
    {
        PluginMenu      *menu = new PluginMenu("Zelda Ocarina Of Time 3D", MAJOR_VERSION, MINOR_VERSION, REVISION_VERSION, about);

        menu->SynchronizeWithFrame(true);

        CreateMenu(*menu);

        // Launch menu and mainloop
        menu->Run();

        // Exit plugin
        return (0);
    }
}
