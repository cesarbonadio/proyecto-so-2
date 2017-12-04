#include "Estructura.h"




int main(){

   printf("HOLA MUNDO \n\n");


   cargarArchivotxt("Entrada.txt");
   mostrarInterrupciones();

   printf("ENTRANDO \n");

   inicializarMarcoDePagina(6);
   mostrarMarcosDePagina();

   printf("SALIENDO \n");
      
   printf("\n\n");
   return 0;

}












