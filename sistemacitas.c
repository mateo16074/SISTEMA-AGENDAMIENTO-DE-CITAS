// Sistema de agendamiento de citas medicas para la fundacion salud para todos
// CODE by Mateo Vaca - Isaac Oña
/*Importing C Libraries*/
/*Importar librerias*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Create Structure named paciente that contains information*/
/*Creacion de un struct para almacenar todos los datos con los que vamos a trabajar*/
struct paciente { 
    int numcita;
    char nombre[50];
    char numtel[15];
    int edad;
    char fecha[25];
    float peso;
    float altura;
    char especialidad[25];
    char sexo[20];
    struct paciente* sig; 
    //puntero sig para llamar al nodo pacient y trabajar con listas enlazadas
    //pointer sig for call nodo paciente and work with linked lists
};

//typedef for for a new patient type name meaning a patient structure to use patient as the data type
//Crear un nuevo nombre de tipo paciente que se refiere a struct paciente, para usar paciente como un tipo de dato
typedef struct paciente paciente; 
int token = 20; // definir token para usarlo para tener un numero de las citas creadas

//Funcion para ingresar la informacion de los pacientes
void informacionPaciente(paciente** puntero) {
    int numcita; //Almacena el número de cita asignado a un paciente - Save the number of medical appointments
    char key;// variable que permite que el programa espere hasta que el usuario ingrese una tecla -variable that allows the program to wait until the user enters a key
    paciente* nuevoPaciente = (paciente*)malloc(sizeof(paciente));
    paciente* ultimoPaciente = *puntero;
    // se utilizan para asignar memoria dinámicamente a un nuevo objeto paciente utilizando malloc, para inicializar un puntero ultimoPaciente con el valor al que apunta el puntero doble puntero 
    

    // condicion if, si token = 0 significa que se han reservado todas las citas para ese dia
    if (token == 0) {
        printf("\n\n\n Lo siento, no se pueden reservar más citas hoy.\n\n Intenta nuevamente mañana\n\n\n");
        free(nuevoPaciente); //se utiliza para liberar la memoria asignada dinámicamente a nuevoPaciente en caso de que no se puedan reservar más citas
    }
    else {
        printf("\nNombre del paciente: ");
        fgets(nuevoPaciente->nombre, sizeof(nuevoPaciente->nombre), stdin); 
        /*Se utiliza la función fgets para capturar una línea de texto ingresada por el usuario. 
        El nombre del paciente se almacena en el miembro nombre de la estructura nuevoPaciente.
        (esto se hace con todas las estructuras char)*/
        printf("\nNumero de celular del paciente: ");
        fgets(nuevoPaciente->numtel, sizeof(nuevoPaciente->numtel), stdin);

        printf("\nEdad del paciente: ");
        scanf("%d", &(nuevoPaciente->edad));

        printf("\nPeso del paciente en kg: ");
        scanf("%f", &(nuevoPaciente->peso));

        printf("\nAltura del paciente en m: ");
        scanf("%f", &(nuevoPaciente->altura));

        getchar(); // Captura el salto de línea después de la altura

        printf("\nEspecialidad solicitada: ");
        fgets(nuevoPaciente->especialidad, sizeof(nuevoPaciente->especialidad), stdin);
        

        printf("\nSexo del paciente: ");
        fgets(nuevoPaciente->sexo, sizeof(nuevoPaciente->sexo), stdin);

        printf("\nFecha en la que desea la cita (dd/mm/aaa/hh): ");
        fgets(nuevoPaciente->fecha, sizeof(nuevoPaciente->fecha), stdin);
       

        token--;
        numcita = 20 - token;
        nuevoPaciente->numcita = numcita; 
        /*Asigna el valor de numcita al miembro numcita de la estructura nuevoPaciente.
         Esto guarda el número de cita asignado al paciente.*/

        printf("\n\n Tu cita con el medico se ha reservado exitosamente para hoy.\n");
        printf("\n Tu numero de token es %d.\n", nuevoPaciente->numcita);
        printf("\n\n Presiona cualquier tecla para continuar.....");
        scanf("%c", &key);

        nuevoPaciente->sig = NULL;
        /*Establece el puntero sig de nuevoPaciente a NULL. 
        Esto indica que el siguiente paciente en la lista enlazada es NULL, ya que nuevoPaciente será el último nodo de la lista.*/
        

        /*captura la entrada del usuario, actualiza el puntero sig de nuevoPaciente 
        y agrega nuevoPaciente a la lista enlazada de pacientes.*/
        if (ultimoPaciente == NULL) {
            *puntero = nuevoPaciente;
        }
        else {
            while (ultimoPaciente->sig != NULL) {
                ultimoPaciente = ultimoPaciente->sig;
            }
            ultimoPaciente->sig = nuevoPaciente;
        }
    }
}

void mostrarCitas(paciente* pointer) {
    printf("\n\nMostrando citas:\n");
    //: El bucle se ejecutará mientras pointer no sea NULL, lo que indica que hay más pacientes en la lista.
    while (pointer != NULL) {
        printf("\nNombre del Paciente: %s ", pointer->nombre);
        printf("\nNumero de token - %d: ", pointer->numcita);
//        printf("\n%s (Numero de celular: %s)", pointer->nombre, strtok(pointer->numtel, "\n"));
        printf("\nNumero de celular: %s\n", pointer->numtel);
        printf("Edad: %d \n", pointer->edad);
        printf("Peso: %.2f\n", pointer->peso);
        printf("Altura: %.2f\n", pointer->altura);
        printf("Especialidad: %s\n", pointer->especialidad);
        printf("Sexo: %s\n", pointer->sexo);
        printf("Fecha: %s\n", pointer->fecha);
        pointer = pointer->sig;
        /*Avanza al siguiente nodo de la lista enlazada. pointer->sig 
        accede al puntero sig del paciente actual, que apunta al siguiente paciente en la lista.*/
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
    /* Declara una variable llamada head que es un puntero a la estructura paciente.
     Inicialmente, se establece en NULL, lo que significa que no hay ningún paciente 
     registrado en la lista.*/
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
        }
        else if (opcion == 2) {
            mostrarCitas(head);
            guardarCitasEnArchivo(head);
        }
        else if (opcion == 3) {
            printf("Saliendo del programa...\n");
            while (head != NULL) {
                paciente* temp = head;
                head = head->sig;
                free(temp);
            }
            break;
        /*esta parte del código se encarga de liberar la memoria asignada a todos los pacientes en
        la lista antes de salir del programa. Esto es importante para asegurarse de que no haya
        fugas de memoria y liberar los recursos utilizados correctamente.*/
        }
        else {
            printf("\n¡Presionaste una tecla de opción incorrecta!\n\n");
            goto menu_principal;
            /*Si el usuario ingresa una opción no válida, se muestra un mensaje de error
             y se utiliza goto para redirigir el flujo de ejecución de nuevo
             a la etiqueta menu_principal, lo que muestra el menú nuevamente y 
             solicita una nueva opción al usuario.*/
        }
    }

    return 0;
}
