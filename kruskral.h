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

void inicial (tipo_nombre A, tipo_elemento x, conjunto_CE * C){
	(C->nombres[x]).nombre_conjunto = A;
	(C->nombres[x]).siguiente_elemento = 0;
	(C->encabezamientos_conjunto[A]).cuenta = 1;
	(C->encabezamientos_conjunto[A]).primer_elemento = x;
}

void combina (tipo_nombre A, tipo nombre B, conjunto_CE * C){
	int i = 1;
	if ((C->encabezamiento_conjunto[A]).cuenta) > (C<-encabezamiento_conjunto[B]).cuenta)){
		i = (C->encabezamiento_conjunto[B]).primer_elemento;
		do{
			(C->nombres[i]).nombre_conjunto = A;
			i = (C->nombres[i]).siguiente_elemento;
		} while ((C->nombres[i]).siguiente_elemento != 0 );
		(C->nombres[i]).nombre_conjunto = A ;
		(C->nombres[i]).siguiente_elemento = (C->encabezamientos_conjunto[A]).primer_elemento;
		(C->encabezamientos_conjunto[A]).primer_elemento = (C->encabezamientos_conjunto[B]).primer_elemento;
		(C->encabezamientos_conjunto[A]).cuenta = (C->encabezamientos_conjunto[A]).cuenta + (C->encabezamientos_conjunto[B]).cuenta;
	} else {
                i = (C->encabezamiento_conjunto[A]).primer_elemento;
                do{
                        (C->nombres[i]).nombre_conjunto = B;
                        i = (C->nombres[i]).siguiente_elemento;
                } while ((C->nombres[i]).siguiente_elemento != 0 );
                (C->nombres[i]).nombre_conjunto = B ;
                (C->nombres[i]).siguiente_elemento = (C->encabezamientos_conjunto[B]).primer_elemento;
                (C->encabezamientos_conjunto[B]).primer_elemento = (C->encabezamientos_conjunto[A]).primer_elemento;
                (C->encabezamientos_conjunto[B]).cuenta = (C->encabezamientos_conjunto[B]).cuenta + (C->encabezamientos_conjunto[A]).cuenta;
	}
}

tipo_nombre encuentra (int x, conjunto_CE * C){
	return ((C->nombres[x]).nombre_conjunto);
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

arista* sacar_min (rama** cabeza){
    arista* respuesta;
    respuesta = &((**cabeza).a);
    rama** aux = cabeza;
    *cabeza = (*cabeza)->sig;
    free(*aux);
}
