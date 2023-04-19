/*****************************************************************//**
 * @file   atlas.h
 * @brief  Tools for importing and exporting sprite atlas 
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#pragma once
#include "../tools/declarer.h"
#include "../common/string.h"

namespace el
{
	using sizet = size_t;
	template<typename T>
	using vector = std::vector<T>;

	template<typename T>
	struct asset;
	struct Cell;


	struct ClipMeta { sizet i; };
	struct Clip
	{
		vector<asset<Cell>> cells;
		float speed;
		bool repeat;
		Clip() : speed(1.0f), repeat(false) {};
		template<typename T>
		void serialize(T& archive) {
			archive(cells, speed, repeat);
		}
	};
}