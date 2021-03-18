CC=g++

CC_FLAGS=-W -Wall -pedantic -std=c++11

INC_DIR=./include

LZ77_CPP=./src/lz77.cpp
LZ77_HPP=$(INC_DIR)/lz77.hpp

ENCODE_CPP=encode.cpp $(LZ77_CPP)
ENCODE_HPP=main_template.hpp $(LZ77_HPP)

DECODE_CPP=decode.cpp $(LZ77_CPP)
DECODE_HPP=main_template.hpp $(LZ77_HPP)

build: encode decode

encode: $(ENCODE_CPP) $(ENCODE_HPP)
	$(CC) $(CC_FLAGS) -o $@ $(ENCODE_CPP) -I $(INC_DIR) 

decode: $(DECODE_CPP) $(DECODE_HPP)
	$(CC) $(CC_FLAGS) -o $@ $(DECODE_CPP) -I $(INC_DIR) 
