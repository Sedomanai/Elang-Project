/*****************************************************************//**
 * @file   atlas.h
 * @brief  Tools for importing and exporting sprite atlas
 *
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#pragma once
#include "cell.h"
#include "clip.h"
#include "../tools/declarer.h"
#include "../registry/registry.h"
#include "../registry/project.h"
#include "../tools/hashmap.h"
#include "../common/define.h"

namespace el
{
	struct SubAssetData;
	struct stream;
	struct Atlas;
	struct Texture;

	// Holds meta data for atlas. Most probably erased in build
	struct AtlasMeta
	{
		friend struct Atlas;

		Entity self;
		int32 width, height;
		vector<string> users;
		vector<Entity> cellorder, cliporder;
		hashmap<Entity, string> cellnames, clipnames;

		friend stream& operator<<(stream& save, const AtlasMeta& am);
		friend stream& operator>>(stream& load, AtlasMeta& am);
	private:
		void clear();
	};

	struct Atlas
	{
		friend struct Texture;

		hashmap<string, Entity> cells, clips;
		Atlas() {}

		/**
		 * @param filePath : File path relative to project directory
		 * @param meta : Necessary meta
		 */
		void importFile(const fio::path& filePath, AtlasMeta& meta);
		void exportFile(const fio::path& filePath, AtlasMeta& data);
		void unload(AtlasMeta& data);
		void addCell(asset<SubAssetData> cell, AtlasMeta& meta);
	};
}