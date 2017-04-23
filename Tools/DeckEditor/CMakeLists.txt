#------------------------------------------------------------------------------
# Arcomage Tribute
# Part of the Arcomage Tribute CMake Build System.
#------------------------------------------------------------------------------
# Game Build Configuration File
#------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# Packages
set (QT_MIN_VERSION "5.5.0")
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core Widgets)

SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt

file(GLOB ArcomageTributeDeckEditor_UI UI/*.ui)
qt5_wrap_ui(ArcomageTributeDeckEditor_UI_HEADERS ${ArcomageTributeDeckEditor_UI})

include_directories(Include Include/OgreIntegration ../../Game/Include ../../Game/Include/System ThirdParty/Include)
include_directories(${ArcomageTributeDeckEditor_UI_HEADERS})

file(GLOB ArcomageTributeDeckEditor HEADERS Include/*[^_p].h)
file(GLOB ArcomageTributeDeckEditor_SOURCES Source/*.cpp Source/OgreIntegration/*.cpp ThirdParty/Source/Ogre/*.cpp)


add_executable(
   ArcomageDeckEditor
   WIN32
   MACOSX_BUNDLE
   ${ArcomageTributeDeckEditor_SOURCES}
   ${ArcomageTributeDeckEditor_UI_HEADERS}
) 


target_link_libraries (
    ArcomageDeckEditor
    ${Qt5Widgets_LIBRARIES}
   )


