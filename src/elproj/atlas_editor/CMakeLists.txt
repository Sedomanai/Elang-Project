
if(EL_TARGET STREQUAL "elang_atlas_editor")

target_sources(${EL_TARGET} PUBLIC
	"atlas_setup.cpp"
	"atlas_setup.h" #moc
	"auto_gen.cpp"
	"auto_gen.h" #moc
	"cells_widget.cpp"
	"cells_widget.h" #moc
	"clips_widget.cpp"
	"clips_widget.h" #moc
	"ghost_dialog.cpp"
	"ghost_dialog.h" #moc
	"pivot_widget.cpp"
	"pivot_widget.h" #moc
	"q_elang_atlas_editor.cpp"
	"q_elang_atlas_editor.h" #moc
)
list(APPEND EL_ATLAS_EDITOR_UI_LIST
	"${CMAKE_CURRENT_LIST_DIR}/auto_gen.ui"
	"${CMAKE_CURRENT_LIST_DIR}/clips_widget.ui"
	"${CMAKE_CURRENT_LIST_DIR}/q_ghost_dialog.ui"
	"${CMAKE_CURRENT_LIST_DIR}/q_elang_atlas_editor.ui"
)
set(EL_ATLAS_EDITOR_UI_LIST ${EL_ATLAS_EDITOR_UI_LIST} PARENT_SCOPE)
endif()