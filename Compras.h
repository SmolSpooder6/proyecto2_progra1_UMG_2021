#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
#include <sstream>

#include "ConexionDB.h"
#include "Proveedores.h"
#include "Productos.h"
#include "Marcas.h"

using namespace std;

class Compras{
    //atributos
public: int idProveedor = 0, idproducto = 0, cantidad = 0;
      float precio_costo_unitario = 0;
      char preguntaProv, preguntaProd;
      
      string producto, descripcion, Imagen, fecha_ingreso;
      int existencia = 0, idMarca = 0;
      float precio_costo = 0, precio_venta = 0;
    

    //metodos
    void crear() {
        int q_estado;
        string consulta_orden_compra, consultaNoc;
        int noC = 1, idcompra = 0, opcionProducto = 0;
        const char* l;
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        ConexionDB cn = ConexionDB();
        cn.abrirconexion();
        if (cn.getConectar()) {


            cout << "Proveedor" << endl;
            cout << "Desea buscar proveedor? (S/N): ";
            cin >> preguntaProv;
            if ((preguntaProv == 'S') || (preguntaProv == 's')) {
                Proveedores p = Proveedores();
                p.leer();
                system("pause");
            }
            else ((preguntaProv == 'N') || (preguntaProv == 'n')); {
                cout << "Ingrese ID del proveedor: ";
                cin >> idProveedor;
            }
            string idpvs = to_string(idProveedor);

            
            string cants = to_string(cantidad);
            
            


            // busca NO. de Orden para seguir la secuencia
            consulta_orden_compra = "SELECT* FROM compras ORDER BY no_orden_compra DESC LIMIT 1;";

            l = consulta_orden_compra.c_str();
            q_estado = mysql_query(cn.getConectar(), l);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                while (fila = mysql_fetch_row(resultado)) {
                    stringstream aux2;
                    aux2 << fila[1];
                    aux2 >> noC;
                    noC++;
                }
            }
            else {
                cout << "Error al consultar No. de Orden de compra...";
            }
            string noCs = to_string(noC);

            //inserta datos en compras
            string insert = "INSERT INTO compras (no_orden_compra, idProveedor, fecha_orden, fechaingreso) VALUES ('" + noCs + "','" + idpvs + "', CURRENT_TIMESTAMP, CURRENT_TIMESTAMP );";
            const char* i = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Ingreso Exitoso..." << endl;
            }
            else {
                cout << "error al ingresar..." << endl;
                cout << "Es posible que el proveedor ingresado no existe." << endl;
            }

//----------------------------------------------------------------------------------------------------------------------------------------------------------------


            // consulta el numero de Orden para compras detalle y sacar el id de compra
            consultaNoc = "SELECT* FROM compras WHERE no_orden_compra = " + noCs + ";";
            l = consultaNoc.c_str();
            q_estado = mysql_query(cn.getConectar(), l);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                while (fila = mysql_fetch_row(resultado)) {
                    stringstream aux4;
                    aux4 << fila[0];
                    aux4 >> idcompra;
                    
                }                
            }          
            else {
                cout << "Error al consultar id de cliente...";
            }
            string idc = to_string(idcompra);



            const char* l;
            
            string idpds, consultaProd, exis, pcs;
            char preguntaMarca;
            cout << "\nProducto" << endl;
            cout << "1. Agregar a producto existente" << endl;
            cout << "2. Ingresar nuevo producto" << endl;
            cout << "Ingrese opcion: ";
            cin >> opcionProducto;

            switch(opcionProducto){
            case 1:
                cout << "Desea buscar producto? (S/N): ";
                cin >> preguntaProd;
                if ((preguntaProd == 'S') || (preguntaProd == 's')) {
                    Productos p = Productos();
                    p.leer();
                    system("pause");
                }
                else ((preguntaProd == 'N') || (preguntaProd == 'n')); {
                    cout << "Ingrese ID del producto: ";
                    cin >> idproducto;
                    cout << "Ingrese cantidad del producto: ";
                    cin >> existencia;
                    cout << "Ingrese el precio de costo del producto: ";
                    cin >> precio_costo;

                    idpds = to_string(idproducto);
                    pcs = to_string(precio_costo);
                    exis = to_string(existencia);

                    
                    insert = "UPDATE productos SET existencia = '" + exis + "', precio_costo = '" + pcs + "' WHERE idProducto = " + idpds + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);                    
                    if (!q_estado) {
                        cout << "Ingreso Exitoso..." << endl;
                    }
                    else {
                        cout << "error al ingresar...";
                    }
                }//termina else de pregunta producto
                break;
            case 2:

                cout << "Ingrese nombre del Producto: ";
                cin.ignore();
                getline(cin, producto);
                cout << "Marcas" << endl;
                cout << "Desea buscar marca? (S/N): ";
                cin >> preguntaMarca;
                if ((preguntaMarca == 'S') || (preguntaMarca == 's')) {
                    Marcas p = Marcas();
                    p.leer();
                    system("pause");
                }
                else ((preguntaMarca == 'N') || (preguntaMarca == 'n')); {
                    cout << "Ingrese Id de la marca: ";
                    cin >> idMarca;
                }
                cout << "Ingrese descripcion del producto: ";
                cin.ignore();
                getline(cin, descripcion);
                cout << "ingrese Imagen: ";
                getline(cin, Imagen);
                cout << "Ingrese el precio de costo del producto: ";
                cin >> precio_costo;
                cout << "Ingrese el precio de venta del producto: ";
                cin >> precio_venta;
                cout << "Ingrese la cantidad de existencia del producto: ";
                cin >> existencia;

                Productos p = Productos(producto, idMarca, descripcion, Imagen, precio_costo, precio_venta, existencia, fecha_ingreso);
                p.crear();
                system("pause");     
                exis = to_string(existencia);
                system("cls");
                consultaProd = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.producto LIKE '%" + producto + "%' AND p.descripcion LIKE '%" + descripcion + "%';";
                l = consultaProd.c_str();
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
                
                pcs = to_string(precio_costo);

                //ID producto
                cout << "Ingrese ID del producto: ";
                cin >> idproducto;
                idpds = to_string(idproducto);
                break;
 
            }//cierra el switch

             //inserta datos en compras detalle
            insert = "INSERT INTO compras_detalle (idcompra, idproducto, cantidad, precio_costo_unitario) VALUES ('" + idc + "', '" + idpds + "', '" + exis + "', '" + pcs + "');";
            i = insert.c_str();
            q_estado = mysql_query(cn.getConectar(), i);
            if (!q_estado) {
                cout << "Ingreso Exitoso..." << endl;
            }
            else {
                cout << "error al ingresar..." << endl;
                cout << "Es posible que el proveedor ingresado no existe." << endl;
            }
            


        }
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }

    void leer(){

        int q_estado, opc, min, max, noc;
        string nocs, consulta, ma, mi;
        const char* l;
        char pregunta;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {

            system("cls");
            cout << "Como desea buscar: " << endl;
            cout << "1. Buscar por No. de orden de compra." << endl;
            cout << "2. Buscar por Id de proveedor." << endl;
            cout << "3. Buscar por Fecha de orden." << endl;
            cout << "4. Buscar por Fecha de ingreso." << endl;
            cout << "5. Buscar por ID de producto." << endl;
            cout << "6. Buscar por Precio de costo." << endl;    
            cout << "7. Ver Todos" << endl;
            cout << "\nIngrese No. de opcion: ";
            cin >> opc;

            switch (opc) {
            case 1:
                system("cls");
                cout << "ingrese No. de orden de compra: ";
                cin >> noc;
                nocs = to_string(noc);
                consulta = "SELECT c.idcompras, c.no_orden_compra, p.proveedor, c.fecha_orden, c.fechaIngreso, cd.idcompras_detalle, pr.producto, pr.Descripcion, cd.cantidad, cd.precio_costo_unitario FROM compras AS c INNER JOIN proveedores AS p ON c.idProveedor = p.idproveedores INNER JOIN compras_detalle AS cd ON cd.idcompra = c.idcompras INNER JOIN productos AS pr ON pr.idproducto = cd.idproducto WHERE c.no_orden_compra = " + nocs + ";";
                break;

            case 2:

                system("cls");
                cout << "Desea buscar proveedor? (S/N): ";
                cin >> pregunta;
                if ((pregunta == 'S') || (pregunta == 's')) {
                    Proveedores p = Proveedores();
                    p.leer();
                }
                else ((pregunta == 'N') || (pregunta == 'n')); {
                    cout << "ingrese ID del proveedor: ";
                    cin >> noc;
                    nocs = to_string(noc);
                    consulta = "SELECT c.idcompras, c.no_orden_compra, p.proveedor, c.fecha_orden, c.fechaIngreso, cd.idcompras_detalle, pr.producto, pr.Descripcion, cd.cantidad, cd.precio_costo_unitario FROM compras AS c INNER JOIN proveedores AS p ON c.idProveedor = p.idproveedores INNER JOIN compras_detalle AS cd ON cd.idcompra = c.idcompras INNER JOIN productos AS pr ON pr.idproducto = cd.idproducto WHERE c.idProveedor = " + nocs + ";";
                    break;
                }
                break;

            case 3:
                system("cls");
                cout << "ingrese Fecha de orden (YYYY-MM-DD): ";
                cin >> nocs;                
                consulta = "SELECT c.idcompras, c.no_orden_compra, p.proveedor, c.fecha_orden, c.fechaIngreso, cd.idcompras_detalle, pr.producto, pr.Descripcion, cd.cantidad, cd.precio_costo_unitario FROM compras AS c INNER JOIN proveedores AS p ON c.idProveedor = p.idproveedores INNER JOIN compras_detalle AS cd ON cd.idcompra = c.idcompras INNER JOIN productos AS pr ON pr.idproducto = cd.idproducto WHERE c.fecha_orden LIKE '%" + nocs + "%';";
                break;
                
            case 4:
                system("cls");
                cout << "ingrese Fecha de Ingreso (YYYY-MM-DD HH:MM:SS): ";
                cin >> nocs;
                consulta = "SELECT c.idcompras, c.no_orden_compra, p.proveedor, c.fecha_orden, c.fechaIngreso, cd.idcompras_detalle, pr.producto, pr.Descripcion, cd.cantidad, cd.precio_costo_unitario FROM compras AS c INNER JOIN proveedores AS p ON c.idProveedor = p.idproveedores INNER JOIN compras_detalle AS cd ON cd.idcompra = c.idcompras INNER JOIN productos AS pr ON pr.idproducto = cd.idproducto WHERE c.fechaIngreso LIKE '%" + nocs + "%';";
                break;

            case 5:
                system("cls");
                cout << "Buscar por producto\nDesea buscar Producto? (S/N): ";
                cin >> pregunta;
                if ((pregunta == 'S') || (pregunta == 's')) {
                    Productos p = Productos();
                    p.leer();
                }
                else ((pregunta == 'N') || (pregunta == 'n')); {
                    cout << "ingrese ID del Producto: ";
                    cin >> noc;
                    nocs = to_string(noc);
                    consulta = "SELECT c.idcompras, c.no_orden_compra, p.proveedor, c.fecha_orden, c.fechaIngreso, cd.idcompras_detalle, pr.producto, pr.Descripcion, cd.cantidad, cd.precio_costo_unitario FROM compras AS c INNER JOIN proveedores AS p ON c.idProveedor = p.idproveedores INNER JOIN compras_detalle AS cd ON cd.idcompra = c.idcompras INNER JOIN productos AS pr ON pr.idproducto = cd.idproducto WHERE cd.idproducto = " + nocs + ";";
                    break;
                }
                break;

            case 6:
                system("cls");
                cout << "ingrese Rango de precio de costo: ";
                cout << "Ingrese rango minimo: ";
                cin >> min;
                cout << "ingrese rango maximo: ";
                cin >> max;
                mi = to_string(min);
                ma = to_string(max);                
                consulta = "SELECT c.idcompras, c.no_orden_compra, p.proveedor, c.fecha_orden, c.fechaIngreso, cd.idcompras_detalle, pr.producto, pr.Descripcion, cd.cantidad, cd.precio_costo_unitario FROM compras AS c INNER JOIN proveedores AS p ON c.idProveedor = p.idproveedores INNER JOIN compras_detalle AS cd ON cd.idcompra = c.idcompras INNER JOIN productos AS pr ON pr.idproducto = cd.idproducto WHERE precio_costo_unitario > " + mi + " AND d.precio_costo_unitario < " + ma + ";";
                break;

            case 7:
                system("cls");
                consulta = "SELECT c.idcompras, c.no_orden_compra, p.proveedor, c.fecha_orden, c.fechaIngreso, cd.idcompras_detalle, pr.producto, pr.Descripcion, cd.cantidad, cd.precio_costo_unitario FROM compras AS c INNER JOIN proveedores AS p ON c.idProveedor = p.idproveedores INNER JOIN compras_detalle AS cd ON cd.idcompra = c.idcompras INNER JOIN productos AS pr ON pr.idproducto = cd.idproducto;";
                break;

            }//cierra switch

            l = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), l);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                system("cls");
                cout << "-------------Compras-------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID compra: " << fila[0] << "\nNo. Orden de compra: " << fila[1] << "\nProveedor: : " << fila[2] << "\nFecha de orden: " << fila[3] << "\nFecha de ingreso: " << fila[4] << "\nID Compras detalle: " << fila[5] << "\nProducto: " << fila[6] << "\nDescripcion: " << fila[7] << "\nCantidad: " << fila[8] << "\nPrecio de costo unitario: " << fila[9] << endl;
                    cout << "--------------------------------------\n" << endl;
                }
            }
            else {
                cout << "error al consultar..." << endl;
            }

        }//cierra if conectar
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }


    void modificar() {

        string compra_new;
        char pregunta, pregunta2;
        int q_estado, opc = 0, idc = 0, set = 0;
        ConexionDB cn = ConexionDB();
        cn.abrirconexion();
        if (cn.getConectar()) {
            cout << "Desea buscar Compras (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                Compras c = Compras();
                c.leer();

            }
            else((pregunta == 'N') || (pregunta == 'n')); {
                cout << "Ingrese ID de compra que desea modificar: ";
                cin >> idc;
                system("cls");
                cout << "ID de compra seleccionada: " + idc << endl;
                cout << "Opciones: " << endl;
                cout << "1. Modificar No. Orden de compra" << endl;
                cout << "2. Modificar ID de proveedor" << endl;
                cout << "3. Modificar Fecha de orden" << endl;
                cout << "4. Modificar Fecha de ingreso" << endl;
                cout << "5. Modificar Id de producto" << endl;
                cout << "6. Modificar Cantidad" << endl;
                cout << "7. Modificar Precio costo unitario" << endl;
                cout << "Ingrese opcion: ";
                cin >> set;

                string c = to_string(idc);
                string insert, puesto;
                int op = 0;
                const char* i;

                switch (set) {
                case 1:
                    cout << "Ingrese el nuevo Numero de orden de compra: ";
                    cin.ignore();
                    getline(cin, compra_new);
                    insert = "UPDATE compras SET no_orden_compra = '" + compra_new + "' WHERE idcompras = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 2:
                    cout << "Ingrese el nuevo ID del proveedor: ";
                    cin.ignore();
                    getline(cin, compra_new);
                    insert = "UPDATE compras SET idProveedor = '" + compra_new + "' WHERE idcompras = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 3:
                    cout << "Ingrese nueva fecha de orden (YYYY-MM-DD): ";
                    cin.ignore();
                    getline(cin, compra_new);
                    insert = "UPDATE compras SET fecha_orden = '" + compra_new + "' WHERE idcompras = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 4:
                    cout << "Ingrese el nueva fecha de ingreso (YYYY-MM-DD): ";
                    cin.ignore();
                    getline(cin, compra_new);
                    insert = "UPDATE compras SET fechaIngreso = '" + compra_new + "' WHERE idcompras = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 5:
                    cout << "Modificar Productos" << endl;
                    cout << "Desea buscar producto? (S/N): ";
                    cin >> pregunta2;
                    if ((pregunta2 == 'S') || (pregunta2 == 's')) {
                        Productos c = Productos();
                        c.leer();

                    }
                    else ((pregunta2 == 'N') || (pregunta2 == 'n')); {
                        cout << "Ingrese nuevo ID de producto: ";
                        cin.ignore();
                        getline(cin, compra_new);
                        insert = "UPDATE compras_detalle SET idproducto = '" + compra_new + "' WHERE idcompra = " + c + ";";
                        i = insert.c_str();
                        q_estado = mysql_query(cn.getConectar(), i);
                    }                    
                    break;

                case 6:
                    cout << "Ingrese nuevo cantidad de producto: ";
                    cin.ignore();
                    getline(cin, compra_new);
                    insert = "UPDATE compras_detalle SET cantidad = '" + compra_new + "' WHERE idcompra = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;
                    
                case 7:
                    cout << "Ingrese nuevo precio de costo unitario: ";
                    cin.ignore();
                    getline(cin, compra_new);
                    insert = "UPDATE compras_detalle SET precio_costo_unitario = '" + compra_new + "' WHERE idcompra = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                }//cerrar switch

                const char* m = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), m);
                if (!q_estado) {
                    cout << "Modificacion Exitosa..." << endl;
                }
                else {
                    cout << "error al ingresar...";
                }
            }//cierra else pregunta
        }//cierra if conectar
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }

    void eliminar() {

        string psto, consulta, consulta2, c_del, t;
        char pregunta;
        int q_estado, opc = 0, idv = 0, set = 0;
        ConexionDB cn = ConexionDB();
        cn.abrirconexion();
        if (cn.getConectar()) {
            cout << "Desea buscar Compras? (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                Compras c = Compras();
                c.leer();
            }
            else((pregunta == 'N') || (pregunta == 'n')); {
                cout << "Ingrese ID de compra que desea Eliminar: ";
                cin >> c_del;
                string insert = "DELETE FROM compras_detalle WHERE idcompra = ('" + c_del + "');";

                const char* d = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), d);
                if (!q_estado) {
                    cout << "El ID: " + c_del + " de venta detalle se ha eliminado correctamente" << endl;
                }
                else {
                    cout << "Error al Eliminar...";
                }

                string insert2 = "DELETE FROM compras WHERE idcompras = ('" + c_del + "');";

                const char* d2 = insert2.c_str();
                q_estado = mysql_query(cn.getConectar(), d2);
                if (!q_estado) {
                    cout << "El ID: " + c_del + " de ventas se ha eliminado correctamente" << endl;
                }
                else {
                    cout << "Error al Eliminar...";
                }
            }//cierra else pregunta

        }//cierra if conectar
    }
};