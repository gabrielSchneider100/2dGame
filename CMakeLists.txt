cmake_minimum_required(VERSION 3.9)
project(MarioLikev1)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-pthread -lSDL2_mixer -lSDL2_ttf")

find_package(SDL2 REQUIRED)
find_package(SDL_mixer REQUIRED)

include_directories( ${SDL2_INCLUDE_DIRS} ${SDL_mixer_INCLUDE_DIRS} )


add_executable(MarioLikev1 main.cpp GameState.cpp GameState.h Button.cpp Button.h guiEntity.h GameLevel.h TextEntity.cpp TextEntity.h Player.cpp Player.h gameObject.h Camera.cpp Camera.h Platform.cpp Platform.h GameEntity.h)

target_link_libraries(MarioLikev1 ${SDL2_LIBRARIES} ${SDL_mixer_LIBRARIES})