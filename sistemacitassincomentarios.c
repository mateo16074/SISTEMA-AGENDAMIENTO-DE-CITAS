// CODE by Mateo Vaca - Isaac Oña
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct paciente {
    int numcita;
    char nombre[50];
    char numtel[15];
    int edad;
    char fecha[20];
    float peso;
    float altura;
    char especialidad[20];
    char sexo[20];
    struct paciente* sig;
};

typedef struct paciente paciente;
int token = 20;

void informacionPaciente(paciente** puntero) {
    int numcita;
    char key;
    paciente* nuevoPaciente = (paciente*)malloc(sizeof(paciente));
    paciente* ultimoPaciente = *puntero;

    if (token == 0) {
        printf("\n\n\n Lo siento, no se pueden reservar más citas hoy.\n\n Intenta nuevamente mañana\n\n\n");
        free(nuevoPaciente);
    } else {
        printf("\nNombre del paciente: ");
        fgets(nuevoPaciente->nombre, sizeof(nuevoPaciente->nombre), stdin);

        printf("\nNumero de celular del paciente: ");
        fgets(nuevoPaciente->numtel, sizeof(nuevoPaciente->numtel), stdin);

        printf("\nEdad del paciente: ");
        scanf("%d", &(nuevoPaciente->edad));

        printf("\nPeso del paciente en kg: ");
        scanf("%f", &(nuevoPaciente->peso));

        printf("\nAltura del paciente en m: ");
        scanf("%f", &(nuevoPaciente->altura));

        getchar();

        printf("\nEspecialidad solicitada: ");
        fgets(nuevoPaciente->especialidad, sizeof(nuevoPaciente->especialidad), stdin);

        printf("\nSexo del paciente: ");
        fgets(nuevoPaciente->sexo, sizeof(nuevoPaciente->sexo), stdin);

        printf("\nFecha en la que desea la cita (dd/mm/aa/hh): ");
        fgets(nuevoPaciente->fecha, sizeof(nuevoPaciente->fecha), stdin);

        token--;
        numcita = 20 - token;
        nuevoPaciente->numcita = numcita;
        printf("\n\n Tu cita con el medico se ha reservado exitosamente para hoy.\n");
        printf("\n Tu numero de token es %d.\n", nuevoPaciente->numcita);
        printf("\n\n Presiona cualquier tecla para continuar.....");
        scanf("%c", &key);

        nuevoPaciente->sig = NULL;
        if (ultimoPaciente == NULL) {
            *puntero = nuevoPaciente;
        } else {
            while (ultimoPaciente->sig != NULL) {
                ultimoPaciente = ultimoPaciente->sig;
            }
            ultimoPaciente->sig = nuevoPaciente;
        }
    }
}

void mostrarCitas(paciente* pointer) {
    printf("\n\nMostrando citas:\n");
    while (pointer != NULL) {
        printf("\nNombre del Paciente: %s ", pointer->nombre);
        printf("Numero de token: %d\n", pointer->numcita);
        printf("Numero de celular: %s\n", pointer->numtel);
        printf("Edad: %d\n", pointer->edad);
        printf("Peso: %.2f\n", pointer->peso);
        printf("Altura: %.2f\n", pointer->altura);
        printf("Especialidad: %s\n", pointer->especialidad);
        printf("Sexo: %s\n", pointer->sexo);
        printf("Fecha: %s\n", pointer->fecha);
        pointer = pointer->sig;
    }
}

void guardarCitasEnArchivo(paciente* pointer) {
    FILE* archivo;
    archivo = fopen("citas.txt", "w");
    if (archivo == NULL) {
        printf("No se puede crear el archivo\n");
        return;
    }

    fprintf(archivo, "\t\t-----  FUNDACION SALUD PARA TODOS  -----\n");

    while (pointer != NULL) {
        fprintf(archivo, "Numero de token %d\n", pointer->numcita);
        fprintf(archivo, "Nombre del paciente: %s\n", pointer->nombre);
        fprintf(archivo, "Numero de celular: %s\n", pointer->numtel);
        fprintf(archivo, "Edad: %d\n", pointer->edad);
        fprintf(archivo, "Peso: %.2f\n", pointer->peso);
        fprintf(archivo, "Altura: %.2f\n", pointer->altura);
        fprintf(archivo, "Especialidad: %s\n", pointer->especialidad);
        fprintf(archivo, "Sexo: %s\n\n", pointer->sexo);
        fprintf(archivo, "Fecha: %s\n\n", pointer->fecha);
        pointer = pointer->sig;
    }

    fclose(archivo);
}

int main() {
    paciente* head = NULL;
    char n;
    int opcion;

    srand(time(0));

    printf("\t\t----- Fundacion Salud para Todos -----\n");

    while (1) {
    menu_principal:
        printf("\n---- Menu ----\n");
        printf("1. Crear cita\n");
        printf("2. Revisar citas\n");
        printf("3. Salir\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();
        if (opcion == 1) {
            informacionPaciente(&head);
        } else if (opcion == 2) {
            mostrarCitas(head);
            guardarCitasEnArchivo(head);
        } else if (opcion == 3) {
            printf("Saliendo del programa...\n");
            while (head != NULL) {
                paciente* temp = head;
                head = head->sig;
                free(temp);
            }
            break;
        } else {
            printf("\n¡Presionaste una tecla de opción incorrecta!\n\n");
            goto menu_principal;
        }
    }

    return 0;
}
