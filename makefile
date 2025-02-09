compiler = g++
flag = -std=c++20

headerFolder = -I /opt/homebrew/Cellar/sfml@2/2.6.2/include
libFolder = -L /opt/homebrew/Cellar/sfml@2/2.6.2/lib
lib = -lsfml-graphics -lsfml-window -lsfml-system

inpFile = main.cpp Object.cpp
objFile = $(inpFile:.cpp=.o)
outFile = a.out

all:
	$(compiler) $(flag) $(headerFolder) $(libFolder) $(lib) $(inpFile) -o $(outFile)

