#ifndef BOTTLEMANAGER_HPP
#define BOTTLEMANAGER_HPP

#include "types.h"

namespace CTRPluginFramework
{
    struct Item
    {
        u8  id;
        std::string name;
    };

    class Bottle
    {
    public:

        Bottle(u32 id, u32 address);
        ~Bottle(){}

        void        operator=(const Item &item);
        void        WriteItem(void);
        const Item  &GetCurrentItem(void);
        std::string ToString(void);

        const u32   ID;
        u8          SelectedItem;

    private:

        u8   *_address;
    };

    void    BottleSettings(MenuEntry *entry);
}

#endif