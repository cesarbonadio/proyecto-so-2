#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

/*
 *
 * Ejercicio 2. Planificacion del disco (FIFO, SSTF, CSCAN)
 * Integrantes:
 * Miguel Ordoñez
 * César Bonadío
 *
*/
/*constantes*/
#define POSICION_INICIAL 11
#define CANTIDAD_CILINDROS 40

int ya_paso;

struct peticion{ //estructura de una peticion {cilindro a usar y peticion siguiente}
  int cilindro;
  int atendida; /*0 si no ha sido atendida, 1 si lo contrario*/
  peticion *prox;
};








peticion* crear(int x) {
    peticion *p = new peticion;
    p->cilindro = x;
    p->prox = NULL;
    p->atendida = 0;
    return p;}
void insertar_aleatorio(peticion **p){/*o encolar*/
 /*int n = rand()%(CANTIDAD_CILINDROS)+1;*/

   int n;
    scanf("%i",&n);


    if (!(*p)) {(*p)= crear(n);} // si no existe se crea

    else{ // si existe actua como una cola
      peticion *aux = (*p);
      peticion *aux2 = (*p);

        while (aux){
            aux2 = aux;
            aux = aux->prox;
        }
        aux = crear(n);
        aux2->prox = aux;
    }}
void mostrar (peticion *p){ /*muestra la cola*/
    if (p){
        printf("%i->", p->cilindro);
        mostrar(p->prox);
    }}
void reiniciar_atendidas(peticion *p){
    while (p){
        if (p->atendida==1) p->atendida = 0;
        p = p->prox;
    }}








int elmas_cercano_menor(peticion *aux, int posicion){

    int cercania;
    int cercania_actual=9999999;
    int mas_cercano=0;
    

    while (aux){

        if (((aux->atendida)==0)&&((aux->cilindro)<=posicion)){

             cercania = abs((aux->cilindro)-posicion);

             if (cercania < cercania_actual){
                cercania_actual = cercania;
                mas_cercano = aux->cilindro;
            }    
        }
      aux = aux->prox;
    }

    return mas_cercano;  
}//end

int elmas_cercano_mayor(peticion *aux, int posicion){

    int cercania;
    int cercania_actual=9999999;
    int mas_cercano=0;
    

    while (aux){

        if (((aux->atendida)==0)&&((aux->cilindro)>=posicion)){

             cercania = abs((aux->cilindro)-posicion);

             if (cercania < cercania_actual){
                cercania_actual = cercania;
                mas_cercano = aux->cilindro;
            }    
        }
      aux = aux->prox;
    }

    return mas_cercano;  
}//end

int elmas_cercano(peticion *aux, int posicion){

    int cercania;
    int cercania_actual=9999999;
    int mas_cercano=0;
    

    while (aux){

        if ((aux->atendida)==0){
             cercania = abs((aux->cilindro)-posicion);

             if (cercania < cercania_actual){
                cercania_actual = cercania;
                mas_cercano = aux->cilindro;
            }    
        }
      aux = aux->prox;
    }

    return mas_cercano;  
}//end


int elmas_lejano (peticion *aux, int posicion){


    int lejania;
    int lejania_actual=0;
    int mas_lejano=0;
    

    while (aux){

        if ((aux->atendida)==0){
             lejania = abs((aux->cilindro)-posicion);

             if (lejania > lejania_actual){
                lejania_actual = lejania;
                mas_lejano = aux->cilindro;
            }    
        }
      aux = aux->prox;
    }

    return mas_lejano;  
} //end





void fifo (peticion **p, peticion **aux){
  *aux = *p;
  int movimientos_brazo=0; //se inicia en 0 para ir contando cuantos brazos se tuvo que mover
  int movimiento;
  int posicion = POSICION_INICIAL;

  printf ("Las peticiones en orden son: ");

  while ((*aux)){
    printf ("%i|",(*aux)->cilindro);
    movimiento = abs(posicion-((*aux)->cilindro));
    movimientos_brazo+=movimiento;
    posicion = (*aux)->cilindro;
    (*aux)->atendida = 1;
    *aux = (*aux)->prox;
  }
 printf ("\nMovimientos del brazo en fifo: %i ", movimientos_brazo );
 *aux = NULL;
 }
void sstf(peticion **p, peticion **aux){
  *aux = *p;
  int movimientos_brazo=0; //se inicia en 0 para ir contando cuantos brazos se tuvo que mover
  int movimiento;
  int posicion = POSICION_INICIAL;
  int mas_cercano;


  printf ("Las peticiones en orden son: ");


  while (true){

    int mas_cercano = elmas_cercano((*aux),posicion);


      while ((*aux)){

        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            movimiento = abs(posicion-((*aux)->cilindro));
            movimientos_brazo+=movimiento;
            posicion = (*aux)->cilindro;
            (*aux)->atendida = 1;
        }

        (*aux)=(*aux)->prox;
      }

      (*aux) = *p;
     if (mas_cercano==0) break;
     
  }
 printf ("\nMovimientos del brazo en sstf: %i ", movimientos_brazo );
 *aux = NULL;
 }
void cscan(peticion **p, peticion **aux){


  *aux = *p;
  int movimientos_brazo=0; //se inicia en 0 para ir contando cuantos brazos se tuvo que mover
  int movimiento;
  int posicion = POSICION_INICIAL;
  int mas_cercano;


  if (ya_paso!=1) printf ("Les peticiones en orden son: ");

  mas_cercano = elmas_cercano((*aux),posicion);

  

   ya_paso=1;


  if (mas_cercano==posicion) {
      while ((*aux)){
        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            (*aux)->atendida = 1;
        }
        (*aux)=(*aux)->prox;
      
  }
  cscan((&*p), (&*aux));
}




  else if (mas_cercano<posicion){


     while (true){

        mas_cercano = elmas_cercano_menor((*aux),posicion);



      while ((*aux)){

        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            movimiento = abs(posicion-((*aux)->cilindro));
            movimientos_brazo+=movimiento;
            posicion = (*aux)->cilindro;
            (*aux)->atendida = 1;
        }

        (*aux)=(*aux)->prox;
      }

       (*aux) = (*p);
       if (mas_cercano==0) break;

     }



  
    mas_cercano = elmas_lejano((*aux),posicion);


  while (true){


      while ((*aux)){

        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            movimiento = abs(posicion-((*aux)->cilindro));
            movimientos_brazo+=movimiento;
            posicion = (*aux)->cilindro;
            (*aux)->atendida = 1;
        }
        (*aux)=(*aux)->prox;
      }
       (*aux) = (*p);
       if (mas_cercano==0) break;

       mas_cercano = elmas_cercano_menor((*aux),posicion);


     }


  }





  else if (mas_cercano>posicion){


     while (true){

        mas_cercano = elmas_cercano_mayor((*aux),posicion);




      while ((*aux)){

        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            movimiento = abs(posicion-((*aux)->cilindro));
            movimientos_brazo+=movimiento;
            posicion = (*aux)->cilindro;
            (*aux)->atendida = 1;
        }

        (*aux)=(*aux)->prox;
      }

       (*aux) = (*p);
       if (mas_cercano==0) break;

     }


     mas_cercano = elmas_lejano((*aux),posicion);

      while (true){

        
      while ((*aux)){

        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            movimiento = abs(posicion-((*aux)->cilindro));
            movimientos_brazo+=movimiento;
            posicion = (*aux)->cilindro;
            (*aux)->atendida = 1;
        }

        (*aux)=(*aux)->prox;
      }

       (*aux) = (*p);
       if (mas_cercano==0) break;
      
       mas_cercano = elmas_cercano_mayor((*aux),posicion);
     }

  }






  if (movimientos_brazo !=0) printf ("\nMovimientos del brazo en cscan: %i ", movimientos_brazo );

  *aux = NULL;

   
 
 } 



void scan(peticion **p, peticion **aux){


  *aux = *p;
  int movimientos_brazo=0; //se inicia en 0 para ir contando cuantos brazos se tuvo que mover
  int movimiento;
  int posicion = POSICION_INICIAL;
  int mas_cercano;


  if (ya_paso!=1) printf ("Les peticiones en orden son: ");

  mas_cercano = elmas_cercano((*aux),posicion);

  ya_paso=1;

  if (mas_cercano==posicion) {
      while ((*aux)){
        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            (*aux)->atendida = 1;
        }
        (*aux)=(*aux)->prox;
      }
      cscan((&*p), (&*aux));
  }




  else if (mas_cercano<posicion){


     while (true){

        mas_cercano = elmas_cercano_menor((*aux),posicion);



      while ((*aux)){

        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            movimiento = abs(posicion-((*aux)->cilindro));
            movimientos_brazo+=movimiento;
            posicion = (*aux)->cilindro;
            (*aux)->atendida = 1;
        }

        (*aux)=(*aux)->prox;
      }

       (*aux) = (*p);
       if (mas_cercano==0) break;

     }






  while (true){

    mas_cercano = elmas_cercano_mayor((*aux),posicion);

      while ((*aux)){

        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            movimiento = abs(posicion-((*aux)->cilindro));
            movimientos_brazo+=movimiento;
            posicion = (*aux)->cilindro;
            (*aux)->atendida = 1;
        }
        (*aux)=(*aux)->prox;
      }
       (*aux) = (*p);
       if (mas_cercano==0) break;
     }


  }





  else if (mas_cercano>posicion){


     while (true){

        mas_cercano = elmas_cercano_mayor((*aux),posicion);




      while ((*aux)){

        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            movimiento = abs(posicion-((*aux)->cilindro));
            movimientos_brazo+=movimiento;
            posicion = (*aux)->cilindro;
            (*aux)->atendida = 1;
        }

        (*aux)=(*aux)->prox;
      }

       (*aux) = (*p);
       if (mas_cercano==0) break;

     }


     


      while (true){

        mas_cercano = elmas_cercano_menor((*aux),posicion);


      while ((*aux)){

        if ((*aux)->cilindro == mas_cercano) {
            printf ("%i|",(*aux)->cilindro);
            movimiento = abs(posicion-((*aux)->cilindro));
            movimientos_brazo+=movimiento;
            posicion = (*aux)->cilindro;
            (*aux)->atendida = 1;
        }

        (*aux)=(*aux)->prox;
      }

       (*aux) = (*p);
       if (mas_cercano==0) break;

     }
   

  }

  


  if (movimientos_brazo !=0)printf ("\nMovimientos del brazo en cscan: %i ", movimientos_brazo );
  *aux = NULL;
 

 
 } 








int main (int argc, char *argv[]) {


   /*Forma de ejecutar el programa: 
   *./objeto -p [p] donde p es la cantidad de peticiones de e/s al disco duro*/
   peticion *peticiones = NULL;
   peticion *actual = NULL;
   int h[5];//vector h va a contener la cantidad de peticiones de entrada
   ya_paso=0;

   for (int i=1; i<argc; i++){ //de caracter a entero
    h[i]=atoi(argv[i]);}



   int cant_peticiones = h[2];     
   srand(time(NULL)); /* Inicializa el generador de numeros, sin esto, se generan siempre los mismos*/
   


   for (int i = 0; i<cant_peticiones; i++){
          insertar_aleatorio(&peticiones);
   }

    printf ("Estas son las peticiones de e/s:\n");
    mostrar(peticiones);
    printf ("\n\n\n");








    printf ("Ejecutando algoritmo FIFO:\n");
    fifo (&peticiones, &actual);
    reiniciar_atendidas(peticiones);




    printf ("\n\nEjecutando algoritmo SSTF:\n");
    sstf (&peticiones, &actual);
    reiniciar_atendidas(peticiones);



    printf ("\n\nEjecutando algoritmo CSCAN:\n");
    cscan(&peticiones, &actual);
    reiniciar_atendidas(peticiones);
    ya_paso=0;


    printf ("\n\nEjecutando algoritmo CSCAN:\n");
    scan(&peticiones, &actual);
    reiniciar_atendidas(peticiones);
    ya_paso=0;
    



    printf ("\n\n");
	return 0;
}
