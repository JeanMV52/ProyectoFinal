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
    fprintf(archivo, "%s %d %.2f %.2f %.2f %d %.2f %d %.2f\n", paciente.nombre, paciente.edad, paciente.altura, paciente.peso, paciente.presionArterial,
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
    archivoTemporal = fopen("temp.txt", "w");

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
        remove("temp.txt");
        return;
    }

    remove("datos_pacientes.txt");
    rename("temp.txt","datos_pacientes.txt");
    printf("Paciente borrado exitosamente.\n");
}
