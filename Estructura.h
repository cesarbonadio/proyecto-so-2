// -------- LIBRERIAS ------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// -------- VARIABLES GLOBALES ---------

const int SI = 1;
const int NO = 0;

const int cantBits = 8;
const char* abecedario = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";


// ------- ESTRUCTURAS -----------

//Relacion entre las paginas virtuales y físicas
struct TablaDePaginas{

   int numeroDePagina;
   int enRAM;
   char *marcoDePagina;

   TablaDePaginas *prox;

};


//Estructura que contiene lo contadores de las paginas que se encuentran en RAM
struct RAM{

   char *marcoDePagina; 
   int contador [cantBits];
   int bitR;

   RAM *prox;

};


//Structura que contiene las demandas de paginas virtuales
struct InterrupcionesDeReloj{

   int *demanda;
   int cantDemandas;

   InterrupcionesDeReloj *prox;

};


// ------- VARIABLES DE ESTRUCTURA ---------

TablaDePaginas *tabla = NULL;
InterrupcionesDeReloj *interrupciones = NULL;
RAM *memoria = NULL;



// ------- CABECERA DE MÉTODOS ---------

void cargarArchivotxt(const char *ubicacion);

void agregarInterrupcion(InterrupcionesDeReloj **p , char *demanda);
InterrupcionesDeReloj* agregarDemanda(char *demanda);

void inicializarMarcoDePagina(int cant);

char* subString(char *cadenaFuente, int desde, int hasta);

void mostrarInterrupciones();
void mostrarMarcosDePagina();



// --------- IMPLEMENTACIÓN ------------


void cargarArchivotxt(const char *ubicacion){

   const int maximoCaracteres = 50;
   //Cantidad maxima de caracteres que se pueden leer en una FILA desde el archivo txt

   char *demanda = new char;
   /*Se tiene que inicializar debido a que fgets debe recibir un puntero char inicializado,
de lo contrario, sale la alerta "Violación de segmento (`core' generado)" */

   FILE *archivo;
   archivo = fopen (ubicacion, "r");

   if (archivo == NULL){
      printf("ERROR en la apertura del archivo \n\n");
      exit(EXIT_FAILURE);
   }
   else{

      while(!feof(archivo)){

         fgets(demanda,maximoCaracteres,archivo);
         
         //Para evitar que el último registro se agregue dos veces
         if(!feof(archivo))
            agregarInterrupcion(&interrupciones,demanda);

      }

      fclose(archivo);

   }

}


//NOTA: Se debe enviar el puntero x como NULL
void agregarInterrupcion(InterrupcionesDeReloj **p , char *demanda){

   if( (*p) != NULL){

      //Se agrega una Nueva Interrupcion
      if( (*p)->prox == NULL){

         InterrupcionesDeReloj *aux = new InterrupcionesDeReloj;
         aux = agregarDemanda(demanda);

         //Se une la Nueva interrupción a la estructura global de interrupciones
         (*p)->prox = aux;

      }
      else
         agregarInterrupcion( &((*p)->prox), demanda);
   }
   //Primera Interrupción
   else{

      *p = new InterrupcionesDeReloj;
      *p = agregarDemanda(demanda);
     
   }

}


InterrupcionesDeReloj* agregarDemanda(char *demanda){

   int numAcum, posDemanda = 0;
   char *demandaToInt;

   InterrupcionesDeReloj *aux = new InterrupcionesDeReloj;

   for(int i = 0; i < strlen(demanda); i++){ 

      numAcum = 0;

      //Toma un numero de la demanada
      while( (demanda[i]!=',')&&(demanda[i]!='\n') ){

         /*Es necesario usar esta función debido a que atoi solo acepta (char*) y no un (char), por lo que si se intenta usar paginasDemandadas[x] no lo permite la función atoi*/
         demandaToInt = subString(demanda,i,i);

         numAcum = (numAcum * 10) + ( atoi(demandaToInt) );
         i++;

      }

      //Guardar valor de la demanda, si no existe (NULL) la crea
      if( aux->demanda == NULL )
         aux->demanda = new int;

      //Anexa el valor de la demanda
      aux->demanda[posDemanda] = numAcum;
      posDemanda++;  

   }

   //Se asigna la cantidad de páginas demandadas
   aux->cantDemandas = posDemanda;

   return aux;

}


void inicializarMarcoDePagina(int cant){

   RAM *aux = memoria;
   RAM *temp = new RAM;

   printf("--- 1 \n");

   char* abc = new char;
   strcpy(abc,abecedario);
   
   //Inicializa el contador
   for(int j = 0; j < cantBits; j++)
      temp->contador[j] = 0;

   //Inicializa el bit_R
   temp->bitR = 0;

   printf("--- 3 %s \n", abc);

   char *prueba = subString(abc,1,6);

   printf("--- 7 \n");
   temp->marcoDePagina = prueba;

   for(int i = 0; i < cant; i++){

      printf("--- 6 \n");

      printf("--- 5 \n");

      //temp->marcoDePagina = subString(abc,i,i);

      printf("--- 4 \n");

      //

      //aux = temp;
      //aux = aux->prox;

   }
   
   printf("--- 2 \n");

}


char* subString(char *cadenaFuente, int desde, int hasta){

   int pos = 0;
   char *cadenaDestino = new char;

   //En caso de que la cadena de origen sea NULL
   if(cadenaFuente != NULL){

      for(int i = desde; i <= hasta; i++){

         cadenaDestino[pos] = cadenaFuente[i];
         pos++;

      }

      cadenaDestino[pos] = '\0';

   }

   return cadenaDestino;

}


void mostrarInterrupciones(){

   InterrupcionesDeReloj *aux = interrupciones;

   printf("LISTA DE INTERRUPCIONES: \n");

   while(aux != NULL){

      for(int i = 0; i < aux->cantDemandas; i++){

         printf(" %i, ", aux->demanda[i]);

      }

      printf("\n");

      aux = aux->prox;

   }

}


void mostrarMarcosDePagina(){

   RAM *aux = memoria;

   printf("LISTA DE MARCOS DE PAGINA: \n");

   while(aux != NULL){

      printf("Marco de Pagina: %s \n", aux->marcoDePagina);

      for(int i = 0; i < cantBits; i++) 
         printf("%i", aux->contador[i]);

      printf("\nBitR: %i \n", aux->bitR);

      aux = aux->prox;

   }


}













