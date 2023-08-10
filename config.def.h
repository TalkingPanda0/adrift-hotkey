#ifndef CONFIG_H
#define CONFIG_H
#include "xhklib.h"
#include <X11/X.h>

typedef enum{
	NOTHING,
	START,
	SPLIT,
	RESET,
	END,
	PAUSE,
	RESUME,
} timer_action;

typedef struct {
	KeySym keybind;
	unsigned int modifiers;
	unsigned int event_mask;
	timer_action action;
} Key;

static Key keys[] = {
	{XK_H,Mod1Mask,xhkKeyPress,START},
	{XK_J,Mod1Mask,xhkKeyPress,SPLIT},
	{XK_R,Mod1Mask,xhkKeyPress,RESET},
	{XK_E,Mod1Mask,xhkKeyPress,END},
	{XK_P,Mod1Mask,xhkKeyPress,PAUSE},
	{XK_G,Mod1Mask,xhkKeyPress,RESUME},
};


#endif

