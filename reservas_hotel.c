// Librerias utilizadas
#include <stdio.h>
// Variables y funciones booleanas
#include <stdbool.h>
// tolower()
#include <ctype.h>
// strlen(), etc... 
#include <string.h>
// malloc() free() realloc()
#include <stdlib.h> 

// Constantes globales
#define PRECIO_DESAYUNO 400
#define PRECIO_NOCHE 1200
// Incrementos en el tamanio del arreglo de structs (en el heap)
#define INCREMENTO_CAPACIDAD 10 

// Definicion de la estructura de una reserva
struct Reserva {
  int ID;
  char fecha_entrada[20];
  char fecha_salida[20];
  char nombre[50];
  float precio;
  int numero_de_habitacion;
  bool desayuno;
  int num_dias;
};

// Puntero al primer elemento de un arreglo de Reserva
struct Reserva *reservas;
// Numero actual de reservas
int num_reservas = 0; 
// Capacidad actual en el arreglo de Reserva
int capacidad_actual = 0;

// Asignacion de IDs 
int current_ID = 1;

// Prototipado de las funciones a utilizar
void incrementar_reservas();
void registrar_reserva();
void modificar_reserva();
void cancelar_reserva();
void buscar_reserva();
void mostrar_reservas(); 
bool verificar_cuarto(const int*const, const char*const, const char*const, const int*const);
bool verificar_fecha(const char*const); 
bool comparar_fechas(const char*const, const char*const);
int calcular_fecha(const char*const, const char*const);
bool isBisiesto(int);

int main() {
  int user_option;
  do {
    // Menu 
    printf("--------------------------------------\n");
    printf("  1. Registrar una nueva reserva\n");
    printf("  2. Modificar una reserva\n");
    printf("  3. Cancelar una reserva\n");
    printf("  4. Buscar una reserva\n");
    printf("  5. Mostrar todas las reservas\n");
    printf("  0. Salir\n");
    printf("--------------------------------------\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &user_option);
    getchar();
    // Condicional para leer la opcion seleccionada por el usuario
    switch (user_option) {
      case 1:
        registrar_reserva();
        break;
      case 2:
        modificar_reserva();
        break;
      case 3:
        cancelar_reserva();
        break;
      case 4:
        buscar_reserva();
        break;
      case 5:
        mostrar_reservas();
        break;
      case 0:
        printf("Saliendo...\n");
        break;
      default:
        printf("Opcion no valida, por favor re-ingrese una opcion valida\n");
    }
  } while (user_option != 0);
  // Liberamos el espacio en memoria del arreglo reservas
  free(reservas);
  return 0;
}

void incrementar_reservas() {
  // Si vamos a hacer una reserva pero, no hay espacio allocated le asignamos 10
  if(capacidad_actual == 0) {
    capacidad_actual = INCREMENTO_CAPACIDAD;
    // Allocamos memoria al puntero reservas
    reservas = malloc(capacidad_actual * sizeof(struct Reserva));
    if(reservas == NULL) {
      printf("Error al asignar memoria.\n");
      exit(1);
    }
  }
  else {
    // Si ya existe memoria, pero llegamos al limite del arreglo y no hay mas memoria, le incrementamos 10 al arreglo y reallocamos memoria
    if(capacidad_actual <= num_reservas) {
      capacidad_actual += INCREMENTO_CAPACIDAD;
      // Reallocamos memoria al puntero reservas
      reservas = realloc(reservas, capacidad_actual * sizeof(struct Reserva));
      if(reservas == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
      }
    }
  }
}

void registrar_reserva() {
  // Primero revisamos si tenemos que allocar o reallocar memoria
  incrementar_reservas(); 
  // Cadena para que el usuario use si o no para decidir su desayuno
  char user_desayuno[3];
  printf("Has seleccionado la opcion registrar reserva.\n");

  // Recoleccion de datos 
  printf("Introduce el nombre del cliente: ");
  fgets(reservas[num_reservas].nombre, sizeof(reservas[num_reservas].nombre), stdin);
  // Eliminamos el caracter que queda en buffer '\n'
  if(reservas[num_reservas].nombre[strlen(reservas[num_reservas].nombre) - 1] == '\n') {
    reservas[num_reservas].nombre[strlen(reservas[num_reservas].nombre) - 1] = '\0';
  }

  do {
    // Recoleccion de datos
    do {
      printf("Introduce la fecha de entrada (dd/mm/aaaa): ");
      fgets(reservas[num_reservas].fecha_entrada, sizeof(reservas[num_reservas].fecha_entrada), stdin);
      // Eliminamos el caracter del "enter"
      if(reservas[num_reservas].fecha_entrada[strlen(reservas[num_reservas].fecha_entrada) - 1] == '\n') {
        reservas[num_reservas].fecha_entrada[strlen(reservas[num_reservas].fecha_entrada) - 1] = '\0';
      }
      // Si verificar fecha es falso, entonces imprimimos
      if(!verificar_fecha(reservas[num_reservas].fecha_entrada)) {
        printf("Fecha no valida, re-ingrese.\n");
      }
    }
    // Verificamos que nuestra fecha sea correcta (formato dd/mm/aaaa, dias y meses correctos)
    while(!verificar_fecha(reservas[num_reservas].fecha_entrada));

    // Recoleccion de datos
    do {
      printf("Introduce la fecha de salida (dd/mm/aaaa): ");
      fgets(reservas[num_reservas].fecha_salida, sizeof(reservas[num_reservas].fecha_salida), stdin);
      // Eliminamos el caracter del "enter"
      if(reservas[num_reservas].fecha_salida[strlen(reservas[num_reservas].fecha_salida) - 1] == '\n') {
        reservas[num_reservas].fecha_salida[strlen(reservas[num_reservas].fecha_salida) - 1] = '\0';
      }
      // Si verificar fecha es falso, entonces imprimimos
      if(!verificar_fecha(reservas[num_reservas].fecha_salida)) {
        printf("Fecha no valida, re-ingrese.\n");
      }
    }
    // Verificamos que nuestra fecha sea correcta (formato dd/mm/aaaa, dias y meses correctos)
    while(!verificar_fecha(reservas[num_reservas].fecha_salida)); 
    // Si al comparar nuestra fecha de entrada con nuestra fecha de salida esta es menor, entonces imprimimos
    if(!comparar_fechas(reservas[num_reservas].fecha_entrada, reservas[num_reservas].fecha_salida)) {
      printf("La fecha de salida es previa a la fecha de entrada, re-ingrese:\n");
    }
  }
  // Verificamos que nuestra fecha de salida no sea mayor a nuestra fecha de entrada
  while(!comparar_fechas(reservas[num_reservas].fecha_entrada, reservas[num_reservas].fecha_salida));

  // Recaudacion de datos
  do {
    printf("Introduce el numero de habitacion (001 a 740): ");
    scanf("%d", &reservas[num_reservas].numero_de_habitacion);
    // Verificamos que el cuarto se encuentre entre 001 y 740 y que no este apartado la fecha seleccionada
  }
  while(!verificar_cuarto(&reservas[num_reservas].numero_de_habitacion, reservas[num_reservas].fecha_entrada, reservas[num_reservas].fecha_salida, &reservas[num_reservas].ID));
  

  // Recaudacion de datos
  printf("Desea desayuno? (Si/No): ");
  getchar();  
  fgets(user_desayuno, sizeof(user_desayuno), stdin);
  // Eliminacion del caracter "enter"
  if(user_desayuno[strlen(user_desayuno) - 1] == '\n') {
    user_desayuno[strlen(user_desayuno) - 1] = '\0';
  }

  // Convertimos la respuesta en minusculas para que todos los casos (SI, NO, Si, No, si, no) sean tomados en cuenta para la asignacion de desayuno 
  for(int i = 0; i < strlen(user_desayuno); i++) {
    user_desayuno[i] = tolower(user_desayuno[i]);
  }
  // Si la respuesta es igual a "si" entonces le asignamos true al desayuno
  reservas[num_reservas].desayuno = (strcmp(user_desayuno, "si") == 0);

  // Calculamos el numero de dias que el usuario planea quedarse en el hotel 
  reservas[num_reservas].num_dias = calcular_fecha(reservas[num_reservas].fecha_entrada, reservas[num_reservas].fecha_salida);

  // Calculo del precio
  reservas[num_reservas].precio = reservas[num_reservas].num_dias * PRECIO_NOCHE; 
  if(reservas[num_reservas].desayuno == 1) {
    reservas[num_reservas].precio += PRECIO_DESAYUNO * reservas[num_reservas].num_dias;
  }

  // Cuando se cumple todo entonces la reserva fue registrada correctamente
  printf("RESERVA REGISTRADA EXITOSAMENTE.\n");
  // Le asignamos el ID actual a la reserva existente
  reservas[num_reservas].ID = current_ID;
  // Aumentamos el ID actual para que la siguiente reserva tenga ID + 1
  current_ID++;
  // Impresion de los datos necesarios para el usuario
  printf("El ID de tu reserva es: %d\n", reservas[num_reservas].ID);
  printf("El precio de tu reserva es: %.2f\n", reservas[num_reservas].precio);
  num_reservas++;
}

void modificar_reserva() {
  // Declaracion de las variables a usar
  int user_ID, user_option; 
  // Si el numero de reservas actual es 0 entonces no existen reservas que modificar
  if(num_reservas == 0) {
    printf("No existen reservas. \n");
  }
  else {
    // Recoleccion de datos
    printf("Introduce el ID de tu reserva: ");
    scanf("%d", &user_ID);
    getchar();
    // Recorremos las reservas existentes
    for(int i = 0; i < num_reservas; i++) {
      // Si el ID ingresado es igual a alguno de las reservas existentes entonces se encontro la reserva 
      if(user_ID == reservas[i].ID) {
        printf("Reserva encontrada.\n");
        printf("Introduzca que modificar:\n");
        printf("1. Nombre\n");
        printf("2. Fecha de entrada\n");
        printf("3. Fecha de salida\n");
        printf("4. Numero de cuarto\n");
        printf("5. Desayuno\n");
        printf("0. Cancelar\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &user_option);
        getchar();
        // Condicional para ejecutar la opcion del usuario
        switch(user_option) {
          case 1:
            printf("Ingrese el nuevo nombre: ");
            // Recoleccion de datos
            fgets(reservas[i].nombre, sizeof(reservas[i].nombre), stdin);
            break;
          case 2:
            // Recoleccion de datos
            do {
              printf("Ingrese la nueva fecha de entrada: ");
              fgets(reservas[i].fecha_entrada, sizeof(reservas[i].fecha_entrada), stdin);
              // Eliminacion del caracter enter '\n'
              if(reservas[i].fecha_entrada[strlen(reservas[i].fecha_entrada) - 1] == '\n') {
              reservas[i].fecha_entrada[strlen(reservas[i].fecha_entrada) - 1] = '\0';
              }
              // Si la fecha es invalida entonces se imprime
              if(!verificar_fecha(reservas[i].fecha_entrada)) {
                printf("La fecha no es valida, re-ingrese: \n");
              } 
              // Si la fecha es posterior a la de salida entonces se imprime
              if(!comparar_fechas(reservas[i].fecha_entrada, reservas[i].fecha_salida)) {
                printf("La fecha de salida actual es: %s\n", reservas[i].fecha_salida);
                printf("La fecha de salida es previa a la fecha de entrada, re-ingrese: \n");
              } 
            }
            while(!verificar_fecha(reservas[i].fecha_entrada) || !comparar_fechas(reservas[i].fecha_entrada, reservas[i].fecha_salida));
            break;
          case 3:
            do {
              printf("Ingrese la nueva fecha de salida: ");
              fgets(reservas[i].fecha_salida, sizeof(reservas[i].fecha_salida), stdin);
              if(reservas[i].fecha_salida[strlen(reservas[i].fecha_salida) - 1] == '\n') {
              reservas[i].fecha_salida[strlen(reservas[i].fecha_salida) - 1] = '\0';
              }
              if(!verificar_fecha(reservas[i].fecha_salida)) {
                printf("La fecha no es valida, re-ingrese: \n");
              } 
              if(!comparar_fechas(reservas[i].fecha_entrada, reservas[i].fecha_salida)) {
                printf("La fecha de entrada actual es: %s\n", reservas[i].fecha_entrada);
                printf("La fecha de salida de previa a la fecha de entrada, re-ingrese: \n");
              }
            }
            while(!verificar_fecha(reservas[i].fecha_salida) || !comparar_fechas(reservas[i].fecha_entrada, reservas[i].fecha_salida));
            break;
          case 4:
            do {
              printf("Ingrese el nuevo numero de cuarto: ");
              scanf("%d", &reservas[i].numero_de_habitacion);
              getchar();
            }
            while(verificar_cuarto(&reservas[i].numero_de_habitacion, reservas[i].fecha_entrada, reservas[i].fecha_salida, &reservas[i].ID));
            break;
          case 5:
            reservas[i].desayuno = !reservas[i].desayuno;
            printf("Desayuno actualizado.\n");
            break;
          case 0:
            printf("Cancelando...\n");
            break;
          default:
            printf("Opcion no valida. Cancelando...\n");
            break;
        }
        reservas[i].num_dias = calcular_fecha(reservas[i].fecha_entrada, reservas[i].fecha_salida);
        reservas[i].precio = reservas[i].num_dias * PRECIO_NOCHE;
        if(reservas[i].desayuno == true) {
          reservas[i].precio += reservas[i].num_dias * PRECIO_DESAYUNO; 
        }
        printf("El nuevo precio de tu reserva es: %.2f\n", reservas[i].precio);
        break;
      }
    }
  }
}

void cancelar_reserva() {
  int user_ID; 
  if(num_reservas == 0) {
    printf("No existen reservas.\n");
  }
  else {
    printf("--------------------------------------------------\n");
    printf("Introduce el ID de tu reserva: ");
    scanf("%d", &user_ID);
    for(int i = 0; i < num_reservas; i++) {
      if(user_ID == reservas[i].ID) {
        reservas[i].ID = 0;
        strcpy(reservas[i].nombre, "");
        strcpy(reservas[i].fecha_entrada, "");
        strcpy(reservas[i].fecha_salida, "");
        reservas[i].desayuno = false;
        reservas[i].numero_de_habitacion = 0; 
        reservas[i].precio = 0; 
        printf("Reserva cancelada.\n");
        num_reservas--;
        break;
        printf("--------------------------------------------------\n");
      }
    }
  }
}

void buscar_reserva() {
  int user_ID;
  if(num_reservas == 0) {
    printf("No existen reservas.\n");
  } 
  else {
    printf("--------------------------------------------------\n");
    printf("Introduce el ID de tu reserva: ");
    scanf("%d", &user_ID);
    for(int i = 0; i < num_reservas; i++) {
      if(user_ID == reservas[i].ID) {
        printf("--------------------------------------------------\n");
        printf("Reserva encontrada:\n");
        printf("Nombre: %s\n", reservas[i].nombre);
        printf("Fecha de entrada: %s\n", reservas[i].fecha_entrada);
        printf("Fecha de salida: %s\n", reservas[i].fecha_salida);
        printf("Numero de cuarto: %d\n", reservas[i].numero_de_habitacion);
        printf("Precio: %.2f\n", reservas[i].precio);
        printf("Desayuno: %d\n", reservas[i].desayuno);
        printf("--------------------------------------------------\n");
        break;
      }
    }
  }
}

void mostrar_reservas() {
  if(num_reservas == 0) {
    printf("--------------------------------------------------\n");
    printf("No existen reservas.\n");
    printf("--------------------------------------------------\n");
  }
  else {  
    for(int i = 0; i < num_reservas; i++) {
      printf("--------------------------------------------------\n");
      printf("RESERVA NUMERO %d:\n", i + 1); 
      printf("Nombre: %s\n", reservas[i].nombre);
      printf("Fecha de entrada: %s\n", reservas[i].fecha_entrada);
      printf("Fecha de salida: %s\n", reservas[i].fecha_salida);
      printf("Numero de cuarto: %d\n", reservas[i].numero_de_habitacion);
      printf("Desayuno: %d\n", reservas[i].desayuno);
    }
  }
}

bool verificar_cuarto(const int *const numero_cuarto, const char *const fecha_entrada, const char *const fecha_salida, const int *const ID) {
  // Si el cuarto no esta dentro del rango de los cuartos disponibles se regresa false
  if (*numero_cuarto < 1 || *numero_cuarto > 740) {
    printf("El cuarto no existe, por favor introduce un numero de 1 a 740: \n");
    return false;
  }
  // Recorremos las reservas existentes
  for (int i = 0; i < num_reservas; i++) { 
    // Si la reserva no es la misma que la que estamos evaluando entonces verificamos que el cuarto y fecha no se solapen
    if (reservas[i].numero_de_habitacion == *numero_cuarto && reservas[i].ID != *ID) {
      /*  
       *  LOGICA PARA QUE DOS RESERVACIONES DEL MISMO CUARTO DIFERENTES NO TENGAN LA MISMA FECHA
       *  Si la fecha de salida de la nueva reservacion es menor a la fecha de entrada de la reservacion a evaluar entonces las fechas no se solapan
       *  si la fecha de salida de la reservacion a evaluar es menor a la fecha de entrada de la nueva reservacion entonces las fechas tampoco se solapan
       *  Ahora, si ambas condiciones son falsas, es decir la fecha de salida de la nueva reservacion es MAYOR a la fecha de entrada de la reservacion evaluada 
       *  y la fecha de salida de la antigua reservacion es MAYOR a la fecha de entrada de la nueva reservacion entonces las fechas se solapan.
       *
       *  [10]-[11]-[12]-[13] - Reservacion antigua
       *                     [14]-[15]-[16] - Nueva reservacion
       *
       *  En este caso la fecha de salida de la nueva reservacion no es menor a la fecha de entrada, pero la fecha de salida de la antigua si es menor a la fecha de entrada de la nueva
       *  POR LO TANTO NO SE SOLAPAN.
      */
      if (!(comparar_fechas(fecha_salida, reservas[i].fecha_entrada) || comparar_fechas(reservas[i].fecha_salida, fecha_entrada))) {
        printf("El cuarto %d ya está reservado entre %s y %s.\n", *numero_cuarto, reservas[i].fecha_entrada, reservas[i].fecha_salida);
        return false;
      }
    }
  }
  return true;
}

bool verificar_fecha(const char *const fecha) {
// Dias por mes 
  int dias_por_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (fecha[2] != '/' || fecha[5] != '/' || strlen(fecha) != 10) {
    return false;
  }

  int dia = (fecha[0] - '0') * 10 + (fecha[1] - '0');
  int mes = (fecha[3] - '0') * 10 + (fecha[4] - '0');
  int anio = (fecha[6] - '0') * 1000 + (fecha[7] - '0') * 100 + (fecha[8] - '0') * 10 + (fecha[9] - '0');

  if (mes < 1 || mes > 12 || dia < 1 || anio < 2024 || anio > 2030) {
    return false;
  }

  int dias_en_mes = dias_por_mes[mes - 1];
  if (mes == 2 && isBisiesto(anio)) {
    dias_en_mes++;
  }

  return dia <= dias_en_mes;
}

bool comparar_fechas(const char *const fecha1, const char *const fecha2) {
  int dia1 = (fecha1[0] - '0') * 10 + (fecha1[1] - '0');
  int mes1 = (fecha1[3] - '0') * 10 + (fecha1[4] - '0');
  int anio1 = (fecha1[6] - '0') * 1000 + (fecha1[7] - '0') * 100 + (fecha1[8] - '0') * 10 + (fecha1[9] - '0');

  int dia2 = (fecha2[0] - '0') * 10 + (fecha2[1] - '0');
  int mes2 = (fecha2[3] - '0') * 10 + (fecha2[4] - '0');
  int anio2 = (fecha2[6] - '0') * 1000 + (fecha2[7] - '0') * 100 + (fecha2[8] - '0') * 10 + (fecha2[9] - '0');

  if (anio1 != anio2) {
    return anio1 < anio2;
  }
  if (mes1 != mes2) {
    return mes1 < mes2;
  }
  return dia1 < dia2;
}

int calcular_fecha(const char *const fecha1, const char *const fecha2) {
// Dias por mes 
  int dias_por_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Asumiendo que fecha1 < fecha2
  int dia1 = (fecha1[0] - '0') * 10 + (fecha1[1] - '0');
  int mes1 = (fecha1[3] - '0') * 10 + (fecha1[4] - '0');
  int anio1 = (fecha1[6] - '0') * 1000 + (fecha1[7] - '0') * 100 + (fecha1[8] - '0') * 10 + (fecha1[9] - '0');

  int dia2 = (fecha2[0] - '0') * 10 + (fecha2[1] - '0');
  int mes2 = (fecha2[3] - '0') * 10 + (fecha2[4] - '0');
  int anio2 = (fecha2[6] - '0') * 1000 + (fecha2[7] - '0') * 100 + (fecha2[8] - '0') * 10 + (fecha2[9] - '0');

  int total_dias1 = 0;
  for (int i = 2024; i < anio1; i++) {
    total_dias1 += isBisiesto(i) ? 366 : 365;
  }
  for (int i = 0; i < mes1 - 1; i++) {
    total_dias1 += dias_por_mes[i];
  }
  total_dias1 += dia1;

  int total_dias2 = 0;
  for (int i = 2024; i < anio2; i++) {
    total_dias2 += isBisiesto(i) ? 366 : 365;
  }
  for (int i = 0; i < mes2 - 1; i++) {
    total_dias2 += dias_por_mes[i];
  }
  total_dias2 += dia2;

  return total_dias2 - total_dias1;
}

bool isBisiesto(int anio) {
  return ((anio % 4 == 0) && (anio % 100 != 0)) || (anio % 400 == 0);
}
