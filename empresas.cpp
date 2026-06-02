#include "empresas.h"
#include <iostream>
using namespace std;

void inicializarVector(Empresas v[], int maxCantidad, int diasPromo)
{
    for (int i = 0; i < maxCantidad; i++)
    {
        v[i].codigo       = -1;
        v[i].importeTotal = 0;

        for (int c = 0; c < diasPromo; c++)
            v[i].dia[c] = 0;
    }
}

int ingresarEmpresas(Empresas v[], int maxCantidad)
{
    int codigo, cantEmpresas = 0;

    cout << "\n------INGRESO DE EMPRESAS ADHERIDAS------" << endl;

    do {
        do {
            cout << "\nCodigo de empresa Nro " << cantEmpresas + 1 << " (0 para salir): ";
            cin >> codigo;

            if (codigo < 0)
                cout << "{Error} El codigo debe ser un numero positivo" << endl;
        } while (codigo < 0);

        cin.ignore();

        if (buscarEmpresa(v, cantEmpresas, codigo) != -1) {
            cout << "Codigo ya existente" << endl;
            continue;
        }

        if (codigo != 0) {
            v[cantEmpresas].codigo = codigo;

            cout << "Nombre de la empresa: ";
            cin.getline(v[cantEmpresas].nombre, 30);

            cantEmpresas++;
        }

    } while (codigo != 0 && cantEmpresas < maxCantidad);

    return cantEmpresas;
}

// Bubble sort optimizado con flag de cambio
void ordenarEmpresas(Empresas v[], int cantEmpresas)
{
    Empresas aux;
    bool cambio;
    int i = 1;

    do {
        cambio = false;

        for (int j = 0; j < (cantEmpresas - i); j++)
        {
            if (v[j].codigo > v[j + 1].codigo)
            {
                aux      = v[j];
                v[j]     = v[j + 1];
                v[j + 1] = aux;
                cambio   = true;
            }
        }

        i++;
    } while (i < cantEmpresas && cambio);
}

// Búsqueda binaria — requiere que el vector esté ordenado
int buscarEmpresa(Empresas v[], int cantEmpresas, int codigoBuscado)
{
    int posicion = -1, desde = 0, hasta = cantEmpresas - 1, medio;

    while (desde <= hasta && posicion == -1)
    {
        medio = (desde + hasta) / 2;

        if (v[medio].codigo == codigoBuscado)
            posicion = medio;
        else if (codigoBuscado < v[medio].codigo)
            hasta = medio - 1;
        else
            desde = medio + 1;
    }

    return posicion;
}

void imprimirDatos(Empresas v[], int cantEmpresas)
{
    cout << "\n-------EMPRESAS ADHERIDAS-------" << endl;

    for (int i = 0; i < cantEmpresas; i++)
    {
        if (v[i].codigo == -1) continue;

        cout << "\nNombre: " << v[i].nombre << endl;
        cout << "Codigo: " << v[i].codigo << endl;
        cout << "Cantidad de ventas:" << endl;

        for (int j = 0; j < DIAS_PROMOCION; j++)
        {
            if (v[i].dia[j] > 0)
                cout << "  - " << v[i].dia[j] << " Venta/s en el dia " << j + 1 << endl;
            else
                cout << "  - Sin ventas durante el dia " << j + 1 << endl;
        }

        if (v[i].importeTotal != 0)
            cout << "Importe Total: $" << v[i].importeTotal << endl;

        cout << "\n--------------------------------" << endl;
    }
}

float buscarMenorImporte(Empresas v[], int cantEmpresas)
{
    float menor = -1;

    for (int i = 0; i < cantEmpresas; i++)
    {
        if ((v[i].importeTotal < menor || menor == -1) && v[i].importeTotal != 0)
            menor = v[i].importeTotal;
    }

    return menor;
}

void imprimirMenor(Empresas v[], int cantEmpresas)
{
    float menorImporte = buscarMenorImporte(v, cantEmpresas);

    if (menorImporte == -1) {
        cout << "\nLas empresas adheridas no registraron ningun importe" << endl;
        return;
    }

    cout << "\nEl menor importe total fue $" << menorImporte
         << " recaudado por la/s empresa/s:" << endl;

    for (int i = 0; i < cantEmpresas; i++)
    {
        if (v[i].importeTotal == menorImporte)
            cout << "  - Codigo: " << v[i].codigo << ", Nombre: " << v[i].nombre << endl;
    }
}
