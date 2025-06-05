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
	
public:
	// Constructor
	Personaje(string nombre, int salud, int ataque, int defensa):
	 nombre(nombre), salud(salud), ataque(ataque), defensa(defensa) {}                                   
	
	// Getters
	string getNombre() { return nombre; }
	int getSalud() { return salud; }
	int getAtaque() { return ataque; }
	int getDefensa() { return defensa; }
	
	// Setters
	void setSalud(int nsalud) {
	     if (nsalud < 0) 
                 salud = 0;
             else
                 salud = nsalud;
        }
	
	// Métodos virtuales
	virtual void atacar(Personaje& objetivo) = 0;
	
	void recibirDanio(int danio) {
		int danioFinal = danio - defensa;
		if (danioFinal < 0) danioFinal = 0;
		setSalud(salud - danioFinal);
		cout << nombre << " recibió " << danioFinal << " de daño. Salud restante: " << salud << endl;
	}
	
	bool estaVivo() const {
		return salud > 0;
	}
	
};

// Clase Guerrero
class Guerrero : public Personaje {
public:
	Guerrero(string nombre) : Personaje(nombre, 100, 25, 10) {}
	
	void atacar(Personaje& objetivo) override {
		cout << getNombre() << " lanza un ataque poderoso con su espada." << endl;
		objetivo.recibirDanio(getAtaque());
	}
};

// Clase Mago
class Mago : public Personaje {
public:
	Mago(string nombre) : Personaje(nombre, 100, 35, 5) {}
	
	void atacar(Personaje& objetivo) override {
		cout << getNombre() << " lanza un hechizo de fuego mágico." << endl;
		objetivo.recibirDanio(getAtaque());
	}
};

// Clase Combate
class Combate {
private:
	Personaje* jugador1;
	Personaje* jugador2;
	
public:
	Combate(Personaje* p1, Personaje* p2)
		: jugador1(p1), jugador2(p2) {}
	
	void iniciar() {
		srand(time(NULL));
		int turno = 1;
		while (jugador1->estaVivo() && jugador2->estaVivo()) {
			cout << "\nTurno " << turno << ":" << endl;
			int opcion=rand()% 2;
	
			switch(opcion){
				case 0: jugador1->atacar(*jugador2); break;
			
				case 1: jugador2->atacar(*jugador1); break;
			}
			turno++;
		}
		
		cout << "\nCombate terminado." << endl;
		if (jugador1->estaVivo()) {
			cout << jugador1->getNombre() << " ha ganado!" << endl;
		} else {
			cout << jugador2->getNombre() << " ha ganado!" << endl;
		}
	}
};

void menu1(int &op){
	cout<<"-------------MENU------------"<<endl;
	cout<<"1_Nuevo combate"<<endl;
	cout<<"2_Cerrar"<<endl;
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

void tipodecombate(string &nombre){
	int op;
	do{
		menu2(op);
		switch(op){
			case 1:
			{	cout<<"1er jugador: ";cin>>nombre;
				Mago mago1(nombre);
				cout<<"2do jugador: ";cin>>nombre;
				Mago mago2(nombre);
				Combate pelea(&mago1, &mago2);
				pelea.iniciar();}
			break;
		
			case 2:
			{	cout<<"1er jugador: ";cin>>nombre;
				Guerrero guerrero1(nombre);
				cout<<"1er jugador: ";cin>>nombre;
				Guerrero guerrero2(nombre);
				Combate pelea(&guerrero1, &guerrero2); 
				pelea.iniciar();}
			break;
			
			case 3:
			{	cout<<"1er jugador(querrero): ";cin>>nombre;
				Guerrero guerrero(nombre);
				cout<<"2do jugador(mago): ";cin>>nombre;
				Mago mago(nombre);
				Combate pelea(&guerrero, &mago);
				pelea.iniciar(); }
			
			default: 
				if(op>4 || op<1)
				cout<<"Opcion no disponible"<<endl;
			break;
			}
		}while(op!=4);
			
}

// Función principal
	int main() {
	string nombre;
	int opcion;
	
	do{
	menu1(opcion);
	switch(opcion){
		case 1: tipodecombate(nombre);break;
		case 2: cout<<"Combate cancelado"<<endl; break;
		default: 
			if(opcion>2 || opcion<1)
				cout<<"Opcion no disponible"<<endl;
			break;
	}
	}while(opcion!=2);

}

