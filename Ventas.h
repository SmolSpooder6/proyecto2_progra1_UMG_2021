#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
#include <sstream>
#include <windows.h>
#include <fstream>
#include <stdio.h>  
#include <string.h> 

#include "ConexionDB.h"
#include "cliente.h"
#include "Empleados.h"
#include "Productos.h"
#include "iomanip"


using namespace std;

class Ventas{
    //atributos
public: string fechaFactura, fechaingreso, nit;
        int noFactura = 1, idcliente = 0, idempleado = 0, idVenta = 0, idProducto = 0, cantidad = 0;
        float precio_unitario = 0, total = 0;

        string nombres, apellidos, genero, correo_electronico;
        int telefono = 0;



    //metodos
    void crear() {
        int q_estado, ex = 0, noF = 1, opc;
        int min, max, existencia;
        string producto, marca, mi, ma, descripcion, tot;
        string insert, insert2, consultaNit, consultaCantidad, consultaFactura, consultaNFac, existe, consultaProducto;
        string noFs, nfacs, idcs, ides, idvs, idps, cants, pus, exis;
        char pregunta, preguntaNit, continuar, gen;
        const char* l;
        const char* i;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {

            //ventas
 //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            //ingreso de datos

            cout << "Desea agregar NIT? (S/N): ";
            cin >> preguntaNit;
            if ((preguntaNit == 'S') || (preguntaNit == 's')) {
                /*pregunta*/cout << "Ingrese NIT: ";
                cin.ignore();
                getline(cin, nit);

                //busca si existe el nit
                existe = "SELECT EXISTS(SELECT * FROM clientes WHERE nit = '" + nit + "');";
                l = existe.c_str();
                q_estado = mysql_query(cn.getConectar(), l);
                if (!q_estado) {
                    resultado = mysql_store_result(cn.getConectar());

                    while (fila = mysql_fetch_row(resultado)) {
                        stringstream aux;
                        aux << fila[0];
                        aux >> ex;

                    }
                }
                else {
                    cout << "error al consultar nit..." << endl;
                }

                switch (ex) {
                    //-----------------------------------------------------------------------------------------------------------
                case 1:
                    //si existe el nit
                    //muestra los datos y saca idcliente
                    consultaNit = "SELECT idClientes, nombres, apellidos, nit, CASE genero WHEN 1 THEN 'M' WHEN 0 THEN 'F' END, telefono, correo_electronico, fechaIngreso FROM clientes WHERE nit = '" + nit + "';";


                    l = consultaNit.c_str();
                    q_estado = mysql_query(cn.getConectar(), l);
                    if (!q_estado) {
                        resultado = mysql_store_result(cn.getConectar());
                        cout << "-------------Cliente-------------" << endl;
                        while (fila = mysql_fetch_row(resultado)) {
                            cout << "ID: " << fila[0] << "\nNombres: " << fila[1] << "\nApellidos: " << fila[2] << "\nNit: " << fila[3] << "\nGenero: " << fila[4] << "\nTelefono: " << fila[5] << "\nCorreo Electronico: " << fila[6] << "\nFecha de Ingreso: " << fila[7] << endl;
                            cout << "--------------------------------------\n" << endl;
                            stringstream aux3;
                            aux3 << fila[0];
                            aux3 >> idcliente;

                        }
                    }
                    else {
                        cout << "error al consultar nit..." << endl;
                    }
                    break;

                case 0:



                    cout << "Ingrese Nombres: ";
                    
                    getline(cin, nombres);
                    cout << "Ingrese Apellidos: ";
                    getline(cin, apellidos);
                    cout << "Ingrese Genero (F/M): ";
                    cin >> gen;

                    switch (gen) {
                    case 'M':
                        genero = '1';
                        break;
                    case 'm':
                        genero = '1';
                        break;

                    case 'F':
                        genero = '0';
                        break;
                    case 'f':
                        genero = '0';
                        break;
                    }
                    cout << "ingrese Telefono: ";
                    cin >> telefono;
                    cin.ignore();
                    cout << "Ingrese Correo Electonico del cliente: ";
                    getline(cin, correo_electronico);
                    cliente c = cliente(nombres, apellidos, nit, genero, telefono, correo_electronico, fechaingreso);
                    c.crear();
                    system("pause");

                    // busca nit del cliente saca su ID
                    consultaNit = "SELECT* FROM clientes WHERE nit = '" + nit + "';";
                    l = consultaNit.c_str();
                    q_estado = mysql_query(cn.getConectar(), l);
                    if (!q_estado) {
                        resultado = mysql_store_result(cn.getConectar());
                        cout << "-------------Cliente-------------" << endl;
                        while (fila = mysql_fetch_row(resultado)) {
                            cout << "ID: " << fila[0] << "\nNombres: " << fila[1] << "\nApellidos: " << fila[2] << "\nNit: " << fila[3] << "\nGenero: " << fila[4] << "\nTelefono: " << fila[5] << "\nCorreo Electronico: " << fila[6] << "\nFecha de Ingreso: " << fila[7] << endl;
                            cout << "--------------------------------------\n" << endl;
                            stringstream aux3;
                            aux3 << fila[0];
                            aux3 >> idcliente;

                        }
                    }
                    else {
                        cout << "error al consultar nit..." << endl;
                    }
                    break;

                }// termina switch de existe
            }//terima if de preguntaNit
            else if((preguntaNit == 'N') || (preguntaNit == 'n')) {
                cout << "no nit C/F" << endl;
                idcliente = 0;
            }

/*pregunta*/            cout << "ingrese su ID de empleado: ";
                        cin >> idempleado;



                        // busca NO. de factura para seguir la secuencia
                        consultaFactura = "SELECT* FROM ventas ORDER BY noFactura DESC LIMIT 1;";

                        l = consultaFactura.c_str();
                        q_estado = mysql_query(cn.getConectar(), l);
                        if (!q_estado) {
                            resultado = mysql_store_result(cn.getConectar());
                            while (fila = mysql_fetch_row(resultado)) {
                                stringstream aux2;
                                aux2 << fila[1];
                                aux2 >> noF;
                                noF++;
                            }
                        }
                        else {
                            cout << "Error al consultar No. de Factura...";
                        }


                        //ingresa datos de ventas
                        noFs = to_string(noF);

                        nfacs = to_string(noFactura);
                        idcs = to_string(idcliente);
                        ides = to_string(idempleado);


                        //ingresa datos de venta
                        insert = "INSERT INTO ventas (noFactura, serie, fechaFactura, idcliente, idempleado, fechaIngreso) VALUES (" + noFs + ", 'e', CURRENT_TIMESTAMP, " + idcs + ", " + ides + ", CURRENT_TIMESTAMP);";
                        //cout << insert << endl;
                        i = insert.c_str();
                        q_estado = mysql_query(cn.getConectar(), i);
                        if (!q_estado) {
                            //cout << "Ingreso Exitoso..." << endl;
                        }
                        else {
                            cout << "error al ingresar ventas..." << endl;
                            cout << "Es posible que el puesto ingresado no exista." << endl;
                        }





                        // agregar otro producto
                        
                        do{

    /*pregunta*/            cout << " Producto\nDesea buscar producto (S/N): ";
                            cin >> pregunta;
                            // busqueda de producto
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
                                    consultaProducto = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.producto LIKE '%" + producto + "%' UNION SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE m.marca LIKE '%" + marca + "%';";
                                    break;

                                case 2:
                                    system("cls");
                                    cout << "ingrese descripcion del producto: ";
                                    cin.ignore();
                                    getline(cin, producto);
                                    consultaProducto = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.descripcion LIKE '%" + descripcion + "%';";
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
                                    consultaProducto = "SELECT p.idProducto, p.producto, m.marca, p.descripcion, p.Imagen, p.precio_costo, p.precio_venta,p.existencia, p.fecha_ingreso FROM productos AS p INNER JOIN marcas AS m ON p.idMarca = m.idMarca WHERE p.precio_venta > " + mi + " AND precio_venta < " + ma + ";";
                                    break;

                                }//cierra switch de busqueda

                                const char* cp = consultaProducto.c_str();
                                q_estado = mysql_query(cn.getConectar(), cp);
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
                                //system("cls");
                                cout << "Ingrese ID del producto: ";
                                cin >> idProducto;
                            }//cierra else pregunta de buscar
                //fin de busqueda de producto

                //ingreso de cantidad
                            cout << "Ingrese cantidad: ";
                            cin >> cantidad;
                            cants = to_string(cantidad);
                            idps = to_string(idProducto);
                            system("cls");
                            consultaCantidad = "SELECT* FROM productos WHERE idProducto = " + idps + ";";
                            l = consultaCantidad.c_str();
                            q_estado = mysql_query(cn.getConectar(), l);
                            if (!q_estado) {
                                resultado = mysql_store_result(cn.getConectar());
                                cout << "-------------Productos-------------" << endl;
                                while (fila = mysql_fetch_row(resultado)) {
                                    cout << "ID del Producto: " << fila[0] << "\nProducto: " << fila[1] << "\nMarca: " << fila[2] << "\nDescripcion: " << fila[3] << "\nImagen: " << fila[4] << "\nPrecio de Costo: " << fila[5] << "\nPrecio de Venta: " << fila[6] << "\nExistencia: " << fila[7] << "\nFecha de Ingreso: " << fila[8] << endl;
                                    cout << "--------------------------------------\n" << endl;
                                    stringstream aux5;
                                    aux5 << fila[7];
                                    aux5 >> existencia;

                                    stringstream aux6;
                                    aux6 << fila[6];
                                    aux6 >> precio_unitario;

                                    exis = to_string(existencia);
                                    if (cantidad <= existencia) {
                                        cout << "hay en bodega\n" << endl;

                                        //realiza la operacion de (existencia - cantidad)
                                        insert = "UPDATE productos SET existencia = " + exis + "-" + cants + " WHERE idProducto = " + idps + ";";
                                        i = insert.c_str();
                                        q_estado = mysql_query(cn.getConectar(), i);
                                        if (!q_estado) {
                                            cout << "se han descontado: " + cants + " de la candidad del producto" << endl;
                                        }
                                        else {
                                            cout << "error al restar producto...";
                                        }




                                        //ventas_detalle
                     //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

                                        // consulta el numero de factura para ventas detalle y sacar el id de ventas
                                        consultaNFac = "SELECT* FROM ventas WHERE noFactura = " + noFs + ";";
                                        l = consultaNFac.c_str();
                                        q_estado = mysql_query(cn.getConectar(), l);
                                        if (!q_estado) {
                                            resultado = mysql_store_result(cn.getConectar());
                                            while (fila = mysql_fetch_row(resultado)) {
                                                stringstream aux4;
                                                aux4 << fila[0];
                                                aux4 >> idVenta;
                                            }
                                        }
                                        else {
                                            cout << "Error al consultar id de cliente...";
                                        }

                                        // ingresa el precio unitario de venta
                //==================================================================

                                            //ingresa datos de ventas_detalle
                                        idvs = to_string(idVenta);

                                        pus = to_string(precio_unitario);


                                        insert2 = "INSERT INTO ventas_detalle (idVenta, idProducto, cantidad, precio_unitario) VALUES ('" + idvs + "', '" + idps + "', " + cants + ", '" + pus + "');";
                                        //cout << insert2 << endl;
                                        i = insert2.c_str();
                                        q_estado = mysql_query(cn.getConectar(), i);
                                        if (!q_estado) {
                                            cout << "Ingreso Exitoso..." << endl;
                                        }
                                        else {
                                            cout << "error al ingresar ventas_detalle..." << endl;
                                            //cout << "Es posible que el puesto ingresado no exista." << endl;
                                        }

                                        //suma la cantidad de productos
                                        int cantidadProducto = 0;
                                        string cc;

                                        consultaFactura = "SELECT SUM(cantidad) FROM ventas_detalle WHERE idVenta = "  + idvs + ";";
                                        l = consultaFactura.c_str();
                                        q_estado = mysql_query(cn.getConectar(), l);
                                        if (!q_estado) {
                                            resultado = mysql_store_result(cn.getConectar());
                                            while (fila = mysql_fetch_row(resultado)) {
                                                stringstream aux7;
                                                aux7 << fila[0];
                                                aux7 >> cantidadProducto;
                                                
                                                
                                            }
                                        }
                                        else {
                                            cout << "Error al consultar No. de Factura...";
                                        }
                                        //suma el precio total
                                        consultaFactura = "SELECT SUM(precio_unitario*cantidad) FROM ventas_detalle WHERE idVenta = " + idvs + ";";
                                        l = consultaFactura.c_str();
                                        q_estado = mysql_query(cn.getConectar(), l);
                                        if (!q_estado) {
                                            resultado = mysql_store_result(cn.getConectar());
                                            while (fila = mysql_fetch_row(resultado)) {
                                                stringstream aux7;
                                                aux7 << fila[0];
                                                aux7 >> total;
                                            }
                                        }
                                        else {
                                            cout << "Error al consultar No. de Factura...";
                                        }
                       


                                        consultaFactura = "SELECT v.noFactura, v.serie, v.fechaFactura, c.nit, c.nombres, c.apellidos, e.nombres, e.apellidos FROM ventas AS v INNER JOIN empleados AS e ON e.idempleados = v.idempleado INNER JOIN clientes AS c ON c.idClientes = v.idcliente WHERE v.idVentas = " + idvs + ";";
                                        l = consultaFactura.c_str();
                                        q_estado = mysql_query(cn.getConectar(), l);
                                        if (!q_estado) {
                                            resultado = mysql_store_result(cn.getConectar());
                                            while (fila = mysql_fetch_row(resultado)) {
                                                cout << "\n\n------------------Factura------------------" << endl;
                                                cout << "Factura No.: " << fila[0] << "\nSerie: " << fila[1] << "\nFecha: " << fila[2] << "\nNit: " << fila[3] << "\n\nCliente\nNombres: " << fila[4] << "\nApellidos: " << fila[5] << "\n\nEmpleado\nNombres: " << fila[6] << "\nApellidos: " << fila[7] << endl;

                                            }
                                        }
                                        else {
                                            cout << "Error al consultar datos de factura";
                                        }

                                        cout << "\nProductos" << endl;

                                        consultaFactura = "SELECT p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM productos AS p INNER JOIN ventas_detalle AS d ON d.idProducto = p.idProducto WHERE d.idVenta = " + idvs + ";";
                                        l = consultaFactura.c_str();
                                        q_estado = mysql_query(cn.getConectar(), l);
                                        if (!q_estado) {
                                            resultado = mysql_store_result(cn.getConectar());
                                            while (fila = mysql_fetch_row(resultado)) {

                                                cout << "\nProducto: " << fila[0] << "\nDescripcion: " << fila[1] << "\t\tCantidad: " << fila[2] << "\tPrecio: Q" << fila[3] << endl;

                                            }
                                        }
                                        else {
                                            cout << "Error al consultar datos de factura";
                                        }
                                        cout << "----------------------------------------------------" << endl;

                                        cc = to_string(cantidadProducto);
                                        tot = to_string(total);
                                        cout << "\n----Total de productos: " + cc + " ----" << endl;
                                        cout << "----Total a pagar: Q" <<fixed<<setprecision(2)<< total << "----\n" << endl;
                                        cout << "----------------------------------------------------" << endl;
                                
                                        
                                        //-----------------------------------------------------------------------------------------------------------

                                    }//cierra if existencia
                                    else if (cantidad > existencia) {
                                        cout << " ----No hay en bodega----" << endl;
                                    }

                                }//cierra while de existencia del producto
                            }//cierra q estado
                            else {
                                cout << "error al consultar...";
                            }
                            cout << "Desea Agregar otro producto? (S/N): ";
                            cin >> continuar;

                        }// cierra el do                        
                        while ((continuar == 's') || (continuar == 'S'));

                        //-----------------------------------------------------------------------------------------------------------
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                        int cantidadProducto = 0;
                        string cc;

                        consultaFactura = "SELECT SUM(cantidad) FROM ventas_detalle WHERE idVenta = " + idvs + ";";
                        l = consultaFactura.c_str();
                        q_estado = mysql_query(cn.getConectar(), l);
                        if (!q_estado) {
                            resultado = mysql_store_result(cn.getConectar());
                            while (fila = mysql_fetch_row(resultado)) {
                                stringstream aux7;
                                aux7 << fila[0];
                                aux7 >> cantidadProducto;


                            }
                        }
                        else {
                            cout << "Error al consultar No. de Factura...";
                        }
                        //suma el precio total
                        consultaFactura = "SELECT SUM(precio_unitario*cantidad) FROM ventas_detalle WHERE idVenta = " + idvs + ";";
                        l = consultaFactura.c_str();
                        q_estado = mysql_query(cn.getConectar(), l);
                        if (!q_estado) {
                            resultado = mysql_store_result(cn.getConectar());
                            while (fila = mysql_fetch_row(resultado)) {
                                stringstream aux7;
                                aux7 << fila[0];
                                aux7 >> total;
                            }
                        }
                        else {
                            cout << "Error al consultar No. de Factura...";
                        }

                        ofstream archivo;

                        archivo.open("texto.txt", ios::out);

                        if (archivo.fail()) {
                            cout << "error al crear archivo para imprimir" << endl;

                        }
                        else {
                            consultaFactura = "SELECT v.noFactura, v.serie, v.fechaFactura, c.nit, c.nombres, c.apellidos, e.nombres, e.apellidos FROM ventas AS v INNER JOIN empleados AS e ON e.idempleados = v.idempleado INNER JOIN clientes AS c ON c.idClientes = v.idcliente WHERE v.idVentas = " + idvs + ";";
                            l = consultaFactura.c_str();
                            q_estado = mysql_query(cn.getConectar(), l);
                            if (!q_estado) {
                                resultado = mysql_store_result(cn.getConectar());
                                while (fila = mysql_fetch_row(resultado)) {
                                    archivo << "------------------Factura------------------" << endl;
                                    archivo << "Factura No.: " << fila[0] << "    Serie: " << fila[1] << "   Fecha: " << fila[2] << "\nNit: " << fila[3] << "\n\nCliente\nNombres: " << fila[4] << "\nApellidos: " << fila[5] << "\n\nEmpleado\nNombres: " << fila[6] << "\nApellidos: " << fila[7] << endl;

                                }
                            }
                            else {
                                cout << "Error al consultar datos de factura";
                            }

                            archivo << "\nProductos" << endl;

                            consultaFactura = "SELECT p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM productos AS p INNER JOIN ventas_detalle AS d ON d.idProducto = p.idProducto WHERE d.idVenta = " + idvs + ";";
                            l = consultaFactura.c_str();
                            q_estado = mysql_query(cn.getConectar(), l);
                            if (!q_estado) {
                                resultado = mysql_store_result(cn.getConectar());
                                while (fila = mysql_fetch_row(resultado)) {

                                    archivo << "Producto: " << fila[0] << "   Descripcion: " << fila[1] << "\nCantidad: " << fila[2] << "   Precio: Q" << fila[3] << endl;

                                }
                            }
                            else {
                                cout << "Error al consultar datos de factura";
                            }
                            
                            archivo << "----------------------------------------------------" << endl;
                            archivo << "----Total de productos: " << cantidadProducto << " ----" << endl;
                            archivo << "----Total a pagar: Q" << fixed << setprecision(2) << total << "----" << endl;
                            archivo << "----------------------------------------------------" << endl;
                        }//cierra else de fail
                        archivo.close();

                        tifstream in(TEXT("texto.txt")); // acá va escrito el nombre del archivo que quieres imprimir 
                        PrintFile(in);
                        in.close();

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA



        }// termina el conectar
        else {
            cout << "--- Error en la conexion ---";
        }
        cn.cerrar_conexion();
    }// termina crear
//PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP


    typedef std::basic_ifstream<TCHAR> tifstream;
    typedef std::basic_string<TCHAR> tstring;

    void Outtextxy(HDC hdc, int x, int y, tstring Msg)
    {
        TextOut(hdc, x, y, Msg.c_str(), static_cast<int>(Msg.length()));
    }

    void ShowError(tstring strMsg)
    {
        MessageBox(NULL, strMsg.c_str(), TEXT("Imprimir"), MB_ICONERROR);
        exit(1);
    }
    void ShowInformation(tstring strText)
    {
        MessageBox(NULL, strText.c_str(), TEXT("Imprimir"), MB_ICONINFORMATION);
    }
    void PrintFile(tifstream& f)
    {
        PRINTDLG pd;
        DOCINFO di;
        tstring strLine;
        int y = 300;

        memset(&pd, 0, sizeof(PRINTDLG));
        memset(&di, 0, sizeof(DOCINFO));

        di.cbSize = sizeof(DOCINFO);
        di.lpszDocName = TEXT("Imprimiendo");

        pd.lStructSize = sizeof(PRINTDLG);
        pd.Flags = PD_PAGENUMS | PD_RETURNDC;
        pd.nFromPage = 1;
        pd.nToPage = 1;
        pd.nMinPage = 1;
        pd.nMaxPage = 0xFFFF;


        if (f.fail())
            ShowError(TEXT("Error el archivo no se pudo abrir para lectura"));

        if (PrintDlg(&pd)) {
            if (pd.hDC) {
                if (StartDoc(pd.hDC, &di) != SP_ERROR) {
                    cout << "Imprimiendo...\nEspere un momento" << endl;
                    StartPage(pd.hDC);
                    while (!f.eof()) {
                        getline(f, strLine);
                        Outtextxy(pd.hDC, 500, y, strLine.c_str());
                        y += 100;
                    }
                    EndPage(pd.hDC);
                    EndDoc(pd.hDC);

                }
                else
                    ShowError(TEXT("Error: No se pudo comenzar a imprimir."));

            }
            else
                ShowError(TEXT("Error: No se pudo crear el contexto de dispositivo"));

        }
        else
            ShowInformation(TEXT("Se cancelo la impresion"));

        ShowInformation(TEXT("Termino la impresion correctamente."));
    }


//PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP

    void leer() {

        string consulta, t, nf, idc, idp, idvds, can, mi, ma;
        int q_estado, opc, idvd, min, max;
        const char* l;
        char pregunta;
        ConexionDB cn = ConexionDB();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrirconexion();
        if (cn.getConectar()) {

            system("cls");
            cout << "Como desea buscar: " << endl;
            cout << "1. Buscar por Numero de factura." << endl;
            cout << "2. Buscar por Fecha de factura." << endl;
            cout << "3. Buscar por ID Cliente." << endl;
            cout << "4. Buscar por ID de empleado." << endl;
            cout << "5. Buscar por fecha de ingreso." << endl;
            cout << "6. Buscar por ID venta detalle." << endl;
            cout << "7. Buscar por ID ID de producto." << endl;
            cout << "8. Buscar por cantidad." << endl;
            cout << "9. Buscar por Precio unitario." << endl;
            cout << "10. Ver Todos" << endl;

            cout << "\nIngrese No. de opcion: ";
            cin >> opc;

            switch (opc) {
            case 1:
                system("cls");
                cout << "ingrese No. de factura: ";                
                cin >> noFactura;
                nf = to_string(noFactura);
                consulta = "SELECT v.idVentas, v.noFactura, v.serie, v.fechaFactura, v.idcliente, v.idempleado, v.fechaIngreso, d.idventa_detalle, d.idProducto, p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM ventas AS v INNER JOIN ventas_detalle AS d ON v.idVentas = d.idVenta INNER JOIN productos AS p ON d.idProducto = p.idProducto WHERE v.noFactura = '" + nf + "';";
                break;

            case 2:
                system("cls");
                cout << "ingrese fecha de factura (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, fechaFactura);
                consulta = "SELECT v.idVentas, v.noFactura, v.serie, v.fechaFactura, v.idcliente, v.idempleado, v.fechaIngreso, d.idventa_detalle, d.idProducto, p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM ventas AS v INNER JOIN ventas_detalle AS d ON v.idVentas = d.idVenta INNER JOIN productos AS p ON d.idProducto = p.idProducto WHERE v.fechaFactura LIKE '%" + fechaFactura + "%' LIMIT 20;";
                break;

            case 3:

                system("cls");
                cout << "Buscar ID de Cliente" << endl;
                cout << "desea buscar cliente? (S/N): ";
                cin >> pregunta;
                if ((pregunta == 'S') || (pregunta == 's')) {
                    cliente c = cliente();
                    c.leer();
                }
                else ((pregunta == 'N') || (pregunta == 'n')); {
                    cout << "Ingrese ID del cliente: ";
                    cin >> idcliente;
                    idc = to_string(idcliente);
                    consulta = "SELECT v.idVentas, v.noFactura, v.serie, v.fechaFactura, v.idcliente, v.idempleado, v.fechaIngreso, d.idventa_detalle, d.idProducto, p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM ventas AS v INNER JOIN ventas_detalle AS d ON v.idVentas = d.idVenta INNER JOIN productos AS p ON d.idProducto = p.idProducto WHERE v.idcliente = '" + idc + "';";
                }
                break;

            case 4:

                system("cls");
                cout << "Buscar ID de Empleado" << endl;
                cout << "desea buscar empleado? (S/N): ";
                cin >> pregunta;
                if ((pregunta == 'S') || (pregunta == 's')) {
                    Empleados c = Empleados();
                    c.leer();
                }
                else ((pregunta == 'N') || (pregunta == 'n')); {
                    cout << "Ingrese ID del empleado: ";
                    cin >> idempleado;
                    idp = to_string(idempleado);
                    consulta = "SELECT v.idVentas, v.noFactura, v.serie, v.fechaFactura, v.idcliente, v.idempleado, v.fechaIngreso, d.idventa_detalle, d.idProducto, p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM ventas AS v INNER JOIN ventas_detalle AS d ON v.idVentas = d.idVenta INNER JOIN productos AS p ON d.idProducto = p.idProducto WHERE v.idempleado = '" + idp + "';";
                }
                break;

            case 5:
                system("cls");
                cout << "ingrese fecha de Ingreso (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, fechaingreso);
                consulta = "SELECT v.idVentas, v.noFactura, v.serie, v.fechaFactura, v.idcliente, v.idempleado, v.fechaIngreso, d.idventa_detalle, d.idProducto, p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM ventas AS v INNER JOIN ventas_detalle AS d ON v.idVentas = d.idVenta INNER JOIN productos AS p ON d.idProducto = p.idProducto WHERE v.fechaIngreso LIKE '%" + fechaingreso + "%' LIMIT 20;";
                break;

            case 6:
                cout << "Ingrese ID de venta detalle: ";
                cin >> idvd;
                idvds = to_string(idvd);
                consulta = "SELECT v.idVentas, v.noFactura, v.serie, v.fechaFactura, v.idcliente, v.idempleado, v.fechaIngreso, d.idventa_detalle, d.idProducto, p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM ventas AS v INNER JOIN ventas_detalle AS d ON v.idVentas = d.idVenta INNER JOIN productos AS p ON d.idProducto = p.idProducto WHERE d.idventa_detalle = '" + idvds + "';";
                break;

            case 7:
                system("cls");
                cout << "Buscar ID de Producto" << endl;
                cout << "desea buscar Producto? (S/N): ";
                cin >> pregunta;
                if ((pregunta == 'S') || (pregunta == 's')) {
                    Productos p = Productos();
                    p.leer();
                }
                else ((pregunta == 'N') || (pregunta == 'n')); {
                    cout << "Ingrese ID del Producto: ";
                    cin >> idProducto;
                    idp = to_string(idProducto);
                    consulta = "SELECT v.idVentas, v.noFactura, v.serie, v.fechaFactura, v.idcliente, v.idempleado, v.fechaIngreso, d.idventa_detalle, d.idProducto, p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM ventas AS v INNER JOIN ventas_detalle AS d ON v.idVentas = d.idVenta INNER JOIN productos AS p ON d.idProducto = p.idProducto WHERE d.idProducto = '" + idp + "';";
                }
                break;
            
            case 8:
                cout << "Ingrese cantidad de la venta: ";
                cin >> cantidad;
                can = to_string(cantidad);
                consulta = "SELECT v.idVentas, v.noFactura, v.serie, v.fechaFactura, v.idcliente, v.idempleado, v.fechaIngreso, d.idventa_detalle, d.idProducto, p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM ventas AS v INNER JOIN ventas_detalle AS d ON v.idVentas = d.idVenta INNER JOIN productos AS p ON d.idProducto = p.idProducto WHERE d.idventa_detalle = '" + can + "';";
                break;

            case 9:
                cout << "ingrese el rango de precio de venta del producto" << endl;
                cout << "Ingrese rango minimo: ";
                cin >> min;
                cout << "ingrese rango maximo: ";
                cin >> max;
                mi = to_string(min);
                ma = to_string(max);
                consulta = "SELECT v.idVentas, v.noFactura, v.serie, v.fechaFactura, v.idcliente, v.idempleado, v.fechaIngreso, d.idventa_detalle, d.idProducto, p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM ventas AS v INNER JOIN ventas_detalle AS d ON v.idVentas = d.idVenta INNER JOIN productos AS p ON d.idProducto = p.idProducto WHERE d.precio_unitario > " + mi + " AND d.precio_unitario < " + ma + ";";
                break;
                
            case 10:
                system("cls");
                consulta = "SELECT v.idVentas, v.noFactura, v.serie, v.fechaFactura, v.idcliente, v.idempleado, v.fechaIngreso, d.idventa_detalle, d.idProducto, p.producto, p.descripcion, d.cantidad, d.precio_unitario FROM ventas AS v INNER JOIN ventas_detalle AS d ON v.idVentas = d.idVenta INNER JOIN productos AS p ON d.idProducto = p.idProducto;";
                break;

            }


        
            l = consulta.c_str();
            q_estado = mysql_query(cn.getConectar(), l);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConectar());
                system("cls");
                cout << "-------------Ventas-------------" << endl;
                while (fila = mysql_fetch_row(resultado)) {
                    cout << "ID: " << fila[0] << "\nNo. Factura: " << fila[1] << "\nSerie: " << fila[2] << "\nFecha de Factura: " << fila[3] << "\nID de cliente: " << fila[4] << "\nID empleado: " << fila[5] << "\nFecha de Ingreso: " << fila[6] << "\nID de venta detalle: " << fila[7] << "\nID producto: " << fila[8] << "\nProducto: " << fila[9] << "\nDescripcion de producto: " << fila[10] << "\nCantidad: " << fila[11] << "\nPrecio Unitario: " << fila[12] << endl;
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

    }


    void modificar() {

        string psto, consulta, consulta2, venta_new, t;
        char pregunta;
        int q_estado, opc = 0, idv = 0, set = 0;
        ConexionDB cn = ConexionDB();
        cn.abrirconexion();
        if (cn.getConectar()) {
            cout << "Desea buscar Ventas (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                Ventas v = Ventas();
                v.leer();

            }
            else((pregunta == 'N') || (pregunta == 'n')); {
                cout << "Ingrese ID de venta que desea modificar: ";
                cin >> idv;
                system("cls");
                cout << "ID de la venta seleccionada: " + idv << endl;
                cout << "Opciones: \n 1. Modificar No. Factura \n2. Modificar Serie \n3. Modificar Fecha de factura \n4. Modificar ID de cliente \n 5. Modificar Id de empleado \n 6. Modificar Fecha de ingreso \n 7. Modificar ID de producto \n8. Modificar cantidad \n9. Modificar Precio Unitario" << endl;
                cout << "Ingrese opcion que desea modificar: ";
                cin >> set;

                string c = to_string(idv);
                string insert, puesto;
                int op = 0;
                const char* i;

                switch (set) {
                case 1:
                    cout << "Ingrese el nuevo Numero de Factura: ";
                    cin.ignore();
                    getline(cin, venta_new);
                    insert = "UPDATE ventas SET noFactura = '" + venta_new + "' WHERE idVentas = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;
                
                case 2:
                    cout << "Ingrese La nueva Serie de la venta: ";
                    cin.ignore();
                    getline(cin, venta_new);
                    insert = "UPDATE ventas SET serie = '" + venta_new + "' WHERE idVentas = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 3:
                    cout << "Ingrese la nueva Fecha de Factura (YYYY-MM-DD): ";
                    cin.ignore();
                    getline(cin, venta_new);
                    insert = "UPDATE ventas SET fechaFactura = '" + venta_new + "' WHERE idVentas = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 4:
                    
                    cout << "Modificar ID de cliente ";
                    cout << "Desea Buscar Cliente (S/N)";
                    cin >> pregunta;
                    if ((pregunta == 'S') || (pregunta == 's')) {
                        system("cls");
                        cliente c = cliente();
                        c.leer();
                    }
                    else ((pregunta == 'N') || (pregunta == 'n')); {
                        cout << "Ingrese nuevo ID de Cliente";
                        cin.ignore();
                        getline(cin, venta_new);
                        insert = "UPDATE ventas SET idcliente = '" + venta_new + "' WHERE idVentas = " + c + ";";
                        i = insert.c_str();
                        q_estado = mysql_query(cn.getConectar(), i);
                    }
                    break;

                case 5:
                    system("cls");
                    cout << "Modificar ID de empleado ";
                    cout << "Desea Buscar empleado (S/N)";
                    cin >> pregunta;
                    if ((pregunta == 'S') || (pregunta == 's')) {
                        system("cls");
                        Empleados e = Empleados();
                        e.leer();
                    }
                    else ((pregunta == 'N') || (pregunta == 'n')); {
                        cout << "Ingrese nuevo ID de Empleado";
                        cin.ignore();
                        getline(cin, venta_new);
                        insert = "UPDATE ventas SET idempleado = '" + venta_new + "' WHERE idVentas = " + c + ";";
                        i = insert.c_str();
                        q_estado = mysql_query(cn.getConectar(), i);
                    }
                    break;

                case 6:
                    cout << "Ingrese la nueva Fecha de Ingreso (YYYY-MM-DD HH-MM-SS): ";
                    cin.ignore();
                    getline(cin, venta_new);
                    insert = "UPDATE ventas SET fechaIngreso = '" + venta_new + "' WHERE idVentas = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;

                case 7:
                    cout << "Modificar ID de Producto ";
                    cout << "Desea Buscar producto (S/N)";
                    cin >> pregunta;
                    if ((pregunta == 'S') || (pregunta == 's')) {
                        system("cls");
                        Productos p = Productos();
                        p.leer();
                    }
                    else ((pregunta == 'N') || (pregunta == 'n')); {
                        cout << "Ingrese nuevo ID de Producto";
                        cin.ignore();
                        getline(cin, venta_new);
                        insert = "UPDATE ventas_detalle SET idempleado = '" + venta_new + "' WHERE idVenta = " + c + ";";
                        i = insert.c_str();
                        q_estado = mysql_query(cn.getConectar(), i);
                    }
                    break;

                case 8:
                    cout << "Modificar cantidad de la venta: ";
                    cin.ignore();
                    getline(cin, venta_new);
                    insert = "UPDATE ventas_detalle SET cantidad = '" + venta_new + "' WHERE idVenta = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;
                
                case 9:
                    cout << "Modificar Precio Unitario: ";
                    cin.ignore();
                    getline(cin, venta_new);
                    insert = "UPDATE ventas_detalle SET precio_unitario = '" + venta_new + "' WHERE idVenta = " + c + ";";
                    i = insert.c_str();
                    q_estado = mysql_query(cn.getConectar(), i);
                    break;


                
                }//cierra el switch
                const char* m = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), m);
                if (!q_estado) {
                    cout << "Ingreso Exitoso..." << endl;
                }
                else {
                    cout << "error al ingresar...";
                }




            }//termina else pregunta 
        }//termina el conectar
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
            cout << "Desea buscar Ventas (S/N): ";
            cin >> pregunta;

            if ((pregunta == 'S') || (pregunta == 's')) {
                Ventas v = Ventas();
                v.leer();
            }
            else((pregunta == 'N') || (pregunta == 'n')); {
                cout << "Ingrese ID de venta que desea Eliminar: ";
                cin >> c_del;
                string insert = "DELETE FROM ventas_detalle WHERE idVenta = ('" + c_del + "');";

                const char* d = insert.c_str();
                q_estado = mysql_query(cn.getConectar(), d);
                if (!q_estado) {
                    cout << "El ID: " + c_del + " de venta detalle se ha eliminado correctamente" << endl;
                }
                else {
                    cout << "Error al Eliminar...";
                }

                string insert2 = "DELETE FROM ventas WHERE idVentas = ('" + c_del + "');";

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