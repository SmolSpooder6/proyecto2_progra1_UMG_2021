#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
#include "ConexionDB.h"

using namespace std;

class Empleados {

    //atributos
private: string  nombres, apellidos, direccion, dpi, genero, fecha_nacimiento, fecha_inicio_labores, fechaingreso;
       int telefono = 0;
       int idPuesto = 0;
       //constructor
public:
    Empleados() {
    }
    Empleados(string nom, string ape, string dir, int tel, string d, string gen, string fn, int idp, string fil, string fi) {
        nombres = nom;
        apellidos = ape;
        direccion = dir;
        telefono = tel;
        dpi = d;
        genero = gen;
        fecha_nacimiento = fn;
        idPuesto = idp;
        fecha_inicio_labores = fil;
        fechaingreso = fi;
    }

    //metodos
    //set (modificar)

    void setNombres(string nom) { nombres = nom; }
    void setApellidos(string ape) { apellidos = ape; }
    void setDireccion(string dir) { direccion = dir; }
    void setTelefono(int tel) { telefono = tel; }
    void setDpi(string d) { dpi = d; }
    void setGenero(string gen) { genero = gen; }
    void setFecha_nacimiento(string fn) { fecha_nacimiento = fn; }
    void setIdPuesto(int idp) { idPuesto = idp; }
    void setFecha_inicio_labores(string fil) { fecha_inicio_labores = fil; }
    void setFechaIngreso(string fi) { fechaingreso = fi; }


    //get(mostrar)

    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getDireccion() { return direccion; }
    int getTelefono() { return telefono; }
    string getDpi() { return dpi; }
    string getGenero() { return genero; }
    string getFecha_nacimiento() { return fecha_nacimiento; }
    int getIdPuesto() { return idPuesto; }
    string getFecha_inicio_labores() { return fecha_inicio_labores; }
    string getFechaIngreso() { return fechaingreso; }


    //metodos
    void crear() {
        int q_estado;
        ConexionDB cn = ConexionDB();
        cn.abrirconexion();
        if (cn.getConectar()) {
            string t = to_string(telefono);
            string id = to_string(idPuesto);
            string insert = "INSERT INTO empleados (nombres,apellidos,direccion,telefono,DPI,genero,fecha_nacimiento,idPuesto,fecha_inicio_labores,fechaIngreso) VALUES ('" + nombres + "','" + apellidos + "','" + direccion + "'," + t + ",'" + dpi + "',b'" + genero + "','" + fecha_nacimiento + "'," + id + ",'" + fecha_inicio_labores + "', CURRENT_TIMESTAMP );";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Ingreso Exitoso..." << endl;
            }
            else {
                cout << "error al ingresar..." << endl;
                cout << "Es posible que el puesto ingresado no exista." << endl;
            }

        }
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }


    void leer() {
        int q_estado, opc;
        string consulta, t, puesto;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {

            cout << "Como desea buscar: " << endl;
            cout << "1. Buscar por nombre y apellido." << endl;
            cout << "2. Buscar por direccion." << endl;
            cout << "3. Buscar por telefono." << endl;
            cout << "4. Buscar por DPI." << endl;
            cout << "5. Buscar por genero." << endl;
            cout << "6. Buscar por Fecha de nacimiento." << endl;
            cout << "7. Buscar por puesto." << endl;
            cout << "8. Buscar por Fecha de inicio de labores." << endl;
            cout << "9. Buscar por Fecha de ingreso." << endl;
            cout << "10. Ver Todos" << endl;
            cout << "\nIngrese No. de opcion: ";
            cin >> opc;

            switch (opc) {
            case 1:
                system("cls");
                cout << "ingrese nombre del empleado: ";
                cin.ignore();
                getline(cin, nombres);
                cout << "ingrese apellido de la persona: ";
                getline(cin, apellidos);
                consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE nombres LIKE '%" + nombres + "%' UNION SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE apellidos LIKE '%" + apellidos + "%' LIMIT 5;";
                break;

            case 2:
                system("cls");
                cout << "ingrese direccion del empleado: ";
                cin.ignore();
                getline(cin, direccion);
                consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE direccion LIKE '%" + direccion + "%'  LIMIT 3;";
                break;

            case 3:
                system("cls");
                cout << "ingrese telefono del empleado: ";
                cin.ignore();
                getline(cin, t);
                consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE telefono LIKE '%" + t + "%'  LIMIT 3;";
                break;

            case 4:
                system("cls");
                cout << "ingrese DPI del empleado: ";
                cin.ignore();
                getline(cin, dpi);
                consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE DPI LIKE '%" + dpi + "%'  LIMIT 3;";
                break;

            case 5:
                system("cls");
                cout << "ingrese genero del empleado (1/0): ";
                cin.ignore();
                getline(cin, genero);
                consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE genero = '" + genero + "'  LIMIT 10;";
                break;

            case 6:
                system("cls");
                cout << "ingrese fecha de nacimiento del empleado: ";
                cin.ignore();
                getline(cin, fecha_nacimiento);
                consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE fecha_nacimiento LIKE '%" + fecha_nacimiento + "%'  LIMIT 10;";
                break;

            case 7:
                int op;
                cout << "1. Ver todos los puestos" << endl;
                cout << "2. Buscar por nombre del puesto" << endl;
                cout << "Ingrese opcion: ";
                cin >> op;
                switch (op) {
   
                case 1:                    
                    system("cls");
                    cout << "ingrese ID del puesto del empleado: ";
                    cin.ignore();
                    getline(cin, puesto);
                    consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE p.idpuesto;";
                    break;
                    
                case 2:
                    string puesto;
                    system("cls");
                    cout << "ingrese puesto del empleado: ";
                    cin.ignore();
                    getline(cin, puesto);
                    consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE p.puesto LIKE '%" + puesto + "%'  LIMIT 5;";
                    break;
                }
                break;
            case 8:
                system("cls");
                cout << "ingrese fecha de inicio de labores del empleado (YY-MM-DD): ";
                cin.ignore();
                getline(cin, fecha_inicio_labores);
                consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE fecha_inicio_labores LIKE '%" + fecha_inicio_labores + "%'  LIMIT 5;";
                break;

            case 9:
                system("cls");
                cout << "ingrese fecha de ingreso del empleado: ";
                cin.ignore();
                getline(cin, fechaingreso);
                consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE fechaingreso LIKE '%" + fechaingreso + "%'  LIMIT 5;";
                break;

            case 10:
                system("cls");
                consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto;";
                break;

            }
            
            
            const char* l = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), l);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                cout << "-------------Empleados-------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID del Empleado: " << fila[0] << "\nNombres: " << fila[1] << "\nApellidos: " << fila[2] << "\nDireccion: " << fila[3] << "\nTelefono: " << fila[4] << "\nDPI: " << fila[5] << "\nGenero: " << fila[6] << "\nFecha de Nacimiento: " << fila[7] << "\nPuesto: " << fila[8] << "\nFecha de Inicio de Labores: " << fila[9] << "\nFecha de Ingreso: " << fila[10] << endl;
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
        string psto, consulta, consulta2, empleado_new, t;
        char pregunta, pregunta2;
        int q_estado, opc, idc, set;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {
            cout << "Desea buscar empleado (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");
                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por nombre y apellido." << endl;
                cout << "2. buscar por DPI." << endl;
                cout << "3. buscar por telefono." << endl;
                cout << "Ingrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre del empleado: ";
                    cin.ignore();
                    getline(cin, nombres);
                    cout << "ingrese apellido de la persona: ";
                    getline(cin, apellidos);
                    consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE nombres LIKE '%" + nombres + "%' UNION SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, e.genero, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE apellidos LIKE '%" + apellidos + "%' LIMIT 5;";
                    break;

                case 2:
                    system("cls");
                    cout << "ingrese DPI del empleado: ";
                    cin.ignore();
                    getline(cin, dpi);
                    consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE DPI LIKE '%" + dpi + "%'  LIMIT 3;";
                    break;

                case 3:
                    system("cls");
                    cout << "ingrese telefono del empleado: ";
                    cin.ignore();
                    getline(cin, t);
                    consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE telefono LIKE '%" + t + "%'  LIMIT 3;";
                    break;

                }
                const char* l = consulta.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Empleados-------------" << endl;
                    while (fila = mysql_fetch_row(resultado)) {
                        cout << "ID del Empleado: " << fila[0] << "\nNombres: " << fila[1] << "\nApellidos: " << fila[2] << "\nDireccion: " << fila[3] << "\nTelefono: " << fila[4] << "\nDPI: " << fila[5] << "\nGenero: " << fila[6] << "\nFecha de Nacimiento: " << fila[7] << "\nPuesto: " << fila[8] << "\nFecha de Inicio de Labores: " << fila[9] << "\nFecha de Ingreso: " << fila[10] << endl;
                        cout << "--------------------------------------\n" << endl;
                    }
                }
                else {
                    cout << "error al consultar...";
                }
            }// cierra if pregunta
            else((pregunta == 'N') || (pregunta == 'n')); {
                cout << "Ingrese el Id del empleado que desea modificar: ";
                cin >> idc;
                system("cls");
                cout << "ID del empleado seleccionado: " + idc << endl;
                cout << "Opciones: \n 1. Nombre \n 2. Apellido \n 3. Direccion \n 4. Telefono \n 5. DPI \n 6. Genero \n 7. Fecha de nacimiento \n 8. Puesto \n 9. Fecha de inicio de labores" << endl;
                cout << "Ingrese opcion que desea modificar: ";
                cin >> set;

                string c = to_string(idc);
                string insert, puesto;
                int op;
                const char* i;
                char gen;


                switch (set) {
                case 1:
                    cout << "Ingrese el nuevo nombre del empleado: ";
                    cin.ignore();
                    getline(cin, empleado_new);
                    insert = "UPDATE empleados SET nombres = '" + empleado_new + "' WHERE idempleados = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 2:
                    cout << "Ingrese el nuevo apellido del empleado: ";
                    cin.ignore();
                    getline(cin, empleado_new);
                    insert = "UPDATE empleados SET apellidos = '" + empleado_new + "' WHERE idempleados = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;
                case 3:
                    cout << "Ingrese la nueva direccion del empleado: ";
                    cin.ignore();
                    getline(cin, empleado_new);
                    insert = "UPDATE empleados SET direccion = '" + empleado_new + "' WHERE idempleados = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 4:
                    cout << "Ingrese el nuevo telefono del empleado: ";
                    cin.ignore();
                    getline(cin, empleado_new);
                    insert = "UPDATE empleados SET telefono = '" + empleado_new + "' WHERE idempleados = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 5:
                    cout << "Ingrese el nuevo DPI del empleado: ";
                    cin.ignore();
                    getline(cin, empleado_new);
                    insert = "UPDATE empleados SET DPI = '" + empleado_new + "' WHERE idempleados = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 6:
                    cout << "Ingrese el nuevo genero del empleado (1/0): ";
                    cin >> gen;
                    switch (gen) {
                    case 'M':
                        empleado_new = '1';
                        break;
                    case 'm':
                        empleado_new = '1';
                        break;

                    case 'F':
                        empleado_new = '0';
                        break;
                    case 'f':
                        empleado_new = '0';
                        break;
                    }
                    insert = "UPDATE empleados SET genero = b'" + empleado_new + "' WHERE idempleados = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 7:
                    cout << "Ingrese La nueva fecha de nacimiento del empleado: ";
                    cin.ignore();
                    getline(cin, empleado_new);
                    insert = "UPDATE empleados SET fecha_nacimiento = '" + empleado_new + "' WHERE idempleados = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 8:
                    system("cls");
                    cout << "Modificar puesto" << endl;
                    cout << "desea buscar puestos? (S/N):";
                    cin >> pregunta2;
                    if ((pregunta2 == 'S') || (pregunta2 == 's')) {
                        cout << "1. Buscar por ID puesto" << endl;
                        cout << "2. Buscar por nombre del puesto" << endl;
                        cout << "3. Ver todos los puestos" << endl;
                        cout << "Ingrese opcion: ";
                        cin >> op;
                        switch (op) {

                        case 1:
                            system("cls");
                            cout << "ingrese ID del puesto: ";
                            cin.ignore();
                            getline(cin, puesto);
                            consulta2 = "SELECT *FROM puestos WHERE idPuestos = " + puesto + ";";
                            break;

                        case 2:
                            system("cls");
                            cout << "ingrese nombre del puesto: ";
                            cin.ignore();
                            getline(cin, puesto);
                            consulta2 = "SELECT *FROM puestos WHERE puesto = '" + puesto + "';";
                            break;

                        case 3:
                            system("cls");
                            consulta2 = "SELECT* FROM puestos;";
                            break;
                        }                     

                        const char* l = consulta.c_str();
                        q_estado = mysql_query(cn.getConectar(), l);
                        if (!q_estado) {
                            resultado = mysql_store_result(cn.getConectar());
                            cout << "-------------Empleados-------------" << endl;
                            while (fila = mysql_fetch_row(resultado)) {
                                cout << "ID del Empleado: " << fila[0] << "\nNombres: " << fila[1] << "\nApellidos: " << fila[2] << "\nDireccion: " << fila[3] << "\nTelefono: " << fila[4] << "\nDPI: " << fila[5] << "\nGenero: " << fila[6] << "\nFecha de Nacimiento: " << fila[7] << "\nPuesto: " << fila[8] << "\nFecha de Inicio de Labores: " << fila[9] << "\nFecha de Ingreso: " << fila[10] << endl;
                                cout << "--------------------------------------\n" << endl;
                            }
                        }
                        const char* p = consulta2.c_str();
                        q_estado = mysql_query(cn.getConectar(), p);
                        if (!q_estado) {
                            resultado = mysql_store_result(cn.getConectar());
                            cout << "-------------puestos-------------" << endl;
                            while (fila = mysql_fetch_row(resultado)) {
                                cout << "ID:" << fila[0] << ": " << fila[1] << endl;

                            }
                        }
                        else {
                            cout << "error al consultar...";
                        }
                    
                    
                    }// cierra if pregunta2
                    else((pregunta == 'N') || (pregunta == 'n')); {
                        cout << "ID del empleado seleccionado: " + idc << endl;
                        cout << "\nIngrese el nuevo ID del puesto del empleado: ";
                        cin.ignore();
                        getline(cin, empleado_new);
                        insert = "UPDATE empleados SET idPuesto = '" + empleado_new + "' WHERE idempleados = " + c + ";";
                        i = insert.c_str();
                        q_estado = mysql_query(cn.getConectar(), i);
                        break;
                    
                    }//cierra else pregunta2

                case 9:
                    cout << "Ingrese La nueva fecha de inicio de labores (YY-MM-DD): ";
                    cin.ignore();
                    getline(cin, empleado_new);
                    insert = "UPDATE empleados SET fecha_inicio_labores = '" + empleado_new + "' WHERE idempleados = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;


                }// switch set

                const char* m = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), m);
                if (!q_estado) {
                    cout << "Ingreso Exitoso..." << endl;
                }
                else {
                    cout << "error al ingresar...";
                }

            }//cierra else pregunta
        }// cierra if conectar
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();

    }

    void eliminar() {
        string c_del, consulta, t;
        char pregunta;
        int q_estado, opc;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {
            cout << "Desea buscar empleado (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");
                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por nombre y apellido." << endl;
                cout << "2. buscar por DPI." << endl;
                cout << "3. buscar por telefono." << endl;
                cout << "Ingrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre del empleado: ";
                    cin.ignore();
                    getline(cin, nombres);
                    cout << "ingrese apellido de la persona: ";
                    getline(cin, apellidos);
                    consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE nombres LIKE '%" + nombres + "%' UNION SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, e.genero, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE apellidos LIKE '%" + apellidos + "%' LIMIT 5;";
                    break;

                case 2:
                    system("cls");
                    cout << "ingrese DPI del empleado: ";
                    cin.ignore();
                    getline(cin, dpi);
                    consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE DPI LIKE '%" + dpi + "%'  LIMIT 3;";
                    break;

                case 3:
                    system("cls");
                    cout << "ingrese telefono del empleado: ";
                    cin.ignore();
                    getline(cin, t);
                    consulta = "SELECT e.idempleados, e.nombres, e.apellidos, e.direccion, e.telefono, e.DPI, CASE e.genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, e.fecha_nacimiento, p.puesto, e.fecha_inicio_labores, e.fechaingreso FROM empleados AS e INNER JOIN puestos AS p ON e.idPuesto = p.idPuesto WHERE telefono LIKE '%" + t + "%'  LIMIT 3;";
                    break;

                }
                const char* l = consulta.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Empleados-------------" << endl;
                    while (fila = mysql_fetch_row(resultado)) {
                        cout << "ID del Empleado: " << fila[0] << "\nNombres: " << fila[1] << "\nApellidos: " << fila[2] << "\nDireccion: " << fila[3] << "\nTelefono: " << fila[4] << "\nDPI: " << fila[5] << "\nGenero: " << fila[6] << "\nFecha de Nacimiento: " << fila[7] << "\nPuesto: " << fila[8] << "\nFecha de Inicio de Labores: " << fila[9] << "\nFecha de Ingreso: " << fila[10] << endl;
                        cout << "--------------------------------------\n" << endl;
                    }
                }
                else {
                    cout << "error al consultar...";
                }
            }// cierra if pregunta
            else((pregunta == 'N') || (pregunta == 'n')); {

                cout << "Ingrese ID del empleado que desea eliminar: ";
                cin >> c_del;
                string insert = "DELETE FROM empleados WHERE idempleados = ('" + c_del + "');";

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