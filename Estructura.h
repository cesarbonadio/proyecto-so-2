// -------- LIBRERIAS ------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// -------- VARIABLES GLOBALES ---------

const int SI = 1;
const int NO = 0;

const int cantBits = 8;
const int maxPaginasVirtuales = 16;

const int maximoCaracteres = 50;
//Cantidad maxima de caracteres que se pueden leer


// ------- ESTRUCTURAS -----------

//Relacion entre las paginas virtuales y físicas
struct TablaDePaginas{

   int numeroDePagina;
   int enRAM;
   
   int marcoDePagina;
   int contador [cantBits];
   int bitR;

   TablaDePaginas *prox;

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



// ------- CABECERA DE MÉTODOS ---------

void cargarArchivotxt(const char *ubicacion);

void agregarInterrupcion(InterrupcionesDeReloj **p , char *demanda);
InterrupcionesDeReloj* agregarDemanda(char *demanda);

void iniciarTablaDePaginas(int cantDeMarcos);

void agregarPagina(TablaDePaginas **p, int demanda);
void inicializarPagina(TablaDePaginas **aux, int numPagina);
void agregarMarco(TablaDePaginas **aux, int numMarco, int pos);

void subString(char *cadenaDestino, char *cadenaFuente, int desde, int hasta);

void mostrarInterrupciones();


// --------- IMPLEMENTACIÓN ------------


void cargarArchivotxt(const char *ubicacion){

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

      //Libera recursos
      free(demanda);

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
   char *demandaToInt = new char;

   InterrupcionesDeReloj *aux = new InterrupcionesDeReloj;

   for(int i = 0; i < strlen(demanda); i++){ 

      numAcum = 0;

      //Toma un numero de la demanada
      while( (demanda[i]!=',')&&(demanda[i]!='\n') ){

         /*Es necesario usar esta función debido a que atoi solo acepta (char*) y no un (char), por lo que si se intenta usar paginasDemandadas[x] no lo permite la función atoi*/
         subString(demandaToInt,demanda,i,i);

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

   //Libera recursos
   free(demandaToInt);

   return aux;

}


void iniciarTablaDePaginas(int cantDeMarcos){

   //Inicializa la tabla de página sin marcos de pagina
   for(int i = 1; i <= maxPaginasVirtuales; i++)
      agregarPagina(&tabla,i);

   //Inicializa los marcos de página
   for(int j = 1; j <= cantDeMarcos; j++)
      agregarMarco(&tabla,j,j);


}


//NOTA: Se debe enviar el puntero x como NULL
void agregarPagina(TablaDePaginas **p, int numPagina){

   if( (*p) != NULL){

      //Se agrega una Nueva Página
      if( (*p)->prox == NULL){

         TablaDePaginas *aux = new TablaDePaginas;
         inicializarPagina(&aux, numPagina);

         //Se une la Nueva tabla de página a la estructura global de tablas
         (*p)->prox = aux;

      }
      else
         agregarPagina( &((*p)->prox), numPagina);
   }
   //Primera Página
   else{

      *p = new TablaDePaginas;
      inicializarPagina(p, numPagina);
     
   }

}


void inicializarPagina(TablaDePaginas **aux, int numPagina){

   (*aux)->numeroDePagina = numPagina;
   (*aux)->bitR = 0;
   (*aux)->enRAM = NO;
   (*aux)->marcoDePagina = 0;

   for(int i = 0; i < cantBits; i++)
      (*aux)->contador[i] = 0;

   //Sumamente importante colocarlo, de lo contrario, se hace mal el enlace de las estructuras
   (*aux)->prox = NULL;

}


void agregarMarco(TablaDePaginas **aux, int numMarco, int pos){

   TablaDePaginas *p = *aux;

   while( (p != NULL)&&( p->numeroDePagina != pos) )
      p = p->prox;

   if(p != NULL){
      p->marcoDePagina = numMarco;
      p->enRAM = SI;
   }

}


void subString(char *cadenaDestino, char *cadenaFuente, int desde, int hasta){

   int pos = 0;

   //En caso de que tanto la cadena de origen como la cadena de fuente sea diferente de NULL
   if( (cadenaFuente != NULL)&&(cadenaDestino != NULL) ){

      for(int i = desde; i <= hasta; i++){

         cadenaDestino[pos] = cadenaFuente[i];
         pos++;

      }

      cadenaDestino[pos] = '\0';

   }

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


























