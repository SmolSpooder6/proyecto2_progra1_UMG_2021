// Proyecto_2_SQL.cpp 


#include <iostream>
#include "cliente.h"
#include "Puestos.h"
#include "Empleados.h"
#include "Proveedores.h"
#include "Marcas.h"
#include "Productos.h"
#include "Ventas.h"
#include "Compras.h"

using namespace std;



void db_clientes();
void nuevo_cliente();
void ver_clientes();
void mod_cliente();
void eliminar_cliente();

void db_puestos();
void nuevo_puesto();
void ver_puesto();
void mod_puesto();
void eliminar_puesto();

void db_empleados();
void nuevo_empleado();
void ver_empleados();
void mod_empleado();
void eliminar_empleado();

void db_proveedores();
void nuevo_proveedor();
void ver_proveedores();
void mod_proveedor();
void eliminar_proveedor();

void db_marcas();
void nueva_marca();
void ver_marcas();
void mod_marcas();
void eliminar_marcas();

void db_productos();
void nuevo_producto();
void ver_Productos();
void mod_producto();
void eliminar_producto();

void db_ventas();
void nueva_venta();
void ver_ventas();
void mod_venta();
void eliminar_venta();

void db_compras();
void nueva_compra();
void ver_compras();
void mod_compra();
void eliminar_compra();


int main(){

    system("title PROYECTO 2");
    int opcion;

    system("cls");

    cout << "\n\nMenu de Opciones" << endl;

    cout << "1. Clientes" << endl;
    cout << "2. Puestos" << endl;
    cout << "3. Empleados" << endl;
    cout << "4. Ventas" << endl;
    cout << "5. Productos" << endl;
    cout << "6. Marcas" << endl;
    cout << "7. Proveedores" << endl;
    cout << "8. Compras" << endl;

    cout << "\nIngrese una opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1:

        system("cls");
        db_clientes();
        break;

    case 2:
        system("cls");
        db_puestos();
        break;
    
    case 3:

        system("cls");
        db_empleados();
        break;

    case 4:
        system("cls");
        db_ventas();
        break;

    case 5:
        system("cls");
        db_productos();
        break;

    case 6:
        system("cls");
        db_marcas();
        break;

    case 7:
        system("cls");
        db_proveedores();
        break;

    case 8:
        system("cls");
        db_compras();
        break;

    }

    
    system("pause");
    
    
}


void db_clientes() {

    int opcion_cliente;

    system("cls");

    cout << "\n\nMenu de Opciones" << endl;

    cout << "1. Nuevo Cliente" << endl;
    cout << "2. Ver Clientes" << endl;
    cout << "3. Modificar Cliente" << endl;
    cout << "4. Eliminar Cliente" << endl;
    cout << "5. Regresar" << endl;

    cout << "\nIngrese una opcion: ";
    cin >> opcion_cliente;

    switch (opcion_cliente) {
    case 1:

        system("cls");
        nuevo_cliente();
        break;

    case 2:

        system("cls");
        ver_clientes();
        break;

    case 3:

        system("cls");
        mod_cliente();
        break;

    case 4:

        system("cls");
        eliminar_cliente();
        break;

    case 5:
        main();
        break;
    }
    



}
void nuevo_cliente() {


    string nombres, apellidos, nit, genero, correo_electronico, fechaingreso;
    int telefono;
    char gen;

    
    cout << "Ingrese Nombres: ";
    getline(cin, nombres);
    getline(cin, nombres);
    cout << "Ingrese Apellidos: ";
    getline(cin, apellidos);
    cout << "Ingrese Nit: ";
    getline(cin, nit);
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
    db_clientes();

}
void ver_clientes() {
    cliente c = cliente();
    c.leer();
    system("pause");
    db_clientes();
}
void mod_cliente() {
    cliente c = cliente();
    c.modificar();
    system("pause");
    db_clientes();
}
void eliminar_cliente() {
    cliente c = cliente();
    c.eliminar();
    system("pause");
    db_clientes();
}



void db_puestos() {

    int opcion_puesto;

    system("cls");

    cout << "\n\nMenu de Opciones" << endl;

    cout << "1. Nuevo Puesto" << endl;
    cout << "2. Ver Puestos" << endl;
    cout << "3. Modificar Puesto" << endl;
    cout << "4. Eliminar Puesto" << endl;
    cout << "5. Regresar" << endl;

    cout << "\nIngrese una opcion: ";
    cin >> opcion_puesto;

    switch (opcion_puesto) {
    case 1:

        system("cls");
        nuevo_puesto();
        break;

    case 2:

        system("cls");
        ver_puesto();
        break;

    case 3:

        system("cls");
        mod_puesto();
        break;

    case 4:

        system("cls");
        eliminar_puesto();
        break;

    case 5:
        main();
        break;
    }

}

void nuevo_puesto() {

    string puesto;
    cout << "Ingrese Puesto: ";
    cin.ignore();
    getline(cin, puesto);
   
    Puestos p = Puestos(puesto);
    p.crear();
    system("pause");
    db_puestos();

}

void ver_puesto() {

    Puestos p = Puestos();
    p.leer();
    system("pause");
    db_puestos();
}

void mod_puesto() {
    Puestos p = Puestos();
    p.modificar();
    system("pause");
    db_puestos();

}

void eliminar_puesto() {
    Puestos p = Puestos();
    p.eliminar();
    system("pause");
    db_puestos();
}


void db_empleados() {

    int opcion_cliente;

    system("cls");

    cout << "\n\nMenu de Opciones" << endl;

    cout << "1. Nuevo Empleado" << endl;
    cout << "2. Ver Empleados" << endl;
    cout << "3. Modificar Empleado" << endl;
    cout << "4. Eliminar Empleado" << endl;
    cout << "5. Regresar" << endl;

    cout << "\nIngrese una opcion: ";
    cin >> opcion_cliente;

    switch (opcion_cliente) {
    case 1:

        system("cls");
        nuevo_empleado();
        break;

    case 2:

        system("cls");
        ver_empleados();
        break;

    case 3:

        system("cls");
        mod_empleado();
        break;

    case 4:
        system("cls");
        eliminar_empleado();
        break;

    case 5:
        main();
        break;

    }


}

void nuevo_empleado() {

    string nombres, apellidos, direccion, dpi, genero, fecha_nacimiento, fecha_inicio_labores, fechaingreso;
    char gen;
    int telefono;
    int idPuesto;
    cout << "Ingrese Nombres: ";
    getline(cin, nombres);
    getline(cin, nombres);
    cout << "Ingrese Apellidos: ";
    getline(cin, apellidos);
    cout << "Ingrese Direccion: ";
    getline(cin, direccion);
    cout << "ingrese Telefono: ";
    cin >> telefono;
    cin.ignore();
    cout << "Ingrese DPI: ";
    getline(cin, dpi);
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
    cout << "Ingrese Fecha de Nacimiento (YY-MM-DD): ";
    cin.ignore();
    getline(cin, fecha_nacimiento);
    cout << "ingrese ID de Puesto: ";
    cin >> idPuesto;
    cin.ignore();
    cout << "Ingrese fecha de inicio de labores (YY-MM-DD): ";
    getline(cin, fecha_inicio_labores);

    Empleados e = Empleados(nombres, apellidos, direccion, telefono, dpi, genero, fecha_nacimiento, idPuesto, fecha_inicio_labores, fechaingreso);
    e.crear();
    system("pause");
    db_empleados();


}

void ver_empleados() {

    Empleados e = Empleados();
    e.leer();
    system("pause");
    db_empleados();

}

void mod_empleado() {

    Empleados e = Empleados();
    e.modificar();
    system("pause");
    db_empleados();

}
void eliminar_empleado() {

    Empleados e = Empleados();
    e.eliminar();
    system("pause");
    db_empleados();

}


void db_proveedores() {

    int opcion_Proveedores;

    system("cls");

    cout << "\n\nMenu de Opciones" << endl;

    cout << "1. Nuevo Proveedor" << endl;
    cout << "2. Ver Proveedores" << endl;
    cout << "3. Modificar Proveedores" << endl;
    cout << "4. Eliminar Proveedor" << endl;
    cout << "5. Regresar" << endl;

    cout << "\nIngrese una opcion: ";
    cin >> opcion_Proveedores;

    switch (opcion_Proveedores) {
    case 1:

        system("cls");
        nuevo_proveedor();
        break;

    case 2:
        system("cls");
        ver_proveedores();
        break;

    case 3:
        system("cls");
        mod_proveedor();
        break;

    case 4:
        system("cls");
        eliminar_proveedor();
        break;

    case 5:
        main();
        break;
    }


}

void nuevo_proveedor() {

    string proveedor, nit, direccion;
    int telefono;
    cout << "Ingrese Proveedor: ";
    getline(cin, proveedor);
    getline(cin, proveedor);
    cout << "Ingrese NIT: ";
    getline(cin, nit);
    cout << "Ingrese Direccion: ";
    getline(cin, direccion);
    cout << "ingrese Telefono: ";
    cin >> telefono;
    cin.ignore();

    Proveedores p = Proveedores(proveedor, nit, direccion, telefono);
    p.crear();
    system("pause");
    db_proveedores();
}

void ver_proveedores() {

    Proveedores p = Proveedores();
    p.leer();
    system("pause");
    db_proveedores();

}

void mod_proveedor(){

    Proveedores p = Proveedores();
    p.modificar();
    system("pause");
    db_proveedores();

}

void eliminar_proveedor() {

    Proveedores p = Proveedores();
    p.eliminar();
    system("pause");
    db_proveedores();
}


void db_marcas() {
    int opcion_marca;

    system("cls");

    cout << "\n\nMenu de Opciones" << endl;

    cout << "1. Nueva Marca" << endl;
    cout << "2. Ver Marcas" << endl;
    cout << "3. Modificar Marca" << endl;
    cout << "4. Eliminar Marca" << endl;
    cout << "5. Regresar" << endl;

    cout << "\nIngrese una opcion: ";
    cin >> opcion_marca;

    switch (opcion_marca) {
    case 1:

        system("cls");
        nueva_marca();
        break;

    case 2:

        system("cls");
        ver_marcas();
        break;

    case 3:

        system("cls");
        mod_marcas();
        break;

    case 4:

        system("cls");
        eliminar_marcas();
        break;

    case 5:
        main();
        break;
    }
}

void nueva_marca() {
    string marca;
    cout << "Ingrese Marca: ";
    cin.ignore();
    getline(cin, marca);

    Marcas m = Marcas(marca);
    m.crear();
    system("pause");
    db_marcas();
}

void ver_marcas() {
    Marcas m = Marcas();
    m.leer();
    system("pause");
    db_marcas();
}

void mod_marcas() {
    Marcas m = Marcas();
    m.modificar();
    system("pause");
    db_marcas();
}

void eliminar_marcas() {
    Marcas m = Marcas();
    m.eliminar();
    system("pause");
    db_marcas();

}

void db_productos() {

    int opcion_Productos;

    system("cls");

    cout << "\n\nMenu de Opciones" << endl;

    cout << "1. Nuevo Producto" << endl;
    cout << "2. Ver Productos" << endl;
    cout << "3. Modificar Producto" << endl;
    cout << "4. Eliminar producto" << endl;
    cout << "5. Regresar" << endl;

    cout << "\nIngrese una opcion: ";
    cin >> opcion_Productos;

    switch (opcion_Productos) {
    case 1:

        system("cls");
        nuevo_producto();
        break;

    case 2:
        system("cls");
        ver_Productos();
        break;

    case 3:
        system("cls");
        mod_producto();
        break;

    case 4:
        system("cls");
        eliminar_producto();
        break;
        
    case 5:
        main();
        break;
    }
}

void nuevo_producto() {
    string producto, descripcion, Imagen, fecha_ingreso;
    int existencia, idMarca;
    float precio_costo, precio_venta;
    char preguntaMarca;

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
    db_productos();
}

void ver_Productos() {
    Productos p = Productos();
    p.leer();
    system("pause");
    db_productos();
}

void mod_producto() {
    Productos p = Productos();
    p.modificar();
    system("pause");
    db_productos();
}

void eliminar_producto() {
    Productos p = Productos();
    p.eliminar();
    system("pause");
    db_productos();
}

void db_ventas() {

    int opcion_ventas;

    system("cls");

    cout << "\n\nMenu de Opciones" << endl;

    cout << "1. Nueva Venta" << endl;
    cout << "2. Ver Ventas" << endl;
    cout << "3. Modificar Venta" << endl;
    cout << "4. Eliminar Venta" << endl;
    cout << "5. Regresar" << endl;

    cout << "\nIngrese una opcion: ";
    cin >> opcion_ventas;

    switch (opcion_ventas) {
    case 1:

        system("cls");
        nueva_venta();
        break;

    case 2:
        system("cls");
        ver_ventas();
        break;

    case 3:
        system("cls");
        mod_venta();
        break;

    case 4:
        system("cls");
        eliminar_venta();
        break;
        
    case 5:
        main();
        break;
    }
}

void nueva_venta() {
    Ventas v = Ventas();
    v.crear();
    system("pause");
    db_ventas();
}

void ver_ventas() {
    Ventas v = Ventas();
    v.leer();
    system("pause");
    db_ventas();
}

void mod_venta() {
    Ventas v = Ventas();
    v.modificar();
    system("pause");
    db_ventas();
}

void eliminar_venta() {
    Ventas v = Ventas();
    v.eliminar();
    system("pause");
    db_ventas();
}

void db_compras() {
    int opcion_compra;

    system("cls");

    cout << "\n\nMenu de Opciones" << endl;

    cout << "1. Nueva Compra" << endl;
    cout << "2. Ver Compras" << endl;
    cout << "3. Modificar Compra" << endl;
    cout << "4. Eliminar Compra" << endl;
    cout << "5. Regresar" << endl;

    cout << "\nIngrese una opcion: ";
    cin >> opcion_compra;

    switch (opcion_compra) {
    case 1:
        system("cls");
        nueva_compra();
        break;

    case 2:
        system("cls");
        ver_compras();
        break;

    case 3:
        system("cls");
        mod_compra();
        break;

    case 4:
        system("cls");
        eliminar_compra();
        break;
        
    case 5:
        main();
        break;
    }
}

void nueva_compra() {
    Compras p = Compras();
    p.crear();
    system("pause");
    db_compras();

}

void ver_compras() {
    Compras p = Compras();
    p.leer();
    system("pause");
    db_compras();
}

void mod_compra() {
    Compras p = Compras();
    p.modificar();
    system("pause");
    db_compras();
}

void eliminar_compra() {
    Compras p = Compras();
    p.eliminar();
    system("pause");
    db_compras();

}