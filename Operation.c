#include "Operation.h"
#include "Offer.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/// <summary>
/// function to create operation
/// </summary>
/// <param name="type">type of operation</param>
/// <param name="of">offer to use</param>
/// <returns>operation created</returns>
Operation* createOperation(opType type, Offer* of) {
	Operation* op = malloc(sizeof(Operation));
	if (op == NULL)
		return NULL;
	op->type = type;
	Offer* copyOfO = copyOffer(of);
	op->of = copyOfO;
	return op;
}

/// <summary>
/// function to destroy operation
/// </summary>
/// <param name="o">operation to destroy</param>
void destroyOperation(Operation* o) {
	if (o == NULL)
		return;
	destroyOffer(o->of);
	free(o);
}

/// <summary>
/// function to get type of operation
/// </summary>
/// <param name="o">operation to get type of</param>
/// <returns>type of operation</returns>
opType getOpType(Operation* o) {
	if (o == NULL)
		return -1;
	return o->type;
}

/// <summary>
/// function to get object of operation
/// </summary>
/// <param name="o">operation to get object of</param>
/// <returns>object of operation</returns>
Offer* getOpObject(Operation* o) {
	if (o == NULL)
		return NULL;
	return o->of;
}

/// <summary>
/// function to test Operation
/// </summary>
void testOperation()
{
	Offer* o = createOffer("type", "destination", "departure_date", 1);
	Operation* op = createOperation(ADD, o);
	assert(op != NULL);
	destroyOperation(op);
	destroyOffer(o);
}

/// <summary>
/// function to test getOpType
/// </summary>
void testGetOpType()
{
	Offer* o = createOffer("type", "destination", "departure_date", 1);
	Operation* op = createOperation(ADD, o);
	assert(getOpType(op) == ADD);
	destroyOperation(op);
	destroyOffer(o);
}

/// <summary>
/// function to test getOpObject
/// </summary>
void testgetOpObject()
{
	Offer* o = createOffer("type", "destination", "departure_date", 1);
	Operation* op = createOperation(ADD, o);
	Offer* co = getOpObject(op);
	assert(strcmp(co->type, "type") == 0);
	assert(strcmp(co->destination, "destination") == 0);
	assert(strcmp(co->departure_date, "departure_date") == 0);
	assert(co->price == 1);
	destroyOperation(op);
	destroyOffer(o);
}

/// <summary>
/// function to use all tests
/// </summary>
void testsOperation()
{
	testOperation();
	testGetOpType();
	testgetOpObject();
}
