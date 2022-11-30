#include "OfferRepository.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/// <summary>
/// function that creates a repository
/// </summary>
/// <returns>repo created</returns>
OfferRepo* createRepo()
{
	OfferRepo* r = (OfferRepo*)malloc(sizeof(OfferRepo));
	if (r == NULL)
		return NULL;
	r->offers = createDynamicArray(CAPACITY, &destroyOffer);
	return r;
}

/// <summary>
/// function that destroyes a repository
/// </summary>
/// <param name="v">repo to destroy</param>
void destroyRepo(OfferRepo* r)
{
	if (r == NULL)
		return;
	destroy(r->offers);
	free(r);
}

/// <summary>
/// function that gets the offer on a given position
/// </summary>
/// <param name="v">repo to search in</param>
/// <param name="pos">position to search for</param>
/// <returns>null if position doesn't exist, offer found otherwise</returns>
Offer* getOfferOnPos(OfferRepo* r, int pos)
{
	if (r == NULL)
		return NULL;
	return get(r->offers, pos);
}

/// <summary>
/// function that finds the offer with a given destination and departure date
/// </summary>
/// <param name="v">repo to search in</param>
/// <param name="destination">destination to search for</param>
/// <param name="departure_date">departure date to search for</param>
/// <returns>null if offer doesn't exist, offer found otherwise</returns>
Offer* findByDestinationDepartureDate(OfferRepo* r, char* destination, char* departure_date)
{
	if (r == NULL || destination == NULL || departure_date == NULL)
		return NULL;
	int i;
	for (i = 0; i < getLength(r->offers); i++) 
	{
		Offer* o = get(r->offers, i);
		if (strcmp(o->destination, destination) == 0 && strcmp(o->departure_date, departure_date) == 0) 
			return o;
	}
	return NULL;
}

/// <summary>
/// function to get length of repository
/// </summary>
/// <param name="v">repo to get length of</param>
/// <returns>length of repo</returns>
int getRepoLength(OfferRepo* r)
{
	if (r == NULL)
		return -1;
	return getLength(r->offers);
}

/// <summary>
/// function to add an offer
/// </summary>
/// <param name="v">repo to add to</param>
/// <param name="o">offer to add</param>
/// <returns>1 if offer was added, 0 otherwise</returns>
int addOffer(OfferRepo* r, Offer* o)
{
	if (r == NULL || o == NULL || findByDestinationDepartureDate(r, o->destination, o->departure_date) != NULL)
	{
		destroyOffer(o);
		return -1;
	}
	add(r->offers, o);
	return 0;
}

/// <summary>
/// function to delete an offer
/// </summary>
/// <param name="v">repo to delete from</param>
/// <param name="destination">destination of offer to delete</param>
/// <param name="departure_date">departure date of offer to delete</param>
/// <returns>1 if offer was deleted, 0 otherwise</returns>
int deleteOffer(OfferRepo* r, char* destination, char* departure_date)
{
	if (r == NULL || destination == NULL || departure_date == NULL)
		return -1;
	Offer* o = findByDestinationDepartureDate(r, destination, departure_date);
	int i;
	for (i = 0; i < getLength(r->offers); i++) 
	{
		if (get(r->offers, i) == o)
		{
			delete(r->offers, i);
			return 0;
		}
	}
	return -1;
}

/// <summary>
/// function to update an offer
/// </summary>
/// <param name="v">repo to update in</param>
/// <param name="destination">destination of offer to update</param>
/// <param name="departure_date">departure date of offer to update</param>
/// <param name="o">offer to update with</param>
/// <returns>1 if offer was updated, 0 otherwise</returns>
int updateOffer(OfferRepo* r, Offer* o)
{
	Offer* of = findByDestinationDepartureDate(r, o->destination, o->departure_date);
	if (of == NULL)
	{
		destroyOffer(o);
		return -1;
	}
	free(of->type);
	free(of->destination);
	free(of->departure_date);
	of->type = o->type;
	of->destination = o->destination;
	of->departure_date = o->departure_date;
	of->price = o->price;
	free(o);
	return 0;
}

/// <summary>
/// function to sort by price offers containing string
/// </summary>
/// <param name="v">repo to extract from</param>
/// <param name="substr">string to search for</param>
/// <returns>sorted offers</returns>
OfferRepo* sortOffers(OfferRepo* r, char* substr)
{
	OfferRepo* new = (OfferRepo*)malloc(sizeof(OfferRepo));
	if (new == NULL)
		return NULL;
	new->offers = createDynamicArray(CAPACITY, &destroyOffer);
	int i, j;
	if (strcmp(substr, "") == 0)
	{
		for (i = 0; i < getLength(r->offers); i++)
		{
			Offer* of = getOfferOnPos(r, i);
			add(new->offers, of);
		}
	}
	else
	{
		for (i = 0; i < getLength(r->offers); i++)
		{
			Offer* of = getOfferOnPos(r, i);
			if (strstr(of->destination, substr))
				add(new->offers, of);
		}
	}
	for (i = 0; i < getLength(new->offers) - 1; i++)
	{
		for (j = i + 1; j < getLength(new->offers); j++)
		{
			Offer* o1 = getOfferOnPos(new, i);
			Offer* o2 = getOfferOnPos(new, j);
			if (o1->price > o2->price)
			{
				Offer* aux = o1;
				o1 = o2;
				o2 = aux;
			}
		}
	}
	return new;
}

/*
OfferRepo* extraOffers(OfferRepo* v)
{
	OfferRepo* new = malloc(sizeof(OfferRepo));
	if (new == NULL)
		return NULL;
	new->length = 0;
	int i, j;
	for (i = 0; i < v->length; i++)
	{
		Offer* of = getOfferOnPos(v, i);
		new->offers[new->length] = of;
		new->length++;
	}
	for (i = 0; i < new->length - 1; i++)
	{
		for (j = i + 1; j < new->length; j++)
		{
			Offer* o1 = getOfferOnPos(new, i);
			Offer* o2 = getOfferOnPos(new, j);
			if (strcmp(o1->destination, o2->destination) > 0)
			{
				Offer* aux = new->offers[i];
				new->offers[i] = new->offers[j];
				new->offers[j] = aux;
			}
		}
	}
	return new;
}
*/

/// <summary>
/// function to test if a date is after another date
/// </summary>
/// <param name="d1">first date</param>
/// <param name="d2">second date</param>
/// <returns>1 if d1 is before d2, 0 otherwise</returns>
int compareDates(char d1[], char d2[])
{
	int day1 = (d1[0] - 48) * 10 + (d1[1] - 48);
	int day2 = (d2[0] - 48) * 10 + (d2[1] - 48);
	int month1 = (d1[3] - 48) * 10 + (d1[4] - 48);
	int month2 = (d2[3] - 48) * 10 + (d2[4] - 48);
	int year1 = (d1[6] - 48) * 1000 + (d1[7] - 48) * 100 + (d1[8] - 48) * 10 + (d1[9] - 48);
	int year2 = (d2[6] - 48) * 1000 + (d2[7] - 48) * 100 + (d2[8] - 48) * 10 + (d2[9] - 48);
	if (year1 < year2)
		return 1;
	if (year1 == year2 && month1 < month2)
		return 1;
	if (year1 == year2 && month1 == month2 && day1 < day2)
		return 1;
	return 0;
}

/// <summary>
/// function to test repo
/// </summary>
void testRepo()
{
	OfferRepo* r = createRepo();
	assert(r != NULL);
	destroyRepo(r);
}

/// <summary>
/// function to test getOfferOnPos
/// </summary>
void testGetOfferOnPos()
{
	OfferRepo* r = createRepo();
	Offer* o = createOffer("citybreak", "Budapest", "22/10/2022", 190);
	addOffer(r, o);
	assert(getOfferOnPos(r, 0) != NULL);
	assert(strcmp(getOfferOnPos(r, 0)->type, "citybreak") == 0);
	assert(strcmp(getOfferOnPos(r, 0)->destination, "Budapest") == 0);
	assert(strcmp(getOfferOnPos(r, 0)->departure_date, "22/10/2022") == 0);
	assert(getOfferOnPos(r, 0)->price == 190);
	destroyRepo(r);
}

/// <summary>
/// function to test findByDestinationDepartureDate
/// </summary>
void testFindByDestinationDepartureDate()
{
	OfferRepo* r = createRepo();
	Offer* o = createOffer("citybreak", "Budapest", "22/10/2022", 190);
	addOffer(r, o);
	assert(findByDestinationDepartureDate(r, "Budapest", "22/10/2022") != NULL);
	assert(findByDestinationDepartureDate(r, "Helsinki", "22/10/2022") == NULL);
	destroyRepo(r);
}

/// <summary>
/// function to test getRepoLength
/// </summary>
void testGetRepoLength()
{
	OfferRepo* r = createRepo();
	assert(getRepoLength(r) == 0);
	Offer* o = createOffer("citybreak", "Budapest", "22/10/2022", 190);
	addOffer(r, o);
	assert(getRepoLength(r) == 1);
	destroyRepo(r);
}

/// <summary>
/// function to test addOffer
/// </summary>
void testAddOffer()
{
	OfferRepo* r = createRepo();
	Offer* o1 = createOffer("seaside", "Egypt", "21/04/2022", 560);
	assert(addOffer(r, o1) == 0);
	assert(getRepoLength(r) == 1);
	Offer* o2 = createOffer("seaside", "Egypt", "21/04/2022", 560);
	assert(addOffer(r, o2) == -1);
	assert(getRepoLength(r) == 1);
	destroyRepo(r);
}

/// <summary>
/// function to test deleteOffer
/// </summary>
void testDeleteOffer()
{
	OfferRepo* r = createRepo();
	Offer* o = createOffer("citybreak", "Budapest", "22/10/2022", 190);
	addOffer(r, o);
	assert(getRepoLength(r) == 1);
	assert(deleteOffer(r, "Budapest", "22/10/2022") == 0);
	assert(getRepoLength(r) == 0);
	assert(deleteOffer(r, "Budapest", "22/10/2022") == -1);
	destroyRepo(r);
}

/// <summary>
/// function to test updateOffer
/// </summary>
void testUpdateOffer()
{
	OfferRepo* r = createRepo();
	Offer* o1 = createOffer("citybreak", "Budapest", "22/10/2022", 190);
	addOffer(r, o1);
	Offer* o2 = createOffer("seaside", "Budapest", "22/10/2022", 560);
	assert(updateOffer(r, o2) == 0);
	Offer* o4 = findByDestinationDepartureDate(r, "Budapest", "22/10/2022");
	assert(strcmp(o4->type, "seaside") == 0);
	assert(strcmp(o4->destination, "Budapest") == 0);
	assert(strcmp(o4->departure_date, "22/10/2022") == 0);
	assert(o4->price == 560);
	Offer* o3 = createOffer("seaside", "Egypt", "21/04/2022", 560);
	assert(updateOffer(r, o3) == -1);
	destroyRepo(r);
}

/// <summary>
/// function to test compareDates
/// </summary>
void testCompareDates()
{
	assert(compareDates("12/01/2021", "01/01/2021") == 0);
	assert(compareDates("12/01/2021", "13/01/2021") == 1);
	assert(compareDates("01/03/2021", "01/09/2021") == 1);
	assert(compareDates("13/02/2021", "13/01/2022") == 1);
}

/// <summary>
/// function to use all tests
/// </summary>
void testsOfferRepo()
{
	testRepo();
	testGetOfferOnPos();
	testFindByDestinationDepartureDate();
	testGetRepoLength();
	testAddOffer();
	testDeleteOffer();
	testUpdateOffer();
	testCompareDates();
}
