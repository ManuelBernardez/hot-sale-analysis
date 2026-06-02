#include "ventas.h"
#include "archivos.h"
#include <iostream>
using namespace std;

int ingresarVentas(Empresas v[], int cantEmpresas)
{
    int codigoEmpresa;
    int ventasPorDia[DIAS_PROMOCION] = {0};

    cout << "\n-------------PANEL DE VENTAS-------------" << endl;

    for (int d = 1; d <= DIAS_PROMOCION; d++)
    {
        cout << "\n\n  |INGRESAR TODAS LAS VENTAS DEL DIA " << d << "|" << endl;

        do {
            cout << "\n> Codigo de empresa (0 para terminar): ";
            cin >> codigoEmpresa;

            if (codigoEmpresa != 0)
            {
                int posicion = buscarEmpresa(v, cantEmpresas, codigoEmpresa);

                if (posicion == -1)
                    procesarVentaNoAdh(codigoEmpresa, d, ventasPorDia);
                else
                    procesarVenta(v, posicion, d, ventasPorDia);
            }

        } while (codigoEmpresa != 0);
    }

    return obtenerDiaMasVentas(ventasPorDia);
}

void procesarVenta(Empresas v[], int posEmpresa, int diaVenta, int ventasPorDia[])
{
    float importe;

    cout << "    Ingrese el importe de la venta: ";
    cin >> importe;

    if (importe > 0)
    {
        v[posEmpresa].importeTotal  += importe;
        v[posEmpresa].dia[diaVenta - 1]++;
        ventasPorDia[diaVenta - 1]++;
    }
    else
        cout << "{Error} El importe debe ser mayor a 0" << endl;
}

void procesarVentaNoAdh(int codigo, int diaVenta, int ventasPorDia[])
{
    Venta v;
    v.codigoEmpresa = codigo;
    v.dia = diaVenta;
    v.importe = 0;

    cin.ignore();

    cout << "\nEmpresa no adherida a la promocion, ingrese su nombre: ";
    cin.getline(v.nombreEmpresa, 30);

    float importe;
    cout << "    Ingrese el importe de la venta: ";
    cin >> importe;

    if (importe > 0)
    {
        v.importe = importe;
        ventasPorDia[diaVenta - 1]++;
        archivoNoAdheridas(v);
    }
    else
        cout << "{Error} El importe debe ser mayor a 0. Venta no registrada." << endl;
}

// Devuelve el día (1-3) con más ventas, o -1 si todos tienen la misma cantidad
int obtenerDiaMasVentas(int ventasPorDia[])
{
    int diaMasVentas = 0;
    bool mismaCantidad = true;

    for (int i = 1; i < DIAS_PROMOCION; i++)
    {
        if (ventasPorDia[i] > ventasPorDia[diaMasVentas])
            diaMasVentas = i+1;
    }

    // Verificar si todos los días tienen la misma cantidad
    for (int i = 1; i < DIAS_PROMOCION; i++)
        if (ventasPorDia[i] != ventasPorDia[0])
            mismaCantidad = false;

    if (mismaCantidad)
        return -1;

    return diaMasVentas;
}

void imprimirDiaMasVentas(int dia)
{
    if (dia != -1)
        cout << "\nLa mayor cantidad de ventas fue durante el dia " << dia << endl;
    else
        cout << "\nLos tres dias tuvieron la misma cantidad de ventas" << endl;
}
