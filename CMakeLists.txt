cmake_minimum_required(VERSION 4.2)
project(OOP6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(OOP6
        main.cpp

        MainWindow.cpp
        MainWindow.h

        Shape.cpp
        Shape.h

        ShapeStorage.cpp
        ShapeStorage.h

        Ccircle.cpp
        Ccircle.h

        CRectangle.cpp
        CRectangle.h

        CSquare.cpp
        CSquare.h

        CEllipse.cpp
        CEllipse.h

        CLine.cpp
        CLine.h

        CTriangle.cpp
        CTriangle.h
        Group.cpp
        Group.h
)
target_link_libraries(OOP6
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

