#include "Casilla.h"
#include<fstream>

Casilla::Casilla(){bomba=abierta=marcada=false;}

ofstream &operator << (ofstream &os, const Casilla &c){
		if (c.bomba == false)
			os << "f";
		else
			os << "t";
		if (c.abierta == true)
			os << "t";
		else 
			os << "f";
		if (c.marcada == false)
			os << "f";
		else
			os << "t";

      return os;
}
