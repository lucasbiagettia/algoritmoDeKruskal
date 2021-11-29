#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kruskral.h"
#define VERTICES 5

typedef int tipo_nombre;
typedef int tipo_elemento;
typedef int vertice;

typedef struct _ARISTA{
    vertice u;
    vertice v;
    int costo;
}arista;

typedef struct _RAMA{
    struct _ARISTA a;
    struct _RAMA* sig;
}rama;

typedef struct _ENCABEZADO{
    int cuenta;
    int primer_elemento;
} encabezado;

typedef struct _NOMBRE{
    tipo_nombre nombre_conjunto;
    int siguiente_elemento;
}nombre;

typedef struct _CONJUNTO_CE{
    nombre nombres [VERTICES];
    encabezado encabezamientos_conjunto [VERTICES];
}conjunto_CE;

void inicial            (tipo_nombre, tipo_elemento, conjunto_CE*);
void combina            (tipo_nombre, tipo_nombre, conjunto_CE*);
tipo_nombre encuentra   (int ,conjunto_CE*);
void kruskal            (rama*);
void inserta            (int ,int ,int ,rama**);                    //Hecha. Agrega al principio de una lista enlazada
arista* sacar_min       (rama**);
void lista              (rama*);                                    //Imprime todo el grafo

int main (){

    int M_Costos [VERTICES][VERTICES]; // ya no me gusta cómo está definida esta matriz
    rama* arbol = (rama*) malloc (sizeof(rama));
    if (arbol==NULL){
        printf ("Error, no se ha podido reservar memoria\n");
        free (arbol);
    }
    for (int i=0; i <= VERTICES-1; i++){
        for ( int j= i+1; j <= VERTICES -1; j ++){
            printf ("Ingrese costo de lado entre vertices %d y %d:" ,i+1 ,j+1);
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
    //kruskal (arbol);
    return 0;

}

void inserta(int i, int j, int peso, rama** cabeza){
    rama* nuevo = (rama*)malloc(sizeof(rama));

    if (nuevo==NULL){
        printf("Error al reservar memorioa\n");
        free(nuevo);
    }

    nuevo->a.costo = peso;
    nuevo->a.u = i;
    nuevo->a.v = j;

    if ((*cabeza) == NULL){
        nuevo->sig = NULL;
        (*cabeza) = nuevo;
    }else if ((*cabeza) != NULL){

        rama* aux = *cabeza;
        rama* anterior;

        if (peso <= (*cabeza)->a.costo){
            nuevo -> sig = aux;
            (*cabeza) = nuevo;
        }else{
            while ((aux!= NULL) && (peso > aux->a.costo)){
                anterior = aux;
                aux = aux->sig;
            }
            nuevo->sig = aux;
            anterior->sig = nuevo;
        }
    }
}

void lista (rama* arbol){
    if (arbol==NULL){
        printf ("No hay ninguna arista en el grafo");
    }
    else{
        arbol=arbol->sig;
        while (arbol!=NULL){
            printf ("Esta rama une %d con %d y su costo es %d\n", arbol->a.u+1, arbol->a.v+1, arbol->a.costo);
            arbol=arbol->sig;
        }
    }
}
