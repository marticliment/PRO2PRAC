ifndef MAKEFLAGS
CPUS ?= $(shell nproc)
MAKEFLAGS += -j $(CPUS) -l $(CPUS)
# $(info Note: running on $(CPUS) CPU cores by default, use flag -j to override.) 
endif

OPCIONS = -D_JUDGE_ -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers

program.exe: program.o City.o Product.o ProductData.o Valley.o Ship.o ProductReference.o
	g++ obj/*.o -o program.exe

%.o: src/%.cc
	mkdir -p obj/
	g++ -c $^ -o obj/$@ $(OPCIONS)

clean:
	rm -rf practica.tar
	rm -rf obj/
	rm -rf *.exe

tar: clean docs
	rm -rf practica.tar
	cd src; tar -cvf practica.tar *.cc *.hh makefile; mv practica.tar ..
	cd docs; zip -r html.zip html/*; mv html.zip ..
	tar -rvf practica.tar Justificació.pdf
	tar -rvf practica.tar html.zip
	rm html.zip



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

docs: src/*.cc src/*.hh doxyfile
	rm -rf docs
	doxygen doxyfile

doxy: docs