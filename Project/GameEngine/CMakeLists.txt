file(GLOB_RECURSE SOURCES "Source/*.cpp" "Include/*.hpp")

add_library(GameEngine SHARED ${SOURCES} ${CLASSES})

target_compile_definitions(GameEngine PRIVATE GAMEENGINEAPI_EXPORT)

# Thirdparty
target_link_libraries(GameEngine PRIVATE SoLoud::SoLoud)
target_link_libraries(GameEngine PRIVATE SDL3::SDL3)
target_link_libraries(GameEngine PRIVATE Assimp::Assimp)
target_link_libraries(GameEngine PRIVATE bgfx::bgfx)
target_link_libraries(GameEngine PRIVATE bx::bx)
target_link_libraries(GameEngine PRIVATE bimg::bimg)

if (WIN32)
	if(MSVC)
		target_compile_options(GameEngine PRIVATE /Zc:__cplusplus /Zc:preprocessor)
		target_compile_options(GameEngine PRIVATE /WX /wd4251 /wd4275 /wd4267)
	endif()
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameEngine PROPERTY CXX_STANDARD 20)
endif()
