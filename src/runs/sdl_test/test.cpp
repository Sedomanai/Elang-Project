//#include <elpch.h>
#include "test.h"
#include <elang/registry/asset_loader.h>
#include <elang/assets/texture.h>
#include <elang/assets/atlas.h>
#include <elang/assets/material.h>
#include <elang/assets/atlas.h>
#include <elang/assets/cell.h>
#include <elang/systems/painter.h>
#include <elang/elements/basic.h>
#include <elang/elements/canvas.h>
#include <elang/elements/clipanim.h>
#include <elang/common/line.h>
#include <elang/common/vecstream.h>

namespace el
{
	void Test::load() {
		gStage = gProject.make<Stage>();

		AssetLoader loader;
		loader.initCommonAssets();
		editor_mat = loader.createNativeGUIAsset<Material>("test_material", gMaterials);

		loader.initProject("../__el_test");

		tex = loader.sync.open<Texture, TextureMeta>("ash.png", gTextures);
		atlas = loader.sync.open<Atlas, AtlasMeta>("ash.atls", gAtlases);
		tex->atlas = atlas;
		editor_mat->setTexture(gTextures.names["ash.png"]);

		spritePainter = gProject.make<Painter>("shaders/basic_sprite.vert", "shaders/texture_uv.frag",
			32, gCameras.names["main_cam"], Projection::eOrtho,
			ePainterFlags::DEPTH_SORT | ePainterFlags::MULTI_MATERIAL | ePainterFlags::Z_CLEAR).add<EditorAsset>();
		spritePainter->init();

		//debug = new ShapeDebug2d();
		//debug->init(gCameras.names["__el_editor_/main_cam"]);
	}

	void Test::start() {
		obj = gStage->make<Sprite>(editor_mat, spritePainter, "ash_0");
		//obj.add<ClipAnimation>(atlas->clips["front_walk"]);
		obj.add<Position>();
		obj->recalc(obj);
	}

	void Test::input() {};
	void Test::update() {
		//obj.get<ClipAnimation>().step(*obj);
		//obj->recalc(obj);
	};

	void Test::paint() {
		static float dx = 0;
		dx += 0.001;
		//debug->line.batchline(line(-10000, 0.0f, 10000, 0.0f), color8(0, 0, 0, 0), 0.0f);
		//debug->line.batchline(line(-10000, 0.0f, 10000, 0.0f), color8(255, 255, 255, 255), 0.0f);

		//debug->fill.batchAABB(aabb(-0 + dx, 0 + dx, 0.5, -0.5), color8(255, 255, 255, 255), 0.0f);
		//debug->fill.batchAABB(aabb(-0.5, 0.5, 0, 0), color8(255, 255, 255, 255), 0.0f);

		//debug->line.batchAABB(aabb(-100, 100, 100, -100), color8(255, 255, 255, 255), 0.0f);
		//debug->line.batchAABB(aabb(100, 200, 200, 100), color8(255, 255, 255, 255), 0.0f);
		obj->batch();

		spritePainter->paint();
		//debug->draw();
	};
}