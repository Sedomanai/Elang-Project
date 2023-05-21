if (ELANG_GUI)
	target_sources(${EL_TARGET} PUBLIC
		# "dialog/empty_dialog.cpp"
		# "dialog/new_project.cpp"
		
		"extension/list.cpp"
		"extension/list.h" # moc
		"extension/main_window.cpp"
		"extension/main_window.h" # moc
		"extension/tree.cpp"
		"extension/tree.h" # moc
		"extension/view.cpp"
		"extension/view.h" # moc
		
		"widget/palette.cpp"
		"widget/palette.h" #moc
		"widget/texture_widget.cpp"
		"widget/texture_widget.h" #moc
		"widget/logo.cpp"
		"widget/logo.h" #moc
	)
	
	list(APPEND EL_GUI_UI_LIST
		"${CMAKE_CURRENT_LIST_DIR}/dialog/empty_dialog.ui"
		"${CMAKE_CURRENT_LIST_DIR}/dialog/new_project.ui"
		"${CMAKE_CURRENT_LIST_DIR}/widget/texture_widget.ui"
		"${CMAKE_CURRENT_LIST_DIR}/widget/logo.ui"
	)
	set(EL_GUI_UI_LIST ${EL_GUI_UI_LIST} PARENT_SCOPE)
endif()