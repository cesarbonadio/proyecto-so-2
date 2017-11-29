#include <string.h>



int maximo_caracter = 40; //tamaño maximo a leer en un string del archivo
int h[40];
int *bits_r_paginas; //para saber que pagina referenciar
//variables globales
int interrupciones; //para saber cuantos pulsos/interrupcciones de reloj




int lineas_en_archivo(char *path){ //cuenta las lineas de la entrada

   FILE *archivo;
   char caracter;
   int i = 0;

   archivo = fopen (path, "r");

   if (archivo==NULL){
    	printf("\n\nError. Archivo no existe\n\n");
        exit (-1);
   }
   else{
        while((caracter = fgetc(archivo)) != EOF){
		  if (caracter=='\n') i++;
	      }
	     fclose(archivo);
   }
  return (i);}




int convertir_string(char *cadena){ // esat funcion es para convertir la cadena y pasar todos los numeros al vector bit r

   printf ("\n\nEsta es la cadena : %s", cadena);
   int j=0;
   
  for (int i = 0; i < strlen(cadena)-1; i++){ // se recorre la cadena
   	 	

    if ((cadena[i]!=',')&&(cadena[i]!=' ')&&(cadena[i]!='\n')){

     	int numero_a_convertir;
     	
        int d1 = (int)cadena[i]-48;
        i++;


      if ((cadena[i]!=',')&&(cadena[i]!=' ')&&(cadena[i]!='\n')){
        int d2 = (int)cadena[i] - 48;
        numero_a_convertir = (d1*10)+d2;
      }

      else{
      	numero_a_convertir = d1;
      }


      bits_r_paginas[j]=numero_a_convertir;

  }
     /*printf("\n");*/ ++j;

    if(cadena[i]=='\n') break;

  }

  printf ("Este sería el vector de cuales referenciar:\n");

  for (int i = 0; i<16; i++){
  	if (bits_r_paginas[i]!=0)
  	printf ("\t %i", bits_r_paginas[i]);
  }

  for (int i = 0; i<16; i++){
  	bits_r_paginas[i]=0;
  }

}





int asignar_bit_r_paginas(char *path, int lineas){ // abre el archivo para leer cada linea

	FILE *archivo;
	char *caracter;
	caracter = malloc (sizeof(int)*maximo_caracter);
	/*el malloc es porque *caracter es un puntero a un string (cadena de chars)*/
	int i = 0;



	archivo = fopen (path, "r");

	if (archivo==NULL){
		printf("\n\nError. Archivo no existe\n\n");
		exit (-1);
	}


	else{

		 while(!feof(archivo)){ //mientras no se termine el archivo

                fgets(caracter,maximo_caracter,archivo);

          if (!feof(archivo)){


           convertir_string(caracter);
        }
      }

   fclose(archivo);
	
	}

 return 0;}
