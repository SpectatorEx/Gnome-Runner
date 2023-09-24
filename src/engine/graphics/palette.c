#include "engine/graphics.h"

void GS_copyPalette(u16 *pal, u16 index, u16 argsCount, ...) {
    Palette palette;

    va_list args;
    va_start(args, argsCount);

    for (u16 i = 0; i < argsCount; i++) {
        palette = va_arg(args, Palette);

        for (u16 j = 0; j < 16; j++) {
            pal[index + j] = palette.data[j];
        }

        index += 16;
    }

    va_end(args);
}