#include <stdio.h>
#include <string.h>
#include "pila.h"
#include "cola.h"

// Para modelar un grafo
// 1.  matriz
// 2.  cuantos elementos tenemos en el grafo
// 3.  elementos - que significan las columnas/renglones para nosotros
#define MAX 20
#define TAM_CADENA 20

typedef struct
{
    char nombre[TAM_CADENA];
    int visitado;
} Vertice;

typedef struct
{
    int relaciones[MAX][MAX];
    Vertice elementos[MAX];
    int tam;
} Grafo;

void capturaGrafo(Grafo *grafo);
void recorridoEnProfundidad(Grafo *g, int indice);
void limpiarVisitados(Grafo *pGrafo);
void recorridoEnAmplitud(Grafo *pGrafo, int indice);

int main()
{
    Grafo grafo;
    Cola cola;

    capturaGrafo(&grafo);

    printf("\nRecorrido en Profundidad: ")
    recorridoEnProfundidad(&grafo, 2);
    printf("\nRecorrido en Amplitud: ");
    limpiarVisitados(&grafo);
    recorridoEnAmplitud(&grafo, 0);

    return 0; 
}

/*
    1.  Imprimir el valor inicial6
    2.  Meterlo en la cola
    3.  Marcarlo como visitado

    4. Hasta que no haya nada en la cola
        4.1 Sacar el elemento de la cola
        4.2 Revisar las relaciones de ese elemento
            4.2.1  Si la relación no fue visitada
                - Imprimir la relación
                - Meter en la cola
                - Marcar como visitada
*/

void recorridoEnAmplitud(Grafo *pGrafo, int indice) // indice nos dice donde iniciamos
{
    Cola cola;
    int indiceVertice, indiceRelacion;

    inicializaCola(&cola);

    printf("%s ", pGrafo->elementos[indice].nombre);
    ponDato(&cola, indice); 
    pGrafo->elementos[indice].visitado = 1;

    while(tieneDatos(cola) == 1) // !colaVacia(cola) 
    {
        indiceVertice = sacaDato(&cola);  // Obtenemos el vertice actual a revisar

        for(indiceRelacion = 0; indiceRelacion < pGrafo->tam; indiceRelacion++)
        {
            if(pGrafo->relaciones[indiceVertice][indiceRelacion] == 1) // Si hay relacion
            {
                if(pGrafo->elementos[indiceRelacion].visitado == 0) // Si no fue visitada
                {
                    printf("%s ", pGrafo->elementos[indiceRelacion].nombre);
                    ponDato(&cola, indiceRelacion);
                    pGrafo->elementos[indiceRelacion].visitado = 1;
                }
            }
        }
    }
}

void limpiarVisitados(Grafo *pGrafo)
{
    int i;

    for(i = 0; i < pGrafo->tam; i++)
    {
        pGrafo->elementos[i].visitado = 0;
    }
}

void recorridoEnProfundidad(Grafo *g, int indice)
{
    int indiceRelacion;

    printf("%s ", g->elementos[indice].nombre);
    g->elementos[indice].visitado = 1;

    for (indiceRelacion = 0; indiceRelacion < g->tam; indiceRelacion++)
    {
        if (g->relaciones[indice][indiceRelacion] == 1 && g->elementos[indiceRelacion].visitado == 0)
        {
            recorridoEnProfundidad(g, indiceRelacion);
        }
    }
}

void capturaGrafo(Grafo *grafo)
{
    int relacion;
    int i, j;

    // Preguntar de que tamaño será el grafo
    printf("Cuantos elementos tendrá el grafo?");
    scanf("%d", &grafo->tam);

    for (i = 0; i < grafo->tam; i++)
    {
        printf("Nombre del elemento %d: ", i);
        scanf("%s", (*grafo).elementos[i].nombre); // grafo->elementos[i]
        grafo->elementos[i].visitado = 0;
    }

    for (i = 0; i < grafo->tam; i++)
    {
        for (j = i; j < grafo->tam; j++)
        {
            printf("%s está relacionado con %s?\n", grafo->elementos[i].nombre, grafo->elementos[j].nombre);
            printf("\t1 si si, 0 si no: ");
            scanf("%d", &relacion);

            grafo->relaciones[i][j] = relacion;
            grafo->relaciones[j][i] = relacion;
        }
    }
}