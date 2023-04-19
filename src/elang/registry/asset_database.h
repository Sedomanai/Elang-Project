/*****************************************************************//**
 * @file   asset_database.h
 * @brief  All actual asset databases. It was separated from asset.h to help reduce compile time for some sources
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#pragma once
#include "asset.h"

namespace el
{
	extern AssetDatabase gTexts, gShaders, gCameras, gPainters, gMaterials, gTextures, gAtlases;
}
