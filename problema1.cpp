//---------- LIBRERIAS ------------

#include <math.h>
#include "Estructura.h"


/*Proyecto de sistemas de operacion (problema 1)
 * Integrantes:
 * - César Bonadío
 * - Miguel Ordoñez
 */


// -------- VARIABLES GLOBALES ---------
int numInterrupcion = 0;


//--------- CABECERA DE MÉTODOS -------------

void manejarInterrupciones();
void agregarBitR(int demanda);
void manejarDemanda(int demanda);

void moverDerecha();
int falloDePagina();

int convertirBinarioToDecimal(int *binario);

void guardarInterrupcion();


// ---------- IMPLEMENTACIÓN --------------

int main(){

   char *ruta = new char;
   int cantMarcos;

   printf("\nIngrese el nombre del archivo: ");
   scanf("%s", ruta);

   //Vacia Buffer
   fflush(stdin);

   printf("\nIngrese la cantidad de marcos de Pagina: ");
   scanf("%i", &cantMarcos);
   fflush(stdin);

   //Inicializa TODOS los procesos necesarios para comenzar el programa
   cargarArchivotxt(ruta);
   iniciarTablaDePaginas(cantMarcos);

   printf("\n");
   mostrarInterrupciones();

   manejarInterrupciones();
   printf("\n\n Se ha procesado la lista de interrupciones con EXITO!!! \n\n");

   free(ruta);

   return 0;

}


void manejarInterrupciones(){

   InterrupcionesDeReloj *inter = interrupciones;

   while(inter != NULL){

      //Agrega todos los bitR = 1
      for(int i = 0; i < inter->cantDemandas; i++)
         agregarBitR(inter->demanda[i]);

      //Maneja todos los fallos de página
      for(int i = 0; i < inter->cantDemandas; i++)
         manejarDemanda(inter->demanda[i]);

      moverDerecha();
      guardarInterrupcion();

      inter = inter->prox;

   }

}


void agregarBitR(int demanda){

   TablaDePaginas *aux = tabla;

   while( (aux != NULL)&&(aux->numeroDePagina != demanda) )
      aux = aux->prox;

   if(aux != NULL)
      aux->bitR = 1;

}


void manejarDemanda(int demanda){

   TablaDePaginas *aux = tabla;

   while( (aux != NULL)&&(aux->numeroDePagina != demanda) )
      aux = aux->prox;

   //Fallo de Página
   if( (aux != NULL)&&(aux->enRAM == NO) ){

      aux->marcoDePagina = falloDePagina();
      aux->enRAM = SI;

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


void guardarInterrupcion(){

   FILE *archivo;
   archivo = fopen ("Salida.txt", "a");

   if (archivo == NULL){
      printf("ERROR en la apertura del archivo \n\n");
      exit(EXIT_FAILURE);
   }
   else{

      TablaDePaginas *aux = tabla;
      
      char *impresion = new char;
      int size = 15;

      numInterrupcion++;
      snprintf(impresion,size,"%d",numInterrupcion);

      fputs("               INTERRUPCION # ", archivo);
      fputs(impresion, archivo);
      fputs("\n", archivo);

      fputs("NUMERO DE PAGINA / CONTADOR / MARCO DE PAGINA \n", archivo);

      while(aux != NULL){

         //Convierte una variable tipo int en char, guardandola en una variable temporal
         snprintf(impresion,size,"%d",aux->numeroDePagina);

         fputs("       ", archivo);
         fputs(impresion, archivo);
         fputs("          ", archivo);

         if(aux->enRAM == 1){

            if(aux->numeroDePagina < 10)
               fputs(" ", archivo);

            for(int i = 0; i < cantBits; i++){

               snprintf(impresion,size,"%d",aux->contador[i]);
               fputs(impresion, archivo);
            }

            
            fputs("         ", archivo);
            snprintf(impresion,size,"%d",aux->marcoDePagina);
            fputs(impresion, archivo);

         }
         else
            if(aux->numeroDePagina < 10)
               fputs("   ----          --- ", archivo);
            else
               fputs("  ----          --- ", archivo);

         fputs("\n",archivo);

         aux = aux->prox;

      }

      fputs("\n----------------------------------------------\n",archivo);
      free(impresion);

      fclose(archivo);

   }


}




