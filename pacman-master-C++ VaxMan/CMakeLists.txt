project(pacman) # Your project name
cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 11) # This is equal to QMAKE_CXX_FLAGS += -std=c++0x

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# This will find the Qt5 files. You will need a QT5_DIR env variable
find_package(Qt5Widgets REQUIRED) # Equivalent of QT += widgetspacman

set(QT_USE_QTGUI TRUE)

set(SOURCES 
    main.cpp 
    gameclass.cpp 
    blinky.cpp 
    pacman.cpp 
    pinky.cpp 
    ghost.cpp 
    clyde.cpp 
    inky.cpp
    )
    
set(HEADERS 
    gameclass.h 
    pacman.h 
    blinky.h 
    pinky.h 
    ghost.h 
    clyde.h 
    inky.h
    )
    
set(RESOURCES qrc.qrc)    
set(UI )

# This will create you executable
add_executable(pacman ${SOURCES} ${HEADERS} ${UI} ${RESOURCES})
# This will link necessary Qt5 libraries to your project
target_link_libraries(pacman Qt5::Widgets Qt5::Core Qt5::Gui)