#include <stdlib.h>
#include <stdio.h>

#include "cabecera1.c"

/*
 *
 * Ejercicio 1. Algoritmo de envejecimiento
 *
*/






int main () {

    int interrupcciones = lineas_en_archivo("Entrada.txt"); 
 

    /*Esto es solo una prueba para ver si cuenta las lineas bien*/
    printf ("\nEl archivo tiene %i lineas",interrupcciones); 
    printf ("\nEs decir, se van a trabajar con %i pulsos de reloj\n\n",interrupcciones);



    bits_r_paginas = malloc(16*sizeof(int)); // malloc del registro 
    
   

    /*for (int i = 0; i<n ; i++){
    	bits_r_paginas[i] =  1;
    }*/
    
    

    asignar_bit_r_paginas("Entrada.txt",interrupcciones);

    
    printf ("\n\n");
	return 0;
}
