#pragma once
#include "Offer.h"
#include "DynamicArray.h"

typedef struct
{
	DynamicArray* offers;
}OfferRepo;

OfferRepo* createRepo();

void destroyRepo(OfferRepo* r);

Offer* getOfferOnPos(OfferRepo* r, int pos);

Offer* findByDestinationDepartureDate(OfferRepo* r, char* destination, char* departure_date);

int getRepoLength(OfferRepo* r);

int addOffer(OfferRepo* r, Offer* o);

int deleteOffer(OfferRepo* r, char* destination, char* departure_date);

int updateOffer(OfferRepo* r, Offer* o);

OfferRepo* sortOffers(OfferRepo* r, char* substr);

//OfferRepo* extraOffers(OfferRepo* r);

int compareDates(char d1[], char d2[]);

void testsOfferRepo();