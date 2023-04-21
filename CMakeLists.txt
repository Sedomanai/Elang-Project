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
	set(ELANG_RUNS_DIR "${ELANG_SRC_DIR}/runs")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

set(ELANG_DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dep")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/ext")
set(ELANG_EXT_DIR "${CMAKE_INSTALL_PREFIX}")
	set(CMAKE_INSTALL_INCLUDEDIR "include")
	set(CMAKE_INSTALL_LIBDIR "lib")
	set(CMAKE_INSTALL_DATAROOTDIR "lib")
	set(ELANG_EXT_BIN_DIR "${ELANG_EXT_DIR}/bin")
	set(ELANG_EXT_SRC_DIR "${ELANG_EXT_DIR}/src")
	set(ELANG_EXT_LIB_DIR "${ELANG_EXT_DIR}/lib")

## IMPORTANT: use this flag to set the installation flag
option(ELANG_INSTALLATION "TURN ON INSTALLATION" ON)


##################### ELANG ######################
if (NOT ELANG_INSTALLATION)
	## Executables ##

	# You cannot mix gui (qt) with engine (sdl). I mean you can, but the setup is more complicated than you think, and most of all it's not necessary.
	if (ELANG_GUI) 
		add_executable(elangqt "${ELANG_RUNS_DIR}/qt_test/main.cpp" "${ELANG_DIR}/elpch.cpp")
	else()
		add_executable(elang "${ELANG_RUNS_DIR}/sdl_test/main.cpp" "${ELANG_RUNS_DIR}/sdl_test/test.cpp" "${ELANG_DIR}/engine.cpp" "src/elang/elpch.cpp")
	endif()

	## Entries ##
	# You can set the target here. 
	# Make sure you set the available targets according to related ELANG flags like ELANG_GUI
	###### >>>>>>>
		set(EL_TARGET elangqt)

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
endif()

################# DEPENDENCIES ####################
if (ELANG_INSTALLATION) 
	##### INSTALLATION #####
	message ("** Installing Elang Dependencies **")
	
	## QT / SDL2 ##
	## It's not recommended to install QT/SDL2 directly as a git submodule.
	## Instead, if you go to the dep/qtbase folder, you will see my other repo instead.
	## Read the README.md of that repo and follow it closely to install them system-wide.
	## Also, QtBase (mini-Qt) is all we need for this project. (Even that is more than we need.)
	
	## GLEW ##
	set(BUILD_UTILS OFF)
	add_subdirectory("${ELANG_DEP_DIR}/glew/build/cmake")

	## Interface Libraries ##
	add_subdirectory("${ELANG_DEP_DIR}/entt")

	set(TSL_ROBIN_MAP_ENABLE_INSTALL ON)
	add_subdirectory("${ELANG_DEP_DIR}/robin-map")
	add_subdirectory("${ELANG_DEP_DIR}/tweeny")

	## Source Direct Copies ##
	set(FPNG_SRC_DIR "${ELANG_DEP_DIR}/fpng/src")
	install(FILES 
		"${FPNG_SRC_DIR}/fpng.h"
 		"${FPNG_SRC_DIR}/fpng.cpp"
 		"${FPNG_SRC_DIR}/lodepng.h"
 		"${FPNG_SRC_DIR}/lodepng.cpp"
	DESTINATION "${ELANG_EXT_SRC_DIR}")
	
	## COPY BINARIES TO BIN ##
	# 
	# This doesn't work sometimes.
	# Run installation again if no shared libs are copied to the runtime output folder.
	#
	if (ELANG_DEBUG)
		file(GLOB ALL_BIN "${ELANG_EXT_BIN_DIR}/*d.dll" "${ELANG_EXT_BIN_DIR}/*d.so" "${ELANG_EXT_BIN_DIR}/*d.dylib")
	else()
		file(GLOB ALL_BIN "${ELANG_EXT_BIN_DIR}/*.dll" "${ELANG_EXT_BIN_DIR}/*.so" "${ELANG_EXT_BIN_DIR}/*.dylib" 
		EXCLUDE "${ELANG_EXT_BIN_DIR}/*d.dll" EXCLUDE "${ELANG_EXT_BIN_DIR}/*d.so" EXCLUDE "${ELANG_EXT_BIN_DIR}/*d.dylib" )
	endif()
	install(FILES ${ALL_BIN} DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
else()
	##### LINKAGE #####

	### Global ###
	#
	# If you've set the paths to their config.cmake files in the system environment 
	# then you don't need to append to CMAKE_PREFIX_PATH
	#
	if (ELANG_GUI)
		## QT ##
		# list(APPEND CMAKE_PREFIX_PATH "C:\Depcpp\Qt_6.5.0\install\lib\cmake")
		find_package(Qt6 REQUIRED COMPONENTS Core GUI Widgets OPENGL OpenGLWidgets )

		set_target_properties(${EL_TARGET} PROPERTIES AUTOMOC TRUE)
		# set_target_properties(${EL_TARGET} PROPERTIES AUTOUIC TRUE) # We're doing this one manually
		set_target_properties(${EL_TARGET} PROPERTIES AUTORCC TRUE)
		## Compile UIC ##
		qt_wrap_ui(EL_GUI_UI_H ${EL_GUI_UI_LIST})

		foreach(ui_file ${EL_GUI_UI_LIST})
			get_filename_component(ui_name ${ui_file} NAME_WE)
			set(output_header_file "${ELANG_DIR}/gui/uic/ui_${ui_name}.h")
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
		target_link_libraries(${EL_TARGET} Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)
	else()
		## SDL ##
		include("C:/Depcpp/SDL2/install/cmake/SDL2Config.cmake")
		# find_package(SDL2)
		target_link_libraries(${EL_TARGET} SDL2::SDL2main SDL2::SDL2)
	endif()

	## GLEW ##
	find_package(OpenGL REQUIRED)
	include("${ELANG_EXT_LIB_DIR}/cmake/glew/glew-config.cmake")
	target_link_libraries(${EL_TARGET} GLEW::glew)

	## Interface Library ##
	include("${ELANG_EXT_LIB_DIR}/EnTT/cmake/EnTTConfig.cmake" NO_SYSTEM_FROM_IMPORTED)
	include("${ELANG_EXT_LIB_DIR}/cmake/tsl-robin-map/tsl-robin-mapConfig.cmake" NO_SYSTEM_FROM_IMPORTED)
	include("${ELANG_EXT_LIB_DIR}/cmake/tweeny/TweenyConfig.cmake" NO_SYSTEM_FROM_IMPORTED)
	target_link_libraries(${EL_TARGET} EnTT::EnTT tsl::robin_map tweeny)
	
	## MISC ##
	target_include_directories(${EL_TARGET} PRIVATE ${ELANG_EXT_SRC_DIR})
endif()
