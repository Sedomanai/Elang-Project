/*****************************************************************//**
 * @file   time.h
 * @brief  All time related variables and functions
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#ifndef  EL_TIME_H
#define  EL_TIME_H
#include "define.h"
#include <chrono>


 /** @typedef chrono_now @brief Type alias for @c std::chrono::high_resolution_clock::now(). */
#define chrono_now std::chrono::high_resolution_clock::now()
/** @typedef chrono_nnsec @brief Type alias for @c std::chrono::duration_cast<std::chrono::nanoseconds>. */
#define chrono_nnsec std::chrono::duration_cast<std::chrono::nanoseconds>
/** @typedef chrono_msec @brief Type alias for @c std::chrono::duration_cast<std::chrono::milliseconds>. */
#define chrono_msec std::chrono::duration_cast<std::chrono::milliseconds>
/** @typedef chrono_sec @brief Type alias for @c std::chrono::duration_cast<std::chrono::seconds>. */
#define chrono_sec std::chrono::duration_cast<std::chrono::seconds>
/** @typedef chrono_timepoint @brief Type alias for @c std::chrono::time_point<std::chrono::steady_clock>. */
#define chrono_timepoint std::chrono::time_point<std::chrono::steady_clock>

namespace  el
{
	/**
	 * @brief Custom mini profiler.
	 * 
	 * For the most basic manual profiling
	 * 
	 * @param functor : Statement to be profiled, mostly in lambda
	 * @param times : Number of repetition time 
	 * @return Total time elapsed
	 * 
	 * @see loop<F>(const F&, float, sizet)
	 */
	template <typename F>
	inline long long profile(const F& functor, sizet times) {
		auto t1 = chrono_now;
		for (sizet i = 0; i < times; i++)
			functor();
		auto t2 = chrono_now;
		auto ret = chrono_nnsec(t2 - t1).count();
		return ret;
	}

	/**
	 * @brief Simple loop function.
	 * 
	 * Not appropriate for endless loops (i.e. not a replacement for game loops).
	 * Do not use this to replace iteration statements such as for loops.
	 * Used mostly in conjuction with @ref el::profile<F>(const F&, sizet).
	 * 
	 * @param functor : Statement to be looped, mostly in lambda
	 * @param speed : Interval between loop iteration in seconds
	 * @param loopCount : Total loop iteration count
	 */
	template<typename F>
	void loop(const F& functor, float interval = 1.0f, sizet loopCount = 10000000) {
		sizet tick = 0;
		auto begin = chrono_now;
		long long it = 0;
		while (true) {
			auto duration = chrono_msec(chrono_now - begin).count();
			if (it < duration - (long long)(1000 / interval)) {
				it = duration;
				functor();
				tick++;
				if (tick > loopCount - 1)
					break;
			}
		}
	}
}
#endif