#include "Tablero.h"
#include "Casilla.h"
#include<fstream>

Tablero::Tablero(int f, int c)
	:f_util(f), c_util(c){
	datos = new (nothrow) Casilla * [f];
	if (!datos) 
		cerr << "Error en reserva" << endl;
	else {
		datos[0] = new (nothrow) Casilla [f*c];
		if (!datos[0]) { 
			cerr << "Error en reserva (2)" << endl; 
			delete [] datos; 
			datos = 0; 
		}
		else
			for (int i = 1; i < f ; i++)
				datos[i] = datos[i-1] + c; 
	}
}

Tablero::Tablero(Tablero& tab){
	f_util = tab.GetFilas();
	c_util = tab.GetColumnas();

	for (int i = 0; i < f_util; i++){
		for (int j = 0; j < c_util; j++){
			datos[i][j] = tab.GetElemento(i,j);
		}
	}
}

void Tablero::Destructor(){
	delete [] datos[0];
	delete [] datos;
}
	
int Tablero::GetFilas() const{
	return f_util;
}

int Tablero::GetColumnas() const{
	return c_util;
}

Casilla Tablero::GetElemento(int i, int j) const{
	if (i < GetFilas() && j < GetColumnas())
		return datos[i][j];
}

void Tablero::Modificar(int i, int j, char cambiar){
	Casilla *datos_i_j = &datos[i][j];
	if (cambiar == 'b')
		datos_i_j->bomba = !datos_i_j->bomba;
	else
		if (cambiar == 'a')
			datos_i_j->abierta = !datos_i_j->abierta;
		else
			if (cambiar == 'm')
				datos_i_j->marcada = !datos_i_j->marcada;
}
	
Tablero &Tablero::operator = (const Tablero &t){
	if (this != &t){
		Destructor();
		f_util = t.GetFilas();
		c_util = t.GetColumnas();
		
		Tablero(f_util,c_util);

		for (int i = 0; i < f_util; i++)
			for (int j = 0; j < c_util; j++)
				datos[i][j] = t.GetElemento(i,j);
	}
	else
		datos = NULL;
	return *this;
}

ofstream &operator << (ofstream &os, const Tablero &t){
	int f_util = t.GetFilas();
	int c_util = t.GetColumnas();
   
	for (int i = 0; i < f_util; i++){
		for (int j = 0; j < c_util; j++)
			os << t.GetElemento(i,j);
      
		os << "\n";
	}

   return os;
}

