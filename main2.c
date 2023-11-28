#include "string.h"
#include <stdlib.h>
#include <stdio.h>
int const dim = 10;
typedef struct { 
   char animal[30];
   int cant;
   int habitat;
   int idEspecie;               
   char especie[20];	 
} registroArchivo; 

typedef struct { 
      char nombreAnimal [30];
	int cantidad;
	int habitat;
// 1 - selva, 2- savana, 3-bosque, 4-mar
} animal;

typedef struct nodoArbol
{
   animal dato;	 
   struct nodoArbol * izquierda;
   struct nodoArbol * derecha;
} nodoArbol;

typedef struct
{
   int idEspecie;
   char especie [20];
 	 // "Mamiferos", "Aves"
       // "Reptiles", "Peces",”Anfibios”
   nodoArbol * arbolDeAnimales;  
} celdaEspecie; 

///PROTOTIPADO DE FUNCION PARA MOSTRAR EL ARCHIVO DE ANIMALES.DAT
void mostrarArchivoAnimales();

///PROTOTIPADO DE FUNCIONES PARA EL MANEJO DE ARBOLES
nodoArbol* inicArbol();
nodoArbol* crearNodoArbol(char nombreAnimal[],int cantidad, int habitat);
nodoArbol* insertarArbol(nodoArbol* arbol, nodoArbol* nuevoNodo);
void inorden(nodoArbol* arbol);
void escribir(nodoArbol* aux);

///PROTOTIPADO DE FUNCIONES PARA EL MANEJO DE ESTRUCTURAS COMPUESTAS
int agregarAnimales(celdaEspecie arreglo[], int dimension);
int alta(celdaEspecie arreglo[], char animal[], int cantidad, int habitat, int idEspecie, char especie[], int validos);
int agregarEspecie(celdaEspecie arreglo[], char especie[], int validos);
int buscarPosEspecie(celdaEspecie arreglo[], char especie[], int validos);
void pasarDeArchivoToADA(celdaEspecie arreglo[], int validos) ;
void guardarEnArchivo(nodoArbol* arbol, int idEspecie, const char especie[], FILE* archivo);
void pasarADAtoArchivo(celdaEspecie arreglo[], int validos) ;


int main(){
    nodoArbol* arbol = inicArbol();
celdaEspecie arreglo[dim];
int validos = 0;
// mostrarArchivoAnimales();
validos = agregarAnimales(arreglo, 10);

pasarDeArchivoToADA(arreglo, validos);
inorden(arbol);



return 0;
}



///funcion para mostrar el archivo de animales.dat
void mostrarArchivoAnimales(){
    FILE* archi;
    registroArchivo animales;
    archi = fopen("animales.dat", "rb");
    if(archi!=NULL){
        while(fread(&animales,sizeof(registroArchivo),1,archi)==1){
            printf("Animal: %s\n",animales.animal);
                        printf("Cantidad: %d\n",animales.cant);
                        printf("Habitat: %d\n",animales.habitat);
                        printf("Especie: %d\n",animales.idEspecie); 
                        printf("Especie: %s\n",animales.especie);
                        printf("\n");
        }
        fclose(archi);
    }
}

///funciones arboles

nodoArbol * inicArbol(){
    return NULL;
}

nodoArbol * crearNodoArbol(char nombreAnimal[],int cantidad, int habitat){
    nodoArbol * aux = (nodoArbol *) malloc(sizeof(nodoArbol));
strcpy(aux->dato.nombreAnimal ,nombreAnimal);
    aux->dato.cantidad = cantidad;
    aux->dato.habitat = habitat;
    aux->izquierda = NULL;
    aux->derecha = NULL;

    return aux;
}
nodoArbol * insertarArbol(nodoArbol * arbol, nodoArbol* nuevoNodo){
    if(arbol==NULL){
        arbol = nuevoNodo;
    }else{
        if(nuevoNodo->dato.cantidad<arbol->dato.cantidad){
            insertarArbol(arbol->izquierda, nuevoNodo);
        }else{
            insertarArbol(arbol->derecha, nuevoNodo);
        }
    }
    return arbol;
}


///funciones estructras compuestas
int agregarAnimales(celdaEspecie arreglo[], int dimension){
char animal[30];
int cantidad;
int habitat;
int idEspecie;
char especie[30];
char eleccion = 's';
int validos = 0;

while(eleccion == 's' && validos<dimension){
    printf("Ingrese el nombre del animal: ");
    scanf("%s",animal);
    printf("Ingrese la cantidad del animal: ");
    scanf("%d",&cantidad);
    printf("Ingrese el habitat del animal: ");
    scanf("%d",&habitat);
    printf("Ingrese el id de la especie del animal: ");
    scanf("%d",&idEspecie);
    printf("Ingrese el nombre de la especie del animal: ");
    scanf("%s",especie);
validos = alta(arreglo,animal,cantidad,habitat,idEspecie,especie,validos);
   printf("Ingrese s si desea cargar otro animal: ");
   fflush(stdin);
   scanf(" %c",&eleccion);
}

return validos;
}


int alta(celdaEspecie arreglo[], char animal[], int cantidad, int habitat, int idEspecie, char especie[], int validos){
    nodoArbol* aux = crearNodoArbol(animal,cantidad,especie);
    int pos = buscarPosEspecie(arreglo,especie,validos);
    if(pos==-1){
        validos=agregarEspecie(arreglo,especie,validos);
        pos=validos-1;
    }
    arreglo[pos].arbolDeAnimales=insertarArbol(arreglo[pos].arbolDeAnimales, aux);
    return validos;
}


int agregarEspecie(celdaEspecie arreglo[], char especie[], int validos){
    strcpy(arreglo[validos].especie, especie);
    ///copio la especie en el arreglo
    arreglo[validos].arbolDeAnimales = inicArbol();
    ///inicializo el arbol de esa especie agregada
    validos++;
    ///incremento la cantidad de especies en el arreglo

    return validos;
}

int buscarPosEspecie(celdaEspecie arreglo[], char especie[], int validos){
    int rta = -1;
    int i = 0;
    while((i<validos) && (rta==-1)){
        if(strcmp(arreglo[i].especie,especie)==0){
            rta = i;
        }
        i++;

        return rta;
    }
}

void pasarDeArchivoToADA(celdaEspecie arreglo[], int validos) {
    FILE *archivo;
    registroArchivo auxRegistro;
    archivo = fopen("animales.dat", "rb");
int i = 0;
    if (archivo != NULL) {
        for (i = 0; i < validos; i++) {
            nodoArbol* auxArbol = arreglo[i].arbolDeAnimales;  // Se cambió el nombre de la variable
            while (fread(&auxRegistro, sizeof(registroArchivo), 1, archivo) == 1) {
                nodoArbol* nuevoNodo = (nodoArbol*)malloc(sizeof(nodoArbol));
                strcpy(nuevoNodo->dato.nombreAnimal, auxRegistro.animal);
                nuevoNodo->dato.cantidad = auxRegistro.cant;
                nuevoNodo->dato.habitat = auxRegistro.habitat;
                auxArbol = insertarArbol(auxArbol, nuevoNodo);
           
            }
                 arreglo[i].idEspecie = auxRegistro.idEspecie;
                strcpy(arreglo[i].especie,auxRegistro.especie);
        }
        

        fclose(archivo);
    }
}


void inorden(nodoArbol* arbol) {
    if(arbol!=NULL){
        inorden(arbol->izquierda);
        escribir(arbol);
        inorden(arbol->derecha);

    }

}

void escribir(nodoArbol* aux){
    puts("--------------------------------------------\n");
    printf("NOMBRE DEL ANIMAL: %s", aux->dato.nombreAnimal);
    printf("CANTIDAD: %d ", aux->dato.cantidad);
    printf("HABITAT: %d ", aux->dato.habitat);
    puts("---------------------------------------------");
}


void pasarADAtoArchivo(celdaEspecie arreglo[], int validos) {
    FILE *archi;
    registroArchivo animales;
    archi = fopen("especies.bin", "wb");

    if (archi != NULL) {
        for (int i = 0; i < validos; i++) {
            // Obtener el árbol de la especie actual
            nodoArbol *aux = arreglo[i].arbolDeAnimales;

            // Llamar a la función para escribir en el archivo
            guardarEnArchivo(aux, arreglo[i].idEspecie, arreglo[i].especie, archi);
        }

        fclose(archi);
    }
}

void guardarEnArchivo(nodoArbol* arbol, int idEspecie, const char especie[], FILE* archivo) {
    if (arbol != NULL) {
        // Recorrer el subárbol izquierdo
        guardarEnArchivo(arbol->izquierda, idEspecie, especie, archivo);

        // Guardar en el archivo
        registroArchivo animales;
        strcpy(animales.animal, arbol->dato.nombreAnimal);
        animales.cant = arbol->dato.cantidad;
        animales.habitat = arbol->dato.habitat;
        animales.idEspecie = idEspecie;
        strcpy(animales.especie, especie);
        fwrite(&animales, sizeof(registroArchivo), 1, archivo);

        // Recorrer el subárbol derecho
        guardarEnArchivo(arbol->derecha, idEspecie, especie, archivo);
    }
}


