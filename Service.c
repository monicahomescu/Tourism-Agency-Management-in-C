#include "Service.h"
#include "Operation.h"
#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/// <summary>
/// function that creates a service
/// </summary>
/// <param name="r">repo to use</param>
/// <returns>created service</returns>
Service* createService(OfferRepo* r)
{
	Service* s = (Service*)malloc(sizeof(Service));
	if (s == NULL)
		return NULL;
	s->repo = r;
	s->undoStack = createDynamicArray(10, &destroyOperation);
	s->redoStack = createDynamicArray(10, &destroyOperation);
	return s;
}

/// <summary>
/// function that destroyes a service
/// </summary>
/// <param name="s">service to destroy</param>
void destroyService(Service* s)
{
	destroyRepo(s->repo);
	destroy(s->undoStack);
	destroy(s->redoStack);
	free(s);
}

/// <summary>
/// function to get repository
/// </summary>
/// <param name="s">service to get repo from</param>
/// <returns>repo of service</returns>
OfferRepo* getRepo(Service* s)
{
	return s->repo;
}

/// <summary>
/// function to add an offer
/// </summary>
/// <param name="s">service to add to</param>
/// <param name="type">type of offer to add</param>
/// <param name="destination">destination of offer to add</param>
/// <param name="departure_date">departure date of offer to add</param>
/// <param name="price">price of offer to add</param>
/// <returns>1 if offer was added, 0 otherwise</returns>
int addOfferServ(Service* s, char* type, char* destination, char* departure_date, double price)
{
	Offer* o = createOffer(type, destination, departure_date, price);
	int res = addOffer(s->repo, o);
	if (res == 0)
	{
		Operation* op1 = createOperation(ADD, o);
		if (op1 == NULL)
			return -1;
		add(s->undoStack, op1);
		destroy(s->redoStack);
		s->redoStack = createDynamicArray(10, &destroyOperation);
	}
	return res;
}

/// <summary>
/// function to delete an offer
/// </summary>
/// <param name="v">service to delete from</param>
/// <param name="destination">destination of offer to delete</param>
/// <param name="departure_date">departure date of offer to delete</param>
/// <returns>1 if offer was deleted, 0 otherwise</returns>
int deleteOfferServ(Service* s, char* destination, char* departure_date)
{
	Offer* o = findByDestinationDepartureDate(s->repo, destination, departure_date);
	Operation* op1 = createOperation(DELETE, o);
	if (op1 == NULL)
		return -1;
	add(s->undoStack, op1);
	destroy(s->redoStack);
	s->redoStack = createDynamicArray(10, &destroyOperation);
	return deleteOffer(s->repo, destination, departure_date);
}

/// <summary>
/// function to update an offer
/// </summary>
/// <param name="v">service to update in</param>
/// <param name="destination">destination of offer to update</param>
/// <param name="departure_date">departure date of offer to update</param>
/// <param name="o">offer to update with</param>
/// <returns>1 if offer was updated, 0 otherwise</returns>
int updateOfferServ(Service* s, Offer* o)
{
	Offer* of = findByDestinationDepartureDate(s->repo, o->destination, o->departure_date);
	Operation* op1 = createOperation(UPDATE, of);
	if (op1 == NULL)
		return -1;
	add(s->undoStack, op1);
	destroy(s->redoStack);
	s->redoStack = createDynamicArray(10, &destroyOperation);
	return updateOffer(s->repo, o);
}

/// <summary>
/// function to sort by price offers containing string
/// </summary>
/// <param name="v">service to extract from</param>
/// <param name="substr">string to search for</param>
/// <returns>sorted offers</returns>
OfferRepo* sortOffersServ(Service* s, char* substr)
{
	return sortOffers(s->repo, substr);
}

/*
OfferRepo* extraOffers(Service* s)
{
	return extra(s->repo);
}
*/

/// <summary>
/// function to undo
/// </summary>
/// <param name="s">service used</param>
/// <returns>0 if undo was executed, 1 if undo cannot be executed anymore, -1 if there was a problem</returns>
int undo(Service* s)
{
	if (s == NULL)
		return -1; 
	int stackSize = getLength(s->undoStack);
	if (stackSize == 0)
		return 1; 
	Operation* op = get(s->undoStack, stackSize - 1);
	if (op == NULL)
		return -1;
	Offer* o = getOpObject(op);
	if (o == NULL)
		return -1;
	Offer* co = copyOffer(o);
	if (getOpType(op) == ADD)
	{
		Operation* p = createOperation(ADD, co);
		add(s->redoStack, p);
		deleteOffer(s->repo, o->destination, o->departure_date);
	}
	else if (getOpType(op) == DELETE)
	{
		Operation* p = createOperation(DELETE, co);
		add(s->redoStack, p);
		addOffer(s->repo, copyOffer(o));
	}	
	else if (getOpType(op) == UPDATE)
	{
		Offer* of = findByDestinationDepartureDate(s->repo, co->destination, co->departure_date);
		Operation* p = createOperation(UPDATE, of);
		add(s->redoStack, p);
		updateOffer(s->repo, copyOffer(o));
	}
	delete(s->undoStack, stackSize - 1);
	destroyOffer(co);
	return 0;
}

/// <summary>
/// function to redo
/// </summary>
/// <param name="s">service used</param>
/// <returns>0 if redo was executed, 1 if redo cannot be executed anymore, -1 if there was a problem</returns>
int redo(Service* s)
{
	if (s == NULL)
		return -1;
	int stackSize = getLength(s->redoStack);
	if (stackSize == 0)
		return 1;
	Operation* op = get(s->redoStack, stackSize - 1);
	if (op == NULL)
		return -1;
	Offer* o = getOpObject(op);
	if (o == NULL)
		return -1;
	Offer* co = copyOffer(o);
	if (getOpType(op) == ADD)
	{
		Operation* p = createOperation(ADD, co);
		add(s->undoStack, p);
		addOffer(s->repo, copyOffer(o));
	}
	else if (getOpType(op) == DELETE)
	{
		Operation* p = createOperation(DELETE, co);
		add(s->undoStack, p);
		deleteOffer(s->repo, o->destination, o->departure_date);
	}
	else if (getOpType(op) == UPDATE)
	{
		Offer* of = findByDestinationDepartureDate(s->repo, co->destination, co->departure_date);
		Operation* p = createOperation(UPDATE, of);
		add(s->undoStack, p);
		updateOffer(s->repo, copyOffer(o));
	}
	delete(s->redoStack, stackSize - 1);
	destroyOffer(co);
	return 0;
}

/// <summary>
/// function to test service
/// </summary>
void testService()
{
	OfferRepo* r = createRepo();
	Service* s = createService(r);
	assert(s != NULL);
	destroyService(s);
}

/// <summary>
/// function to test getRepo
/// </summary>
void testGetRepo()
{
	OfferRepo* r = createRepo();
	Service* s = createService(r);
	assert(getRepo(s) == r);
	destroyService(s);
}

/// <summary>
/// function to test addOfferServ
/// </summary>
void testAddOfferServ()
{
	OfferRepo* r = createRepo();
	Service* s = createService(r);
	assert(addOfferServ(s, "citybreak", "Budapest", "22/10/2022", 190) == 0);
	assert(addOfferServ(s, "seaside", "Budapest", "22/10/2022", 285) == -1);
	destroyService(s);
}

/// <summary>
/// function to test deleteOfferServ
/// </summary>
void testDeleteOfferServ()
{
	OfferRepo* r = createRepo();
	Service* s = createService(r);
	Offer* o = createOffer("citybreak", "Budapest", "22/10/2022", 190);
	addOffer(r, o);
	assert(deleteOfferServ(s, "Budapest", "22/10/2022") == 0);
	assert(deleteOfferServ(s, "Budapest", "22/10/2022") == -1);
	destroyService(s);
}

/// <summary>
/// function to test updateOfferServ
/// </summary>
void testUpdateOfferServ()
{
	OfferRepo* r = createRepo();
	Service* s = createService(r);
	Offer* o = createOffer("citybreak", "Budapest", "22/10/2022", 190);
	addOffer(r, o);
	Offer* u1 = createOffer("seaside", "Budapest", "22/10/2022", 230);
	assert(updateOfferServ(s, u1) == 0);
	Offer* u2 = createOffer("seaside", "Liverpool", "27/11/2022", 230);
	assert(updateOfferServ(s, u2) == -1);
	destroyService(s);
}

/// <summary>
/// function to test undo
/// </summary>
void testUndo()
{
	OfferRepo* r = createRepo();
	Service* s = createService(r);
	addOfferServ(s, "citybreak", "Budapest", "22/10/2022", 190);
	assert(getRepoLength(s->repo) == 1);
	assert(getLength(s->undoStack) == 1);
	int res = undo(s);
	assert(getRepoLength(s->repo) == 0);
	assert(getLength(s->undoStack) == 0);
	res = redo(s);
	assert(getRepoLength(s->repo) == 1);
	deleteOfferServ(s, "Budapest", "22/10/2022");
	assert(getRepoLength(s->repo) == 0);
	assert(getLength(s->undoStack) == 2);
	res = undo(s);
	assert(getRepoLength(s->repo) == 1);
	Offer* o = getOfferOnPos(s->repo, 0);
	assert(strcmp(o->type, "citybreak") == 0);
	assert(strcmp(o->destination, "Budapest") == 0);
	assert(strcmp(o->departure_date, "22/10/2022") == 0);
	assert(o->price == 190);
	assert(getLength(s->undoStack) == 1);
	destroyService(s);
}

/// <summary>
/// function to test redo
/// </summary>
void testRedo()
{
	OfferRepo* r = createRepo();
	Service* s = createService(r);
	addOfferServ(s, "citybreak", "Budapest", "22/10/2022", 190);
	assert(getLength(s->redoStack) == 0);
	int res = undo(s);
	assert(getRepoLength(s->repo) == 0);
	assert(getLength(s->redoStack) == 1);
	res = redo(s);
	assert(getLength(s->redoStack) == 0);
	assert(getRepoLength(s->repo) == 1);
	Offer* o = getOfferOnPos(s->repo, 0);
	assert(strcmp(o->type, "citybreak") == 0);
	assert(strcmp(o->destination, "Budapest") == 0);
	assert(strcmp(o->departure_date, "22/10/2022") == 0);
	assert(o->price == 190);
	deleteOfferServ(s, "Budapest", "22/10/2022");
	assert(getRepoLength(s->repo) == 0);
	assert(getLength(s->redoStack) == 0);
	res = undo(s);
	assert(getRepoLength(s->repo) == 1);
	assert(getLength(s->redoStack) == 1);
	res = redo(s);
	assert(getRepoLength(s->repo) == 0);
	assert(getLength(s->redoStack) == 0);
	destroyService(s);
}

/// <summary>
/// function to use all tests
/// </summary>
void testsService()
{
	testService();
	testGetRepo();
	testAddOfferServ();
	testDeleteOfferServ();
	testUpdateOfferServ();
	testUndo();
	testRedo();
}
