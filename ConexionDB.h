#pragma once

#include <mysql.h>
#include <iostream>

using namespace std;

class ConexionDB{
private : MYSQL* conectar;
public:
	void abrirconexion(){
		conectar = mysql_init(0);
		conectar = mysql_real_connect(conectar, "localhost", "usr_proyecto2", "proyecto2", "proyecto2_db", 3306, NULL, 0);
	}
	MYSQL* getConectar() {
		return conectar;
	}


	void cerrar_conexion() {
		mysql_close(conectar);
	}
	

};

