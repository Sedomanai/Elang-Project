/*****************************************************************//**
 * @file   camera.h
 * @brief  All camera/viewport related types and functions. 
 *		   Due to how entt handles new types, Camera is not treated the same as Transform
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/
#pragma once
#include "../common/define.h"
#include "../common/transform.h"
#include "../common/matrix4x4.h"

namespace el
{
	constexpr int ortho_far = 100000000;

	struct CameraMeta { sizet meta; };

	struct Camera : Transform { 
		EL_USING_BASE_CLASS(Camera, Transform)
	};
	
	enum class Projection
	{
		eOrtho, ePerspective
	};

	inline matrix4x4 gOrtho(1), gPerspective(0);
	extern void updateViewport(float left, float right, float bottom, float top);
	extern void updateViewport(matrix4x4& ortho, float left, float right, float bottom, float top);
}