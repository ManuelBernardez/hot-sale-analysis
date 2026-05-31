#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define MaxCantEmpresas 500
#define DiasPromocion 3

struct Empresas { 
    char nombre[30]; 
    int codigo;
    float importeTotal; 
    int dia[DiasPromocion]; // Almacena ventas por dia, cada posición representa un dia de la promoción
}; 

void inicializarVector (Empresas a[], int maxCantidad, int diasPromo);
int ingresarEmpresas (Empresas v[], int maxCantidad);
void ordenarEmpresas (Empresas v[], int cantEmpresas);

int buscarEmpresa (Empresas v[], int cantEmpresas, int codigo);
int ingresarVentas (Empresas v[], int cantEmpresas);
void procesarVenta (Empresas v[], int posicion, int dia, int ventasPorDia[]);
void procesarVentaNoAdh (int codigoEmpresa, int diaVenta, int ventasPorDia[]);
void archivoNoAdheridas (Empresas e);

int obtenerDiaMasVentas (int ventasPorDia[]);
float buscarMenorImporte (Empresas v[], int cantEmpresas);
void generarArchivoAdheridas (Empresas v[], int cantEmpresas);

void imprimirDatos (Empresas v[], int cantEmpresas);
void imprimirDiaMasVentas (int dia);
void imprimirMenor (Empresas v[], int cantEmpresas);

void leerArchivoGenerado();

int main() {
    int deseaLeer = 0;

    // Definir e inicializar el vector de empresas
    Empresas adheridas[MaxCantEmpresas];
    inicializarVector(adheridas, MaxCantEmpresas, DiasPromocion);

        // Registrar código y nombre de empresas adheridas + ordenarlas por código
    int cantidad = ingresarEmpresas(adheridas, MaxCantEmpresas);
    ordenarEmpresas(adheridas,cantidad);

        // Registrar ventas y procesar datos
    remove("sinAdhesion.dat"); // Borro registros preexistentes, en caso de que haya
    int diaMasVentas = ingresarVentas(adheridas, cantidad);

    imprimirDatos(adheridas, cantidad);
    imprimirMenor(adheridas, cantidad);
    imprimirDiaMasVentas(diaMasVentas);

    generarArchivoAdheridas(adheridas, cantidad);

        // OPCIONAL - Mostrar datos de archivos en pantalla
    cout << "\nDesea leer un archivo? 1: Si / 0: No: ";
    cin >> deseaLeer;

    if(deseaLeer == 1)
        leerArchivoGenerado();

    return 0;
}

void inicializarVector (Empresas v[], int maxCantidad, int diasPromo) 
{
    for (int i = 0; i < maxCantidad; i++)
    {
        v[i].codigo = -1;
        v[i].importeTotal=0; // Acumulador

        for (int c=0; c < diasPromo; c++){
            v[i].dia[c]=0; // Contador por cada día de promoción
        }
    }
}

int ingresarEmpresas (Empresas v[], int maxCantidad) 
{
    int codigo, cantEmpresas = 0;

    cout << "\n------INGRESO DE EMPRESAS ADHERIDAS------" << endl;

   do { // Mientras el código sea != 0 y la cantidad de empresas < 500

        do { // Mientras el código sea negativo, se repite el ingreso
            cout << "\nCodigo de empresa Nro " << cantEmpresas+1 << " (0 para salir): ";
            cin >> codigo;

            if(codigo < 0) 
                cout << "{Error} El codigo debe ser un numero positivo" << endl;   
        } while (codigo < 0);
        
        cin.ignore(); //Ignorar el salto de línea restante en el buffer (por el getline)

        // Si ya existe una empresa con ese código, no se toman los datos
        if(buscarEmpresa(v, cantEmpresas, codigo) != -1){
            cout << "Codigo ya existente";
            continue;
        }
        
        if (codigo != 0) {
            v[cantEmpresas].codigo = codigo;

            cout << "Nombre de la empresa: ";
            cin.getline(v[cantEmpresas].nombre, 30);

            cantEmpresas++;
        }

    } while (codigo !=0 && cantEmpresas < maxCantidad);

    return cantEmpresas;
}

// Burbujeo
void ordenarEmpresas (Empresas v[], int cantEmpresas) 
{
    Empresas aux;
    bool cambio;
    int i=1;

    do {
        cambio=false;

        for(int j=0; j<(cantEmpresas-i); j++)
        {
            if(v[j].codigo > v[j+1].codigo)
            {
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;

                cambio = true;
            }
        }

        i++;
    }while(i<cantEmpresas && cambio);
}

// Búsqueda binaria
int buscarEmpresa (Empresas v[], int cantEmpresas, int codigoBuscado) 
{
    int posicion=-1, desde=0, hasta=cantEmpresas-1, medio;

    while(desde <= hasta && posicion == -1)
    {
        medio = (desde + hasta)/2;
        if(v[medio].codigo == codigoBuscado)
            posicion = medio;
        else
        {
            if(codigoBuscado < v[medio].codigo)
                hasta = medio-1;
            else
                desde = medio+1;
        }
    }
    
    return posicion;
}

// PUNTO 4
int obtenerDiaMasVentas (int ventasPorDia[]) 
{
    int diaMasVentas = 0; 
    bool mismaCantidad = true;

    for (int i = 0; i < DiasPromocion; i++) 
    {
        if (ventasPorDia[i] > ventasPorDia[diaMasVentas])
        {
            diaMasVentas = i+1; // Sumar 1 para que el día esté en el rango 1-3
            mismaCantidad = false;
        }
    }

    if (mismaCantidad)
        return -1;

    return diaMasVentas; 
}

int ingresarVentas (Empresas v[], int cantEmpresas) 
{
    int codigoEmpresa;
    int ventasPorDia[DiasPromocion] = {0}; 

    cout << "\n-------------PANEL DE VENTAS-------------" << endl;

    for (int d = 1; d <= DiasPromocion; d++) // Por cada día de promoción (1 a 3)
    {
        cout << "\n\n  |INGRESAR TODAS LAS VENTAS DEL DIA " << d << "|" << endl;

        do {
            cout << "\n> Codigo de empresa (0 para terminar): ";
            cin >> codigoEmpresa;

            if (codigoEmpresa != 0) // Si el usuario quiere terminar, se omite el procesamiento y sale del while
            {
                int posicion = buscarEmpresa(v,cantEmpresas,codigoEmpresa); // Busco la empresa
                
                if(posicion == -1) // No se encontró la empresa en el vector (no está adherida a la promoción)
                {
                    procesarVentaNoAdh(codigoEmpresa, d, ventasPorDia); 
                }
                else 
                {
                    procesarVenta(v, posicion, d, ventasPorDia);
                }
            }
            
        } while (codigoEmpresa != 0);
    }

    int diaMasVentas = obtenerDiaMasVentas(ventasPorDia); // (El vector de ventas por día fue cargado al procesar las ventas)

    return diaMasVentas;
}

// Ingresar importe, acumularlo y contar ventas (de la empresa adherida y por día)
void procesarVenta(Empresas v[], int posEmpresa, int diaVenta, int ventasPorDia[]) 
{
    float importe;

    cout << "    Ingrese el importe de la venta: ";
    cin >> importe;

    if(importe > 0)
    {
        v[posEmpresa].importeTotal += importe; // Importe de empresa adherida
        v[posEmpresa].dia[diaVenta-1]++; // Ventas de la empresa en el día
        ventasPorDia[diaVenta-1]++; // Ventas totales en el día
    }
}

void procesarVentaNoAdh(int codigo, int diaVenta, int ventasPorDia[]) 
{
    Empresas noAdherida; // Variable que permite ingresar nuevos datos sin modificar el vector de empresas adheridas
    noAdherida.codigo = codigo; 
    noAdherida.importeTotal = 0;

    cin.ignore();

    cout << "\nEmpresa no adherida a la promocion, ingrese su nombre: ";
    cin.getline(noAdherida.nombre, 30);
    
    float importe;

    cout << "    Ingrese el importe de la venta: ";
    cin >> importe;

    if(importe > 0)
    {
        noAdherida.importeTotal += importe;
        noAdherida.dia[0] = diaVenta; // Asignar el día de la venta a una posición (no importa la cantidad de ventas, sino el día)
        ventasPorDia[diaVenta-1]++;

        archivoNoAdheridas(noAdherida); 
    }
}

// Punto 3
float buscarMenorImporte(Empresas v[], int cantEmpresas) 
{
    float menor = -1;

    for (int i = 0; i < cantEmpresas; i++)
    {
            // (Si importe de la empresa < menor importe  Ó  es el primer ingreso)   Y   el importe no es 0
        if ((v[i].importeTotal < menor || menor == -1) && v[i].importeTotal != 0) 
        {
            menor = v[i].importeTotal;
        }
    }
    
    return menor;
}

void imprimirDiaMasVentas(int dia) 
{
    if (dia != -1)
    {
        cout << "\nLa mayor cantidad de ventas alcanzada fue durante el dia " << dia;
    }
    else
        cout << "\nLos tres dias tuvieron la misma cantidad de ventas" << endl;

    cout << endl;
}

void imprimirMenor(Empresas v[], int cantEmpresas) 
{
    float menorImporte = buscarMenorImporte(v, cantEmpresas);

    if(menorImporte == -1){
        cout << "\nLas empresas adheridas no registraron ningun importe" << endl; 
    }
    else{
        cout << "\nEl menor importe total fue $" << menorImporte << " recaudado por la/s empresa/s: " << endl;

        for (int i = 0; i < cantEmpresas; i++) //
        {
            if (v[i].importeTotal == menorImporte)
            {
                cout << "  - Codigo: " <<  v[i].codigo << ", Nombre: " << v[i].nombre << endl;
            }
        }
    }
}

// PUNTO 1 y 2 (Mostrar nombre, código, importe total y cantidad de ventas por día de promoción)
void imprimirDatos(Empresas v[], int cantidadEmpresas)
{
    cout << "\n-------EMPRESAS ADHERIDAS-------" << endl;

        // Por cada empresa adherida:
    for (int i = 0; i < cantidadEmpresas; i++) 
    {
        if (v[i].codigo != -1) 
        {
            cout << "\nNombre: " << v[i].nombre << endl;
            cout << "Codigo: " << v[i].codigo << endl;
            cout << "Cantidad de ventas: " << endl;

                // Por cada día de promoción:
            for (int j = 0; j < DiasPromocion; j++) 
            {
                if(v[i].dia[j] > 0) // Si cantidad de ventas > 0
                {
                    cout << "  - " << v[i].dia[j] << " Venta/s en el dia " << j+1 << endl;
                } 
                else{
                    cout << "  - " << "Sin ventas durante el dia " << j+1 << endl;
                }
            }

            if(v[i].importeTotal != 0)
                cout << "Importe Total: " << v[i].importeTotal << endl;

            cout << "\n--------------------------------" << endl; // Separador entre empresas
        }
    }
}

// PUNTO 5 (Registrar empresas adheridas)
void generarArchivoAdheridas(Empresas v[], int cantEmpresas) 
{
    FILE* adheridas = fopen("ImporteEmpresas.dat", "wb");

    if (adheridas != NULL) 
    {
        for (int i = 0; i < cantEmpresas; i++)
        {
            fwrite(&v[i], sizeof(Empresas), 1, adheridas);
        }
    }
    else 
        cerr << "No se pudo abrir el archivo" << endl;

    fclose(adheridas);
}

// PUNTO 6 (Incorporar ventas de empresas no adheridas)
void archivoNoAdheridas(Empresas e) 
{ 
    FILE *noAdheridas = fopen("SinAdhesion.dat", "ab");

    if (noAdheridas != NULL) 
    {
        fwrite(&e, sizeof(Empresas), 1, noAdheridas);
    }
    else 
        cerr << "No se pudo abrir el archivo" << endl;

    fclose(noAdheridas);
}

// OPCIONAL
void leerArchivoGenerado() 
{
    char nombreArchivo[20]; 
    int releer = 0;

    cout << "\nQue archivo leer? ImporteEmpresas / SinAdhesion (ingrese por teclado) " << endl;
    cin >> nombreArchivo;

    strcat(nombreArchivo,".dat");
    cout << "\nLeyendo archivo de empresas " << nombreArchivo; cout << endl;

    FILE *archivo = fopen(nombreArchivo, "rb");

    if (archivo == NULL) 
        cerr << "No se pudo abrir el archivo" << endl;
    else 
    {
        Empresas empresa;

        while (fread(&empresa, sizeof(Empresas), 1, archivo)) {
            cout << "\n--------------------------\n" << endl;
            cout << "Nombre: " << empresa.nombre << endl;
            cout << "Codigo: " << empresa.codigo << endl;
                // Compruebo si se eligió "SinAdhesión"
            if(strcmp(nombreArchivo,"SinAdhesion.dat") == 0)
                cout << "Dia de la venta: " << empresa.dia[0] << endl;
            else
                cout << "Ventas por dia: " << empresa.dia[0] << ", " << empresa.dia[1] << ", " << empresa.dia[2] << endl;
            cout << "Importe: " << empresa.importeTotal << endl;
        }
        fclose(archivo);

        cout << "\nDesea leer otro archivo? 1: Si / 0: No: ";
        cin >> releer;

        if(releer == 1)
            leerArchivoGenerado();
    }
}