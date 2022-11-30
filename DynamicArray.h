#pragma once
#define CAPACITY 10

typedef void* TElement;

typedef void (*DestroyElementFunctionType)(void*);

typedef struct
{
	TElement* elems;
	int length;			
	int capacity;		
	DestroyElementFunctionType destroyElemFct; 
} DynamicArray;

DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElemFct);

void destroy(DynamicArray* arr);

void add(DynamicArray* arr, TElement t);

void delete(DynamicArray* arr, int pos);

int getLength(DynamicArray* arr);

TElement get(DynamicArray* arr, int pos);

void testsDynamicArray();
