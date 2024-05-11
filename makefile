OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -fno-extended-identifiers -DDEBUG


program.exe: program.o City.o NavigationDecisions.o Product.o ProductData.o RiverArray.o Ship.o
	#⌛ Assembling executable...
	g++ obj/*.o -o program.exe
	#✅ Build completed!

%.o: src/%.cc
	#🛠️  Compiling $^...
	mkdir -p obj/
	g++ -c $^ -o obj/$@ $(OPCIONS)

clean: clear
clear:
	rm -rf dist/
	rm -rf obj/
	rm -rf *.exe
	#🧹 Clean complete!


tar:
	mkdir -p dist/
	tar -cvf dist/practica.tar src/*.cc makefile
	#📦 Tar creation complete!

run: program.exe
	./program.exe

run_in: program.exe
	./program.exe <in
