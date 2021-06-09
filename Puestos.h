#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
#include "ConexionDB.h"

using namespace std;


class Puestos{
    //atributos
 private: string  puesto;
       //constructor
public:
    Puestos() {
    }
    Puestos(string pu) {
        puesto = pu;
    }
    //metodos
    //set (modificar)
    void setPuesto(string pu) { puesto = pu; }
    //get(mostrar)
    string getPuesto() { return puesto; }
    
    //metodos

    void crear() {
        int q_estado;
        ConexionDB cn = ConexionDB();
        cn.abrirconexion();
        if (cn.getConectar()) {
            string insert = "INSERT INTO puestos(puesto) VALUES ('" + puesto + "');";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Ingreso Exitoso..." << endl;
            }
            else {
                cout << "error al ingresar...";
            }

        }
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }

    void leer() {
        int q_estado, opc;
        string consulta;
        const char* l;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {

            system("cls");
            cout << "Como desea buscar: " << endl;
            cout << "1. Buscar por nombre del puesto." << endl;
            cout << "2. Buscar todos los puestos." << endl;
            cout << "\nIngrese No. de opcion: ";
            cin >> opc;

            switch (opc) {
            case 1:
                system("cls");
                cout << "ingrese nombre del puesto: ";
                cin.ignore();
                getline(cin, puesto);
                consulta = "SELECT* FROM puestos WHERE puesto LIKE '%" + puesto + "%' LIMIT 3;";
                break;
            case 2:
                consulta = "SELECT *FROM puestos;";
                break;
            }

            l = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), l);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                cout << "-------------Puestos-------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout <<"ID:" << fila[0] << ": " << fila[1] << endl;
                   
                }
            }
            else {
                cout << "error al consultar...";
            }
        }
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();

    }

    void modificar() {
        //variables de productos en modificar
        string conf, puesto_new, consulta;
        int q_estado, idp, opc;
        char pregunta;
        const char* l;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {

            cout << "Desea buscar puesto (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");
            
                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por nombre del puesto." << endl;
                cout << "2. Buscar todos los puestos." << endl;
                cout << "\nIngrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre del puesto: ";
                    cin.ignore();
                    getline(cin, puesto);
                    consulta = "SELECT* FROM puestos WHERE puesto LIKE '%" + puesto + "%' LIMIT 3;";                    
                    break;
                case 2:
                    consulta = "SELECT *FROM puestos;";                   
                    break;
                }

                l = consulta.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Puestos-------------" << endl;
                    while (fila = mysql_fetch_row(resultado)) {
                        cout << "ID:" << fila[0] << ": " << fila[1] << endl;

                    }
                }
                else {
                    cout << "error al consultar...";
                }
                system("pause");
            }// cierra if pregunta
            else ((pregunta == 'N') || (pregunta == 'n')); {

                cout << "Ingrese el ID del puesto que desea modificar: ";
                cin >> idp;
                cout << "Ingrese el nuevo puesto modificado: ";
                cin >> puesto_new;
                string c = to_string(idp);

                string insert = "UPDATE puestos SET puesto = ('" + puesto_new + "') WHERE idPuesto = " + c + ";";
                const char* m = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), m);
                if (!q_estado) {
                    cout << "Ingreso Exitoso..." << endl;
                }
                else {
                    cout << "error al ingresar...";
                }
            }//cierra el else de pregunta
        }//cierra el conectar
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();

    }// cierra void


    void eliminar() {
        string consulta;
        char pregunta;
        int q_estado, opc, c_del;
        const char* l;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {
            system("cls");

            cout << "Desea buscar puesto (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");

                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por nombre del puesto." << endl;
                cout << "2. Buscar todos los puestos." << endl;
                cout << "\nIngrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre del puesto: ";
                    cin.ignore();
                    getline(cin, puesto);
                    consulta = "SELECT* FROM puestos WHERE puesto LIKE '%" + puesto + "%' LIMIT 3;";
                    break;
                case 2:
                    system("cls");
                    consulta = "SELECT *FROM puestos;";
                    break;

                }

                l = consulta.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Puestos-------------" << endl;
                    while (fila = mysql_fetch_row(resultado)) {
                        cout << "ID:" << fila[0] << ": " << fila[1] << endl;

                    }
                }
                else {
                    cout << "error al consultar...";
                }
                system("pause");
            }// cierra if pregunta
            else ((pregunta == 'N') || (pregunta == 'n')); {

                cout << "Ingrese ID del puesto que desea eliminar: ";
                cin >> c_del;
                string c = to_string(c_del);
                string insert = "DELETE FROM puestos WHERE idPuesto = " + c + ";";
                const char* d = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), d);
                if (!q_estado) {
                    cout << "El puesto: " + c + " se ha eliminado correctamente" << endl;
                }
                else {
                    cout << "Error al Eliminar...\npara elimiar un puesto no deben de exixtir empleados con el puesto que se desea eliminar\n" << endl;
                }
            }

        }
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();

    }



};

