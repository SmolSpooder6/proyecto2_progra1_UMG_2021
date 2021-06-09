#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
#include "ConexionDB.h"




using namespace std;

class cliente {
    //atributos
private: string  nombres, apellidos, nit, genero, correo_electronico, fechaingreso;
       int telefono = 0;
        //constructor
public :
    cliente() {
    }
    cliente(string nom, string ape, string n, string gen, int tel, string ce, string fi){
        nombres = nom;
        apellidos = ape;
        nit = n;
        genero = gen;
        telefono = tel;
        correo_electronico = ce;
        fechaingreso = fi;
    }
    
    //metodos
    //set (modificar)
    
    void setNombres(string nom) { nombres = nom; }
    void setApellidos(string ape) { apellidos = ape; }
    void setNit(string n) { nit = n; }
    void setGenero(string gen) { genero = gen; }
    void setTelefono(int tel) { telefono = tel; }
    void setCorreo_Electronico(string ce) { correo_electronico = ce; }
    void setFechaIngreso(string fi) { fechaingreso = fi; }

    //get(mostrar)
    
    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getNit() { return nit; }
    string getGenero() { return genero; }
    int getTelefono() { return telefono; }
    string getCorreo_electronico() { return correo_electronico; }
    string getFechaIngreso() { return fechaingreso; }


    //metodos
    void crear() {
        int q_estado;
        ConexionDB cn = ConexionDB();
        cn.abrirconexion();
        if (cn.getConectar()) {
            
            
            string t = to_string(telefono);
            string insert = "INSERT INTO clientes(nombres,apellidos,nit,genero,telefono,correo_electronico,fechaIngreso) VALUES ('" + nombres + "','" + apellidos + "','" + nit + "',b'" + genero + "'," + t + ",'" + correo_electronico + "', CURRENT_TIMESTAMP);";
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
        string consulta, t, ge;
        int q_estado, opc;
        const char* l;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {

            system("cls");
            cout << "Como desea buscar: " << endl;
            cout << "1. Buscar por nombre y apellido." << endl;
            cout << "2. Buscar por NIT." << endl;
            cout << "3. Buscar por genero." << endl;
            cout << "4. Buscar por telefono." << endl;
            cout << "5. Buscar por correo electronico." << endl;
            cout << "6. Buscar por fecha de ingreso." << endl;
            cout << "7. Ver todos" << endl;
            cout << "\nIngrese No. de opcion: ";
            cin >> opc;

            switch (opc) {
            case 1:
                system("cls");
                cout << "ingrese nombre del cliente: ";
                cin.ignore();
                getline(cin, nombres);
                cout << "ingrese apellido de la persona: ";
                getline(cin, apellidos);
                consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE nombres LIKE '%" + nombres + "%' UNION SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE apellidos LIKE '%" + apellidos + "%';";
                break;

            case 2:
                system("cls");
                cout << "ingrese NIT del cliente: ";
                cin.ignore();
                getline(cin, nit);
                consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE nit LIKE '%" + nit + "%' LIMIT 3;";                
                break;
                //------------------------------
            case 3:
                system("cls");
                cout << "ingrese Genero del cliente (0/1): ";
                cin >> genero;
                
                consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE genero = " + genero + " LIMIT 10;";                
                break;
                //------------------------------
            case 4:
                system("cls");
                cout << "ingrese telefono del cliente: ";
                cin.ignore();
                getline(cin, t);
                consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE telefono LIKE '%" + t + "%' LIMIT 3;";
                break;

            case 5:
                system("cls");
                cout << "ingrese correo electronico del cliente: ";
                cin.ignore();
                getline(cin, correo_electronico);
                consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE correo_electronico LIKE '%" + correo_electronico + "%' LIMIT 3;";
                break;

            case 6:
                system("cls");
                cout << "ingrese Fecha de ingreso del cliente (YY-MM-DD): ";
                cin.ignore();
                getline(cin, fechaingreso);
                consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE fechaIngreso LIKE '%" + fechaingreso + "%' LIMIT 10;";
                break;

            case 7:
                system("cls");
                consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes;";
                break;

            }//cierra el switch

            l = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), l);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                cout << "-------------Clientes-------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID: " << fila[0] << "\nNombres: " << fila[1] << "\nApellidos: " << fila[2] << "\nNit: " << fila[3] << "\nGenero: " << fila[4] << "\nTelefono: " << fila[5] << "\nCorreo Electronico: " << fila[6] << "\nFecha de Ingreso: " << fila[7] << endl;
                    cout << "--------------------------------------\n" << endl;
                }
            }
            else {
                cout << "error al consultar..." << endl;
            }

        }//cierra el conectar
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
        
    } //cierra void

    void modificar() {
        //variables de productos en modificar
        string cliente_new, consulta, t;
        char pregunta;
        const char* l;
        int set = 0; // opcion del switch
        int idc = 0; // seleccion de id
         
        int q_estado, opc;//opcion de busqueda
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {

            cout << "Desea buscar cliente (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");
                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por nombre y apellido." << endl;
                cout << "2. buscar por nit." << endl;
                cout << "3. buscar por telefono." << endl;
                cout << "Ingrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre del cliente: ";
                    cin.ignore();
                    getline(cin, nombres);
                    cout << "ingrese apellido de la persona: ";
                    getline(cin, apellidos);

                    consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE nombres LIKE '%" + nombres + "%' UNION SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE apellidos LIKE '%" + apellidos + "%' LIMIT 3;";                    
                    break;

                case 2:
                    system("cls");
                    cout << "ingrese NIT del cliente: ";
                    cin.ignore();
                    getline(cin, nit);

                    consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE nit LIKE '%" + nit + "%';";                    
                    break;

                case 3:
                    system("cls");
                    cout << "ingrese telefono del cliente: ";
                    cin.ignore();
                    getline(cin, t);

                    consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE telefono LIKE '%" + t + "%';";     
                    break;

                }//cierra switch

                l = consulta.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Clientes-------------" << endl;
                    while (fila = mysql_fetch_row(resultado)) {
                        cout << "ID: " << fila[0] << "\nNombres: " << fila[1] << "\nApellidos: " << fila[2] << "\nNit: " << fila[3] << "\nGenero: " << fila[4] << "\nTelefono: " << fila[5] << "\nCorreo Electronico: " << fila[6] << "\nFecha de Ingreso: " << fila[7] << endl;
                        cout << "--------------------------------------\n" << endl;
                    }
                    system("pause");
                }
                else {
                    cout << "error al consultar...";
                }


            } //cierra if pregunta
            else ((pregunta == 'N') || (pregunta == 'n')); {

                //system("cls");
                cout << "Ingrese el Id del cliente que desea modificar: ";
                cin >> idc;

                cout << "Opciones: \n 1. Nombre \n 2. Apellido \n 3. NIT \n 4. Genero \n 5. Telefono \n 6. Correo Electronico" << endl;
                cout << "Ingrese que desea modificar: ";
                cin >> set;

                string c = to_string(idc);
                string insert;
                const char* i;
                char gen;

                switch (set) {
                case 1:
                    cout << "Ingrese el nuevo nombre del cliente: ";
                    cin.ignore();
                    getline(cin, cliente_new);
                    insert = "UPDATE clientes SET nombres = '" + cliente_new + "' WHERE idClientes = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 2:
                    cout << "Ingrese el nuevo apellido del cliente: ";
                    cin.ignore();
                    getline(cin, cliente_new);
                    insert = "UPDATE clientes SET apellidos = '" + cliente_new + "' WHERE idClientes = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 3:
                    cout << "Ingrese el nuevo NIT del cliente: ";
                    cin.ignore();
                    getline(cin, cliente_new);
                    insert = "UPDATE clientes SET nit = '" + cliente_new + "' WHERE idClientes = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;
                case 4:
                    cout << "Ingrese el nuevo Genero del cliente (F/M): ";
                    cin >> gen;
                    switch (gen) {
                    case 'M':
                        cliente_new = '1';
                        break;
                    case 'm':
                        cliente_new = '1';
                        break;

                    case 'F':
                        cliente_new = '0';
                        break;
                    case 'f':
                        cliente_new = '0';
                        break;
                    }
                    insert = "UPDATE clientes SET genero = b'" + cliente_new + "' WHERE idClientes = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 5:
                    cout << "Ingrese el nuevo Telefono del cliente: ";
                    cin.ignore();
                    getline(cin, cliente_new);
                    insert = "UPDATE clientes SET telefono = '" + cliente_new + "' WHERE idClientes = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 6:
                    cout << "Ingrese el nuevo Correro Electronico del cliente: ";
                    cin.ignore();
                    getline(cin, cliente_new);
                    insert = "UPDATE clientes SET correo_electronico = '" + cliente_new + "' WHERE idClientes = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                }
                if (!q_estado) {
                    cout << "\nModificacion Exitosa..." << endl;
                }
                else {
                    cout << "error al Modificar...";
                }

            } // cierra else de pregunta para buscar
        } // cierra if de conectar

        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();

    }




    void eliminar() {
        string c_del, consulta, t;
        char pregunta;
        const char* l;
        int opc = 0;
        int q_estado;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {
            cout << "Desea buscar cliente (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");
                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por nombre y apellido." << endl;
                cout << "2. buscar por nit." << endl;
                cout << "3. buscar por telefono." << endl;
                cout << "Ingrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre del cliente: ";
                    cin.ignore();
                    getline(cin, nombres);
                    cout << "ingrese apellido del cliente: ";
                    getline(cin, apellidos);

                    consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE nombres LIKE '%" + nombres + "%' UNION SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE apellidos LIKE '%" + apellidos + "%' LIMIT 3;";
                    break;

                case 2:
                    system("cls");
                    cout << "ingrese NIT del cliente: ";
                    cin.ignore();
                    getline(cin, nit);

                    consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE nit LIKE '%" + nit + "%';";                    
                    break;

                case 3:
                    system("cls");
                    cout << "ingrese telefono del cliente: ";
                    cin.ignore();
                    getline(cin, t);

                    consulta = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE telefono LIKE '%" + t + "%';";                    
                    break;

                }//cierra switch

                l = consulta.c_str();

                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Clientes-------------" << endl;
                    while (fila = mysql_fetch_row(resultado)) {
                        cout << "ID: " << fila[0] << "\nNombres: " << fila[1] << "\nApellidos: " << fila[2] << "\nNit: " << fila[3] << "\nGenero: " << fila[4] << "\nTelefono: " << fila[5] << "\nCorreo Electronico: " << fila[6] << "\nFecha de Ingreso: " << fila[7] << endl;
                        cout << "--------------------------------------\n" << endl;
                    }

                }
                else {
                    cout << "error al consultar...";
                }


            } //cierra if pregunta
            else((pregunta == 'N') || (pregunta == 'n')); {

                cout << "Ingrese ID de cliente para eliminar: ";
                cin >> c_del;
                string insert = "DELETE FROM clientes WHERE idClientes = ('" + c_del + "')";

                const char* d = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), d);
                if (!q_estado) {
                    cout << "El cliente: " + c_del + " se ha eliminado correctamente" << endl;
                }
                else {
                    cout << "Error al Eliminar...";
                }


            }
            
        }// cierra el conectar
        else {
        cout << "--- Error en la conexion ---";
            }
            cn.cerrar_conexion();

    }//void eliminar

    
};