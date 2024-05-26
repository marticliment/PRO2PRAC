ifndef MAKEFLAGS
CPUS ?= $(shell nproc)
MAKEFLAGS += -j $(CPUS) -l $(CPUS)
endif

OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: program.o City.o Product.o ProductData.o Valley.o Ship.o ProductReference.o
	g++ *.o -o program.exe

%.o: %.cc
	g++ -c $^ -o $@ $(OPCIONS)


clean:
	rm -rf practica.tar

	rm -rf *.exe
	rm -rf *.o

tar: clean docs
	rm -rf practica.tar
	tar -cvf practica.tar *.cc *.hh makefile
	tar -rvf practica.tar Justificació.pdf
	zip -r html.zip html/*
	tar -rvf practica.tar html.zip
	rm html.zip

run: program.exe
	clear
	./program.exe

run_in: program.exe
	clear
	./program.exe <in

diff: program.exe
	./program.exe <in >out
	clear
	# _________________________________________________________________________
	#                                                  <<COR   |   OUT>>
	#
	diff cor out --color -y --left-column --width=120 --minimal
	#
	#                                                  <<COR   |   OUT>>
	# _________________________________________________________________________

time: clean program.exe
	chmod +x program.exe
	time --verbose ./program.exe <in >out

docs: src/*.cc src/*.hh doxyfile
	rm -rf docs
	doxygen doxyfile