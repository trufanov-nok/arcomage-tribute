#------------------------------------------------------------------------------
# Arcomage Tribute
# Part of the Arcomage Tribute CMake Build System.
#------------------------------------------------------------------------------
# Game Build Configuration File
#------------------------------------------------------------------------------


# ------------------------------------------------------------------------------
# Packages
set (QT_MIN_VERSION "5.5.0")
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core Gui Widgets)

#SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt

file(GLOB ArcomageTributeLauncher_UI UI/*.ui)
file(GLOB ArcomageTributeLauncher_HEADERS HEADERS Include/*[^_p].h)
file(GLOB ArcomageTributeLauncher_SOURCES Source/*.cpp)
file(GLOB ArcomageTributeLauncher_SOURCES_Aeon Include/AeonXML-master/src/*.cpp Include/AeonXML-master/src/expat/*.*)
set(ArcomageTributeLauncher_RESOURCE launcher.qrc)
file(GLOB ArcomageTributeLauncher_IMAGES Resources/*.*)

qt5_wrap_cpp(ArcomageTributeLauncher_SOURCES_MOC ${ArcomageTributeLauncher_HEADERS})
qt5_wrap_ui(ArcomageTributeLauncher_HEADERS ${ArcomageTributeLauncher_UI})
qt5_add_resources(ArcomageTributeLauncher_RESOURCE_ADDED ${ArcomageTributeLauncher_RESOURCE})

include_directories(Include
                    Include/AeonXML-master/include
                    Include/AeonXML-master/include/expat/
                    ${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${ArcomageTributeLauncher_UI_HEADERS})

add_executable(
   ArcomageLauncher
   ${ArcomageTributeLauncher_HEADERS}
   ${ArcomageTributeLauncher_SOURCES_MOC}
   ${ArcomageTributeLauncher_SOURCES}
   ${ArcomageTributeLauncher_SOURCES_Aeon}
   ${ArcomageTributeLauncher_RESOURCE_ADDED}
) 


target_link_libraries (
    ArcomageLauncher
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
   )
