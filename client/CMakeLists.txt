CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
CMAKE_POLICY(VERSION 2.6)
PROJECT(client)

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

#FIND_PACKAGE(SFML REQUIRED)

SET(SRCS
  ./networking/client.hpp
  ./networking/main_client.cpp
  ./networking/client.cpp
  ./interfacing/interfacing.hpp
  ./interfacing/interfacing.cpp
  ./game/mothership.hpp
  ./game/player.hpp
  ./game/game.hpp
  ./game/game.cpp
  ./game/planet.hpp
  ./game/ship.cpp
  ./game/planets/barrierplanet.hpp
  ./game/fleet.hpp
  ./game/ship.hpp
  ./game/fleet.cpp
  ./game/mothership.cpp)

SET(PROGRAMS client)

#INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

ADD_EXECUTABLE(client ${SRCS})

TARGET_LINK_LIBRARIES(client
  #${SFML_LIBRARY}
  -lsfml-graphics
  -lsfml-window
  -lsfml-network
  -lsfml-system
  )

INSTALL(TARGETS client RUNTIME DESTINATION .)

SET_TARGET_PROPERTIES(client PROPERTIES COMPILE_FLAGS "${FLAGS}")