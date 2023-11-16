LAGS = -Wall -Wextra -Werror -std=c11
LFLAGS = -lcheck -lm -lpthread
SOURCES=s21_*.c
OBJECTS=s21_*.o

ifeq ($(shell uname -s), Linux)
	LFLAGS = -lm -lpthread -lcheck -lsubunit
endif

all: clean calc.a

test: calc.a
	gcc $(FLAGS) -c test.c
	gcc test.o $(FLAGS) $(OBJECTS) $(LFLAGS) -L. build/calc.a -o test
	rm -rf *.o
	
calc.a:
	gcc $(FLAGS) -c $(SOURCES)
	ar rcs build/calc.a $(OBJECTS)
	ranlib build/calc.a

install:
	rm -rf build
	mkdir build
	cd build && cmake ../Calc/CMakeLists.txt
	cd Calc && make
	cp -rf Calc/calc $(HOME)/Desktop/Calculator.a

uninstall: clean
	rm -rf build
	rm -rf Calc/calc.a
	rm -rf Calc/CMakeFiles
	rm -rf Calc/Makefile
	rm -rf Calc/calc_autogen
	rm -rf Calc/CMakeCache.txt
	rm -rf Calc/cmake_install.cmake
	rm -rf $(HOME)/Desktop/Calculator.a

dist: 
	mkdir SmartCalc_v1.0/
	mkdir SmartCalc_v1.0/src
	cp Makefile *.c *.h *.user SmartCalc_v1.0/src/
	cp -R calc SmartCalc_v1.0/src/
	tar cvzf SmartCalc_v1.0.tgz SmartCalc_v1.0/
	mv SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf SmartCalc_v1.0/

dvi:
	open instruction.html

gcov_report: clean add_coverage test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.o gcov_report *.a *.gcda *.gcno test test.info

add_coverage:
	$(eval FLAGS += --coverage)
