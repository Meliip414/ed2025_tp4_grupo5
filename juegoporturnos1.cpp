#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Clase padre
class Personaje {
private:
	string nombre;
	int salud;
	int ataque;
	int defensa;
	int curacion;
	
public:
	// Constructor
	Personaje(string nombre, int salud, int ataque, int defensa, int curacion):
	 nombre(nombre), salud(salud), ataque(ataque), defensa(defensa), curacion(curacion) {}                                   
	
	// Getters
	string getNombre() { return nombre; }
	int getSalud() { return salud; }
	int getAtaque() { return ataque; }
	int getDefensa() { return defensa; }
	int getCuracion() { return curacion; }
	
	// Setters
	void setSalud(int nSalud) {
	     if (nSalud < 0) 
                 salud = 0;
             else
                 salud = nSalud;
        }
	
	// Métodos virtuales
	virtual void atacar(Personaje& objetivo) = 0;
	
   //Metodo para recibir danio
	void recibirDanio(int danio) {
		if (danio < 0) {
			danio= 0;}
			
			setSalud(salud - danio);
			cout << nombre << " recibió " << danio << " de daño. Salud restante: " << salud << endl;
	}
	//Defensa del personaje 
	void defenderse(){
		if(salud+defensa>110)
			setSalud(100);
		else
			setSalud(salud + defensa); 
		
		cout << nombre << " se ha defendido " <<endl; 
	}
	//Curacion del personaje 
	void curarse(){

		if(salud+curacion>100)
			setSalud(100);
		else
			setSalud(salud + curacion);
			
		cout << nombre << " se ha curado. Salud restante " << salud <<endl;
	}
	
	//Saber si el personaje esta vivo
	bool estaVivo() {
		return salud > 0;
	}
	
};
// Turno jugado
bool turnoJugado(bool turn){
		return turn == true;
}

// Clase Guerrero
class Guerrero : public Personaje {
public:
	Guerrero(string nombre): Personaje(nombre, 100, 25, 15, 10) {}
	
	void atacar(Personaje& objetivo) override {
		cout << getNombre() << " lanza un ataque poderoso con su espada." << endl;
		objetivo.recibirDanio(getAtaque());
	}
};

// Clase Mago
class Mago : public Personaje {
public:
	Mago(string nombre): Personaje(nombre, 100, 35, 5, 15) {}
	
	void atacar(Personaje& objetivo) override {
		cout << getNombre() << " lanza un hechizo letal." << endl;
		objetivo.recibirDanio(getAtaque());
	}
};
// menu  de Turno
void menudeaccion(int &op){
	cout<<"1_atacar"<<endl;
	cout<<"2_defender"<<endl;
	cout<<"3_curarse (puedes curarte hasta tres veces)"<<endl;
	cout<<"---------------------"<<endl;
	cout<<"Elegir opcion: ";cin>>op;
}

// acciones del jugador
void accion(Personaje* jugador1, Personaje* jugador2, int t,int &cont){
	bool turnojugado=false;
	int op;
	
	if(t==1 || t==2){
		do{
				cout<<"--------Turno de "<<jugador1->getNombre()<<"--------"<<endl;
				
			menudeaccion(op);
			
			switch(op){
				case 1:
					jugador1 -> atacar(*jugador2);
					turnojugado=true;
				break;
				case 2:
					jugador1->defenderse();
					turnojugado=true;
				break;
				case 3: 
					cont++;
					if(cont<=3){
						jugador1->curarse();
						turnojugado=true;}
					else
						cout<<"Ya no puedes curarte. Elige otra accion"<<endl;
					
				break;
				default: cout<<"opcion no disponible"<<endl;
			}
		}while(op>3 || op<1 || turnoJugado(turnojugado)==false);
	}else{
		while(turnoJugado(turnojugado)==false){
		int aux=rand()% 3;
		switch(aux){
			case 0: 
				jugador2 -> atacar(*jugador1);
				turnojugado=true;
			break;
			case 1: 
				jugador2->defenderse();
				turnojugado=true;
			break;
			case 2:
				cont++;
				if(cont<=3){
					jugador2->curarse();
					turnojugado=true;
				}
			break;
		}
	}
	}
}




// Clase Combate
class Combate {
private:
	Personaje* jugador1;
	Personaje* jugador2;
	
public:
	Combate(Personaje* p1, Personaje* p2) : jugador1(p1), jugador2(p2) {}
	
	void iniciar(int n) {
		int turno = 1,cont1=0,cont2=0;
		while (jugador1->estaVivo() && jugador2->estaVivo()) {
	
			cout << "------------Turno "<<turno<<"----------- " << endl;
			//un jugador
			if(n==1){
				int opcion=rand()% 2;
				switch(opcion){
					case 0: accion(jugador1,jugador2,opcion,cont1); break;
					case 1: accion(jugador1,jugador2,opcion,cont2); break;
				}
				turno++;
			}
			//dos jugadores
			else{
				int opcion=(rand()% 2)+1;
	
				switch(opcion){
					case 1: 
						accion(jugador1,jugador2,opcion,cont1);
					break;
			
					case 2: 
						accion(jugador2,jugador1,opcion,cont2);
					break;
				}
				turno++;
			}
		}
		
		cout << "Combate terminado." << endl;
		if (jugador1->estaVivo()) {
			cout << jugador1->getNombre() << " ha ganado!" << endl;
		} else {
			cout << jugador2->getNombre() << " ha ganado!" << endl;
		}
	}
};

//menus
void menu1(int &op){
	cout<<"-------------MENU------------"<<endl;
	cout<<"1_Combate de un jugador"<<endl;
	cout<<"2_Combate de dos jugadores"<<endl;
	cout<<"3_Cerrar"<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<"Elegir opcion: ";cin>>op;
}

void menu2(int &op){
	cout<<"-------------MENU------------"<<endl;
	cout<<"1_mago vs mago"<<endl;
	cout<<"2_guerrero vs guerrero"<<endl;
	cout<<"3_guerrero vs mago"<<endl;
	cout<<"4_Cancelar"<<endl;
	cout<<"-----------------------------"<<endl;
	cout<<"Elegir combate: ";cin>>op;
}

void menu3(int &op){
	cout<<"-----------Personaje------------"<<endl;
	cout<<"1_Mago"<<endl;
	cout<<"    Fuerza de ataque: 35"<<endl;
	cout<<"    Capacidad de defenza: 5"<<endl;
	cout<<"    Poder de curacion: 15"<<endl;
	cout<<"2_Guerrero"<<endl;
	cout<<"    Fuerza de ataque: 25"<<endl;
	cout<<"    Capacidad de defenza: 15"<<endl;
	cout<<"    Poder de curacion: 10"<<endl;
	cout<<"--------------------------------"<<endl;
	cout<<"Elige tu personaje: ";cin>>op;
}

//Personajes a luchar
void tipodecombate(string &nombre, int opc){
	int op1,op2;

	do{
		menu2(op1);
		switch(op1){
			case 1:
			{	
				if(opc==1){
					cin.clear(); cin.ignore();
					cout<<"Ingresar nombre del jugador: ";
					getline(cin,nombre);
					Mago mago1(nombre);
					Mago mago2("Mago");
					Combate pelea(&mago1, &mago2);
					pelea.iniciar(opc);}
				else{
					cin.clear(); cin.ignore();
					cout<<"Ingresar nombre del jugador 1: ";
					getline(cin,nombre);
					Mago mago1(nombre);
					cin.clear();
					cout<<"Ingresar nombre del jugador 2: ";
					getline(cin,nombre);
					Mago mago2(nombre);
					Combate pelea(&mago1, &mago2);
					pelea.iniciar(opc);}
			}
			break;
		
			case 2:
			{	
				if(opc==1){
					cin.clear(); cin.ignore();
					cout<<"Ingresar nombre del jugador: ";
					getline(cin,nombre);
					Guerrero guerrero1(nombre);
					Guerrero guerrero2("Guerrero");
					Combate pelea(&guerrero1, &guerrero2); 
					pelea.iniciar(opc);}
				else{
					cin.clear(); cin.ignore();
					cout<<"Ingresar nombre del jugador 1: ";
					getline(cin,nombre);
					Guerrero guerrero1(nombre);
					cin.clear(); 
					cout<<"Ingresar nombre del jugador 2: ";
					getline(cin,nombre);
					Guerrero guerrero2(nombre);
					Combate pelea(&guerrero1, &guerrero2);
					pelea.iniciar(opc);}
			}
			break;
			
			case 3:
			{	do{	menu3(op2);
					switch(op2){
						case 1:{
								if(opc==1){
									cin.clear(); cin.ignore();
									cout<<"Ingresar nombre del jugador: ";
									getline(cin,nombre);
									Mago mago(nombre);
									Guerrero guerrero("Guerrero");
									Combate pelea(&mago, &guerrero);
									pelea.iniciar(opc); }
								else{
									cin.clear(); cin.ignore();
									cout<<"Ingresar nombre del jugador 1(mago): ";
									getline(cin,nombre);
									Mago mago(nombre);
									cin.clear(); 
									cout<<"Ingresar nombre del jugador 2(guerrero): ";
									getline(cin,nombre);
									Guerrero guerrero(nombre);
									Combate pelea(&mago, &guerrero);
									pelea.iniciar(opc);}
								
								} break;
						case 2:{
								if(opc==1){
									cin.clear(); cin.ignore();
									cout<<"Ingresar nombre del jugador: ";
									getline(cin,nombre);
										Guerrero guerrero(nombre);
										Mago mago("Mago");
										Combate pelea(&guerrero, &mago);
									pelea.iniciar(opc); }
								else{
									cin.clear(); cin.ignore();
									cout<<"Ingresar nombre del jugador 1(guerrero): ";
									getline(cin,nombre);									
									Guerrero guerrero(nombre);
									cin.clear(); 
									cout<<"Ingresar nombre del jugador 2(mago): ";
									getline(cin,nombre);
									Mago mago(nombre);
									Combate pelea(&guerrero, &mago);
									pelea.iniciar(opc);}
								
								} break;
						default: cout<<"Opcion no disponible"<<endl;
						}
						}while(op2>2 || op2<1);
						}
						break;
						default:
							if(op1>4 || op1<1)
								cout<<"Opcion no disponible"<<endl;
			}
		}while(op1!=4); 
	
}

// Función principal
	int main() {
	string nombre;
	int opcion;
	srand(time(NULL));
	do{
	menu1(opcion);
	switch(opcion){
		case 1: tipodecombate(nombre,opcion);break;
		case 2: tipodecombate(nombre,opcion);break;
		case 3: cout<<"Combate cancelado"<<endl; break;
		default: 
			if(opcion>3 || opcion<1)
				cout<<"Opcion no disponible"<<endl;
			break;
	}
	}while(opcion!=3);
	
}
