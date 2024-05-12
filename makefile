OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers -DDEBUG


program.exe: program.o City.o NavigationDecisions.o Product.o ProductData.o Valley.o Ship.o debug.o ProductReference.o 
	g++ obj/*.o -o program.exe

%.o: src/%.cc
	mkdir -p obj/
	g++ -c $^ -o obj/$@ $(OPCIONS)

clean: clear
clear:
	rm -rf dist/
	rm -rf obj/
	rm -rf *.exe


tar:
	mkdir -p dist/
	tar -cvf dist/practica.tar src/*.cc makefile

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
	diff cor out --color -y --left-column --width=120 --minimal
