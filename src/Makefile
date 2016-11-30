###################################################
# Sample Makefile for HW8
# Ben Mitchell
# 2016-11-14
#
###################################################

###############################
# Compiler commands
###############################
GCC = g++
CPPFLAGS = -std=c++11 -pedantic -Wall -Wextra -g -I../include

###############################
# pa.hpp variables
###############################
# where to look for .hpp files
INC_DIR = ../include
# where to put .o files
OBJ_DIR = ./obj
# where to put executables
BIN_DIR = ../bin
 
# make sure the output directories exists...
$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

###############################
# targets 
###############################

all: $(BIN_DIR)/a8 

$(BIN_DIR)/a8: $(OBJ_DIR)/a8.o $(OBJ_DIR)/NgramCollection.o $(OBJ_DIR)/Document.o 
	$(GCC) $(CPPFLAGS) $(OBJ_DIR)/a8.o $(OBJ_DIR)/NgramCollection.o $(OBJ_DIR)/Document.o -o $(BIN_DIR)/a8

$(OBJ_DIR)/a8.o: a8.cpp 
	$(GCC) $(CPPFLAGS) -c a8.cpp -o $(OBJ_DIR)/a8.o

$(OBJ_DIR)/NgramCollection.o: NgramCollection.cpp $(INC_DIR)/NgramCollection.hpp 
	 $(GCC) $(CPPFLAGS) -c NgramCollection.cpp -o $(OBJ_DIR)/NgramCollection.o

$(OBJ_DIR)/Document.o: Document.cpp $(INC_DIR)/Document.hpp $(INC_DIR)/NgramCollection.hpp
	 $(GCC) $(CPPFLAGS) -c Document.cpp -o $(OBJ_DIR)/Document.o


###############################
# "utility" rules
###############################
# the .PHONY line says these targets aren't expected to generate files named after the target
.PHONY: clean test

# clean up generated files
clean:
	@echo removing generated files...
	@rm -f $(OBJ_DIR)/*.o 
