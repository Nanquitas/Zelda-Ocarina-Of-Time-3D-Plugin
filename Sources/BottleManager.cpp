#include "CTRPluginFramework.hpp"
#include "BottleManager.hpp"
#include <vector>

namespace CTRPluginFramework
{
    static const std::vector<Item> g_bottleItems = 
    {
        {0x15, "Red potion"},
        {0x16, "Green potion"},
        {0x17, "Blue potion"},
        {0x18, "Fairy"},
        {0x19, "Fish"},
        {0x1A, "Milk, 2 Doses"},        
        {0x1F, "Milk, 1 dose"},
        {0x1B, "Letter"},
        {0x1C, "Blue flamme"},
        {0x1D, "Insect"},
        {0x1E, "Soul"},
        {0x20, "Spirit"},
        {0x14, "Empty" },
        {0xFF, "Locked" },
        {0x00, "Unknown / Error"}
    };

    Bottle::Bottle(u32 id, u32 address) : ID(id), SelectedItem(0)
    {
        _address = reinterpret_cast<u8 *>(address);
    }

    void    Bottle::operator=(const Item &item)
    {
        SelectedItem = item.id;
        *_address = item.id;
    }

    void    Bottle::WriteItem(void)
    {
        if (SelectedItem)
            *_address = SelectedItem;
    }

    const Item &Bottle::GetCurrentItem(void)
    {
        u8 id = *_address;

        for (const Item &item : g_bottleItems)
            if (item.id == id)
                return (item);

        return (g_bottleItems.back());
    }

    std::string Bottle::ToString(void)
    {
        std::string str("Bottle #");

        str += std::to_string(ID);
        str += " : " << Color::LimeGreen << GetCurrentItem().name;

        return (str);
    }

    using StringVector = std::vector<std::string>;
    void    BottleSettings(MenuEntry *entry)
    {
        Bottle          *bottle = reinterpret_cast<Bottle*>(entry->GetArg());
        Keyboard        keyboard;
        StringVector    items;

        for (const Item &item : g_bottleItems)
            if (item.id != 0)
                items.push_back(item.name);

        keyboard.DisplayTopScreen = false;
        keyboard.Populate(items);

        int choice = keyboard.Open();

        if (choice != -1)
        {
            *bottle = g_bottleItems[choice];
        }

        entry->Name() = bottle->ToString();

        entry->SetGameFunc([](MenuEntry *entry)
        {
            Bottle *bottle = reinterpret_cast<Bottle*>(entry->GetArg());

            bottle->WriteItem();
        });
    }
}
