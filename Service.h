#pragma once
#include "OfferRepository.h"

typedef struct
{
	OfferRepo* repo;
	DynamicArray* undoStack;
	DynamicArray* redoStack;
}Service;

Service* createService(OfferRepo* r);

void destroyService(Service* s);

OfferRepo* getRepo(Service* s);

int addOfferServ(Service* c, char* type, char* destination, char* departure_date, double price);

int deleteOfferServ(Service* c, char* destination, char* departure_date);

int updateOfferServ(Service* c, Offer* o);

OfferRepo* sortOffersServ(Service* c, char* substr);

//OfferRepo* extraOffers(Service* c);

int undo(Service* s);

int redo(Service* s);

void testsService();