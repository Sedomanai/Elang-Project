/*****************************************************************//**
 * @file   singleton.h
 * @brief  Singleton.
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_SINGLETON_H
#define  EL_SINGLETON_H

namespace el
{
	/**
	 * @param Generic singleton pattern.
	 * 
	 * A template function that creates a singleton out of a type.
	 * Type must have a constructor that takes no params.
	 * 
	 * @tparam T Type of singleton. T must have a basic constructor of type void(*func)().
	 */
	template<typename T>
	struct singleton
	{
		/**
		 * @brief Get or resetter of singleton.
		 * 
		 * Get the singleton instance as reference.
		 * Also used to reset and create a new instance if a true flag is passed.
		 * 
		 * @param reset If set to true, will destroy the instance (default to false).
		 * @return T& Get instance as reference.
		 */
		static T& get(bool reset = false) {
			static T* instance = nullptr;
			if (reset)
				instance = nullptr;
			else if (!instance)
				instance = new T();
			return (*instance);
		}
	};
}
#endif