#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
#include "ConexionDB.h"

using namespace std;

class Proveedores {

    //atributos
private: string  proveedor, nit, direccion;
       int telefono = 0;
       //constructor
public:
    Proveedores() {
    }
    Proveedores(string prov, string ni, string dir, int tel) {
        proveedor = prov;
        nit = ni;
        direccion = dir;
        telefono = tel;
    }
    //metodos
    //set (modificar)
    void setProveedor(string prov) { proveedor = prov; }
    void setNit(string ni) { nit = ni; }
    void setDireccion(string dir) { direccion = dir; }
    void setTelefonor(int tel) { telefono = tel; }

    //get(mostrar)
    string getProveedor() { return proveedor; }
    string getNit() { return nit; }
    string getDireccion() { return direccion; }
    int getTelefono() { return telefono; }


    //metodos
    void crear() {
        int q_estado;
        ConexionDB cn = ConexionDB();
        cn.abrirconexion();
        if (cn.getConectar()) {
            string t = to_string(telefono);
            string insert = "INSERT INTO proveedores (proveedor, nit, direccion, telefono) VALUES ('" + proveedor + "','" + nit + "','" + direccion + "'," + t + ");";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Ingreso Exitoso..." << endl;
            }
            else {
                cout << "error al ingresar..." << endl;
            }

        }
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }

    void leer() {
        int q_estado, opc;
        string consulta, t;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {
            cout << "Como desea buscar: " << endl;
            cout << "1. Buscar por proveedor." << endl;
            cout << "2. Buscar por nit." << endl;
            cout << "3. Buscar por direccion." << endl;
            cout << "4. Buscar por telefono." << endl;
            cout << "5. Ver Todos" << endl;

            cout << "\nIngrese No. de opcion: ";
            cin >> opc;

            switch (opc) {
            case 1:
                system("cls");
                cout << "ingrese nombre del proveedor: ";
                cin.ignore();
                getline(cin, proveedor);
                consulta = "SELECT* FROM proveedores WHERE proveedor LIKE '%" + proveedor + "%' LIMIT 3;";
                break;

            case 2:
                system("cls");
                cout << "ingrese nit del proveedor: ";
                cin.ignore();
                getline(cin, nit);
                consulta = "SELECT* FROM proveedores WHERE nit LIKE '%" + nit + "%' LIMIT 3;";
                break;

            case 3:
                system("cls");
                cout << "ingrese direccion del proveedor: ";
                cin.ignore();
                getline(cin, nit);
                consulta = "SELECT* FROM proveedores WHERE direccion LIKE '%" + direccion + "%' LIMIT 3;";
                break;

            case 4:
                system("cls");
                cout << "ingrese telefono del proveedor: ";
                cin.ignore();
                getline(cin, t);
                consulta = "SELECT* FROM proveedores WHERE telefono LIKE '%" + t + "%' LIMIT 3;";
                break;

            case 5:
                system("cls");
                consulta = "SELECT* FROM proveedores;";
                break;

            }
            
            const char* l = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), l);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                cout << "-------------Proveedores-------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID del Proveedor: " << fila[0] << "\nNombre del Proveedor: " << fila[1] << "\nNIT: " << fila[2] << "\nDireccion: " << fila[3] << "\nTelefono: " << fila[4] << endl;
                    cout << "--------------------------------------\n" << endl;
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
        string insert, consulta, prov_new;
        int q_estado, opc, set, idc;
        char pregunta;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {
            cout << "Desea buscar proveedor (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");
                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por nombre del proveedor." << endl;
                cout << "2. buscar por NIT del proveedor." << endl;
                cout << "Ingrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre del proveedor: ";
                    cin.ignore();
                    getline(cin, proveedor);
                    consulta = "SELECT* FROM proveedores WHERE proveedor LIKE '%" + proveedor + "%' LIMIT 3;";
                    break;
                case 2:
                    system("cls");
                    cout << "ingrese NIT del proveedor: ";
                    cin.ignore();
                    getline(cin, nit);
                    consulta = "SELECT* FROM proveedores WHERE proveedor LIKE '%" + nit + "%' LIMIT 3;";
                    break;
                }
                const char* l = consulta.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Proveedores-------------" << endl;
                    while (fila = mysql_fetch_row(resultado)) {
                        cout << "ID del Proveedor: " << fila[0] << "\nNombre del Proveedor: " << fila[1] << "\nNIT: " << fila[2] << "\nDireccion: " << fila[3] << "\nTelefono: " << fila[4] << endl;
                        cout << "--------------------------------------\n" << endl;
                    }
                }
                else {
                    cout << "error al consultar...";
                }
            }




            else((pregunta == 'N') || (pregunta == 'n')); {
                const char* i;

                cout << "Ingrese el Id del proveedor que desea modificar: ";
                cin >> idc;
                system("cls");
                cout << "ID del proveedor seleccionado: " + idc << endl;
                cout << "Opciones: \n 1. Nombre del proveedor \n 2. NIT del proveedor \n 3. Direccion del proveedor \n 4. Telefono del proveedor" << endl;
                cout << "Ingrese opcion que desea modificar: ";
                cin >> set;
                string c = to_string(idc);
                switch (set) {
                case 1:
                    cout << "Ingrese el nuevo nombre del proveedor: ";
                    cin.ignore();
                    getline(cin, prov_new);
                    insert = "UPDATE proveedores SET proveedor = '" + prov_new + "' WHERE idproveedores = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 2:
                    cout << "Ingrese el nuevo NIT del proveedor: ";
                    cin.ignore();
                    getline(cin, prov_new);
                    insert = "UPDATE proveedores SET nit = '" + prov_new + "' WHERE idproveedores = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 3:
                    cout << "Ingrese el nueva direccion del proveedor: ";
                    cin.ignore();
                    getline(cin, prov_new);
                    insert = "UPDATE proveedores SET direccion = '" + prov_new + "' WHERE idproveedores = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 4:
                    cout << "Ingrese el nuevo telefono del proveedor: ";
                    cin.ignore();
                    getline(cin, prov_new);
                    insert = "UPDATE proveedores SET telefono = '" + prov_new + "' WHERE idproveedores = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;
                }

            }
            const char* m = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), m);
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

    void eliminar() {
        string c_del, consulta;
        int q_estado, opc;
        char pregunta;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {
            cout << "Desea buscar proveedor (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");
                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por nombre del proveedor." << endl;
                cout << "2. buscar por NIT del proveedor." << endl;
                cout << "Ingrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre del proveedor: ";
                    cin.ignore();
                    getline(cin, proveedor);
                    consulta = "SELECT* FROM proveedores WHERE proveedor LIKE '%" + proveedor + "%' LIMIT 3;";
                    break;
                case 2:
                    system("cls");
                    cout << "ingrese NIT del proveedor: ";
                    cin.ignore();
                    getline(cin, nit);
                    consulta = "SELECT* FROM proveedores WHERE proveedor LIKE '%" + nit + "%' LIMIT 3;";
                    break;
                }
                const char* l = consulta.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Proveedores-------------" << endl;
                    while (fila = mysql_fetch_row(resultado)) {
                        cout << "ID del Proveedor: " << fila[0] << "\nNombre del Proveedor: " << fila[1] << "\nNIT: " << fila[2] << "\nDireccion: " << fila[3] << "\nTelefono: " << fila[4] << endl;
                        cout << "--------------------------------------\n" << endl;
                    }
                }
                else {
                    cout << "error al consultar...";
                }
            }




            else((pregunta == 'N') || (pregunta == 'n')); {

                cout << "Ingrese ID que desea eliminar: ";
                cin >> c_del;
                string insert = "DELETE FROM proveedores WHERE idproveedores = ('" + c_del + "');";

                const char* d = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), d);
                if (!q_estado) {
                    cout << "El ID: " + c_del + " se ha eliminado correctamente" << endl;
                }
                else {
                    cout << "Error al Eliminar...";
                }

            }
        }
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }

};

