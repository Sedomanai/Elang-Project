/*****************************************************************//**
 * @file   controls.h
 * @brief  Global controls. For a game with one window, this would suffice.
 *		   Just make sure to reset whenever there's a change in scene and/or window.
 *		   Alternatively, create a simulator set for each scene/window.
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#pragma once
#include "../common/mousesym.h"
#include "../common/keysym.h"

namespace el
{
	extern KeySym gKey;
	extern MouseSym gMouse;
}