g++ -c modelframe.cpp -o modelframe.o -I/usr/include/freetype2 -I/usr/include
g++ -c main.cpp -o main.o -I/usr/include/freetype2 -I/usr/include
g++ main.o modelframe.o -o thing.out -lGL -lfreetype -lk5 -lGLEW -lglfw -lassimp -lSOIL
