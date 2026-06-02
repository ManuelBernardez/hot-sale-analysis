#pragma once

const int MAX_EMPRESAS   = 500;
const int DIAS_PROMOCION = 3;

struct Empresas {
    char  nombre[30];
    int   codigo;
    float importeTotal;
    int   dia[DIAS_PROMOCION]; // Cantidad de ventas por día ([0] = día 1, [1] = día 2, etc)
};

void inicializarVector (Empresas v[], int maxCantidad, int diasPromo);
int ingresarEmpresas (Empresas v[], int maxCantidad);
void ordenarEmpresas (Empresas v[], int cantEmpresas);
int buscarEmpresa (Empresas v[], int cantEmpresas, int codigoBuscado);

void imprimirDatos (Empresas v[], int cantEmpresas);
void imprimirMenor (Empresas v[], int cantEmpresas);
float buscarMenorImporte (Empresas v[], int cantEmpresas);
