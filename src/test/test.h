/*****************************************************************//**
 * @file   test.h
 * @brief  Most basic test - see if shaders compile, properly initated, textures load, etc.
 * 
 * @author Sedomanai
 * @date   August 2022
 *********************************************************************/

#pragma once
#include <elang/engine.h>

#include <elang/registry/stage.h>
#include <elang/elements/sprite.h>

#include <GL/glew.h>


namespace el
{
	struct Texture;
	struct Atlas;
	struct ShapeDebug2d;
	struct Test : Engine
	{
		Project project;

	protected:
		asset<Material> mat, editor_mat;
		obj<Sprite> obj;

		virtual void load() override;
		virtual void start() override;
		virtual void input() override;
		virtual void update() override;
		virtual void paint() override;

		//asset<Camera> mainCam;
		asset<Texture> tex;
		asset<Atlas> atlas;
		asset<Painter> spritePainter, uiPainter;
		ShapeDebug2d* debug;
		//ShapeDebug* debugger, * ui_debugger;
		//obj<Sprite> link;

		GLuint VertexArrayID, vertexbuffer;
	};
}
