# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(3DViewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Определение операционной системы
if(APPLE)
    set(SHARED_EXT ".dylib")
elseif(WIN32)
    set(SHARED_EXT ".dll")
else()
    set(SHARED_EXT ".so")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Исходные файлы
set(SOURCES
    model/geometry.cpp
    model/io.cpp
    model/model.cpp
    view/mainwindow.cpp
    view/modelwidget.cpp
    view/rendering.cpp
    view/main.cpp
    controller/controller.cpp
)

# Заголовочные файлы
set(HEADERS
    model/geometry.h
    model/io.h
    model/model.h
    view/mainwindow.h
    view/modelwidget.h
    view/rendering.h
    controller/controller.h
)

# Создание исполняемого файла
add_executable(3DViewer ${SOURCES} ${HEADERS})
target_link_libraries(3DViewer Qt6::Core Qt6::Widgets)

# Установка выходной директории
set_target_properties(3DViewer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
