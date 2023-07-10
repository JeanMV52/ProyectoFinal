#include<stdio.h> //Se incluye la librería estándar
#include<stdlib.h> //Esta librería se incluye para el uso de gets y puts, y la lectura de cadenas de caracteres.
#include<string.h> //Se incluye esta librería para cambiar caracteres y comparar cadenas.
#include<time.h> //Esta librería se agrega para poder añadir la fecha y hora del ingreso de datos.
struct Paciente{ //Estructura donde se guardan todos los datos que se registrarán.
    char nombre[50];
    int edad;
    float altura;
    float presionArterial;
    int pulso;
    float temperatura;
    int frecuenciaRespiratoria;
    float imc;
};

void guardarDatos(struct Paciente paciente){ //Se hace uso de la función void para que no se devuelva ningún valor, y toma el parámetro del struct que contiene los datos de los pacientes.
    FILE *archivo; //Usamos el archivo FILE para poder mover los datos a un archivo plano.
    archivo = fopen("datosPacientes.csv", "a");
    fprintf(archivo, "%s %d %.2f %.2f %.2f %d %.2f %d %.2f\n", paciente.nombre, paciente.edad, paciente.altura, paciente.presionArterial,
    paciente.pulso, paciente.temperatura, paciente.frecuenciaRespiratoria, paciente.imc); //fprintf para imprimir los datos en el archivo plano.
    fclose(archivo); //fclose para cerrar el archivo.

}
