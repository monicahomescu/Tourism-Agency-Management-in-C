#include "Offer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

/// <summary>
/// function that creates an offer
/// </summary>
/// <param name="type">type of offer</param>
/// <param name="destination">destination of offer</param>
/// <param name="departure_date">departure date of offer</param>
/// <param name="price">price of offer</param>
/// <returns>offer created</returns>
Offer* createOffer(char* type, char* destination, char* departure_date, double price)
{
	Offer* o = malloc(sizeof(Offer));
	if (o == NULL)
		return NULL;
	o->type = malloc(sizeof(char) * (strlen(type) + 1));
	if (o->type != NULL)
		strcpy(o->type, type);
	o->destination = malloc(sizeof(char) * (strlen(destination) + 1));
	if (o->destination != NULL)
		strcpy(o->destination, destination);
	o->departure_date = malloc(sizeof(char) * (strlen(departure_date) + 1));
	if (o->departure_date != NULL)
		strcpy(o->departure_date, departure_date);
	o->price = price;
	return o;
}

/// <summary>
/// function that destroyes an offer
/// </summary>
/// <param name="o">offer to destroy</param>
void destroyOffer(Offer* o)
{
	if (o == NULL)
		return;
	free(o->type);
	free(o->destination);
	free(o->departure_date);
	free(o);
}

/// <summary>
/// function to transform offer into string
/// </summary>
/// <param name="o">offer to transform</param>
/// <param name="str">string to contain offer</param>
void toString(Offer* o, char str[])
{
	if (o == NULL)
		return;
	sprintf(str, "type: %s | destination: %s | departure_date: %s | price: %.2lf", o->type, o->destination, o->departure_date, o->price);
}

/// <summary>
/// function to make a copy of offer
/// </summary>
/// <param name="o">offer to copy</param>
/// <returns>copied offer</returns>
Offer* copyOffer(Offer* o) 
{
	if (o == NULL)
		return NULL;
	return createOffer(o->type, o->destination, o->departure_date, o->price);
}

/// <summary>
/// function that checks if command is valid
/// </summary>
/// <param name="command">command to check</param>
/// <returns>1 if valid, 0 otherwise</returns>
int validCommand(int c)
{
	if (c >= 0 && c <= 9)
		return 1;
	return 0;
}

/// <summary>
/// function that checks if type is valid
/// </summary>
/// <param name="s">type to check</param>
/// <returns>1 if valid, 0 otherwise</returns>
int checkType(char s[50])
{
	if (strcmp(s, "seaside") == 0 || strcmp(s, "mountain") == 0 || strcmp(s, "citybreak") == 0)
		return 1;
	return 0;
}

/// <summary>
/// function to check if destination is valid
/// </summary>
/// <param name="s">destination to check</param>
/// <returns>1 if valid, 0 otherwise</returns>
int checkDestination(char s[50])
{
	int i;
	for (i = 0; i < strlen(s); i++)
	{
		if (isalpha(s[i]) == 0)
			return 0;
	}
	return 1;
}

/// <summary>
/// function to check if departure date is valid
/// </summary>
/// <param name="s">departure date to check</param>
/// <returns>1 if valid, 0 otherwise</returns>
int checkDepartureDate(char s[50])
{
	if (strlen(s) != 10)
		return 0;
	int i;
	for (i = 0; i < strlen(s); i++)
	{
		if ((i == 2 || i == 5) && s[i] != '/')
			return 0;
		if ((i != 2 && i != 5) && isdigit(s[i]) == 0)
			return 0;
	}
	int day = (s[0] - 48) * 10 + (s[1] - 48);
	if (day < 1 || day > 31)
		return 0;
	int month = (s[3] - 48) * 10 + (s[4] - 48);
	if (month < 1 || month > 12)
		return 0;
	return 1;
}

/// <summary>
/// function to check if price is valid
/// </summary>
/// <param name="s">price to check</param>
/// <returns>1 if valid, 0 otherwise</returns>
int checkPrice(char s[50])
{
	int i;
	for (i = 0; i < strlen(s); i++)
	{
		if (isdigit(s[i]) == 0)
			return 0;
	}
	return 1;
}

/// <summary>
/// function to test offer
/// </summary>
void testOffer()
{
	Offer* o = createOffer("type", "destination", "departuredate", 1);
	assert(o != NULL);
	destroyOffer(o);
}

/// <summary>
/// function to test toString
/// </summary>
void testToString()
{
	Offer* o = createOffer("type", "destination", "departuredate", 1);
	char str[100];
	toString(o, str);
	assert(strcmp(str, "type: type | destination: destination | departure_date: departuredate | price: 1.00") == 0);
	destroyOffer(o);
}

/// <summary>
/// function to test copyOffer
/// </summary>
void testCopyOffer()
{
	Offer* o = createOffer("type", "destination", "departuredate", 1);
	Offer* co = copyOffer(o);
	assert(strcmp(o->type, co->type) == 0);
	assert(strcmp(o->destination, co->destination) == 0);
	assert(strcmp(o->departure_date, co->departure_date) == 0);
	assert(o->price == co->price);
	destroyOffer(o);
	destroyOffer(co);
}

/// <summary>
/// function to test validComment
/// </summary>
void testValidCommand()
{
	assert(validCommand(-1) == 0);
	assert(validCommand(10) == 0);
	assert(validCommand(0) == 1);
	assert(validCommand(1) == 1);
}

/// <summary>
/// function to test checkType
/// </summary>
void testCheckType()
{
	assert(checkType("abc") == 0);
	assert(checkType("seaside") == 1);
	assert(checkType("mountain") == 1);
	assert(checkType("citybreak") == 1);
}

/// <summary>
/// function to test checkDestination
/// </summary>
void testCheckDestination()
{
	assert(checkDestination("1Tokyo") == 0);
	assert(checkDestination("Tokyo/") == 0);
	assert(checkDestination("Tok.yo") == 0);
	assert(checkDestination("Tokyo") == 1);
}

/// <summary>
/// function to test checkDepartureDate
/// </summary>
void testCheckDepartureDate()
{
	assert(checkDepartureDate("31122022") == 0);
	assert(checkDepartureDate("31.12.2022") == 0);
	assert(checkDepartureDate("32/13/2022") == 0);
	assert(checkDepartureDate("31/12/2022") == 1);
}

/// <summary>
/// function to test checkPrice
/// </summary>
void testCheckPrice()
{
	assert(checkPrice("abc") == 0);
	assert(checkPrice("1abc") == 0);
	assert(checkPrice("abc1") == 0);
	assert(checkPrice("a1bc") == 0);
	assert(checkPrice("123") == 1);
}

/// <summary>
/// function to use all tests
/// </summary>
void testsOffer()
{
	testOffer();
	testToString();
	testCopyOffer();
	testValidCommand();
	testCheckType();
	testCheckDestination();
	testCheckDepartureDate();
	testCheckPrice();
}
