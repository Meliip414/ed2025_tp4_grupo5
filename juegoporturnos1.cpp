#include <iostream>
using namespace std ;
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Clase base
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
	string getNombre() const { return nombre; }
	int getSalud() const { return salud; }
	int getAtaque() const { return ataque; }
	int getDefensa() const { return defensa; }
	
	// Setters
	void setSalud(int nuevaSalud) {
		salud = (nuevaSalud < 0) ? 0 : nuevaSalud; //operador ternario
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
	Guerrero(string nombre)
		: Personaje(nombre, 100, 25, 10) {}
	
	void atacar(Personaje& objetivo) override {
		cout << getNombre() << " lanza un ataque poderoso con su espada." << endl;
		objetivo.recibirDanio(getAtaque());
	}
};

// Clase Mago
class Mago : public Personaje {
public:
	Mago(string nombre)
		: Personaje(nombre, 100, 35, 5) {}
	
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

// Función principal
int main() {
	
	Guerrero guerrero("Arthas");
	Mago mago("Merlin");
	
	Combate pelea(&guerrero, &mago);
	pelea.iniciar();
}

