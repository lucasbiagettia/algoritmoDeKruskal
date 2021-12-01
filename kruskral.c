#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kruskral.h"


int main (){

    int M_Costos [VERTICES+1][VERTICES+1];
    rama* grafo = NULL;
    rama* arbol = NULL;
    conjunto_CE componentes;

    for (int i=1; i <= VERTICES; i++){
        for ( int j= i+1; j <= VERTICES; j++){
            printf ("Ingrese costo de lado entre vertices %d y %d:" ,i ,j);
            fflush(stdin);
            //scanf ("%d", &M_Costos[i][j]);
            M_Costos[i][j] = (rand()%50)+1;
            printf ("%d", M_Costos[i][j]);
            printf("\n");
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
    printf("Hizo Kruskral\n");


    lista(arbol);

    return 0;

}
