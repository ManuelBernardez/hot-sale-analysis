# UTN FRBA - Algoritmos y Estructura de Datos

## Trabajo Práctico – Hot Sale

Se requiere una aplicación para registrar datos y generar estadísticas sobre un evento Hot Sale en el que participan hasta **500 empresas adheridas**.

---

## Datos de las empresas adheridas

Por cada empresa participante se deberá registrar:

- Código de empresa
- Nombre de la empresa

> Definir el criterio para finalizar la carga de datos.

---

## Datos de las ventas

También se registrarán las ventas realizadas durante los **3 días** del Hot Sale.

Por cada venta se deberá ingresar:

- Día de la venta (1, 2 o 3)
- Código de empresa
- Importe de la venta

> Definir el criterio para finalizar la carga de datos.

---

## Requerimientos del sistema

1. **Ventas por empresa por día:** Por cada día de la promoción, informar:
   - Cantidad de ventas realizadas por cada empresa adherida.
   - Importe total recaudado por cada empresa adherida.

2. **Días sin ventas:** Para cada empresa adherida, informar los días en los que no registró ventas (si corresponde).

3. **Menor recaudación:** Determinar e informar la o las empresas que obtuvieron la menor recaudación total, junto con el importe total recaudado por dichas empresas.

4. **Día con más ventas:** Informar cuál de los tres días del Hot Sale registró la mayor cantidad de ventas.

5. **Archivo binario de empresas:** Generar un archivo binario con un registro por cada empresa adherida, ordenado por código de empresa. Cada registro deberá contener:
   - Código de empresa
   - Nombre de la empresa
   - Importe total recaudado
   - Cantidad total de ventas

6. **Archivo binario de ventas no adheridas:** Generar un archivo binario que contenga todas las ventas ingresadas correspondientes a empresas que **no** se encontraban adheridas a la promoción.
