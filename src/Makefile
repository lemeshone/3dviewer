CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -I. -I./model
GTEST_FLAGS = -lgtest -lgtest_main -pthread
PRO_FILE = project.pro
BUILD_DIR = build
DIST_DIR = s21_3DViewer

all: install

install:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && qmake6 ../$(PRO_FILE)
	$(MAKE) -C $(BUILD_DIR)

run:
	./$(BUILD_DIR)/project

uninstall:
	rm -rf build

test:
	$(CXX) $(CXXFLAGS) tests/*.cpp model/*.cpp $(GTEST_FLAGS) -o tests/test
	cd tests && ./test

dvi:
	latex -output-directory=dvi dvi/documentation.tex
	dvips -o dvi/documentation.ps dvi/documentation.dvi
	ps2pdf dvi/documentation.ps dvi/documentation.pdf
	rm -f dvi/*.aux dvi/*.log dvi/*.toc dvi/*.out dvi/*.ps

dist:
	mkdir -p $(DIST_DIR)
	cp -a Controller $(DIST_DIR)
	cp -a model $(DIST_DIR)
	cp -a View $(DIST_DIR)
	cp -a tests $(DIST_DIR)
	cp -a dvi $(DIST_DIR)
	cp -a objModels $(DIST_DIR)
	cp main.cpp $(DIST_DIR)
	cp project.pro $(DIST_DIR)
	cp Makefile $(DIST_DIR)
	tar -czf 3DViewer.tar.gz $(DIST_DIR)
	rm -rf $(DIST_DIR)

clang_check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n Controller/*.cpp Controller/*.h
	clang-format -n model/*.cpp model/*.h
	clang-format -n View/*.cpp View/*.h
	clang-format -n main.cpp
	clang-format -n tests/*.c tests/*.cpp
	rm -f .clang-format

clang_format:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i Controller/*.cpp Controller/*.h
	clang-format -i model/*.cpp model/*.h
	clang-format -i View/*.cpp View/*.h
	clang-format -i main*.cpp
	clang-format -i tests/*.cpp
	rm -f .clang-format

clean:
	rm -rf $(BUILD_DIR)
	rm -f tests/test
	rm -f dvi/*.dvi dvi/*.pdf
	rm -rf 3DViewer.tar.gz
	rm -rf 3DViewer

rebuild: clean all

.PHONY: dvi