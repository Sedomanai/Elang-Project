cmake_minimum_required (VERSION 3.20)

project ("elang_project")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# From cmake v3.13 this allows parent cmakelists to set options of chlidren.
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) 

message("COMPILER ID: ${CMAKE_C_COMPILER_ID}")
if(CMAKE_BUILD_TYPE MATCHES Debug OR NOT CMAKE_BUILD_TYPE)
	set(ELANG_DEBUG ON)
else()
	set(ELANG_DEBUG OFF)
endif()

##################### DIRECTORIES / OPTIONS ######################
set(ELANG_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
	set(ELANG_DIR "${ELANG_SRC_DIR}/elang")
	set(ELANG_GUI_DIR "${ELANG_SRC_DIR}/elgui")
	set(ELANG_PROJ_DIR "${ELANG_SRC_DIR}/elproj")
	set(ELANG_RUNS_DIR "${ELANG_SRC_DIR}/runs")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(ELANG_DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dep")
set(ELANG_QRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qrc")

##################### ELANG ######################

## Executables ##
# You cannot mix gui (qt) with engine (sdl). 
# I mean you can, but the setup is more complicated than you think, and most of all it's not necessary.
set(ELANG_GUI off)

if (ELANG_GUI) 
	add_executable(elangqt "${ELANG_RUNS_DIR}/qt_test/main.cpp" "${ELANG_DIR}/elpch.cpp" "src/runs/refractor/main.cpp")
	add_executable(elang_atlas_editor "${ELANG_RUNS_DIR}/atlas_editor/main.cpp" "${ELANG_DIR}/elpch.cpp" "${ELANG_QRC_DIR}/resources.qrc")
	add_executable(elang_main_editor "${ELANG_RUNS_DIR}/main_editor/main.cpp" "${ELANG_DIR}/elpch.cpp" "${ELANG_QRC_DIR}/resources.qrc")
else()
	add_executable(elang_test "${ELANG_RUNS_DIR}/sdl_test/main.cpp" "${ELANG_RUNS_DIR}/sdl_test/test.cpp" "${ELANG_DIR}/engine.cpp" "${ELANG_DIR}/elpch.cpp")
endif()
	add_executable(entt_lab "${ELANG_RUNS_DIR}/entt_lab/main.cpp" "${ELANG_DIR}/elpch.cpp" "${ELANG_RUNS_DIR}/entt_lab/reflection.h" "${ELANG_RUNS_DIR}/entt_lab/basic.h")
	add_executable(elang_refractor "${ELANG_RUNS_DIR}/refractor/main.cpp" "${ELANG_DIR}/elpch.cpp")

## Entries ##
# You can set the target here. 
# Make sure you set the available targets according to related ELANG flags like ELANG_GUI
###### >>>>>>>
	set(EL_TARGET elang_refractor)

if (ELANG_GUI)
	target_compile_definitions(${EL_TARGET} PRIVATE ELANG_GUI)
else()
	target_compile_definitions(${EL_TARGET} PRIVATE ELANG_SDL)
endif()

## Compilation ##
set_target_properties(${EL_TARGET} PROPERTIES
	LINKER_LANGUAGE CXX
	CXX_STANDARD 17
)
target_compile_features(${EL_TARGET} PRIVATE cxx_std_17)
target_include_directories(${EL_TARGET} PRIVATE "${ELANG_SRC_DIR}")
target_precompile_headers(${EL_TARGET} PRIVATE "${ELANG_DIR}/elpch.h")
add_subdirectory("${ELANG_DIR}")

if (ELANG_GUI)
	add_subdirectory("${ELANG_GUI_DIR}")
	add_subdirectory("${ELANG_PROJ_DIR}/main_editor")
	add_subdirectory("${ELANG_PROJ_DIR}/atlas_editor")
endif()

################# DEPENDENCIES ####################

## Please read the dependency_list.txt in the dep folder
target_include_directories(${EL_TARGET} PRIVATE "${ELANG_DEP_DIR}/fpng/src")

if (ELANG_GUI)
	## QT ##
	find_package(Qt6 REQUIRED COMPONENTS Core GUI Widgets OPENGL OpenGLWidgets )
	set_target_properties(${EL_TARGET} PROPERTIES AUTOMOC TRUE)
	set_target_properties(${EL_TARGET} PROPERTIES AUTORCC TRUE)

	## Compile UIC ##
	list(APPEND EL_FINAL_UI_LIST 
		${EL_GUI_UI_LIST}
		${EL_MAIN_EDITOR_UI_LIST}
		${EL_ATLAS_EDITOR_UI_LIST}
	)
	
	foreach(ui_file ${EL_FINAL_UI_LIST})
		get_filename_component(ui_name ${ui_file} NAME_WE)
		get_filename_component(ui_dir ${ui_file} DIRECTORY)
		set(output_header_file "${ui_dir}/${ui_name}_ui.h")
		list(APPEND EL_GUI_UI_H ${output_header_file})
		add_custom_command(
			OUTPUT ${output_header_file}
			COMMAND Qt6::uic ARGS ${ui_file} -o ${output_header_file}
			DEPENDS ${ui_file}
			COMMENT "Generating UI header for ${ui_file}"
		)
	endforeach()

	add_custom_target(EL_GUI_H_TARGET DEPENDS ${EL_GUI_UI_H})
	add_dependencies(${EL_TARGET} EL_GUI_H_TARGET)
	target_sources(${EL_TARGET} PUBLIC ${EL_GUI_UI_H})
	target_link_libraries(${EL_TARGET} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)
else()
	## SDL ##
	find_package(SDL2 CONFIG REQUIRED)
	target_link_libraries(${EL_TARGET}
		PRIVATE
		$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
		$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
	)
endif()
	
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(EnTT CONFIG REQUIRED)
find_package(Tweeny CONFIG REQUIRED)
find_package(tsl-robin-map CONFIG REQUIRED)
target_link_libraries(${EL_TARGET} PRIVATE GLEW::GLEW tsl::robin_map tweeny) # EnTT::EnTT