#define VERTICES 15

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

void inicial            (tipo_nombre, tipo_elemento, conjunto_CE*); //Inicializa los valores del conjunto Combina Encuentra
void combina            (tipo_nombre, tipo_nombre, conjunto_CE*);   //Combina dos conjuntos en uno (previamente se debe verificar con encuentra
tipo_nombre encuentra   (int ,conjunto_CE*);                        //Devuelve el conjunto al que pertenecen dos elementos
void kruskal            (rama*, rama**, conjunto_CE*);              //Realiza el algoritmo de Kruskal inicializando con inicia, e iterando con combina-encuentra
void inserta            (int ,int ,int ,rama**);                    //Agrega una arista ordenada según su peso
void sacar_min          (rama**);                                   //Elimina el primer elemento de una lista enlazada.
void lista              (rama*);                                    //Imprime todo el grafo
void imprimeCE          (conjunto_CE*);                             //IMPRIME LA TABLA COMBINA ENCUENTRA
void imprimeEnTabla     (rama*);

void imprimeCE (conjunto_CE* C){
    printf("Encabezamiento conjuntos    --------------------           Nombres \n");
    printf("       Cuenta | 1er elemento--------------------    Nombre Conj.| Siguiente el.\n");

    for (int i=1; i<=VERTICES; i++){
        printf ("|%2d |   %2d    |   %2d    |   --------------------  |%2d |   %2d    |   %2d    |\n", i, C->encabezamientos_conjunto[i].cuenta, C->encabezamientos_conjunto[i].primer_elemento,i, C->nombres[i].nombre_conjunto ,C->nombres[i].siguiente_elemento );
    }
}

void inicial (tipo_nombre A, tipo_elemento x, conjunto_CE * C){
	(C->nombres[x]).nombre_conjunto = A;
	(C->nombres[x]).siguiente_elemento = 0;
	(C->encabezamientos_conjunto[A]).cuenta = 1;
	(C->encabezamientos_conjunto[A]).primer_elemento = x;
}

void kruskal (rama* cabeza, rama** arbol, conjunto_CE* componentes){
    for (int i=1; i<=VERTICES; i++){                //INICIALIZA LA TABLA COMBINA_ENCUENTRA
        inicial (i, i, componentes);
    }

    int it = 1; //Esta variable sólo sirve para imprimir el número de iteración.

    //Si hay algún elemento en la lista de prioridad
    while (cabeza != NULL){

        arista a = cabeza->a;                       //Arista toma el valor del primer elemento
        sacar_min(&cabeza);                         //Elimina el primer elemento (la funcion ahora es void) con esto cambia el puntero

        tipo_nombre comp_u = a.u;                   //comp_u y comp_v toman los valores de los vertices de la arista que estamos trabajando.
        tipo_nombre comp_v = a.v;
        comp_u = encuentra(comp_u, componentes);    //comp_u y comp_v toman el valor del conjunto al que pertenecen
        comp_v = encuentra(comp_v, componentes);

        printf ("\nIteraci\242n %d\n",it);
        it++;

        imprimeCE(componentes);                         //Imprime la tabla CE
        printf ("Toma la arista %d %d, costo %d:\n",a.u,a.v,a.costo);

        if (comp_u != comp_v){                          //si pertenecen a conjuntos distintos las une con combina()
    	    combina(comp_u, comp_v, componentes);
            inserta(a.u, a.v, a.costo, arbol);          //usa la función inserta pero ahora para armar otra cola con las aristas del arbol
            printf ("Inserta la arista %d %d: de los conjuntos %d y %d\n",a.u,a.v, comp_u, comp_v);
        }

    }

}


void combina (tipo_nombre A, tipo_nombre B, conjunto_CE * C){
	int i;

	if (((C->encabezamientos_conjunto[A]).cuenta) > ((C->encabezamientos_conjunto[B]).cuenta)){  //Si la cantidad de elementos de A es mayor a la de B
		i = (C->encabezamientos_conjunto[B]).primer_elemento;
		while ((C->nombres[i]).siguiente_elemento != 0 ) {  //itera hasta que no haya siguiente elemento, actualizando el nombre del conjunto en la tabla Nombre
			(C->nombres[i]).nombre_conjunto = A;
			i = (C->nombres[i]).siguiente_elemento;
		}

                                                            //Actualiza el resto de los valoes
		(C->nombres[i]).nombre_conjunto = A;
		(C->nombres[i]).siguiente_elemento = (C->encabezamientos_conjunto[A]).primer_elemento;
		(C->encabezamientos_conjunto[A]).primer_elemento = (C->encabezamientos_conjunto[B]).primer_elemento;
		(C->encabezamientos_conjunto[A]).cuenta = (C->encabezamientos_conjunto[A]).cuenta + (C->encabezamientos_conjunto[B]).cuenta;
		(C->encabezamientos_conjunto[B]).primer_elemento = 0;
		(C->encabezamientos_conjunto[B]).cuenta = 0;
	}else{
        i = (C->encabezamientos_conjunto[A]).primer_elemento;//Idem arriba pero para el caso B >= A
        while ((C->nombres[i]).siguiente_elemento != 0 ) {
            (C->nombres[i]).nombre_conjunto = B;
            i = (C->nombres[i]).siguiente_elemento;
            }
        (C->nombres[i]).nombre_conjunto = B ;
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

void inserta(int i, int j, int peso, rama** cabeza){    //Inserta arista en la cola de prioridad según su costo
    rama* nuevo = (rama*)malloc(sizeof(rama));          //Reserva memoria

    if (nuevo==NULL){
        printf("Error al reservar memorioa\n");
        free(nuevo);
    }
                                                        //Inicializa los valores de la arista (vértices y costo)
    nuevo->a.costo = peso;
    nuevo->a.u = i;
    nuevo->a.v = j;

                                                        //Busca el lugar en dónde insertar. Se analiza el caso particular en la que no hay primer elemento.
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

void lista (rama* cabeza){                              //Imprime todos los elementos de un grafo a partir de una lista enlazada
    if (cabeza==NULL){
        printf ("No hay ninguna arista en el grafo");
    }
    else{

        while (cabeza != NULL){
            printf ("Arista %d,%d de costo %d\n", cabeza->a.u, cabeza->a.v, cabeza->a.costo);
            cabeza=cabeza->sig;
        }
    }
}

void sacar_min (rama** cabeza){   //Elimina el primer elemento de una lista enlazada. En este caso la que contiene al grafo completo.
    rama* aux = *cabeza;
    *cabeza = (*cabeza)->sig;
    free(aux);
}





