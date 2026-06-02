# Hot Sale – Gestión de Ventas

Aplicación de consola en C/C++ para gestionar las ventas de un Hot Sale.
Trabajo práctico de la materia **Algoritmos y Estructuras de Datos**, UTN FRBA

> Este repositorio contiene la versión original (entregada como TP) y una versión posterior, en la que implementé mejoras de diseño y algunas correcciones.

## Conocimientos aplicados

- Structs
- Arreglos
- Ordenamiento
- Búsqueda binaria
- Manejo de archivos binarios
- Modularización y validación de datos
- Programación estructurada 


## Funcionalidades

- Registro de empresas adheridas (hasta 500).
- Registro de ventas por día, diferenciando empresas adheridas y no adheridas.
- Estadísticas por pantalla:
  - Cantidad de ventas e importe total por día de cada empresa.
  - Empresa/s con menor recaudación total.
  - Día con mayor cantidad de ventas.
  - Días sin ventas por empresa.
- Generación de archivos binarios con la información procesada.


## Archivos generados

| Archivo               | Contenido                                                                               |
|-----------------------|-----------------------------------------------------------------------------------------|
| `ImporteEmpresas.dat` | Código y nombre de la empresa, importe total y cantidad de ventas. Ordenado por código. |
| `SinAdhesion.dat`     | Ventas de empresas que no participaron de la promoción.                                 |


## Ejecución

1. Ingresar empresas adheridas (código `0` para finalizar).
2. Ingresar ventas por día — Primero las del día 1, luego día 2, luego día 3 (código `0` para finalizar cada día).
3. Se muestran las estadísticas en pantalla y se guarda la información en los archivos correspondientes.
4. Si se desea, consultar los archivos binarios ingresando `SinAdhesion` o `ImporteEmpresa` cuando el programa lo solicite.


## Documentación

La carpeta `/docs` contiene el enunciado del TP, guía de uso y capturas de ejecución.


## Autor

Manuel Bernardez.
