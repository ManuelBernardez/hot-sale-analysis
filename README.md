# Hot Sale – Gestión de Ventas

Aplicación de consola en C++ para gestionar las ventas de un Hot Sale de 3 días, con hasta 500 empresas adheridas.

Trabajo práctico de la materia **Algoritmos y Estructuras de Datos**, UTN FRBA


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

| Archivo               | Contenido                                                                                |
|-----------------------|------------------------------------------------------------------------------------------|
| `ImporteEmpresas.dat` | Código y nombre de la empresa, importe total y cantidad de ventas. Ordenado por código.  |
| `SinAdhesion.dat`     | Ventas de empresas que no participaron de la promoción. Registra código y nombre         |


## Ejecución

1. Ingresar empresas adheridas (código `0` para finalizar).
2. Ingresar ventas por día — Primero las del día 1, luego día 2, luego día 3 (código `0` para finalizar cada día).
3. Se muestran las estadísticas en pantalla.
4. Si se desea, consultar los archivos binarios ingresando `SinAdhesion` o `ImporteEmpresa` cuando el programa lo solicite.


## Documentación

La carpeta `/docs` contiene el enunciado del TP, guía de uso y capturas de ejecución.


## Autor

Manuel Bernardez, proyecto académico para la materia Algoritmos y Estructuras de Datos.
