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
	set(ELANG_TEST_DIR "${ELANG_SRC_DIR}/test")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

set(ELANG_DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dep")
set(ELANG_EXT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ext")
set(CMAKE_INSTALL_PREFIX "${ELANG_EXT_DIR}")
	set(CMAKE_INSTALL_INCLUDEDIR "include")
	set(CMAKE_INSTALL_LIBDIR "lib")
	set(CMAKE_INSTALL_DATAROOTDIR "lib")
	set(ELANG_EXT_BIN_DIR "${ELANG_EXT_DIR}/bin")
	set(ELANG_EXT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ext/src")

	# "${CMAKE_INSTALL_FULL_BINDIR}" "${CMAKE_INSTALL_PREFIX}"
## IMPORTANT: use this flag to turn on or off installation 
option(ELANG_INSTALLATION "TURN ON INSTALLATION" ON)

##################### ELANG ######################
if (NOT ELANG_INSTALLATION)
	## Executables ##
	add_executable(elang "${ELANG_TEST_DIR}/main.cpp" "${ELANG_TEST_DIR}/test.cpp" "${ELANG_SRC_DIR}/elang/elpch.cpp")
#	if(WIN32 AND CMAKE_C_COMPILER_ID STREQUAL "MSVC")
#	  target_link_options(elang PRIVATE "-mwindows")
#	endif()

	## Entries ##
	# You can change between targets to quickly switch between entries
	###### >>>>>>>
		set(EL_TARGET elang)

	## Compilation ##
	set_target_properties(${EL_TARGET} PROPERTIES
	  LINKER_LANGUAGE CXX
	  CXX_STANDARD 17
	)
	target_compile_features(${EL_TARGET} PRIVATE cxx_std_17)
	target_include_directories(${EL_TARGET} PUBLIC "${ELANG_SRC_DIR}")
	target_precompile_headers(${EL_TARGET} PUBLIC "${ELANG_DIR}/elpch.h")
	add_subdirectory("${ELANG_DIR}")

endif()

################# DEPENDENCIES ####################
if (ELANG_INSTALLATION) 
	##### INSTALLATION #####
	message ("** Installing Elang Dependencies **")
	
	## Reset Library/Archive Directories for Externals (SDL, mainly) ##
			# It keeps making unnecessary copies without this so.. here we are.
 	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_INSTALL_PREFIX}/lib")
 	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin")
 	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    set(LIBRARY_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    set(ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

	## SDL2 ##
	set(SDL_SHARED ON)
	set(SDL2_DISABLE_INSTALL OFF CACHE BOOL "Disable installation of SDL2" FORCE)
	add_subdirectory("${ELANG_DEP_DIR}/sdl2")

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
	DESTINATION ${ELANG_EXT_SRC_DIR})
else() 
	##### LINKAGE #####

	## COPY BINARIES TO BIN ##
if (ELANG_DEBUG)
	FILE(GLOB BINARIES "${ELANG_EXT_BIN_DIR}/*d.dll" "${ELANG_EXT_BIN_DIR}/*d.so" "${ELANG_EXT_BIN_DIR}/*d.dylib")
else()
	FILE(GLOB D_BINARIES "${ELANG_EXT_BIN_DIR}/*d.dll" "${ELANG_EXT_BIN_DIR}/*d.so" "${ELANG_EXT_BIN_DIR}/*d.dylib")
	FILE(GLOB BINARIES "${ELANG_EXT_BIN_DIR}/*.dll" "${ELANG_EXT_BIN_DIR}/*.so" "${ELANG_EXT_BIN_DIR}/*.dylib")
	list(REMOVE_ITEM BINARIES ${D_BINARIES})
endif()
	install(FILES ${BINARIES} DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

	##### Linkage #####
	message ("** Building Elang Dependencies **")
	set(ELANG_EXT_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")

	## SDL ##
	if (CMAKE_C_COMPILER_ID STREQUAL GNU)
		include("${ELANG_EXT_LIB_DIR}/cmake/SDL2/SDL2Config.cmake")
	else()
		include("${ELANG_EXT_DIR}/cmake/SDL2Config.cmake")
	endif()
	target_link_libraries(${EL_TARGET} SDL2::SDL2main SDL2::SDL2)

	## GLEW ##
	find_package(OpenGL REQUIRED)
	include("${ELANG_EXT_LIB_DIR}/cmake/glew/glew-config.cmake")
	target_link_libraries(${EL_TARGET} GLEW::glew)

	## Interface Library ##
	include("${ELANG_EXT_LIB_DIR}/EnTT/cmake/EnTTConfig.cmake")
	include("${ELANG_EXT_LIB_DIR}/cmake/tsl-robin-map/tsl-robin-mapConfig.cmake")
	include("${ELANG_EXT_LIB_DIR}/cmake/tweeny/TweenyConfig.cmake")
	target_link_libraries(${EL_TARGET} EnTT::EnTT tsl::robin_map tweeny)
	
	## MISC ##
	target_include_directories(${EL_TARGET} PUBLIC ${ELANG_EXT_SRC_DIR})
endif()
