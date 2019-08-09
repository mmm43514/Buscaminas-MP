#include "Casilla.h"
#include "Tablero.h"
#include "CampoMinas.h"
	int CampoMinas::BombasAlrededor(int f, int c, Tablero &tablero){
		int bombas = 0;
		for (int i = - 1; i <= 1; i++)
			for (int j = - 1; j <= 1; j++)
				if (!(i == 0 && j == 0) && f+i >= 0 && c+j >= 0)
					if (tablero.GetElemento(f+i,c+j).bomba == true)
						bombas++;
            
		return bombas;
	}

	CampoMinas::CampoMinas(int i, int j, int minas, Tablero &tablero){
		srand(time(0));
		int f,c;
		for (int k = 0; k < minas; k++){
			f = rand()%i;
			c = rand()%j;
			if (tablero.GetElemento(f,c).bomba == false)
				tablero.Modificar(f,c,'b');
			else
				k--;
		}
		mina_explosionada = false;
	}

	int CampoMinas::GetFilasTablero(Tablero &tablero){
		return tablero.GetFilas();
	}

	int CampoMinas::GetColumnasTablero(Tablero &tablero){
		return tablero.GetColumnas();
	}

	bool CampoMinas::MinaExplosionada(Tablero &tablero){
		return mina_explosionada;
	}

	bool CampoMinas::PartidaGanada(Tablero &tablero){	
		if (MinaExplosionada(tablero))
			return true;

		for (int i = 0; i < GetFilasTablero(tablero); i++)
			for (int j = 0; j < GetColumnasTablero(tablero); j++)
				if (tablero.GetElemento(i,j).abierta == false && tablero.GetElemento(i,j).bomba == false)
					return false;

		return true;
	}

	bool CampoMinas::Marcar(int f, int c, Tablero &tablero){
		if (tablero.GetElemento(f,c).marcada == true){
			return false;
		}
		else{
			tablero.Modificar(f,c,'m');
			return true;
		}
	}

	void CampoMinas::Add(CeldaPosicion* &pos, int i, int j){
		CeldaPosicion *p;
		p = new (nothrow) CeldaPosicion;
		(*p).fila = i;
		(*p).columna = j;
		(*p).siguiente = pos;
		pos = p;
	}
	CeldaPosicion CampoMinas::ExtraerElemento(CeldaPosicion* &pos){
		CeldaPosicion salida;
		salida.fila = (*pos).fila;
		salida.columna = (*pos).columna;
		pos = (*pos).siguiente;
		
		return salida;
	}
	bool CampoMinas::Abrir(int f, int c, Tablero &tablero){
			
		CeldaPosicion *pend=NULL;
		Add(pend,f,c);
		CeldaPosicion extraido = ExtraerElemento(pend);
		if (tablero.GetElemento(extraido.fila,extraido.columna).bomba == true){
			mina_explosionada = true;
			return true;
		}
		if (tablero.GetElemento(extraido.fila,extraido.columna).abierta == false \
          && tablero.GetElemento(extraido.fila,extraido.columna).marcada == false){
			if (BombasAlrededor(extraido.fila,extraido.columna,tablero) <= 8 && \
             BombasAlrededor(extraido.fila,extraido.columna,tablero) >= 1)
				tablero.Modificar(extraido.fila,extraido.columna,'a');
			
			if (BombasAlrededor(extraido.fila,extraido.columna,tablero) == 0){
				tablero.Modificar(extraido.fila,extraido.columna,'a');
				for (int i = - 1; i <= 1; i++)
					for (int j = - 1; j <= 1; j++)
						if (!(i==0 && j==0) && extraido.fila+i >= 0 && extraido.columna+j >= 0 \
                      && i+extraido.fila < GetFilasTablero(tablero) && \
                      extraido.columna+j < GetColumnasTablero(tablero))
							Add(pend,extraido.fila + i,extraido.columna + j);
			}
		}
			
		while (pend != NULL){
			CeldaPosicion extraido = ExtraerElemento(pend);
			if (tablero.GetElemento(extraido.fila,extraido.columna).abierta == false && \
             tablero.GetElemento(extraido.fila,extraido.columna).bomba == false && \
             tablero.GetElemento(extraido.fila,extraido.columna).marcada == false){
				if (BombasAlrededor(extraido.fila,extraido.columna,tablero) <= 8 && \
                BombasAlrededor(extraido.fila,extraido.columna,tablero) >= 1)
					tablero.Modificar(extraido.fila,extraido.columna,'a');
				
				if (BombasAlrededor(extraido.fila,extraido.columna,tablero) == 0){
					tablero.Modificar(extraido.fila,extraido.columna,'a');
					for (int i = - 1; i <= 1; i++)
						for (int j = - 1; j <= 1; j++)
							if (!(i == 0 && j == 0) && extraido.fila + i >= 0 && \
                         extraido.columna+j >= 0 && i+extraido.fila < GetFilasTablero(tablero) \
                         && extraido.columna+j < GetColumnasTablero(tablero))
								Add(pend,extraido.fila+i,extraido.columna+j);
				}
			
			}
		}	
	return true;
	}

	void CampoMinas::PrettyPrint(Tablero &tablero, ostream &salida){
		salida << "    ";
		for (int j = 0; j < GetColumnasTablero(tablero); j++)
			salida << setw(3) << right << j;

		salida << "\n";
		for (int i = 0; i < GetFilasTablero(tablero); i++){
			salida << setw(3) << right << i << " ";
			for (int j = 0; j < GetColumnasTablero(tablero); j++){
				if (tablero.GetElemento(i,j).abierta == true){
					if (tablero.GetElemento(i,j).bomba == true)
						salida << "| X";
					else{
						if (BombasAlrededor(i,j,tablero) == 0)
							salida << "|  ";
						else
							salida << "| " << BombasAlrededor(i,j,tablero);
					}
				}
				else{
					if (tablero.GetElemento(i,j).marcada == true)
						salida << "| ?";
					else
						salida << "| *";
				}
			}
		salida << "|\n";
		}
	}
	void CampoMinas::MostrarTodo(Tablero &tablero, ostream &salida){
		salida << "    ";
		for (int j = 0; j < GetColumnasTablero(tablero); j++)
			salida << setw(3) << right << j;

		salida << "\n";
		for (int i = 0; i < GetFilasTablero(tablero); i++){
			salida << setw(3) << right << i << " ";
			for (int j = 0; j < GetColumnasTablero(tablero); j++){
				if (tablero.GetElemento(i,j).bomba == true)
						salida << "| X";
				else{
					if (BombasAlrededor(i,j,tablero) == 0)
						salida << "|  ";
					else
						salida << "| " << BombasAlrededor(i,j,tablero);
				}
			}
		salida << "|\n";	
		}

	}
	
   bool CampoMinas::Escribir(char * escribir, Tablero &t){
		ofstream ofs;
		ofs.open(escribir);
		ofs << "#MP−BUSCAMINAS−V1\n";
		ofs << t;
		if (ofs)
			return true;
		else
			return false;
	}

	bool CampoMinas::Leer(char * leer, Tablero* &t){

		ifstream ifsleer;
		ifsleer.open(leer);
		ifsleer.ignore(22);
		int fil, col;
		fil = col = 0;
		while (!ifsleer.eof()){
			if (ifsleer.peek() != '\n'){
				col++;
				ifsleer.ignore();
			}
			else
				if (ifsleer.peek() == '\n'){
					fil++;
					ifsleer.ignore();
				}
		}
		col = (col/3)/fil;
	
		ifsleer.close();
		(*t).Destructor();
		Tablero obsoleto(fil,col);
		t = new Tablero(fil,col);
		ifstream ifs;
		ifs.open(leer);
				
		int i = 0;
		int j = 0;
		ifs.ignore(22);
		
		while (!ifs.eof()){
			if (ifs.peek() == '\n'){
				ifs.ignore(1);
				i++;
				j=0;
			}
			else{
				for (int k = 0; k < 3; k++){
					if (ifs.get() == 't'){
						if (k == 0)
							t->Modificar(i,j,'b');
						else
							if (k == 1)
								t->Modificar(i,j,'a');
							else
								if (k == 2)
									t->Modificar(i,j,'m');
					}
				}
			j++;
			}
		}
	return true;
	}

