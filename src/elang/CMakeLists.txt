
target_sources(${EL_TARGET} PUBLIC
	"assets/atlas.cpp"
	"assets/camera.cpp"
	"assets/cell.cpp"
	"assets/material.cpp"
	"assets/shader.cpp"
	"assets/texture.cpp"

	"common/aabb.cpp"
	"common/circle.cpp"
	"common/fileio.cpp"
	"common/keysym.cpp"
	"common/mousesym.cpp"
	"common/transform.cpp"
	"common/transform2d.cpp"
	
	"elements/button.cpp"
	"elements/canvas.cpp"
	"elements/clipanim.cpp"
	"elements/sprite.cpp"
	"elements/visage.cpp"

	"registry/asset_database.cpp"
	"registry/asset_loader.cpp"
	"registry/asset_sync.cpp"
	"registry/project.cpp"
	"registry/stage.cpp"

	"systems/painter.cpp"
	"systems/ui.cpp"

	"tools/controls.cpp"
)

if (ELANG_GUI)
	add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/gui")
	set(EL_GUI_UI_LIST ${EL_GUI_UI_LIST} PARENT_SCOPE)
else()
	target_sources(${EL_TARGET} PUBLIC
		"engine.cpp"
	)
endif()