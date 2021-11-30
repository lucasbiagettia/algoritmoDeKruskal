#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kruskral.h"

int main (){

    int M_Costos [VERTICES][VERTICES];
    rama* arbol;
    
    for (int i=0; i <= VERTICES-1; i++){
        for ( int j= i+1; j < VERTICES; j++){
            printf ("Ingrese costo de lado entre vertices %d y %d:" ,i ,j);
            fflush(stdin);
            scanf ("%d", &M_Costos[i][j]);
        }
    }
	

    for (int i=0; i <= VERTICES-1; i++){
        for ( int j= i+1; j <= VERTICES -1; j ++){
            printf (" %d " , M_Costos[i][j]);
        }
        printf ("\n");
    }

    for (int i=0; i <= VERTICES -1; i ++){ // la mitad inf. de diagonal de matriz
        for ( int j = i +1; j <= VERTICES -1; j ++){
            if (M_Costos [i][j] !=0){
                inserta (i, j, M_Costos [i][j], &arbol); // inserto en cola prior.
            }
        }
    }

    lista (arbol);
    printf("----\n");
    sacar_min(&arbol);
    lista(arbol);
    //kruskal (arbol);
    
    return 0;

}
