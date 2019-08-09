#ifndef _TABLERO_H_
#define _TABLERO_H_

#include "Casilla.h"
#include <iostream>

using namespace std;

class Tablero{
private:
	Casilla ** datos;
	int f_util;
	int c_util;
public:
	Tablero(int f, int c);

	Tablero(Tablero& tab);

	void Destructor();
	
	int GetFilas() const;

	int GetColumnas() const;

	Casilla GetElemento(int i, int j) const;

	void Modificar(int i, int j, char cambiar);

	Tablero &operator = (const Tablero &t);
	
};

ofstream &operator << (ofstream &os, const Tablero &t);


#endif
