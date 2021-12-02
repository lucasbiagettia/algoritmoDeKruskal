#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "kruskral.h"

int main (){

    int M_Costos [VERTICES+1][VERTICES+1];
    rama* grafo = NULL;
    rama* arbol = NULL;
    conjunto_CE componentes;

    srand(getpid());
    int opcion = 0;

    do {
    	printf("Ingrese 1 para ingresar los valores manualmente o 2 para ingresar los valores de forma aleatoria: ");
        fflush(stdin);
        scanf ("%d",&opcion);
    } while ((opcion != 1) && (opcion !=2));


    for (int i=1; i <= VERTICES; i++){
	for ( int j= i+1; j <= VERTICES; j++){
            printf ("Ingrese costo de lado entre vertices %d y %d:" ,i ,j);
            fflush(stdin);
            if (opcion == 1){
	    	scanf ("%d", &M_Costos[i][j]);
	    } else if (opcion == 2) {
		M_Costos[i][j] = (rand()%50)+1;
            	printf ("%d \n", M_Costos[i][j]);
	    }
        }
    }

    for (int i=1; i <= VERTICES ; i ++){ // la mitad inf. de diagonal de matriz
        for ( int j = i +1; j <= VERTICES ; j ++){
            if (M_Costos [i][j] !=0){
                inserta (i, j, M_Costos [i][j], &grafo); // inserto en cola prior.
            }
        }
    }

    for (int i=1; i<=VERTICES; i++){
        inicial (i, i, &componentes);
    }

    imprimeCE(&componentes);

    lista (grafo);
    printf("----\n");


    kruskal(grafo, &arbol, &componentes);
    printf("Algoritmo de Kruskral finalizado\n");

    lista(arbol);

    return 0;

}
