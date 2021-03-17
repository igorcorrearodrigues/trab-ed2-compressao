CC=g++

CC_FLAGS=-W -Wall -pedantic -std=c++11

INC_DIR=./include

MAIN_CPP=main.cpp ./src/lz77.cpp

MAIN_HPP=$(INC_DIR)/lz77.hpp

build: main

main: $(MAIN_CPP) $(MAIN_HPP)
	$(CC) $(CC_FLAGS) -o $@ $(MAIN_CPP) -I $(INC_DIR) 