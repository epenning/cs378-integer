FILES := 							\
    .gitignore                      \
    .travis.yml					    \
    Integer.h						\
    RunInteger.c++					\
	RunInteger.out					\
	TestInteger.c++					\
	TestInteger.out					\
	html/							\
	integer.log

ifeq ($(shell uname), Darwin)
	ifeq ($(CXX), clang++)
	    COVFLAGS := --coverage
	    GCOV     := gcov-4.6 --relative-only
	else
	    CXX       := g++
	    CXXVER    := --version 2>&1 | grep c++
	    GTESTVER  := head -1 /usr/local/src/gtest-1.7.0/CHANGES
	    GCOV      := gcov
	    GCOVFLAGS := -fprofile-arcs -ftest-coverage
	    GCOVVER   := -version | grep version
	endif
    BOOST     := /usr/local/src/boost_1_57_0/boost
    LDFLAGS   := -lgtest_main
    VALGRIND  :=
else
	ifeq ($(CXX), clang++)
	    COVFLAGS := --coverage
	    GCOV     := gcov-4.6 --relative-only
	else
	    CXX       := g++-4.8
	    CXXVER    := --version 2>&1 | grep g++
	    GTESTVER  := dpkg -l libgtest-dev | grep libgtest
	    GCOV      := gcov-4.8  --relative-only
	    GCOVFLAGS := -fprofile-arcs -ftest-coverage
	    GCOVVER   := -v | grep gcov
	endif
    BOOST     := /usr/include/boost
    LDFLAGS   := -lgtest -lgtest_main -pthread
    VALGRIND  := valgrind
endif

CXXFLAGS := -pedantic -std=c++11 -Wall

.PRECIOUS: %.app

check:
	@for i in $(FILES);                                         \
	do                                                          \
        [ -e $$i ] && echo "$$i found" || echo "$$i NOT FOUND"; \
    done

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunInteger
	rm -f RunInteger.out
	rm -f TestInteger
	rm -f TestInteger.out

sync:
	@echo `pwd`
	@rsync -r -t -u -v --delete        \
    --include "Integer.h"              \
    --include "makefile"               \
    --include "RunInteger.c++"         \
    --exclude "*"                      \
    . downing@$(CS):cs/cs378/github/c++/integer/

all: RunInteger.out TestInteger.out

run: RunInteger.out

test: TestInteger.out

integer-tests:
	git clone https://github.com/cs378-summer-2015/integer-tests.git

html: Doxyfile Integer.h RunInteger.c++ TestInteger.c++
	doxygen Doxyfile
	
Integer.log:
	git log > Integer.log
	
Doxyfile:
	doxygen -g
	
versions:
	uname -a
	@echo
	printenv
	@echo
	which $(CXX)
	@echo hi
	$(CXX) $(CXXVER)
	@echo hi
	$(GTESTVER)
	@echo
	which $(GCOV)
	@echo
	$(GCOV) $(GCOVVER)
	@echo
	grep "#define BOOST_VERSION " $(BOOST)/version.hpp
ifdef VALGRIND
	@echo
	which $(VALGRIND)
	@echo
	$(VALGRIND) --version
endif
	@echo
	which doxygen
	@echo
	doxygen --version

RunInteger: Integer.h RunInteger.c++
	$(CXX) $(CXXFLAGS) RunInteger.c++ -o RunInteger

RunInteger.out: RunInteger
	./RunInteger > RunInteger.out
	cat RunInteger.out
	
TestInteger: Integer.h TestInteger.c++
	$(CXX) $(GCOVFLAGS) $(CXXFLAGS) TestInteger.c++ -o TestInteger $(LDFLAGS)

TestInteger.out: TestInteger
	$(VALGRIND) ./TestInteger  >  TestInteger.out 2>&1
	$(GCOV) -b Integer.h       >> TestInteger.out
	$(GCOV) -b TestInteger.c++ >> TestInteger.out
	cat TestInteger.out
