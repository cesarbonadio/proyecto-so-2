//---------- LIBRERIAS ------------

#include <math.h>
#include "Estructura.h"


//--------- CABECERA DE MÉTODOS -------------

void manejarInterrupciones();
void manejarDemanda(int demanda);

void moverDerecha();
int falloDePagina();

int convertirBinarioToDecimal(int *binario);


int main(){

   printf("HOLA MUNDO \n\n");

   cargarArchivotxt("Entrada.txt");
   mostrarInterrupciones();

   printf("\n\n");

   iniciarTablaDePaginas(7);
   mostrarPaginas();

   manejarInterrupciones();
   mostrarPaginas();

   printf("\n\n SALIENDO \n");
      
   printf("\n\n");
   return 0;

}


void manejarInterrupciones(){

   InterrupcionesDeReloj *inter = interrupciones;

   while(inter != NULL){

      for(int i = 0; i < inter->cantDemandas; i++){

         manejarDemanda(inter->demanda[i]);

      }

      printf("\n");

      moverDerecha();
      mostrarPaginas();

      inter = inter->prox;

   }

}


void manejarDemanda(int demanda){

   TablaDePaginas *aux = tabla;

   while( (aux != NULL)&&(aux->numeroDePagina != demanda) )
      aux = aux->prox;

   if(aux != NULL){

      aux->bitR = 1;

      //Fallo de Página
      if(aux->enRAM == NO){

         aux->marcoDePagina = falloDePagina();
         aux->enRAM = SI;

      }

   }

}


void moverDerecha(){

   TablaDePaginas *aux = tabla;

   while(aux != NULL){

      for(int i = cantBits; i > 1; i--)
         aux->contador[i - 1] = aux->contador[i - 2];

      aux->contador[0] = aux->bitR;
      aux->bitR = 0;

      aux = aux->prox;

   }

}


int falloDePagina(){

   int valorMinimo, valorComparar, valorRetorno;
   TablaDePaginas *aux = tabla;
   TablaDePaginas *min = NULL;

   while(aux != NULL){

      /*En caso de que sea una pagina que tenga un marco de página asignado y no esté referenciada se puede quitar de la RAM*/ 
      if( (aux->bitR == 0)&&(aux->enRAM == SI) ){

         valorComparar = convertirBinarioToDecimal(aux->contador);

         if(min == NULL){
            min = aux;
            valorMinimo = valorComparar;
         }
         else
            if(valorComparar < valorMinimo){
              min = aux;
              valorMinimo = valorComparar;
            }

      }

       aux = aux->prox;
   }


   valorRetorno = min->marcoDePagina;

   //Inicializa la pagina con el contador menor
   min->enRAM = NO;
   min->marcoDePagina = 0;

   for(int i = 0; i < cantBits; i++)
      min->contador[i] = 0;

   return valorRetorno;

}


int convertirBinarioToDecimal(int *binario){

   int numAcum = 0, base = 2, exponente;

   for(int i = 0; i < cantBits; i++){

      if(binario[i] != 0){
         exponente = cantBits - i -1;
         numAcum = numAcum + pow(base,exponente);
      }

   }

   return numAcum;

}






