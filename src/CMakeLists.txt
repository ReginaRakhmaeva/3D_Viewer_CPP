# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(3DViewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Исходные файлы
set(SOURCES
    src/model/geometry.cpp
    src/model/io.cpp
    src/model/strategies.cpp
    src/model/model.cpp
    src/view/mainwindow.cpp
    src/view/modelwidget.cpp
    src/controller/controller.cpp
    src/view/main.cpp
)

# Заголовочные файлы
set(HEADERS
    src/model/geometry.h
    src/model/io.h
    src/model/strategies.h
    src/model/model.h
    src/view/mainwindow.h
    src/view/modelwidget.h
    src/controller/controller.h
)

# Создание исполняемого файла
qt6_add_executable(3DViewer ${SOURCES} ${HEADERS})
qt6_add_resources(3DViewer "resources" PREFIX "/" FILES
    # ресурсы если нужны
)

target_link_libraries(3DViewer Qt6::Core Qt6::Widgets)
