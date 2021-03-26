#include <stdlib.h>
#include<string.h>
#define SUM_VOID(array, nrBits) ((void*)(((char*)array)+(nrBits)))
#define SUB_VOID(array, nrBits) (void*(((char*)array)-(nrBits)))

/*va dato in in input il puntatore all'array, una funzione di tipo (*void, *void) che 
ritorna 1 se il primo elem > secondo elem, -1 se il primo elem < secondo elem, e 0 se sono uguali,
la dimensione di un singolo elemento dell'array e il nr di elementi dell'array*/
void sort(void* array,int (*compare)(void*,void*), int dimElem, int nrElem);