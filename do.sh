g++ -c modelframe.cpp -o modelframe.o -I/usr/include/freetype2
g++ -c main.cpp -o main.o -I/usr/include/freetype2
g++ main.o modelframe.o -o thing.out -lGL -lfreetype -l:k5.a -lGLEW -lglfw -lassimp -lSOIL
