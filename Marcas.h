#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
#include "ConexionDB.h"

using namespace std;


class Marcas{

    //atributos
private: string  marca;
       //constructor
public:
    Marcas() {
    }
    Marcas(string ma) {
        marca = ma;
    }
    //metodos
    //set (modificar)
    void setMarca(string ma) { marca = ma; }
    //get(mostrar)
    string getMarca() { return marca; }

    //metodos

    void crear() {
        int q_estado;
        ConexionDB cn = ConexionDB();
        cn.abrirconexion();
        if (cn.getConectar()) {
            string insert = "INSERT INTO marcas(marca) VALUES ('" + marca + "');";
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
            cout << "1. Buscar por nombre de la marca." << endl;
            cout << "2. Buscar todas las marcas." << endl;
            cout << "\nIngrese No. de opcion: ";
            cin >> opc;

            switch (opc) {
            case 1:
                system("cls");
                cout << "ingrese nombre de la marca: ";
                cin.ignore();
                getline(cin, marca);
                consulta = "SELECT* FROM marcas WHERE marca LIKE '%" + marca + "%' LIMIT 3;";
                break;
            case 2:
                consulta = "SELECT *FROM marcas;";
                break;
            }

            l = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), l);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                cout << "-------------Marcas-------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID:" << fila[0] << ": " << fila[1] << endl;

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
        string conf, marca_new, consulta;
        int q_estado, idp, opc;
        char pregunta;
        const char* l;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {

            cout << "Desea buscar marca (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");

                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por nombre de la marca." << endl;
                cout << "2. Buscar todas las marcas." << endl;
                cout << "\nIngrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre de la marca: ";
                    cin.ignore();
                    getline(cin, marca);
                    consulta = "SELECT* FROM marcas WHERE marca LIKE '%" + marca + "%' LIMIT 3;";
                    break;
                case 2:
                    system("cls");
                    consulta = "SELECT *FROM marcas;";
                    break;
                }

                l = consulta.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Marcas-------------" << endl;
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

                cout << "Ingrese el ID de la marca que desea modificar: ";
                cin >> idp;
                cout << "Ingrese la nueva marca modificada: ";
                cin >> marca_new;
                string c = to_string(idp);

                string insert = "UPDATE marcas SET marca = ('" + marca_new + "') WHERE idMarca = " + c + ";";
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

            cout << "Desea buscar marca (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");

                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por nombre de la marca." << endl;
                cout << "2. Buscar todas las marcas." << endl;
                cout << "\nIngrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre de la marca: ";
                    cin.ignore();
                    getline(cin, marca);
                    consulta = "SELECT* FROM marcas WHERE marca LIKE '%" + marca + "%' LIMIT 3;";
                    break;
                case 2:
                    consulta = "SELECT *FROM marcas;";
                    break;
                }

                l = consulta.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Marcas-------------" << endl;
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

                cout << "Ingrese ID de la marca que desea eliminar: ";
                cin >> c_del;
                string c = to_string(c_del);
                string insert = "DELETE FROM marcas WHERE idMarca = " + c + ";";
                const char* d = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), d);
                if (!q_estado) {
                    cout << "La marca: " + c + " se ha eliminado correctamente" << endl;
                }
                else {
                    cout << "Error al Eliminar..." << endl;
                }
            }

        }
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }

};

