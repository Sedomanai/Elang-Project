/*****************************************************************//**
 * @file   keysym.h
 * @brief  Basic operations for all kinds of key simulations.
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_KEYSYM_H
#define  EL_KEYSYM_H
#include "define.h"
#include "enums.h"

namespace el
{
	/**
	 * @brief Elang Custom Keycode.
	 * 
	 * This keycode was created centered around SDL keycode, with some adjustments.
	 * All keycodes fall within 256, making it a char value.
	 * Covers most if not all keys on the keyboard.
	 * 
	 * @attention Description not given due to how obvious it is.
	 */
	enum class eKeyCode
	{
		Backspace = 8,
		Tab,

		Return = 13,
		Escape = 27,

		Space = 32,

		Apostrophe = 39,

		Comma = 44,
		Minus,
		Period,
		Slash,

		N0 = 48,
		N1,
		N2,
		N3,
		N4,
		N5,
		N6,
		N7,
		N8,
		N9,

		Semicolon = 59,
		Equals = 61,

		LBracket = 91,
		BackSlahs,
		RBracket,

		Acute = 96,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		Delete = 127,

		LCtrl = 167,
		LShift,
		LAlt,
		LWin,
		RCtrl,
		RShift,
		RAlt,
		RWin,

		Caps = 200,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		Print_Screen,
		Lock,
		Break,
		Insert,
		Home,
		Pgup,
		Void,
		End,
		Pgdn,

		Right,
		Left,
		Down,
		Up,

		NumLock,
		NumSlash,
		NumAsterisk,
		NumMinus,
		NumPlus,
		NumEnter,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Num0,
		NumPeriod,

		Context = 244
	};

#define ELANG_TOTAL_KEY_PRESS_COUNT 32

	/**
	 * @brief Refined key input state machine.
	 * 
	 * Useful for event based loops such as game loops.
	 * Can also be used in GUI app for more refined keyboard input.
	 * eKeyCode is based on modified version of SDLK(ey).
	 * @ref KeySym::update() must register at the END of a game loop along with @ref MouseSym::update().
	 * 
	 * @see MouseSym
	 * @see MouseSym::update()
	 */
	struct KeySym
	{
		/**
		 * Translate from SDL Keycode to Elang Keycode.
		 *
		 * @param key The given SDL keycode by integer index of enum.
		 * @return Translated Elang keycode by integer index of enum.
		 */
		sizet translateFromSDLKeyCode(sizet key);

		/**
		 * @brief Current eInput state of key in Elang Keycode. 
		 * Refer to @ref el::eInput for more on eInput state.
		 *
		 * @param key Elang keycode.
		 * @return Current state of key in @ref el::eInput by  @ref el::eKeycode enum.
		 * @see el::eInput
		 * @see el::eKeycode
		 */
		eInput state(eKeyCode key);

		/**
		 * @brief Current eInput state of key in Elang Keycode. 
		 * Refer to @ref el::eInput  for more on eInput state.
		 *
		 * @param key Elang keycode by integer index.
		 * @return Current state of key in @ref el::eInput by integer index.
		 * @see el::eInput
		 */
		eInput state(sizet key);

		/**
		 * @brief Input listener.
		 * Invoked anywhere that can trigger a key press event.
		 * Updates all None state to Once state.
		 *
		 * @param key The keycode to trigger press input. Key code index must be in @ref el::eKeyCode (and not in, say, SDLK).
		 */
		void onPress(sizet key);

		/**
		 * 
		 * @brief Release listener.
		 * Invoked anywhere that can trigger a key release event.
		 * Updates all Hold state to Lift.
		 *
		 * @param key The keycode to trigger release input. Key code index must be in @ref el::eKeyCode (and not in, say, SDLK).
		 * @warning The given key will save its state in a 256 length char array.
		 *			If the given code is not @ref el::eKeycode, but still manages to have all its code within the bounds of 0~255, 
		 *			then this class can also be used for that keycode.
		 */
		void onRelease(sizet key);

		/**
		 * @brief Update all keys.
		 * 
		 * Invoke this method every frame or in any interval that should detect key signals. Updates all key states.
		 * This detects presses and releases from previous frame. If pressed last tick (@ref el::eInput::Once), update to @ref el::eInput::Hold state.
		 * If released (Lift) update to None state
		 *
		 * @see @KeySym
		 */
		void update();

		/**
		 * @brief Completely reset the key simulator. 
		 * 
		 * This means clearing all 256 key states.
		 * 
		 * @warning This may be absolutely necessary when transitioning between mutliple mouse event loops, for example between two windows.
		 *		It really depends on the platform, but generally call this between every window change. 
		 *		Otherwise may result in exceptions and/or weird behavior.
		 *		Alternatively consider creating multiple MouseSym for every window instead of using a single global controller.
		 */
		void reset();

	private:
		eInput mKeys[256];
		sizet mUpdates[ELANG_TOTAL_KEY_PRESS_COUNT];
		sizet mUpdateNum;

		void registerUpdate(sizet key);
	};

	/** @var gKey @brief A global Keysym. There's almost always no more need than only one. */
	// KeySym gKey;
}

#endif