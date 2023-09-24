#ifndef _JOYTYPE_H_
#define _JOYTYPE_H_

#include <genesis.h>

#define JOY_INPUT(joy, button) \
    ((joy.value & button) && !(joy.preValue & button))

typedef struct {
    u16 type;
    u16 value, preValue;
} JoyType;

#endif