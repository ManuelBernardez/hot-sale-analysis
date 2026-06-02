#include "archivos.h"
#include <iostream>
#include <fstream>
using namespace std;

void generarArchivoAdheridas(Empresas v[], int cantEmpresas)
{
    FILE* archivo = fopen("ImporteEmpresas.dat", "wb");

    if (archivo == NULL) {
        cerr << "Error: no se pudo abrir ImporteEmpresas.dat" << endl;
        return;
    }

    for (int i = 0; i < cantEmpresas; i++)
        fwrite(&v[i], sizeof(Empresas), 1, archivo);

    fclose(archivo);
}

void archivoNoAdheridas(Venta v)
{
    FILE* archivo = fopen("SinAdhesion.dat", "ab");

    if (archivo == NULL) {
        cerr << "Error: no se pudo abrir SinAdhesion.dat" << endl;
        return;
    }

    fwrite(&v, sizeof(Venta), 1, archivo);
    fclose(archivo);
}

void leerArchivoAdheridas()
{
    FILE* archivo = fopen("ImporteEmpresas.dat", "rb");

    if (archivo == NULL) {
        cerr << "Error: no se pudo abrir ImporteEmpresas.dat" << endl;
        return;
    }

    cout << "\n--- Empresas adheridas ---\n" << endl;

    Empresas e;
    while (fread(&e, sizeof(Empresas), 1, archivo))
    {
        cout << "  Nombre: " << e.nombre << endl;
        cout << "  Codigo: " << e.codigo << endl;
        cout << "  Importe: $" << e.importeTotal << endl;
        cout << "  Ventas por dia: "
             << e.dia[0] << " / " << e.dia[1] << " / " << e.dia[2] << endl;
    }

    fclose(archivo);
}

void leerArchivoNoAdheridas()
{
    FILE* archivo = fopen("SinAdhesion.dat", "rb");

    if (archivo == NULL) {
        cerr << "Error: no se pudo abrir SinAdhesion.dat" << endl;
        return;
    }

    cout << "\n--- Ventas sin adhesion ---\n" << endl;

    Venta v;
    while (fread(&v, sizeof(Venta), 1, archivo))
    {
        cout << "  Empresa: " << v.nombreEmpresa << endl;
        cout << "  Codigo: "   << v.codigoEmpresa << endl;
        cout << "  Dia de la venta: " << v.dia << endl;
        cout << "  Importe: $" << v.importe << endl;
    }

    fclose(archivo);
}

// Permite al usuario elegir qué archivo leer y repetir si lo desea
void leerArchivos()
{
    int opcion;

    cout << "\nQue archivo desea leer?" << endl;
    cout << "  1. ImporteEmpresas (empresas adheridas)" << endl;
    cout << "  2. SinAdhesion     (ventas no adheridas)" << endl;
    cout << "  0. Salir" << endl;
    cout << "> ";
    cin  >> opcion;

    switch (opcion)
    {
        case 1: leerArchivoAdheridas();    break;
        case 2: leerArchivoNoAdheridas();  break;
        case 0: return;
        
        default: cout << "Opcion invalida" << endl;
    }

    cout << "\nDesea leer otro archivo? 1: Si / 0: No: ";
    cin >> opcion;

    if (opcion == 1)
        leerArchivos();
}
