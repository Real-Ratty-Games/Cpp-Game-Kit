file(GLOB_RECURSE SOURCES "Source/*.cpp" "Include/*.hpp")

if (WIN32)
    add_executable (Game ${SOURCES})
	set_target_properties(Game PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/../GameDir)
else()
    add_executable(Game MACOSX_BUNDLE ${SOURCES})
	set_target_properties(Game PROPERTIES)
endif()

# Thirdparty
target_link_libraries(Game PRIVATE SoLoud::SoLoud)
target_link_libraries(Game PRIVATE SDL3::SDL3)
target_link_libraries(Game PRIVATE Assimp::Assimp)
target_link_libraries(Game PRIVATE bgfx::bgfx)
target_link_libraries(Game PRIVATE bx::bx)
target_link_libraries(Game PRIVATE bimg::bimg)

if (WIN32)
	target_link_libraries(Game PRIVATE GameEngine)
	target_link_directories(Game PRIVATE
			$<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/../x64/Debug>
			$<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/../x64/Release>
	)
	include_directories(Game PRIVATE "../GameEngine/Include")
else()
	target_link_libraries(Game PRIVATE GameEngine)
	target_link_directories(Game PRIVATE
			$<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/../arm64/Debug>
			$<$<CONFIG:Release>:${CMAKE_SOURCE_DIR}/../arm64/Release>
	)
	include_directories(Game PRIVATE "../GameEngine/Include")
endif()

set_target_properties(Game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/x64/Debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/x64/Release
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/x64/RelWithDebInfo
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_SOURCE_DIR}/x64/MinSizeRel
)

if (WIN32)
	if(MSVC)
		target_compile_options(Game PRIVATE /Zc:__cplusplus /Zc:preprocessor)
	endif()
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Game PROPERTY CXX_STANDARD 20)
endif()
