#include <unistd.h>
#include "Estructura.h"




int main(){

   printf("HOLA MUNDO \n\n");


   cargarArchivotxt("Entrada.txt");
   mostrarInterrupciones();

   printf("\n\n");

   iniciarTablaDePaginas(8);
   mostrarPaginas();

   printf("\n\n SALIENDO \n");








//----IMPLEMENTACION 5/12---------------

   printf("\n\n Hay %i interrupciones", cantidadInterrupciones());


   for (int i = 1; i <= cantidadInterrupciones(); i++){



      printf ("\nCon la interrupcion %i que viene dada por: \n", i);
      mostrarInterrupcion(i);










   	//printf ("\n\nSaliendo del tiempo %i", i); //sleep(1);
   }


//--------------------------------------





      
   printf("\n\n");
   return 0;

}












