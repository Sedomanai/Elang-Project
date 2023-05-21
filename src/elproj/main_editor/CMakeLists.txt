
if(EL_TARGET STREQUAL "elang_main_editor")

target_sources(${EL_TARGET} PUBLIC
	"q_main.cpp"
	"q_main.h" #moc
)
list(APPEND EL_MAIN_EDITOR_UI_LIST
	"${CMAKE_CURRENT_LIST_DIR}/q_main.ui"
)
set(EL_MAIN_EDITOR_UI_LIST ${EL_MAIN_EDITOR_UI_LIST} PARENT_SCOPE)
endif()