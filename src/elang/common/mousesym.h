/*****************************************************************//**
 * @file   mousesym.h
 * @brief  For mouse simulation.
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_MOUSESYM_H
#define  EL_MOUSESYM_H

#include "enums.h"
#include "vec2.h"

namespace el
{
	/** 
	 * @brief Refined mouse input state machine.
	 * 
	 * In Qt, and in most GUI frameworks where the screen is not updated every frame, @ref MouseSym::update() should occur every "mouse move" events.
	 * It should also be invoked once before every mouse press and once before every release event, in order to update the delta value properly.
	 * 
	 * In game loops (in SDL etc.), @ref MouseSym::update() must register at the END of the loop along with @ref KeySym::update(). 
	 * Where it is precisely invoked may vary, per system, depending on where it receives the coordinate values. 
	 * 
	 * @ref el::MouseSym does not care about the nature of its coordinates, whether they are screen coordinates or the world's. 
	 * It only cares about mouse events, the given vectors, and the relative vector change.
	 * You may decide the nature of the coordinates you give, according to your own needs.
	 * 
	 * @see MouseSym::update()
	 * @see KeySym
	 * @see KeySym::update()
	 */
	struct MouseSym
	{
		enum
		{
			Left = 0x00, ///< Code for left mouse button = 0.
			Right = 0x01, ///< Code for right mouse button = 1.
			Middle = 0x02, ///< Code for middle mouse button = 2.
		};

		/**
		 * Constructor for MouseSym.
		 */
		MouseSym();

		/**
		 * @brief Input listener.
		 * Invoked anywhere that can trigger a mouse press event.
		 * Updates all None state to Once state.
		 * 
		 * @param pos Current mouse position.
		 * @param buttonIndex Index of mouse button. Valid values are @Left, @Right, and @Middle.
		 */
		void onPress(const vec2& pos, sizet buttonIndex);

		/**
		 * @brief Release listener.
		 * Invoked anywhere that can trigger a mouse release event.
		 * Updates all el::eInput::Hold state to @ref el::eInput::Lift
		 *
		 * @param pos Current mouse position.
		 * @param buttonIndex Index of mouse button. Valid values are @Left, @Right, and @Middle.
		 */
		void onRelease(const vec2& pos, sizet buttonIndex);

		/**
		 * @brief Update all mouse input.
		 * 
		 * Invoke this method every frame or in any interval that should detect mouse signals. Updates all mouse states.
		 * This detects presses and releases from previous frame. 
		 * If pressed during last tick (@ref el::eInput::Once), update to @ref el::eInput::Hold state.
		 * If released (@ref el::eInput::Lift), update to @ref el::eInput::None state.
		 *
		 * @see @MouseSym
		 */
		void update(const vec2& pos);

		/**
		 * @brief Los current data. 
		 * 
		 * Log all mouse state data, including mouse state and delta position, as well as last clicked and last released functions. (Uses cout.)
		 */
		void print() const;

		/**
		 * Current @ref el::eInput state of mouse state
		 *
		 * @param buttonIndex The mousebutton to check state of. Valid values are @Left, @Right, and @Middle.
		 * @return Current state of key in eInput by button index. 
		 */
		eInput state(sizet buttonIndex) const;

		/**
		 * Current mouse position.
		 * @return Current mouse position in @ref el::vec2.
		 */
		vec2 currentPosition() const;

		/**
		 * Previous mouse position = position of mouse last tick.
		 * @return Previous mouse position in @ref el::vec2.
		 */
		vec2 previousPosition() const;

		/**
		 * @brief Delta of mouse position.
		 * Previous positon - current position.
		 * Or, how much the moved during the last to current tick.
		 * @return Delta of moved position in @ref el::vec2.
		 */
		vec2 deltaPosition() const;

		/**
		 * @brief Final clicked position.
		 * Mouse position where the last click happened.
		 * @return Last clicked position in @ref el::vec2.
		 * @param buttonIndex The clicked mousebutton. Valid values are @Left, @Right, and @Middle.
		 */
		vec2 lastClickedPosition(sizet buttonIndex) const;
		/**
		 * @brief Final released position.
		 * Mouse position where the last mouse release happened.
		 * @return Last clicked position in @ref el::vec2.
		 * @param buttonIndex The released mousebutton. Valid values are @Left, @Right, and @Middle.
		 */
		vec2 lastReleasedPosition(sizet buttonIndex) const;

		/**
		 * @brief Update all mousewheel input.
		 * Invoked every frame or any interval that should detect mouse wheel signals/events.
		 * @ref Mousesym does not care about the standards of magnitude or direction.
		 *		Scrolling up can be negative or positive. 
		 *		And the magnitude of each physical scroll can be anywhere between decimals or large integers.
		 * 
		 * @param value Mouse wheel delta. 
		 */
		void updateWheel(float value);
		/**
		 * @brief Mouse wheel state.
		 * Simply put, mouse scroll value.
		 * 
		 * @return The scroll value. Actually, the relationship between scroll direction and the value's sign, 
		 *			as well as the magnitude for each physical scroll tick, is implementation dependent.
		 * @see updateWheel(float)
		 */
		float wheel() const;

		/**
		 * @brief Completely reset the mouse simulator. 
		 * 
		 * This means clearing all position/delta states, wheel state, and previous mouse data, etc.
		 * 
		 * @warning This may be absolutely necessary when transitioning between mutliple mouse event loops, for example between two windows.
		 *			It really depends on the platform, but generally call this between every window change. 
		 *			Otherwise may result in exceptions and/or weird behavior.
		 *			Alternatively consider creating multiple MouseSym for every window instead of using a single global controller.
		 */
		void reset();
	private:
		float mWheel;
		vec2 mPrev, mCurr;
		vec2 mLastC[3], mLastR[3];
		eInput mState[3];
	};
}
#endif