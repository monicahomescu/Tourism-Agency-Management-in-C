#pragma once

typedef struct
{
	char* type;
	char* destination;
	char* departure_date;
	double price;
}Offer;

Offer* createOffer(char* type, char* destination, char* departure_date, double price);

void destroyOffer(Offer* o);

void toString(Offer* o, char str[]);

Offer* copyOffer(Offer* o);

int validCommand(int c);

int checkType(char s[50]);

int checkDestination(char s[50]);

int checkDepartureDate(char s[50]);

int checkPrice(char s[50]);

void testsOffer();