# Makefile для 3D Viewer
# Адаптирован под стиль предыдущего проекта

# === Определение ОС ===
UNAME_S := $(shell uname -s)

# === Компиляторы и флаги ===
CXX = g++
CXXFLAGS = -fPIC -Wall -Wextra -std=c++20 -g -O0 -fvisibility=hidden

# === Настройки под ОС ===
ifeq ($(UNAME_S),Linux)
    LDFLAGS = -ldl
    SHARED_EXT = .so
    SHARED_FLAGS = -shared
endif
ifeq ($(UNAME_S),Darwin)
    LDFLAGS = 
    SHARED_EXT = .dylib
    SHARED_FLAGS = -dynamiclib
endif
ifeq ($(OS),Windows_NT)
    LDFLAGS = 
    SHARED_EXT = .dll
    SHARED_FLAGS = -shared
endif

# === Qt настройки ===
QT_BUILD_DIR = build_qt
QTFLAGS = $(shell pkg-config --cflags Qt6Core Qt6Widgets 2>/dev/null || echo "")
QTLIBS = $(shell pkg-config --libs Qt6Core Qt6Widgets 2>/dev/null || echo "")

# === Исходники ===
SOURCES = \
	model/geometry.cpp \
	model/io.cpp \
	model/model.cpp \
	view/mainwindow.cpp \
	view/modelwidget.cpp \
	view/rendering.cpp \
	view/main.cpp \
	controller/controller.cpp

# === Цели ===
all: 3DViewer

# === Прямая сборка с g++ ===
3DViewer: $(SOURCES)
	@echo "=== Building 3D Viewer with g++ ==="
	$(CXX) $(CXXFLAGS) $(QTFLAGS) -o $@ $(SOURCES) $(QTLIBS) $(LDFLAGS)
	@echo "=== Build completed ==="

clean:
	@echo "=== Cleaning build artifacts ==="
	# Удаляем исполняемые файлы
	rm -f 3DViewer 3DViewer_qt
	
	# Удаляем объектные файлы
	rm -f *.o
	
	# Удаляем файлы покрытия кода
	rm -f *.gcda *.gcno *.gcov
	
	# Удаляем тестовые исполняемые файлы
	rm -f test/test_*_bin
	
	# Удаляем файлы покрытия тестов
	rm -f test/*.gcno test/*.gcda
	rm -f test/coverage.info test/coverage_filtered.info
	rm -rf test/coverage_report test/lcov_report
	
	# Удаляем директории сборки Qt
	rm -rf $(QT_BUILD_DIR)
	
	# Удаляем документацию и архивы
	rm -rf doc/
	rm -rf dist/
	rm -f Doxyfile
	
	# Удаляем macOS служебные файлы
	find . -name "._*" -type f -delete
	find . -name ".DS_Store" -type f -delete

	@echo "=== Clean completed ==="

# === Тесты ===
# TEST_SOURCES = test/test_geometry.cpp \
#                test/test_io.cpp \
#                test/test_model.cpp \
#                test/test_main.cpp

# TEST_BIN = test/test_3dviewer_bin

# # Тесты
# test: $(TEST_SOURCES)
# 	@echo "=== Building 3D Viewer tests ==="
# 	@mkdir -p test
# 	$(CXX) $(CXXFLAGS) -o $(TEST_BIN) $(TEST_SOURCES) -lgtest -lgtest_main -lpthread
# 	@echo "=== Running 3D Viewer tests ==="
# 	./$(TEST_BIN)

# Покрытие кода
coverage:
	@echo "=== Building and running tests with coverage ==="
	$(CXX) $(CXXFLAGS) -fprofile-arcs -ftest-coverage -o $(TEST_BIN) $(TEST_SOURCES) -lgtest -lgtest_main -lpthread
	./$(TEST_BIN)
	@echo "=== Generating coverage report ==="
	gcov -r model/*.cpp view/*.cpp controller/*.cpp
	lcov --capture --directory . --output-file test/coverage.info
	lcov --remove test/coverage.info '/usr/*' '/opt/*' '/tmp/*' 'test_*' --output-file test/coverage_filtered.info
	genhtml test/coverage_filtered.info --output-directory test/coverage_report --title "3D Viewer Coverage"


