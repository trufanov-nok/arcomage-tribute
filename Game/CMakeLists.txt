#------------------------------------------------------------------------------
# Arcomage Tribute
# Part of the Arcomage Tribute CMake Build System.
#------------------------------------------------------------------------------
# Game Build Configuration File
#------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# Packages
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system filesystem regex thread )


Find_Package ( SDL REQUIRED )
Find_Package ( SDL_image REQUIRED )
Find_Package ( SDL_ttf REQUIRED )
Find_Package ( SDL_mixer REQUIRED )
find_package ( Lua51 REQUIRED )

#SET(CMAKE_BUILD_TYPE Debug)


# BOOST
include_directories ( ${Boost_INCLUDE_DIRS} )

# SDL
include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLMIXER_INCLUDE_DIR})
include_directories(${SDLTTF_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})

#LUA
include_directories(${LUA_INCLUDE_DIR})

include_directories(Include Include/txml Include/Lua Include/System Include/UI)
file(GLOB ArcomageTribute_HEADERS Include/*[^_p].h)
file(GLOB ArcomageTribute_SOURCES Source/*.cpp Source/System/*.cpp Include/txml/*.cpp)

add_executable(
   ArcomageTribute 
   ${ArcomageTribute_SOURCES}
) 

if (PKG_CONFIG_FOUND)
        PKG_CHECK_MODULES(UNZIP minizip)
endif (PKG_CONFIG_FOUND)

target_link_libraries (
    ArcomageTribute
    ${Boost_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY} 
    ${SDLTTF_LIBRARY} 
    ${SDLMIXER_LIBRARY} 
    ${SDLMAIN_LIBRARY}
    ${LUA_LIBRARIES}
    ${UNZIP_LIBRARIES}
   )
