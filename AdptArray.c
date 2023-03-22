#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

typedef struct AdptArray_{
    PElement *arr;
    int capacity;
    int size;

    DEL_FUNC del_func;
    COPY_FUNC copy_func;
    PRINT_FUNC print_func;

} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func){
    PAdptArray padpt = (PAdptArray) malloc(sizeof(AdptArray));
    if (!padpt)
    {
        return NULL;
    }

    PElement* arr = (PElement*)malloc(sizeof(PElement));
    if (!arr)
    {
        free(padpt);
        return NULL;
    }
    padpt->arr = arr;

    padpt->capacity = 1;
    padpt->size = 0;
    padpt->del_func = del_func;
    padpt->copy_func = copy_func;
    padpt->print_func = print_func;
    return padpt;
}

void DeleteAdptArray(PAdptArray padpt){
    if(padpt)
    {
        for (int i = 0; i < padpt->size ; i++)
        {
            if(padpt->arr[i])
            {
                padpt->del_func(padpt->arr[i]);
            }
        }
        free(padpt->arr);
        free(padpt);
    }
    return;
}

Result SetAdptArrayAt(PAdptArray padpt, int n, PElement pelem){
    if (padpt)
    {
        if (n < 0)
        {
            return FAIL;
        }
        else if (n < padpt->size)
        {
            if (padpt->arr[n])
            {
                padpt->del_func(padpt->arr[n]);
            }
            padpt->arr[n] = padpt->copy_func(pelem);
            return SUCCESS;
        }
        else if (n >= padpt->size)
        {
            int new_size = 2*n+1;
            PElement* new_pelement = (PElement*)realloc(padpt->arr, sizeof(PElement)*new_size);
            if (!new_pelement)
            {
                return FAIL;
            }
            for (int i = padpt->size; i < new_size; i++)
            {
                new_pelement[i] = NULL;
            }
            padpt->arr = new_pelement;
            padpt->size = new_size;
            padpt->arr[n] = padpt->copy_func(pelem);
            padpt->capacity = n+1;
            return SUCCESS;
        }
    }
    return FAIL;
}

PElement GetAdptArrayAt(PAdptArray padpt, int n){
    if(padpt && n >= 0 && n < padpt->capacity && padpt->arr[n] != NULL)
    {
        return padpt->copy_func(padpt->arr[n]);
    }
    return NULL;
}

int GetAdptArraySize(PAdptArray padpt){
    if (padpt)
    {
        return padpt->capacity;
    }
    return 0;
}

void PrintDB(PAdptArray padpt){
    if (padpt)
    {
        for (int i = 0; i < padpt->capacity ; i++)
        {
            if (padpt->arr[i])
            {
                padpt->print_func(padpt->arr[i]);
            }
        }

    }
}