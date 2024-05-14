OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: program.o City.o NavigationDecisions.o Product.o ProductData.o Valley.o Ship.o debug.o ProductReference.o
	g++ *.o -o program.exe

%.o: %.cc
	g++ -c $^ -o $@ $(OPCIONS)

clean:
	rm -rf practica.tar
	rm -rf *.exe
	rm -rf *.o

tar: clean
	rm -rf practica.tar
	tar -cvf practica.tar *.cc *.hh makefile
