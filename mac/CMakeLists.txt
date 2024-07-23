cmake_minimum_required(VERSION 3.24)
project(PhantomDogs)

#has to be under macbuild folder
#add_subdirectory(../source/Nancy)

#TODO: make ${PROJECT_NAME}

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)
set(CMAKE_MACOSX_BUNDLE TRUE)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
if(!XCODE)
set(CMAKE_SKIP_BUILD_RPATH TRUE)
endif()

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)

add_compile_options(-I /Users/jason/Documents/Xcode/PhantomDogs/SapphireEngine/include/) 
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(../SapphireEngine/ext/mac/imgui/misc/cpp)
include_directories(../SapphireEngine/ext/mac/imgui)
include_directories(../SapphireEngine/ext/mac/imgui/backends)
include_directories(../SapphireEngine/ext/mac)
include_directories(../SapphireEngine/ext/loguru-master)
include_directories(../SapphireEngine/ext/toml11)
include_directories(../SapphireEngine/include)
include_directories(../SapphireEngine/include/Engine)
include_directories(../src)
include_directories(..)

find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h)
find_library(AVCODEC_LIBRARY avcodec)

find_path(AVFORMAT_INCLUDE_DIR libavformat/avformat.h)
find_library(AVFORMAT_LIBRARY avformat)

find_path(AVUTIL_INCLUDE_DIR libavutil/avutil.h)
find_library(AVUTIL_LIBRARY avutil)

find_path(AVFILTER_INCLUDE_DIR libavfilter/avfilter.h)
find_library(AVFILTER_LIBRARY avfilter)

find_path(SWSCALE_INCLUDE_DIR libswscale/swscale.h)
find_library(SWSCALE_LIBRARY swscale)

find_path(SWRESAMPLE_INCLUDE_DIR libswresample/swresample.h)
find_library(SWRESAMPLE_LIBRARY swresample)

include_directories(${AVCODEC_INCLUDE_DIR})
include_directories(${AVFORMAT_INCLUDE_DIR})
include_directories(${AVUTIL_INCLUDE_DIR})
include_directories(${AVDEVICE_INCLUDE_DIR})

file(GLOB HEADERS_ENGINE CONFIGURE_DEPENDS "../SapphireEngine/include/Engine/*.h" "../SapphireEngine/include/*.h")
add_library( SapphireEngine SHARED IMPORTED HEADERS_ENGINE)

file(GLOB SOURCES_TOML CONFIGURE_DEPENDS "../SapphireEngine/ext/toml11/*.h" "../SapphireEngine/ext/toml11/*.cpp")
file(GLOB SOURCES_IMGUI_STD CONFIGURE_DEPENDS "../SapphireEngine/ext/mac/imgui/misc/cpp/*.h" "../SapphireEngine/ext/mac/imgui/misc/cpp/*.cpp")
file(GLOB SOURCES_IMGUI CONFIGURE_DEPENDS "../SapphireEngine/ext/mac/imgui/*.h" "../SapphireEngine/ext/mac/imgui/*.cpp")
file(GLOB SOURCES_GFX CONFIGURE_DEPENDS "../SapphireEngine/ext/mac/SDL2/*.h" "../SapphireEngine/ext/mac/SDL2/*.c")
file(GLOB IMGUI_LIB "../SapphireEngine/ext/mac/imgui/build/*.dylib")
file(GLOB SOURCES_LOG CONFIGURE_DEPENDS "../SapphireEngine/ext/loguru-master/*.hpp" "../SapphireEngine/ext/loguru-master/*.cpp")
file(GLOB SOURCES CONFIGURE_DEPENDS "../src/*.h" "../src/*.cpp")
file(GLOB SOURCES_NANCY CONFIGURE_DEPENDS "../src/Nancy/*.h" "../src/Nancy/*.cpp")
file(GLOB SOURCES_NANCY_CHUNKS CONFIGURE_DEPENDS "../src/Nancy/HIFFChunks/*.h" "../src/Nancy/HIFFChunks/*.cpp")
file(GLOB SOURCES_NANCY_ACT CONFIGURE_DEPENDS "../src/Nancy/HIFFChunks/ACT/*.h" "../src/Nancy/HIFFChunks/ACT/*.cpp")
file(GLOB SOURCES_FF CONFIGURE_DEPENDS "../src/player-cpp-ffmpeg-sdl/*.h" "../src/player-cpp-ffmpeg-sdl/*.cpp")
file(GLOB SOURCES_HER CONFIGURE_DEPENDS "../src/oldhertools/*.h" "../src/oldhertools/*.cpp")

#add_executable(PhantomDogs main.cpp arial.ttf AppIcon.icns)
add_executable(PhantomDogs ${SOURCES_TOML} ${SOURCES_IMGUI_STD} ${SOURCES_IMGUI} ${SOURCES_GFX} ${SOURCES_LOG} ${SOURCES_NANCY_CHUNKS} ${SOURCES_NANCY_ACT} ${SOURCES_NANCY} ${SOURCES_FF} ${SOURCES} ${SOURCES_HER})

#target_include_directories(PhantomDogs PRIVATE HEADERS_ENGINE)
target_include_directories(PhantomDogs PRIVATE ../SapphireEngine/include)
target_include_directories(PhantomDogs PRIVATE ../SapphireEngine/include/Engine)
target_link_libraries(PhantomDogs PRIVATE ${IMGUI_LIB})
target_link_libraries(PhantomDogs PRIVATE ${SAPPHIRE_LIB})
#set_target_properties( SapphireEngine PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/res/mylib.so )

target_link_libraries(PhantomDogs PRIVATE stdc++ "-framework Foundation" "-framework Cocoa" objc)
#target_link_libraries(PhantomDogs PRIVATE "-framework CoreFoundation")
target_link_libraries(PhantomDogs PRIVATE SDL2::SDL2)
target_link_libraries(PhantomDogs PRIVATE SDL2_image::SDL2_image)
target_link_libraries(PhantomDogs PRIVATE SDL2_mixer::SDL2_mixer)
target_link_libraries(PhantomDogs PRIVATE SDL2_ttf::SDL2_ttf)
target_link_libraries(PhantomDogs PRIVATE ${AVCODEC_LIBRARY})
target_link_libraries(PhantomDogs PRIVATE ${AVFORMAT_LIBRARY})
target_link_libraries(PhantomDogs PRIVATE ${AVUTIL_LIBRARY})
target_link_libraries(PhantomDogs PRIVATE ${AVFILTER_LIBRARY})
target_link_libraries(PhantomDogs PRIVATE ${SWSCALE_LIBRARY})
target_link_libraries(PhantomDogs PRIVATE ${SWRESAMPLE_LIBRARY})

set(RESOURCE_FILES) # these files go into .app/Contents/Resources/
#set(RESOURCE_FILES arial.ttf AppIcon.icns) # these files go into .app/Contents/Resources/
#set(MACOSX_BUNDLE_ICON_FILE AppIcon.icns)
set_target_properties(PhantomDogs PROPERTIES MACOSX_BUNDLE TRUE MACOSX_FRAMEWORK_IDENTIFIER SapphireForge.TestApp RESOURCE "${RESOURCE_FILES}")
# <lastname>.<firstname>.<appname> or <domain>.<appname>
# (domain formatted as com.example instead of example.com)

#copy frameworks
set(OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
message(PROJECT_SOURCE_DIR="${OUTPUT_DIRECTORY}")
set(EXECUTABLE_OUTPUT_PATH "${OUTPUT_DIRECTORY}")
set(CMAKE_EXECUTABLE_OUTPUT_PATH "${OUTPUT_DIRECTORY}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIRECTORY}")
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIRECTORY}")
SET( ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY}")
SET( ARCHIVE_OUTPUT_DIRECTORY_<CONFIG> "${OUTPUT_DIRECTORY}")

set(APP_BUNDLE_CONTENTS_DIR "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.app/Contents")
set(APP_BUNDLE_FRAMEWORKS_DIR "${APP_BUNDLE_CONTENTS_DIR}/Frameworks")
set(FRAMEWORKS_DIR "${CMAKE_SOURCE_DIR}/Frameworks")

file(GLOB DYLIB_PATHS "${FRAMEWORKS_DIR}/SDL2.framework" "${FRAMEWORKS_DIR}/SDL2_image.framework" "${FRAMEWORKS_DIR}/SDL2_mixer.framework" "${FRAMEWORKS_DIR}/SDL2_ttf.framework" "${FRAMEWORKS_DIR}/libimgui_backend_sdl.dylib" "${FRAMEWORKS_DIR}/libimgui.dylib")
target_link_libraries(PhantomDogs PRIVATE ${DYLIB_PATHS})
file(COPY ${DYLIB_PATHS} DESTINATION ${APP_BUNDLE_FRAMEWORKS_DIR})

if(!XCODE)
add_custom_command(TARGET ${PROJECT_NAME} 
    POST_BUILD COMMAND 
    install_name_tool -add_rpath "@executable_path/../Frameworks/"
    "${APP_BUNDLE_CONTENTS_DIR}/MacOS/${PROJECT_NAME}")
endif()


#bundle game resources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/../romfs"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/../SapphireEngine"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources"
)

if(APPLE)
set(APPS "\${CMAKE_INSTALL_PREFIX}/PhantomDogs.app")
INSTALL(CODE "
        include(BundleUtilities)
        fixup_bundle(\"${APPS}\" \"\" \"${APP_BUNDLE_CONTENTS_DIR}/Frameworks\")
        " COMPONENT Runtime)

    set(CPACK_BINARY_DRAGNDROP ON)
    include(CPack)
endif()