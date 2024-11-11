#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> 

#define INCREMENTO_CAPACIDAD 10 

struct Reserva {
  int ID;
  char fecha_entrada[20];
  char fecha_salida[20];
  char nombre[50];
  float precio;
  int numero_de_habitacion;
  bool desayuno;
};

struct Reserva *reservas;
int num_reservas = 0; 
int capacidad_actual = 0;

int current_ID = 1;

void registrar_reserva();
void modificar_reserva();
void cancelar_reserva();
void buscar_reserva();
void mostrar_reservas(); 
void verificar_cuarto(int*);
bool verificar_fecha(char*); 
void organizar_reservas();

int main() {
  int user_option;
  do {
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
  free(reservas);
  return 0;
}

void incrementar_reservas() {
  if(capacidad_actual == 0) {
    capacidad_actual = INCREMENTO_CAPACIDAD;
    reservas = malloc(capacidad_actual * sizeof(struct Reserva));
    if(reservas == NULL) {
      printf("Error al asignar memoria.\n");
      exit(1);
    }
  }
  else {
    if(capacidad_actual <= num_reservas) {
      capacidad_actual += INCREMENTO_CAPACIDAD;
      reservas = realloc(reservas, capacidad_actual * sizeof(struct Reserva));
      if(reservas == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
      }
    }
  }
}

void registrar_reserva() {
  incrementar_reservas(); 
  char user_desayuno[3];
  printf("Has seleccionado la opcion registrar reserva.\n");

  printf("Introduce el nombre del cliente: ");
  fgets(reservas[num_reservas].nombre, sizeof(reservas[num_reservas].nombre), stdin);
  if(reservas[num_reservas].nombre[strlen(reservas[num_reservas].nombre) - 1] == '\n') {
    reservas[num_reservas].nombre[strlen(reservas[num_reservas].nombre) - 1] = '\0';
  }

  do {
    printf("Introduce la fecha de entrada (dd/mm/aaaa): ");
    fgets(reservas[num_reservas].fecha_entrada, sizeof(reservas[num_reservas].fecha_entrada), stdin);
    if(reservas[num_reservas].fecha_entrada[strlen(reservas[num_reservas].fecha_entrada) - 1] == '\n') {
      reservas[num_reservas].fecha_entrada[strlen(reservas[num_reservas].fecha_entrada) - 1] = '\0';
    }
    if(!verificar_fecha(reservas[num_reservas].fecha_entrada)) {
      printf("Fecha no valida, re-ingrese.\n");
      printf("%s\n", reservas[num_reservas].fecha_entrada);
    }
  }
  while(!verificar_fecha(reservas[num_reservas].fecha_entrada));

  printf("Introduce la fecha de salida (dd/mm/aaaa): ");
  fgets(reservas[num_reservas].fecha_salida, sizeof(reservas[num_reservas].fecha_salida), stdin);
  if(reservas[num_reservas].fecha_salida[strlen(reservas[num_reservas].fecha_salida) - 1] == '\n') {
    reservas[num_reservas].fecha_salida[strlen(reservas[num_reservas].fecha_salida) - 1] = '\0';
  }

  printf("Introduce el numero de habitacion (001 a 740): ");
  scanf("%d", &reservas[num_reservas].numero_de_habitacion);
  verificar_cuarto(&reservas[num_reservas].numero_de_habitacion);

  printf("Desea desayuno? (Si/No): ");
  getchar();  
  fgets(user_desayuno, sizeof(user_desayuno), stdin);
  if(user_desayuno[strlen(user_desayuno) - 1] == '\n') {
    user_desayuno[strlen(user_desayuno) - 1] = '\0';
  }

  for(int i = 0; i < strlen(user_desayuno); i++) {
    user_desayuno[i] = tolower(user_desayuno[i]);
  }
  reservas[num_reservas].desayuno = (strcmp(user_desayuno, "si") == 0);

  printf("RESERVA REGISTRADA EXITOSAMENTE.\n");
  reservas[num_reservas].ID = current_ID;
  current_ID++;
  printf("El ID de tu reserva es: %d\n", reservas[num_reservas].ID);
  printf("El precio de tu reserva es: %.2f\n", reservas[num_reservas].precio);
  num_reservas++;
  organizar_reservas();
}

void modificar_reserva() {
  int user_ID, user_option; 
  printf("Introduce el ID de tu reserva: ");
  scanf("%d", &user_ID);
  getchar();
  for(int i = 0; i < num_reservas; i++) {
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
      switch(user_option) {
        case 1:
          printf("Ingrese el nuevo nombre: ");
          fgets(reservas[i].nombre, sizeof(reservas[i].nombre), stdin);
          break;
        case 2:
          printf("Ingrese la nueva fecha de entrada: ");
          fgets(reservas[i].fecha_entrada, sizeof(reservas[i].fecha_entrada), stdin);
          break;
        case 3:
          printf("Ingrese la nueva fecha de salida: ");
          fgets(reservas[i].fecha_salida, sizeof(reservas[i].fecha_salida), stdin);
          break;
        case 4:
          printf("Ingrese el nuevo numero de cuarto: ");
          scanf("%d", &reservas[i].numero_de_habitacion);
          getchar();
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
      break;
    }
  }
}

void cancelar_reserva() {
  int user_ID; 
  if(num_reservas == 0) {
    printf("No existen reservas.\n");
  }
  else {
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
    printf("Introduce el ID de tu reserva: ");
    scanf("%d", &user_ID);
    for(int i = 0; i < num_reservas; i++) {
      if(user_ID == reservas[i].ID) {
        printf("Reserva encontrada:\n");
        printf("Nombre: %s\n", reservas[i].nombre);
        printf("Fecha de entrada: %s\n", reservas[i].fecha_entrada);
        printf("Fecha de salida: %s\n", reservas[i].fecha_salida);
        printf("Numero de cuarto: %d\n", reservas[i].numero_de_habitacion);
        printf("Precio: %f\n", reservas[i].precio);
        printf("Desayuno: %d\n", reservas[i].desayuno);
        break;
      }
    }
  }
}

void mostrar_reservas() {
  if(num_reservas == 0) {
    printf("No existen reservas.\n");
  }
  else {  
    for(int i = 0; i < num_reservas; i++) {
      printf("RESERVA NUMERO %d:\n", i + 1); 
      printf("Nombre: %s\n", reservas[i].nombre);
      printf("Fecha de entrada: %s\n", reservas[i].fecha_entrada);
      printf("Fecha de salida: %s\n", reservas[i].fecha_salida);
      printf("Numero de cuarto: %d\n", reservas[i].numero_de_habitacion);
      printf("Desayuno: %d\n", reservas[i].desayuno);
    }
  }
}

void verificar_cuarto(int *numero_cuarto) {
  while(*numero_cuarto < 1 || *numero_cuarto > 740) {
    printf("Numero de habitacion no valido. Porfavor re-ingrese numero de habitacion: ");
    scanf("%d", numero_cuarto);
  }
}

bool verificar_fecha(char *fecha) {
  if(fecha[2] != '/' || strlen(fecha) != 10 || fecha[5] != '/') {
    return false;
  }
  return true;
}

void organizar_reservas() {
  for(int i = 0; i < num_reservas; i++) {

  }
}
