#ifndef CTRPLUGINFRAMEWORK_UTILS_UTILS_HPP
#define CTRPLUGINFRAMEWORK_UTILS_UTILS_HPP

#include "types.h"

#include "CTRPluginFramework/System/Process.hpp"

#include <string>
#include <vector>
#include <cstring>

namespace CTRPluginFramework
{
    class Color;
    class Utils
    {
    public:

        /**
         * \brief Get a string formatted with format specifier from printf
         * \param fmt String to be formatted
         * \param ... Addtionnal arguments
         * \return The formatted std::string
         */
        static std::string  Format(const char *fmt, ...);

        /**
         * \brief Get the hexadecimal representation of a value
         * \param value The value to convert
         * \return An std::string with the the hexadecimal representation of value
         */
        static std::string  ToHex(u32 value);

        /**
         * \brief Get the string representation of a float value
         * \param fpval The value to convert
         * \param precision The number of digit after the .
         * \return An std::string with the representation of the value\n
         * Values between -999999.f && 999999.f will be a fixed representation \n
         * while anything lower / higher will be a scientific representation
         */
        static std::string  ToString(float fpval, int precision = 2);

        /**
         * \brief Get a random number
         * \return A random number
         */
        static u32          Random(void);

        /**
         * \brief Get a random number
         * \param min Minimu value for the random number
         * \param max Maximum value for the random number
         * \return A random number between min & max
         */
        static u32          Random(u32 min, u32 max);

        /**
         * \brief Get the size of an utf8 std::string (max size 0x100)
         * \param str The string to count
         * \return The count of utf8 chars in the str
         */
        static u32          GetSize(const std::string &str);

        /**
         * \brief Remove the last char of an utf8 string (max size 0x100)
         * \param str The string to remove the char from
         * \return The codepoint value of the char removed
         */
        static u32          RemoveLastChar(std::string &str);

        template <typename T>
        static u32     Search(const u32 start, const u32 size, const std::vector<T> &pattern)
        {
            if (!start || !size || pattern.empty())
                return (0);

            const u32   patternSize = pattern.size() * sizeof(T);
            const u8    *patternc = reinterpret_cast<const u8 *>(pattern.data());
            const u8    *startPos = reinterpret_cast<const u8 *>(start);

            u32     table[256];

            for (u32 i = 0; i < 256; i++)
                table[i] = patternSize;

            for (u32 i = 0; i < patternSize - 1; i++)
                table[patternc[i]] = patternSize - i - 1;

            u32 j = 0;
            while (j <= size - patternSize)
            {
                const u8 c = startPos[j + patternSize - 1];
                if (patternc[patternSize - 1] == c && std::memcmp(patternc, startPos + j, patternSize - 1) == 0)
                    return (reinterpret_cast<u32>(startPos + j));
                j += table[c];
            }
            return (0);
        }

        template <typename T>
        static u32     Rsearch(const u32 start, const u32 size, const std::vector<T> &pattern)
        {
            if (!start || !size || pattern.empty())
                return (0);

            const u32   patternSize = pattern.size() * sizeof(T);
            const u8    *patternc = reinterpret_cast<const u8 *>(pattern.data());
            const u8    *startPos = reinterpret_cast<const u8 *>(start);

            u32     table[256];

            for (u32 i = 0; i < 256; i++)
                table[i] = patternSize;

            for (u32 i = 0; i < patternSize - 1; i++)
                table[patternc[i]] = patternSize - i - 1;

            u32 j = 0;
            u32 last = 0;
            while (j <= size - patternSize)
            {
                const u8 c = startPos[j + patternSize - 1];
                if (patternc[patternSize - 1] == c && std::memcmp(patternc, startPos + j, patternSize - 1) == 0)
                    last = reinterpret_cast<u32>(startPos + j);
                j += table[c];
            }
            return (last);
        }
    };
}

#endif