CC = gcc
LIBS = -lpthread -lm -lcheck

CCFLAGS =  -std=c11
COVERAGE = 

SOURCES = afine.c parser.c
OBJECTS = $(patsubst %.c,%.o,$(SOURCES))


TESTS_DIR = tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.c)
TESTS_OBJ = $(patsubst %.c,%.o,$(notdir $(TESTS_SRC)))


TARGET = afine.a

ifeq ($(shell uname -s), Linux)
	LIBS = -lpthread -lcheck -lsubunit -lm
endif

## Application Block
.PHONY: all clean test gcov_report

add_coverage:
	$(eval COVERAGE += --coverage)

$(TARGET): clean
	$(CC) $(CCFLAGS) $(COVERAGE) -c $(SOURCES)
	ar rc $@ $(OBJECTS)
	ranlib $@

test: $(TARGET)
	$(CC) $(CCFLAGS) -c $(TESTS_SRC)
	$(CC) $(CCFLAGS) $(COVERAGE) $(TESTS_OBJ) $(LIBS) $(TARGET) -o $@
	rm -rf $@.o

gcov_report: add_coverage test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info


all: gcov_report install

gcov_report: clean test

install:
	mkdir build
	mkdir screenshots 
	cd App && qmake && make
ifeq ($(shell uname -s), Linux)
	mv ./App/App ./build/app.exe
else
	mv ./App/App.app/Contents/MacOS/App ./build/app.exe
endif
	rm -rf App/*.o App/Makefile

uninstall: clean
	rm -rf build screenshots

run:
	./build/app.exe

clean:
	rm -rf build_files *.gcda *.o *.gcno test report *.info

