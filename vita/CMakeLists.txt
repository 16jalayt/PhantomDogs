cmake_minimum_required(VERSION 3.2)
SET(CMAKE_INSTALL_PREFIX ./lib)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(PhantomDogs)
include("${VITASDK}/share/vita.cmake" REQUIRED)

find_package(SDL2 REQUIRED)

set(VITA_APP_NAME "Phantom Dogs")
set(VITA_TITLEID  "VSDK00905")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
#might allow to remove additions from loguru *_additions
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

include_directories(
  "$ENV{VITASDK}/arm-vita-eabi/include/SDL2"
  "$ENV{VITASDK}/arm-vita-eabi/include/imgui_vita2d"
  "../src/"
  "../src/player-cpp-ffmpeg-sdl"
  "../SapphireEngine/ext/loguru-master"
  "../SapphireEngine/include"
)

file(GLOB_RECURSE game_SRC CONFIGURE_DEPENDS "../src/*.h" "../src/*.cpp")
file(GLOB_RECURSE game_EXT CONFIGURE_DEPENDS "../SapphireEngine/vita/ext/*.h" "../SapphireEngine/vita/ext/*.hpp" "../SapphireEngine/vita/ext/*.cpp")

add_executable(${PROJECT_NAME}
  ${game_SRC}
  ${game_EXT}
)

link_directories("../SapphireEngine/vita/build")
target_link_directories(${PROJECT_NAME} PRIVATE "../SapphireEngine/vita/build")

target_link_libraries(${PROJECT_NAME}
  SapphireEngine
  SDL2_mixer 
  SDL2_image 
  SDL2_ttf 
  SDL2_gfx 
  SDL2 
  taihen_stub
  SceAppMgr_stub
  SceProcessmgr_stub
  SceIme_stub_weak
  avformat
  avfilter
  swscale 
  avcodec
  webpdemux
  webp
  opusfile
  vorbisfile
  vorbis
  ogg
  mpg123
  FLAC
  mikmod
  modplug
  opus
  swresample 
  mp3lame
  avutil 
  freetype 
  mpdec 
  xmp
  jpeg 
  png 
  bz2 
  SceMotion_stub
  SceCommonDialog_stub
  SceHid_stub
  SceGxm_stub
  SceAudio_stub
  SceAudioIn_stub
  SceAvPlayer_stub
  ScePower_stub
  SceDisplay_stub
  SceCtrl_stub
  SceTouch_stub
  SceIofilemgr_stub
  SceNet_stub
  SceNetCtl_stub
  SceSsl_stub
  SceVshBridge_stub
  SceSysmodule_stub
  ${SDL2_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  pthread
  intl
  fribidi
  harfbuzz
  gcc
  z
  m
)

#Cant find what actual platform define is. Not __PSP2__
add_compile_definitions(__VITA__)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)