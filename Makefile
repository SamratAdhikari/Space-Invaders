# Makefile

# Target to compile and link the application with an icon
all: compile resources link

# Compile all source files into object files
compile:
	g++ -Isrc/include -c Main.cpp -o SpaceInvaders.o
	g++ -Isrc/include -c Collision.cpp -o Collision.o

# Compile the resource file into an object file
resources:
	windres resources.rc -o resources.o

# Link the object files with the necessary SFML libraries to create the executable
link:
	g++ SpaceInvaders.o Collision.o resources.o -o SpaceInvaders -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -mwindows

# Clean up the build (optional, use `make clean` to remove generated files)
clean:
	rm -f SpaceInvaders.o Collision.o resources.o
