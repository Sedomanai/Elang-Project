/*****************************************************************//**
 * @file   enums.h
 * @brief  Contains very common/universal enum structs (enum class). 
 *			All el enum structs are prefixed with e.
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_ENUMS_H
#define  EL_ENUMS_H

namespace el {
	/**
	 * @brief Custom input state enum.
	 *
	 * Used to determine the states of user input.
	 * Checks for the conditions of any kind of input according to framerate or events.
	 *
	 * @warning Do not change the order of the states; many units depend on it
	 */
	enum struct eInput
	{
		None = 0, ///< Default state, where no input is received.
		Lift, ///< The state of first "release" or cease input; the frame/state that should be None.
		Snap, ///< Legacy: for very slow framerates. They must be internally resolved to either of the four above.
		Once, ///< The state of first input/press; the frame/state after that should be Hold.
		Hold, ///< The state of continous input/press. Should starts with once and end with lift.
		Flap ///< Legacy: for very slow framerates. They must be internally resolved to either of the four above.
	};

	/**
	 * @brief Universal enum for selection.
	 *
	 * Selection state for a single unit. (Not for multiple units each with its own selection state.)
	 */
	enum struct eSelect
	{
		NoChange, ///< Default state, where it is not selected.
		Selected, ///< Selected state.
		Deselected ///< Deselected state.
	};


	/**
	 * @brief Universal enum for alignment.
	 *
	 * Can also be used for horizontal/vertical alignment, as well as different use cases.
	 * In most cases, start should be left for horizontal, and top for vertical.
	 */
	enum struct eAlignment
	{
		Start = -1, ///< Start aligned. Note that the value is -1, not 0. (Default state.)
		Center, ///< Center aligned. Note that the value is 0,
		End ///< End aligned.
	};

	/**
	 * @brief Universal enum for data types.
	 *
	 * Not recommended for obvious reasons, but sometimes there's no other choice.
	 * Description for enum values not listed because they're too obvious.
	 */
	enum struct eDataType
	{
		Void_type = 0,

		Int,
		Short,
		Long,
		Longlong,
		Int8,
		Int16,
		Int32,
		Int64,

		Uint,
		Ushort,
		Ulong,
		Ulonglong,
		Uint8,
		Uint16,
		Uint32,
		Uint64,

		Float,
		Vec2,
		Vec3,
		Vec4,
		Color8,

		Matrix3,
		Matrix4
	};
}
#endif