#include "DynamicArray.h"
#include "Offer.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/// <summary>
/// function to create DynamicArray
/// </summary>
/// <param name="capacity">cpacity of the DynamicArray</param>
/// <param name="destroyElemFct">function to destroy the DynamicArray</param>
/// <returns>created DynamicArray</returns>
DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionType destroyElemFct)
{
	DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (da == NULL)
		return NULL;
	da->capacity = capacity;
	da->length = 0;
	da->elems = (TElement*)malloc(capacity * sizeof(TElement));
	if (da->elems == NULL)
		return NULL;
	da->destroyElemFct = destroyElemFct;
	return da;
}

/// <summary>
/// function to destroy DynamicArray
/// </summary>
/// <param name="arr">DynamicArray to destroy</param>
void destroy(DynamicArray* arr)
{
	if (arr == NULL)
		return;
	for (int i = 0; i < arr->length; i++)
		arr->destroyElemFct(arr->elems[i]);
	free(arr->elems);
	arr->elems = NULL;
	free(arr);
	arr = NULL;
}

/// <summary>
/// function to resize DynamicArray
/// </summary>
/// <param name="arr">DynamicArray to resize</param>
/// <returns>0 if DynamicArray was resized, -1 if there was a problem</returns>
int resize(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;
	arr->capacity *= 2;
	TElement* aux = (TElement*)malloc(arr->capacity * sizeof(TElement));
	if (aux == NULL)
		return -1;
	for (int i = 0; i < arr->length; i++)
		aux[i] = arr->elems[i];
	free(arr->elems);
	arr->elems = aux;
	return 0;
}

/// <summary>
/// function to add element to DynamicArray
/// </summary>
/// <param name="arr">DynamicArray to add to</param>
/// <param name="t">element to add</param>
void add(DynamicArray* arr, TElement t)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;
	if (arr->length == arr->capacity)
		resize(arr);
	arr->elems[arr->length++] = t;
}

/// <summary>
/// function to delete an element of DynamicArray
/// </summary>
/// <param name="arr">DynamicArray to delete element from</param>
/// <param name="pos">position to delete element</param>
void delete(DynamicArray* arr, int pos)
{
	if (arr == NULL || pos < 0 || pos >= arr->length)
		return;
	arr->destroyElemFct(arr->elems[pos]);
	if (pos != arr->length - 1)
		arr->elems[pos] = arr->elems[arr->length - 1];
	arr->length--;
}

/// <summary>
/// function to get length of DynamicArray
/// </summary>
/// <param name="arr">DynamicArray to get length of</param>
/// <returns>length found</returns>
int getLength(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;
	return arr->length;
}

/// <summary>
/// function to get an element of DynamicArray
/// </summary>
/// <param name="arr">DynamicArray to get element from</param>
/// <param name="pos">position to get element</param>
/// <returns>element found</returns>
TElement get(DynamicArray* arr, int pos)
{
	if (arr == NULL || pos < 0)
		return NULL;
	return arr->elems[pos];
}

/// <summary>
/// function to test DynamicArray
/// </summary>
void testDynamicArray()
{
	DynamicArray* d = createDynamicArray(CAPACITY, &destroy);
	assert(d != NULL);
	destroy(d);
}

/// <summary>
/// function to test resize
/// </summary>
void testResize()
{
	DynamicArray* d = createDynamicArray(CAPACITY, &destroy);
	assert(resize(d) == 0);
	destroy(d);
}

/// <summary>
/// function to test add
/// </summary>
void testAdd()
{
	DynamicArray* d = createDynamicArray(CAPACITY, &destroyOffer);
	assert(getLength(d) == 0);
	Offer* o = createOffer("type", "destination", "departure_date", 1);
	add(d, o);
	assert(getLength(d) == 1);
	destroy(d);
}

/// <summary>
/// function to test delete
/// </summary>
void testDelete()
{
	DynamicArray* d = createDynamicArray(CAPACITY, &destroyOffer);
	Offer* o = createOffer("type", "destination", "departure_date", 1);
	add(d, o);
	assert(getLength(d) == 1);
	delete(d, 0);
	assert(getLength(d) == 0);
	destroy(d);
}

/// <summary>
/// function to test getLength
/// </summary>
void testGetLength()
{
	DynamicArray* d = createDynamicArray(CAPACITY, &destroyOffer);
	Offer* o = createOffer("type", "destination", "departure_date", 1);
	add(d, o);
	assert(getLength(d) == 1);
	delete(d, 0);
	assert(getLength(d) == 0);
	destroy(d);
}

/// <summary>
/// function to test get
/// </summary>
void testGet()
{
	DynamicArray* d = createDynamicArray(CAPACITY, &destroyOffer);
	Offer* o = createOffer("type", "destination", "departure_date", 1);
	add(d, o);
	Offer* co = get(d, 0);
	assert(strcmp(co->type, "type") == 0);
	assert(strcmp(co->destination, "destination") == 0);
	assert(strcmp(co->departure_date, "departure_date") == 0);
	assert(co->price == 1);
	destroy(d);
}

/// <summary>
/// function to use all tests
/// </summary>
void testsDynamicArray()
{
	testDynamicArray();
	testResize();
	testAdd();
	testDelete();
	testGetLength();
	testGet();
}