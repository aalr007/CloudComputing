// PruebaOMP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"      //comentado por que no tengo pre compiled headers
#include <iostream>
#include <omp.h>


#define N 2000          //cantidad de elementos a manejar en los arreglos
#define chunk 10       // tamaño que tendran los pedazos de los arreglos para que cada hilo creado se encargue de esta cantidad de elementos
#define mostrar 50      //Permitirá manejar la cantidad de datos a imprimir

void imprimeArreglo(float* d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];         //arreglos a y b para la suma, c el resultado
    int i;
    
    for (i =0; i<N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 2.5;
    }
    int pedazos = chunk;

    /* #pragma omp parallel for \ define que la instrucción for se realizará en paralelo por medio de las instrucciones de la librería OpenMP*/
    /*  shared(a,b,c,pedazos) private(i) \  indicarle que los arreglos estarán en un área de memoria compartida para que los diferentes hilos puedan accesar a los valores*/
    /*schedule(static, pedazos) finalmente estableces la planificación como estática y le indicas también el tamaño de los pedazos que debe tomar la planificación para cada hilo.*/

    #pragma omp parallel for \
    shared(a,b,c,pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    std::cout << "imprimiendo los primeros " << mostrar << " valores del arreglo a :" << std::endl;
        imprimeArreglo(a);
    std::cout << "imprimiendo los primeros " << mostrar <<" valores del arreglo b:" << std::endl;
        imprimeArreglo(b);
    std::cout << "imprimiendo los primeros " << mostrar <<" valores del arreglo c:" << std::endl;
        imprimeArreglo(c);

}

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
