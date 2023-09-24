#include <genesis.h>

u16 getRandomRange(u16 min, u16 max) {
    return (random() % (max - min + 1)) + min;
}