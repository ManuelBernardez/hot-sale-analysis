#pragma once
#include "empresas.h"

struct Venta {
    int   codigoEmpresa;
    char  nombreEmpresa[30];
    int   dia;
    float importe;
};

int  ingresarVentas (Empresas v[], int cantEmpresas);
void procesarVenta (Empresas v[], int posicion, int dia, int ventasPorDia[]);
void procesarVentaNoAdh (int codigo, int dia, int ventasPorDia[]);
int  obtenerDiaMasVentas (int ventasPorDia[]);
void imprimirDiaMasVentas (int dia);
