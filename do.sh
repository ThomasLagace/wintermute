g++ -c modelframe.cpp -o modelframe.o -I/usr/include/freetype2 -I/usr/include
g++ -c main.cpp -o main.o -I/usr/include/freetype2 -I/usr/include
g++ main.o modelframe.o -o thing.out -lGL -lfreetype -l:k5.a -lGLEW -lglfw -lassimp -lSOIL
