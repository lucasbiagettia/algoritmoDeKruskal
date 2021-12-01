#define VERTICES 7 

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
    nombre nombres [VERTICES+1];
    encabezado encabezamientos_conjunto [VERTICES+1];
}conjunto_CE;

void inicial            (tipo_nombre, tipo_elemento, conjunto_CE*);
void combina            (tipo_nombre, tipo_nombre, conjunto_CE*);
tipo_nombre encuentra   (int ,conjunto_CE*);
void kruskal            (rama*, rama**, conjunto_CE*);
void inserta            (int ,int ,int ,rama**);                    //Hecha. Agrega al principio de una lista enlazada
void sacar_min       (rama**);
void lista              (rama*);                                    //Imprime todo el grafo
void imprimeCE          (conjunto_CE*);                             //IMPRIME LA TABLA COMBINA ENCUENTRA

void imprimeCE (conjunto_CE* C){
    printf("Encabezamiento conjuntos   --------------------   nombres \n");

    for (int i=1; i<=VERTICES; i++){
        printf ("|%d | |%d || %d |   --------                 |%d || %d || %d |\n", i, C->encabezamientos_conjunto[i].cuenta, C->encabezamientos_conjunto[i].primer_elemento,i, C->nombres[i].nombre_conjunto ,C->nombres[i].siguiente_elemento );

    }

}

void inicial (tipo_nombre A, tipo_elemento x, conjunto_CE * C){
	(C->nombres[x]).nombre_conjunto = A;
	(C->nombres[x]).siguiente_elemento = 0;
	(C->encabezamientos_conjunto[A]).cuenta = 1;
	(C->encabezamientos_conjunto[A]).primer_elemento = x;
}
void kruskal (rama* cabeza, rama** arbol, conjunto_CE* componentes){

    //INICIALIZA LA TABLA COMBINA_ENCUENTRA
    for (int i=1; i<=VERTICES; i++){
        inicial (i, i, componentes);
    }

    //SI HAY ALGUN ELEMENTO EN LA LISTA DE PRIORIDAD
    while (cabeza != NULL){

        arista a = cabeza->a;               //Arista toma el valor del primer elemento
        sacar_min(&cabeza);                 //Elimina el primer elemento (la funcion ahora es void) con esto cambia el puntero

        tipo_nombre comp_u = a.u;           //comp_u y comp_v toman los valores de los vertices de la arista que estamos trabajando.
        tipo_nombre comp_v = a.v;
        comp_u = encuentra(comp_u, componentes);    //comp_u y comp_v toman el valor del conjunto al que pertenecen
        comp_v = encuentra(comp_v, componentes);

        imprimeCE(componentes);

        if (comp_u!=comp_v){                    //si pertenecen a otro conjunto las une con combina()
    	    combina(a.u, a.v, componentes);
	    inserta(a.u, a.v, a.costo, arbol); //usa la función inserta pero ahora para armar otra cola con las aristas del arbol
            printf ("Inserta la arista %d %d:\n",a.u,a.v);
        }
        
    }
    
}


void combina (tipo_nombre A, tipo_nombre B, conjunto_CE * C){
	int i;
	if (((C->encabezamientos_conjunto[A]).cuenta) > ((C->encabezamientos_conjunto[B]).cuenta)){
		i = (C->encabezamientos_conjunto[B]).primer_elemento;
		while ((C->nombres[i]).siguiente_elemento != 0 ) {
			(C->nombres[i]).nombre_conjunto = A;
			i = (C->nombres[i]).siguiente_elemento;
		}
		(C->nombres[i]).nombre_conjunto = A;
		printf("(C->nombres[%d]).siguiente_elemento = (C->encabezamientos_conjunto[%d]).primer_elemento;\n",i,A);
		printf("sig elemento: %d\n",(C->encabezamientos_conjunto[A]).primer_elemento);
		(C->nombres[i]).siguiente_elemento = (C->encabezamientos_conjunto[A]).primer_elemento;
		(C->encabezamientos_conjunto[A]).primer_elemento = (C->encabezamientos_conjunto[B]).primer_elemento;
		(C->encabezamientos_conjunto[A]).cuenta = (C->encabezamientos_conjunto[A]).cuenta + (C->encabezamientos_conjunto[B]).cuenta;
		(C->encabezamientos_conjunto[B]).primer_elemento = 0;
		(C->encabezamientos_conjunto[B]).cuenta = 0;
	} else {
                i = (C->encabezamientos_conjunto[A]).primer_elemento;
                while ((C->nombres[i]).siguiente_elemento != 0 ) {
                        (C->nombres[i]).nombre_conjunto = B;
                        i = (C->nombres[i]).siguiente_elemento;
                }
                (C->nombres[i]).nombre_conjunto = B ;
		printf("(C->nombres[%d]).siguiente_elemento = (C->encabezamientos_conjunto[%d]).primer_elemento;\n",i,B);
                printf("sig elemento: %d\n",(C->encabezamientos_conjunto[B]).primer_elemento);
		(C->nombres[i]).siguiente_elemento = (C->encabezamientos_conjunto[B]).primer_elemento;
                (C->encabezamientos_conjunto[B]).primer_elemento = (C->encabezamientos_conjunto[A]).primer_elemento;
                (C->encabezamientos_conjunto[B]).cuenta = (C->encabezamientos_conjunto[B]).cuenta + (C->encabezamientos_conjunto[A]).cuenta;
		(C->encabezamientos_conjunto[A]).primer_elemento = 0;
		(C->encabezamientos_conjunto[A]).cuenta = 0;
	}
}

tipo_nombre encuentra (int x, conjunto_CE * C){
	return ((*C).nombres[x].nombre_conjunto);
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

void lista (rama* cabeza){
    if (cabeza==NULL){
        printf ("No hay ninguna arista en el grafo");
    }
    else{
        while (cabeza != NULL){
            printf ("Esta rama une %d con %d y su costo es %d\n", cabeza->a.u, cabeza->a.v, cabeza->a.costo);
            cabeza=cabeza->sig;
        }
    }
}

void sacar_min (rama** cabeza){
    rama* aux = *cabeza;
    *cabeza = (*cabeza)->sig;
    free(aux);
}

