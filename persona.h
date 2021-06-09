#pragma once
#include<iostream>
using namespace std;
class persona{
	//atributos
protected: string nombres, apellidos, genero, fechaingreso;
		 int telefono = 0;
		 //constructor
protected:
	persona() {

	}
	persona(string nom, string ape, string gen, string fi, int tel) {
		nombres = nom;
		apellidos = ape;
		genero = gen;
		fechaingreso = fi;
		telefono = tel;
		
		
	}
};

