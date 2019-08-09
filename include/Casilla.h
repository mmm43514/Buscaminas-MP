#ifndef _CASILLA_H_
#define _CASILLA_H_

#include <iostream>
using namespace std;

struct Casilla{
	bool bomba, abierta, marcada;

	Casilla();
};
struct CeldaPosicion{
		int fila;
		int columna;
		CeldaPosicion *siguiente;
};

ofstream &operator << (ofstream &os, const Casilla &c);

#endif

