#pragma once

#include<mysql.h>
#include<iostream>
#include<string>
#include "ConexionDB.h"

using namespace std;

class Productos{
    //atributos
private: string  producto, descripcion, Imagen, fecha_ingreso;
       int idMarca = 0;
       int existencia = 0;
       float precio_costo = 0, precio_venta = 0;
       //constructor
public:
    Productos() {
    }
    Productos(string pro, int idm, string des, string img, float pc, float pv, int exi, string fi) {
        producto = pro;
        idMarca = idm;
        descripcion = des;
        Imagen = img;
        precio_costo = pc;
        precio_venta = pv;
        existencia = exi;
        fecha_ingreso = fi;
    }

    //metodos
    //set (modificar)

    void setProducto(string pro) { producto = pro; }
    void setIdMarca(int idm) { idMarca = idm; }
    void setDescripcion(string des) { descripcion = des; }
    void setImagen(string img) { Imagen = img; }
    void setPrecio_costo(float pc) { precio_costo = pc; }
    void setGenero(float pv) { precio_venta = pv; }
    void setIdPuesto(int exi) { existencia = exi; }
    void setFechaIngreso(string fi) { fecha_ingreso = fi; }


    //get(mostrar)
    string getProducto() { return producto; }
    int getIdMarca() { return idMarca; }
    string getDescripcion() { return descripcion; }
    string getImagen() { return Imagen; }
    float getPrecio_costo() { return precio_costo; }
    float getPrecio_venta() { return precio_venta; }
    int getExistencia() { return existencia; }
    string getFechaIngreso() { return fecha_ingreso; }


    //metodos
    void crear() {
        int q_estado;
        ConexionDB cn = ConexionDB();
        cn.abrirconexion();
        if (cn.getConectar()) {
            string idma = to_string(idMarca);
            string pcp = to_string(precio_costo);
            string pvp = to_string(precio_venta);
            string exis = to_string(existencia);
            string insert = "INSERT INTO Productos (producto, idMarca, descripcion, Imagen, precio_costo, precio_venta, existencia, fecha_ingreso) VALUES ('" + producto + "'," + idma + ",'" + descripcion + "','" + Imagen + "'," + pcp + "," + pvp + "," + exis + ", CURRENT_TIMESTAMP );";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Ingreso Exitoso..." << endl;
            }
            else {
                cout << "error al ingresar..." << endl;
                cout << "Es posible que la marca ingresada no exista." << endl;
            }

        }
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }

    void leer() {
        int q_estado, opc;
        float  min, max;
        string consulta, t, puesto, marca, mi, ma;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {

            cout << "Como desea buscar: " << endl;
            cout << "1. Buscar por producto." << endl;
            cout << "2. Buscar por marca." << endl;
            cout << "3. Buscar por descripcion." << endl;
            cout << "4. Buscar por imagen." << endl;
            cout << "5. Buscar por precio de costo." << endl;
            cout << "6. Buscar por precio de venta." << endl;
            cout << "7. Buscar por existencia." << endl;
            cout << "8. Buscar por Fecha de ingreso." << endl;
            cout << "9. Ver Todos." << endl;
            cout << "\nIngrese No. de opcion: ";
            cin >> opc;

            switch (opc) {
            case 1:
                system("cls");
                cout << "ingrese nombre del producto: ";
                cin.ignore();
                getline(cin, producto);
                consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.producto LIKE '%" + producto + "%' LIMIT 5;";
                break;

            case 2:
                system("cls");
                cout << "ingrese marca del producto: ";
                cin.ignore();
                getline(cin, marca);
                consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE m.marca LIKE '%" + marca + "%' LIMIT 5;";
                break;

            case 3:
                system("cls");
                cout << "ingrese descripcion del producto: ";
                cin.ignore();
                getline(cin, descripcion);
                consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.descripcion LIKE '%" + descripcion + "%' LIMIT 5;";
                break;

            case 4:
                system("cls");
                cout << "ingrese Imagen del producto: ";
                cin.ignore();
                getline(cin, Imagen);
                consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.Imagen LIKE '%" + Imagen + "%' LIMIT 5;";
                break;

            case 5:
                system("cls");
                cout << "Ingrese el rango de precios de costo del producto que desea buscar" << endl;
                cout << "Ingrese rango minimo: ";
                cin >> min;
                cout << "ingrese rango maximo: ";
                cin >> max;
                mi = to_string(min);
                ma = to_string(max);
                consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.precio_costo > " + mi + " AND precio_costo < " + ma + ";";
                break;

            case 6:
                system("cls");
                cout << "ingrese el rango de precio de venta del producto" << endl;
                cout << "Ingrese rango minimo: ";
                cin >> min;
                cout << "ingrese rango maximo: ";
                cin >> max;
                mi = to_string(min);
                ma = to_string(max);
                consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.precio_venta > " + mi + " AND precio_venta < " + ma + ";";
                break;

            case 7:
                system("cls");
                cout << "ingrese rango de existencia del producto" << endl;
                cout << "Ingrese rango minimo: ";
                cin >> min;
                cout << "ingrese rango maximo: ";
                cin >> max;
                mi = to_string(min);
                ma = to_string(max);
                consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.existencia >= " + mi + " AND existencia <= " + ma + ";";
                break;
            case 8:
                system("cls");
                cout << "ingrese fehca de ingreso del producto: ";
                cin.ignore();
                getline(cin, fecha_ingreso);
                consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.Imagen LIKE '%" + fecha_ingreso + "%' LIMIT 10;";
                break;

            case 9:
                system("cls");
                consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca;";
                break;

            }//termina el switch
            const char* l = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), l);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                cout << "-------------Productos-------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID del Producto: " << fila[0] << "\nProducto: " << fila[1] << "\nMarca: " << fila[2] << "\nDescripcion: " << fila[3] << "\nImagen: " << fila[4] << "\nPrecio de Costo: " << fila[5] << "\nPrecio de Venta: " << fila[6] << "\nExistencia: " << fila[7] << "\nFecha de Ingreso: " << fila[8] << endl;
                    cout << "--------------------------------------\n" << endl;
                }
            }
            else {
                cout << "error al consultar...";
            }


            
            



        }//termina if conectar
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }

    void modificar() {
        //variables de productos en modificar
        int q_estado, opc, idp, set;
        float  min, max;
        string consulta, t, marca, mi, ma, producto_new;
        char pregunta, pregunta2;
        
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {
            cout << "Desea buscar producto (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                system("cls");
                cout << "Como desea buscar: " << endl;
                cout << "1. Buscar por producto y marca." << endl;
                cout << "2. buscar por descripcion." << endl;
                cout << "3. buscar por precio de venta." << endl;
                cout << "Ingrese No. de opcion: ";
                cin >> opc;

                switch (opc) {
                case 1:
                    system("cls");
                    cout << "ingrese nombre del producto: ";
                    cin.ignore();
                    getline(cin, producto);
                    cout << "ingrese la marca del producto: ";
                    getline(cin, marca);
                    consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.producto LIKE '%" + producto + "%' UNION SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE m.marca LIKE '%" + marca + "%';";
                    break;

                case 2:
                    system("cls");
                    cout << "ingrese descripcion del producto: ";
                    cin.ignore();
                    getline(cin, producto);
                    consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.descripcion LIKE '%" + descripcion + "%';";
                    break;

                case 3:
                    system("cls");
                    cout << "ingrese el rango de precio de venta del producto" << endl;
                    cout << "Ingrese rango minimo: ";
                    cin >> min;
                    cout << "ingrese rango maximo: ";
                    cin >> max;
                    mi = to_string(min);
                    ma = to_string(max);
                    consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.precio_venta > " + mi + " AND precio_venta < " + ma + ";";
                    break;

                }//cierra switch
                const char* l = consulta.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());
                    cout << "-------------Productos-------------" << endl;
                    while (fila = mysql_fetch_row(resultado)) {
                        cout << "ID del Producto: " << fila[0] << "\nProducto: " << fila[1] << "\nMarca: " << fila[2] << "\nDescripcion: " << fila[3] << "\nImagen: " << fila[4] << "\nPrecio de Costo: " << fila[5] << "\nPrecio de Venta: " << fila[6] << "\nExistencia: " << fila[7] << "\nFecha de Ingreso: " << fila[8] << endl;
                        cout << "--------------------------------------\n" << endl;
                    }
                }
                else {
                    cout << "error al consultar...";
                }


            }//cierra if pregunta
            else((pregunta == 'N') || (pregunta == 'n')); {
                cout << "Ingrese el Id del producto que desea modificar: ";
                cin >> idp;
                system("cls");
                cout << "ID del producto seleccionado: " + idp << endl;
                cout << "Opciones: \n 1. Producto \n 2. ID de Marca \n 3. Descripcion \n 4. Imagen \n 5. Precio de costo \n 6. Precio de venta \n 7. Existencia" << endl;
                cout << "Ingrese opcion que desea modificar: ";
                cin >> set;

                string c = to_string(idp);
                string insert, puesto;
                const char* i;
                const char* l;


                switch (set) {
                case 1:
                    cout << "Ingrese el nuevo nombre del producto: ";
                    cin.ignore();
                    getline(cin, producto_new);
                    insert = "UPDATE productos SET producto = '" + producto_new + "' WHERE idProducto = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 2:
                    cout << "Modificar Marca";
                    cout << "Desea buscar Marca (S/N): ";
                    cin >> pregunta2;

                    if ((pregunta2 == 'S') || (pregunta2 == 's')) {
                        system("cls");
                        cout << "Como desea buscar: " << endl;
                        cout << "1. Buscar por marca." << endl;
                        cout << "2. Ver todas las marcas." << endl;                        
                        cout << "Ingrese No. de opcion: ";
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


                    }// termina if pregunta2
                    else((pregunta2 == 'N') || (pregunta2 == 'n')); {
                        cout << "ID del producto seleccionado: " + c << endl;
                        cout << "Ingrese la nueva Id de la marca del producto: ";
                        cin.ignore();
                        getline(cin, producto_new);
                        insert = "UPDATE productos SET idMarca = '" + producto_new + "' WHERE idProducto = " + c + ";";
                        i = insert.c_str();
                        q_estado = mysql_query(cn.getConectar(), i);
                        break;
                    }//termina else pregunta2
                    
                case 3:
                    cout << "Ingrese la nueva descripcion del producto: ";
                    cin.ignore();
                    getline(cin, producto_new);
                    insert = "UPDATE productos SET descripcion = '" + producto_new + "' WHERE idProducto = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 4:
                    cout << "Ingrese la nueva imagen del producto: ";
                    cin.ignore();
                    getline(cin, producto_new);
                    insert = "UPDATE productos SET Imagen = '" + producto_new + "' WHERE idProducto = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 5:
                    cout << "Ingrese el nuevo precio de costo del producto: ";
                    cin.ignore();
                    getline(cin, producto_new);
                    insert = "UPDATE productos SET precio_costo = '" + producto_new + "' WHERE idProducto = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 6:
                    cout << "Ingrese el nuevo precio de venta del producto: ";
                    cin.ignore();
                    getline(cin, producto_new);
                    insert = "UPDATE productos SET precio_venta = '" + producto_new + "' WHERE idProducto = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 7:
                    cout << "Ingrese nueva cantidad de existencia del producto: ";
                    cin.ignore();
                    getline(cin, producto_new);
                    insert = "UPDATE productos SET existencia = '" + producto_new + "' WHERE idProducto = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;
                }//termina switch

                const char* p = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), p);
                if (!q_estado) {
                    cout << "Ingreso Exitoso..." << endl;
                }
                else {
                    cout << "error al ingresar...";
                }

            }//termina esle pregunta


        }//cierra conectar
        else {
        cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }// cierra modificar

    void eliminar() {
             string c_del, consulta, marca, mi, ma;
             float min, max;
             char pregunta;
             int q_estado, opc;
             ConexionDB cn = ConexionDB();
             MYSQL_ROW fila;
             MYSQL_RES* resultado;
             cn.abrirconexion();
             if (cn.getConectar()) {
                 cout << "Desea buscar producto (S/N): ";
                 cin >> pregunta;

                 if ((pregunta == 'S') || (pregunta == 's')) {
                     system("cls");
                     cout << "Como desea buscar: " << endl;
                     cout << "1. Buscar por producto y marca." << endl;
                     cout << "2. buscar por descripcion." << endl;
                     cout << "3. buscar por precio de venta." << endl;
                     cout << "Ingrese No. de opcion: ";
                     cin >> opc;

                     switch (opc) {
                     case 1:
                         system("cls");
                         cout << "ingrese nombre del producto: ";
                         cin.ignore();
                         getline(cin, producto);
                         cout << "ingrese la marca del producto: ";
                         getline(cin, marca);
                         consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.producto LIKE '%" + producto + "%' UNION SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE m.marca LIKE '%" + marca + "%';";
                         break;

                     case 2:
                         system("cls");
                         cout << "ingrese descripcion del producto: ";
                         cin.ignore();
                         getline(cin, producto);
                         consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.descripcion LIKE '%" + descripcion + "%';";
                         break;

                     case 3:
                         system("cls");
                         cout << "ingrese el rango de precio de venta del producto" << endl;
                         cout << "Ingrese rango minimo: ";
                         cin >> min;
                         cout << "ingrese rango maximo: ";
                         cin >> max;
                         mi = to_string(min);
                         ma = to_string(max);
                         consulta = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.precio_venta > " + mi + " AND precio_venta < " + ma + ";";
                         break;

                     }//cierra switch
                     const char* l = consulta.c_str();
                     q_estado = mysql_query(cn.getConectar(), l);
                     if (!q_estado) {
                         resultado = mysql_store_result(cn.getConectar());
                         cout << "-------------Productos-------------" << endl;
                         while (fila = mysql_fetch_row(resultado)) {
                             cout << "ID del Producto: " << fila[0] << "\nProducto: " << fila[1] << "\nMarca: " << fila[2] << "\nDescripcion: " << fila[3] << "\nImagen: " << fila[4] << "\nPrecio de Costo: " << fila[5] << "\nPrecio de Venta: " << fila[6] << "\nExistencia: " << fila[7] << "\nFecha de Ingreso: " << fila[8] << endl;
                             cout << "--------------------------------------\n" << endl;
                         }
                     }
                     else {
                         cout << "error al consultar...";
                     }


                 }//cierra if pregunta
                 else((pregunta == 'N') || (pregunta == 'n')); {
                     cout << "Ingrese ID del producto que desea eliminar: ";
                     cin >> c_del;
                     string insert = "DELETE FROM productos WHERE idProducto = ('" + c_del + "');";
                     
                     const char* d = insert.c_str();
                     q_estado = mysql_query(cn.getConectar(), d);
                     if (!q_estado) {
                         cout << "El ID: " + c_del + " se ha eliminado correctamente" << endl;
                     }
                     else {
                         cout << "Error al Eliminar...";
                     }

                 }//cierra else pregunta
             }//cierra conectar
             
    }

};

