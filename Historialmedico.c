#include<stdio.h> //Se incluye la librería estándar
#include<stdlib.h> //Esta librería se incluye para el uso de gets y puts, y la lectura de cadenas de caracteres.
#include<string.h> //Se incluye esta librería para cambiar caracteres y comparar cadenas.
#include<time.h> //Esta librería se agrega para poder añadir la fecha y hora del ingreso de datos.
struct Paciente{ //Estructura donde se guardan todos los datos que se registrarán.
    char nombre[50];
    int edad;
    float altura;
    float peso;
    float presionArterial;
    int pulso;
    float temperatura;
    int frecuenciaRespiratoria;
    float imc;
};

void guardarDatos(struct Paciente paciente){ //Se hace uso de la función void para que no se devuelva ningún valor, y toma el parámetro del struct que contiene los datos de los pacientes.
    FILE *archivo; //Usamos el archivo FILE para poder mover los datos a un archivo plano.
    archivo = fopen("datosPacientes.csv", "a");
    time_t tiempoActual;
    time(&tiempoActual);
    struct tm *miTiempo = localtime(&tiempoActual); //Funcion para que muestre el tiempo actual que queramos

    fprintf(archivo, "%d/%d/%d\n", miTiempo->tm_mday, miTiempo->tm_mon+1, miTiempo->tm_year+1900); //Este apartado muestra el anio

    fprintf(archivo, "%d:%d:%d\t", miTiempo->tm_hour, miTiempo->tm_min, miTiempo->tm_sec); //Este apartado muestra la hora, minutos y segundos en el que se ingresaron los datos

    fprintf(archivo, "%s; %d; %.2f; %.2f; %.2f; %d; %.2f; %d; %.2f\n", paciente.nombre, paciente.edad, paciente.altura, paciente.peso, paciente.presionArterial,
    paciente.pulso, paciente.temperatura, paciente.frecuenciaRespiratoria, paciente.imc); //fprintf para imprimir los datos en el archivo plano.
    fclose(archivo); //fclose para cerrar el archivo.

}

void leerDatos(){ //Uso de función void para leer los datoa ingresados
    FILE *archivo;
    archivo = fopen("datosPacientes.csv", "r");
    struct Paciente paciente;
    printf("Nombre ; Edad ; Altura ; Peso ; PresionArterial ; Pulso ; Temperatura ; FrecuenciaRespiratoria ; IMC ;\n");
    printf("\n");
    while(fscanf(archivo, "%s %d %f %f %f %d %f %d %f\n", paciente.nombre, &paciente.edad, &paciente.altura, &paciente.peso, &paciente.presionArterial,
    &paciente.pulso, &paciente.temperatura, &paciente.frecuenciaRespiratoria, &paciente.imc) != EOF){//Se escanean los datos para que sean los correspondientes y se usa EOF(end-of-file) para el conteo de datos.
    printf("%s     ; %d   ; %f     ; %f   ; %f              ; %d    ; %f          ; %d                     ; %f  ;\n", paciente.nombre, paciente.edad, paciente.altura, paciente.peso, paciente.presionArterial,
    paciente.pulso, paciente.temperatura, paciente.frecuenciaRespiratoria, paciente.imc);
}
fclose(archivo);
}

void buscarDatos(char nombreBuscado[]){
    FILE *archivo;
    archivo = fopen("datosPacientes.csv", "r");
    struct Paciente paciente;
    int encontrado = 0;
    while(fscanf(archivo, "%s %d %f %f %f %d %f %d %f\n", paciente.nombre, &paciente.edad, &paciente.altura, &paciente.peso, &paciente.presionArterial,
    &paciente.pulso, &paciente.temperatura, &paciente.frecuenciaRespiratoria, &paciente.imc) != EOF){
        if(strcmp(paciente.nombre, nombreBuscado) == 0){
           printf("Nombre ; Edad ; Altura ; Peso ; PresionArterial ; Pulso ; Temperatura ; FrecuenciaRespiratoria ; IMC ;\n");
           printf("%s     ; %d   ; %f     ; %f   ; %f              ; %d    ; %f          ; %d                     ; %f  ;\n", paciente.nombre, paciente.edad, paciente.altura, paciente.peso, paciente.presionArterial,
           paciente.pulso, paciente.temperatura, paciente.frecuenciaRespiratoria, paciente.imc);
           encontrado = 1;
           break;

        }
    }
    if (!encontrado) {
        printf("Paciente no encontrado.\n");
    }
    fclose(archivo);
}

void borrarDatos(char nombreBorrar[]){ //Esta funcion es para borrar los datos de un paciente en especifico
    FILE *archivoEntrada;
    archivoEntrada = fopen("datos_pacientes.csv", "r");

    if (archivoEntrada == NULL) {
        printf("El archivo no existe o no se puede abrir.\n");
        return;
    }

    FILE *archivoTemporal;
    archivoTemporal = fopen("temp.csv", "w");

    if (archivoTemporal == NULL) {
        printf("Error al crear el archivo temporal.\n");
        fclose(archivoEntrada);
        return;
    }

    struct Paciente paciente;
    int encontrado = 0;

    while (fscanf(archivoEntrada, "%s %d %f %f %f %d %f %d\n", paciente.nombre, &paciente.edad, &paciente.altura, &paciente.peso, &paciente.presionArterial,
    &paciente.pulso, &paciente.temperatura, &paciente.frecuenciaRespiratoria, &paciente.imc) != EOF) {
        if (strcmp(paciente.nombre, nombreBorrar) != 0) {
            fprintf(archivoTemporal, "%s %d %.2f %.2f %.2f %d %.2f %d\n", paciente.nombre, &paciente.edad, &paciente.altura, &paciente.peso, &paciente.presionArterial,
    &paciente.pulso, &paciente.temperatura, &paciente.frecuenciaRespiratoria, &paciente.imc);
        } else {
            encontrado = 1;
        }
    }

    fclose(archivoEntrada);
    fclose(archivoTemporal);

    if (!encontrado) {
        printf("Paciente no encontrado.\n");
        remove("temp.csv");
        return;
    }

    remove("datos_pacientes.csv");
    rename("temp.csv","datos_pacientes.csv");
    printf("Paciente borrado exitosamente.\n");
}

float calcularMC(float peso, float altura){
    return peso/(altura*altura);
}

int main(){
    int opcion;
    struct Paciente paciente;
    time_t tiempoActual;

    do{//uso de ciclo do while para realizar el menu 
        printf("\n---- Menu ----\n");
        printf("1. Ingresar datos del paciente\n");
        printf("2. Mostrar todos los datos\n");
        printf("3. Buscar un paciente en la base de datos\n");
        printf("4. Borrar un paciente de la base de datos\n");
        printf("5. Actualizar datos de un paciente de su eleccion\n");
        printf("6. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        getchar();  // Limpiar el buffer del teclado

        switch (opcion){
         case 1:
                printf("\n---- Ingrese los datos del paciente ----\n");
                printf("Nombre: ");
                scanf("%s", paciente.nombre);
                printf("Edad: ");
                scanf("%d", &paciente.edad);
                printf("Altura (en metros): ");
                scanf("%f", &paciente.altura);
                printf("Peso (en kg): ");
                scanf("%f", &paciente.peso);
                printf("Presion: ");
                scanf("%f", &paciente.presionArterial);
                printf("Ritmo Cardiaco: ");
                scanf("%d", &paciente.pulso);
                printf("Temperatura: ");
                scanf("%f", &paciente.temperatura);
                printf("Frecuencia Respiratoria: ");
                scanf("%d", &paciente.frecuenciaRespiratoria);
                guardarDatos(paciente);
                printf("Datos guardados exitosamente.\n");
                break;
            case 2:
                leerDatos();
                break;
            case 3:
                printf("\n---- Buscar paciente ----\n");
                printf("Ingrese el nombre del paciente: ");
                scanf("%s", paciente.nombre);
                buscarDatos(paciente.nombre);
                break;
            case 4:
                printf("\n---- Borrar paciente ----\n");
                printf("Ingrese el nombre del paciente: ");
                scanf("%s", paciente.nombre);
                borrarDatos(paciente.nombre);
                break;
            case 5:
                printf("\n---- Actualizar paciente ----\n");
                printf("Ingrese el nombre del paciente: ");
                scanf("%s", paciente.nombre);
                buscarDatos(paciente.nombre);
                printf("\nIngrese el nuevo dato a actualizar:\n");
                printf("1. Edad\n");
                printf("2. Altura\n");
                printf("3. Peso\n");
                printf("4. Presión\n");
                printf("5. Ritmo Cardiaco\n");
                printf("6. Temperatura\n");
                printf("7. Frecuencia Respiratoria\n");
                printf("Ingrese el número de la opción: ");
                int opcionActualizar;
                scanf("%d", &opcionActualizar);
                getchar();  // Limpiar el buffer del teclado
                switch (opcionActualizar) {
                    case 1:
                        printf("Ingrese la nueva edad: ");
                        scanf("%d", &paciente.edad);
                        break;
                    case 2:
                        printf("Ingrese la nueva altura: ");
                        scanf("%f", &paciente.altura);
                        break;
                    case 3:
                        printf("Ingrese el nuevo peso: ");
                        scanf("%f", &paciente.peso);
                        break;
                    case 4:
                        printf("Ingrese la nueva presion: ");
                        scanf("%f", &paciente.presionArterial);
                        break;
                    case 5:
                        printf("Ingrese el nuevo ritmo cardiaco: ");
                        scanf("%d", &paciente.pulso);
                        break;
                    case 6:
                        printf("Ingrese la nueva temperatura: ");
                        scanf("%f", &paciente.temperatura);
                        break;
                    case 7:
                        printf("Ingrese la nueva frecuencia respiratoria: ");
                        scanf("%d", &paciente.frecuenciaRespiratoria);
                        break;
                    default:
                        printf("Opcion invalida.\n");
                        break;
                }
                borrarDatos(paciente.nombre);
                guardarDatos(paciente);
                printf("Paciente actualizado exitosamente.\n");
                break;
            case 6:
                printf("\nHa salido con exito del programa, vuelva pronto\n");
                break;
            default:
                printf("\nOpcion invalida. Por favor, seleccione una opcion valida.\n");
                break;
        }
    }while(opcion!=6);
}