#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "auxiliar.h"

int main(int argc, char * argv[]){
	argv0 = "bocabajo"; /* El valor de argv[0] será bocabajo, el nombre del programa. */
   int aux = 0; /* Valor auxiliar para saber si una entrada es argc == 1, y se salte la parte 
   de expandir la memoria (la parte central) */
   int i,j;  /* Variables para los bucles for*/
   int vistos = 0; /* esta variable aumenta con los numeros de lineas vistas */ 
   char palabra[2048];/* la palabras contienen 2048 caracteres, asi que creo un array con
   esa dimension */ 
   FILE *entrada; /*es el fichero que se nos da para invertir */
   char **puntero; /*es un puntero doble*/
  	
   if(argc == 1){  /* si arg es igual a 1 entramos en el if ya que hara un recorrido distinto que si es mayor que 1,
haciendo que se salte la parte central del codigo donde se establece la memoria, ya que no hace falta.*/
   	aux = 1;
    	entrada = stdin;
    	argc = 2;
    	}
  	else if(strcmp(argv[1], "-h") == 0|| strcmp(argv[1], "--help")==0){ /* como indica el enunciado respondo a -h y --help*/
     fprintf(stdout, "bocabajo: Uso: bocabajo [ fichero... ]\n");
	  fprintf(stdout, "bocabajo: Invierte el orden de las lineas de los ficheros (o de la entrada).\n");
	  return EX_OK;  
      }
      
   puntero = (char **) malloc(sizeof(2048)); /*asigno 2048 bites como indica el enunciado a la memoria dinamica*/
   
   if (puntero == NULL) { /* compruebo que la memoria se asigno correctamente*/
    Error(EX_OSERR, "No se puede leer"); 

  	}
  	else{

   for (i = 1; i < argc; i++) {/*uso un for para recorrerme todos los argc */

      if(aux == 0){ 
      entrada = fopen(argv[i], "rt"); /* abro el fichero para la lectura*/
      }

      if(entrada == NULL) { /* compruebo que es null la entrada y respondo a los errores derivados de que lo sea*/
      	if (strcmp(strerror(errno), "Permission denied")) {
          Error(EX_NOINPUT, ".*\"no_existe\"...");
          }
          else{
          Error(EX_NOINPUT, ".*\"no_legible\"...");
        }
      }
      else{ /* si la entrada no es null, entra aqui*/
      
      	while(fgets(palabra, 2048, entrada) != NULL) { /* bucle que se asegura que no haya vacio*/
          *(puntero + vistos) = (char *) malloc(2048* sizeof(char)); /*expando la memoria del array*/
          if (*(puntero + vistos) == NULL) { /* compruebo que la memoria se asigno correctamente*/
            Error(EX_OSERR, "No se puede leer");
          }
          else{
            strcpy(puntero[vistos], palabra); /*añado las palabras al array*/
            vistos++;
            puntero = (char **) realloc(puntero, vistos * (sizeof(palabra))); /* expando la memoria*/
            if(puntero == NULL){/* compruebo que la memoria se asigno correctamente*/
              Error(EX_OSERR, "No se puede leer");
            }
          }
        }
        if(aux == 0){ 
        fclose(entrada); /* cierro el fichero*/ 
        }
      }
    }
  }
  for (j = vistos - 1; j >= 0; j--) { /* hago un bucle para recorrer el array hacia atras y lo imprimo en orden invertido*/
    printf("%s", puntero[j]);
  }
  free(puntero); /* vacio la memoria*/
  return EX_OK;
}
