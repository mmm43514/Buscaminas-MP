AR= ar
CXX= g++
CXXFLAGS= -Wall -g -I./include 
LDFLAGS=
LDLIBS= -lformas
SRC= src/
OBJ= obj/
LIB= lib/
BIN= bin/
INC= include/
all: $(BIN)BuscaMinas
$(OBJ)Casilla.o: $(INC)Casilla.h $(SRC)Casilla.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)Casilla.o $(SRC)Casilla.cpp
$(OBJ)Tablero.o: $(INC)Tablero.h $(SRC)Tablero.cpp 
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)Tablero.o $(SRC)Tablero.cpp 
$(OBJ)CampoMinas.o: $(INC)CampoMinas.h $(SRC)CampoMinas.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)CampoMinas.o $(SRC)CampoMinas.cpp
$(OBJ)BuscaMinas.o: $(INC)Tablero.h $(INC)CampoMinas.h $(INC)Casilla.h $(SRC)BuscaMinas.cpp
	$(CXX) -c $(CXXFLAGS) -o $(OBJ)BuscaMinas.o $(SRC)BuscaMinas.cpp
$(BIN)BuscaMinas: $(OBJ)BuscaMinas.o $(OBJ)CampoMinas.o $(OBJ)Tablero.o $(OBJ)Casilla.o
	$(CXX) -o $(BIN)BuscaMinas $(OBJ)BuscaMinas.o $(OBJ)CampoMinas.o $(OBJ)Tablero.o $(OBJ)Casilla.o
clean:
	@echo "\nLimpiando..."
	rm $(OBJ)*.o
cleanall: clean
	@echo "\nLimpiando ejecutables..."
	rm $(BIN)*
