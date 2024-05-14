OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: program.o City.o Product.o ProductData.o Valley.o Ship.o debug.o ProductReference.o
	g++ obj/*.o -o program.exe

%.o: src/%.cc
	mkdir -p obj/
	g++ -c $^ -o obj/$@ $(OPCIONS)

clean:
	rm -rf practica.tar
	rm -rf obj/
	rm -rf *.exe

tar: clean
	rm -rf practica.tar
	cd src; tar -cvf practica.tar *.cc *.hh makefile; mv practica.tar ..

#
# --------------------------------------------------------
# Entrades utilitzades durant el debugging a partir d'aquí
# --------------------------------------------------------
#

# Build and run the code
run: program.exe
	clear
	./program.exe

# Build and run the code with stdin contents from "in"
run_in: program.exe
	clear
	./program.exe <in


# Build and run the code with tsdin contents from "in", and save
# stdout to "out" and compare it against the contents of the file "cor"
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