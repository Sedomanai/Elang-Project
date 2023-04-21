/*****************************************************************//**
 * @file   signal.h
 * @brief  Extremely simple signal-slot system, like event/delegates
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_FUNCTIONAL_H
#define  EL_FUNCTIONAL_H
#include <functional>

namespace el
{
	/**
	 * @brief Signal.
	 * 
	 * Signals of the signal-slot pattern.
	 * Able to connect to slots of anything that can translate to std::function.
	 * @tparam ...Arg Array of types that should match the parameters of the expected functions.
	 */
	template<typename ...Arg>
	struct signal
	{
		/**
		 * @brief Invoke.
		 * @param arg Parameters to send to invoke the connected slot functions. 
		 */
		void invoke(Arg... arg) {
			for (auto& s : mSlots) {
				s(arg...);
			}
		}
		/**
		 * @brief Connect a function as a slot. 
		 * 
		 * The function slot params has to match the signal type params. 
		 * For some reason currently only works with Lambdas, so beware.
		 * @param function The function to connect/enlist.
		 * @warning Only works with lambdas currently.
		 */
		void connect(std::function<void(Arg...)> function) {
			mSlots.push_back(function);
		}

		//void connect(void(*function)(Arg... arg)) {
		//	mSlots.push_back(function);
		//}

		template<typename T>
		void connect(T* instance, void(T::* method)(Arg... arg)) {
			mSlots.push_back([instance, method](Arg... arg) { ((*instance).*method)(arg...); });
		}

		/**
		 * @brief Clear all slots.
		 * 
		 * Disconnect all function slots enlisted/connected to this signal.
		 */
		void clear() { mSlots.clear(); }
	private:
		std::vector<std::function<void(Arg...)>> mSlots;
	};

	/**
	 * @brief Signal that can only connect to one Slot
	 * 
	 * Signals of the signal-slot pattern.
	 * Able to connect to slots of anything that can translate to std::function.
	 * Works the same as @ref single_signal<...Arg>.
	 * 
	 * @see signal<...Arg>
	 */
	template<typename ...Arg>
	struct single_signal
	{
		void invoke(Arg... arg) {
			if (mSlot) mSlot(arg...);
		}
		void connect(std::function<void(Arg...)> function) {
			mSlot = function;
		}
		//void connect(void(*function)(Arg... arg)) {
		//	mSlot = function;
		//}
		
		template<typename T>
		void connect(T& instance, void(T::* method)(Arg... arg)) {
			mSlot = [&instance, method](Arg... arg) { (instance.*method)(arg...); };
		}
		void disconnect() { mSlot.swap(); }
	private:
		std::function<void(Arg...)> mSlot;
	};
}
#endif