# Sistema de Reservas de Hotel

Este programa en C permite gestionar reservas de habitaciones en un hotel. Incluye funciones para registrar, modificar, cancelar, buscar y mostrar reservas, además de manejar el cálculo de precios en función de la estancia y opciones de desayuno.

## Contenido
- [Instalación](#instalación)
- [Uso](#uso)
- [Funciones Principales](#funciones-principales)
- [Dependencias](#dependencias)

## Instalación

Clona este repositorio o descarga el archivo fuente.
   
      git clone https://github.com/usuario/sistema-reservas-hotel.git

Navega hasta el directorio del proyecto:

      cd sistema-reservas-hotel

Compila el archivo:

      gcc reservas_hotel.c -o reservas -Wall

## Uso

Ejecuta el programa compilado en la terminal:

      ./reservas

Se mostrará un menú interactivo donde puedes seleccionar las opciones para manejar las reservas.
Opciones del Menú

    Registrar una nueva reserva: Agrega una nueva reserva con los datos del cliente, fechas, habitación y desayuno.
    Modificar una reserva: Permite cambiar los datos de una reserva existente mediante el ID de la reserva.
    Cancelar una reserva: Elimina una reserva registrada según su ID.
    Buscar una reserva: Muestra detalles de una reserva específica.
    Mostrar todas las reservas: Lista todas las reservas activas.

## Funciones Principales

    incrementar_reservas(): Expande la capacidad del arreglo de reservas en memoria.
    registrar_reserva(): Permite ingresar una nueva reserva.
    modificar_reserva(): Modifica una reserva existente.
    cancelar_reserva(): Elimina una reserva registrada.
    buscar_reserva(): Busca y muestra una reserva específica.
    mostrar_reservas(): Muestra todas las reservas activas.

## Dependencias

Las siguientes librerías estándar de C se utilizan en el programa:

    stdio.h: Entrada y salida.
    stdbool.h: Manejo de booleanos.
    ctype.h: Manipulación de caracteres.
    string.h: Manejo de cadenas de caracteres.
    stdlib.h: Asignación de memoria dinámica.

### Contribuciones

Si deseas contribuir al proyecto, puedes hacer un fork del repositorio y enviar un pull request.
> [!NOTE]
> No soy el unico contribuidor del proyecto | creditos a: Dulce Maria y Axel Adrian

Licencia
Este proyecto está licenciado bajo la Licencia MIT.
