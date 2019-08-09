#ifndef _CAMPOMINAS_H_
#define _CAMPOMINAS_H_

#include "Casilla.h"
#include "Tablero.h"
#include <iostream>
#include<string>
#include<stdlib.h>
#include<ctime>
#include<iomanip>
#include<fstream>

using namespace std;

class CampoMinas{
private:
	bool mina_explosionada;

	int BombasAlrededor(int f, int c, Tablero &tablero);
public:
	CampoMinas(int i, int j, int minas, Tablero &tablero);

	int GetFilasTablero(Tablero &tablero);

	int GetColumnasTablero(Tablero &tablero);

	bool MinaExplosionada(Tablero &tablero);

	bool PartidaGanada(Tablero &tablero);

	bool Marcar(int f, int c, Tablero &tablero);

	bool Abrir(int f, int c, Tablero &tablero);

	void Add(CeldaPosicion* &pos, int i, int j);

	CeldaPosicion ExtraerElemento(CeldaPosicion* &pos);

	void PrettyPrint(Tablero &tablero, ostream &salida = cout);

	void MostrarTodo(Tablero &tablero, ostream &salida = cout);
	
   bool Escribir(char * escribir, Tablero &t);

	bool Leer(char * leer, Tablero* &t);
};
#endif
