#include "empresas.h"
#include "ventas.h"
#include "archivos.h"
#include <stdio.h>

int main()
{
    // Inicializar vector de empresas adheridas
    Empresas adheridas[MAX_EMPRESAS];
    inicializarVector(adheridas, MAX_EMPRESAS, DIAS_PROMOCION);

    // Registrar empresas y ordenarlas por código
    int cantidad = ingresarEmpresas(adheridas, MAX_EMPRESAS);
    ordenarEmpresas(adheridas, cantidad);

    // Registrar ventas (borra registros previos de SinAdhesion al inicio)
    remove("SinAdhesion.dat");
    int diaMasVentas = ingresarVentas(adheridas, cantidad);

    // Mostrar informes en pantalla
    imprimirDatos(adheridas, cantidad);
    imprimirMenor(adheridas, cantidad);
    imprimirDiaMasVentas(diaMasVentas);

    // Generar archivo binario de empresas adheridas
    generarArchivoAdheridas(adheridas, cantidad);

    // Lectura opcional de archivos generados
    leerArchivos();

    return 0;
}
