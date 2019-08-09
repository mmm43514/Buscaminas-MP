#include "Casilla.h"
#include "Tablero.h"
#include "CampoMinas.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]){
	
	if (argc == 4){
		int filas, columnas;
		char action;
		filas = atoi(argv[1]);
		columnas = atoi(argv[2]);
		Tablero tab(filas,columnas);
		CampoMinas campomin(filas, columnas, atoi(argv[3]), tab);
		
		campomin.PrettyPrint(tab);
		cout << "\n";

		while (campomin.PartidaGanada(tab) == false){
			cout << "\nAcción a realizar -- > ";
			cin >> action;
			if (action == 's'){
				char *str = new char[500];
				cin.ignore(1);
				cin.getline(str,500);
				
				if (campomin.Escribir(str,tab))
					cout << "\nLa partida se ha guardado con éxito." << endl;
			}
			else{
				cin >> filas >> columnas;
		
				if (action == 'm')
					campomin.Marcar(filas,columnas,tab);
				else
					if (action == 'a')
						campomin.Abrir(filas, columnas, tab);
			
				campomin.PrettyPrint(tab);
			}
		}
			if (campomin.MinaExplosionada(tab)){
				cout << "\n\n";
				campomin.MostrarTodo(tab);
				tab.Destructor();
				cout << " PERDISTE" << endl;
			}
			else{
				tab.Destructor();
				cout << " GANASTE" << endl;
			}
	}
	else
		if (argc == 2){
			char action;
			Tablero t(2,2);
			CampoMinas campomin(2,2,1,t);
			Tablero *tab = &t;
			cout << argv[1];
			campomin.Leer(argv[1],tab);
			cout << "\n\n";
			campomin.PrettyPrint(*tab);
	
		while (campomin.PartidaGanada(*tab) == false){
			cout << "\nAcción a realizar -- > ";
			cin >> action;
			if (action == 's'){
				char *directorio = new char[20];
				int i = 0;
				cin.ignore(1);
				while (cin.peek() != EOF){
					directorio[i] = cin.get();
					i++;
				}
				campomin.Escribir(directorio,*tab);
			}
			else{
				int filas, columnas;
				cin >> filas >> columnas;
		
				if (action == 'm')
					campomin.Marcar(filas,columnas,*tab);
				else
					if (action == 'a')
						campomin.Abrir(filas, columnas, *tab);
            
				campomin.PrettyPrint(*tab);
			}
		}
			if (campomin.MinaExplosionada(*tab)){
				cout << "\n\n";
				campomin.MostrarTodo(*tab);
				(*tab).Destructor();
				cout << " PERDISTE" << endl;
			}
			else{
				(*tab).Destructor();
				cout << " GANASTE" << endl;
			}
		}
		else
			cerr << "El número de parámetros es incorrecto.\n  -Si se introducen 3 parámetros se considerarán que son las filas, columnas y número de minas respectivamente. \n  - Si se introduce 1 parámetros se considerará que es el archivo que contiene una partida anterior." << endl;

}

