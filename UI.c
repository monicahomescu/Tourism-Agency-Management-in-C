#include "UI.h"
#include "OfferRepository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

/// <summary>
/// function that creates ui
/// </summary>
/// <param name="s">service to use</param>
/// <returns>created ui</returns>
UI* createUI(Service* s)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->serv = s;
	return ui;
}

/// <summary>
/// function that destroyes ui
/// </summary>
/// <param name="ui">ui to destroy</param>
void destroyUI(UI* ui)
{
	destroyService(ui->serv);
	free(ui);
}

void printMenu()
{
	printf("******************************************************\n");
	printf("0 - Exit application.\n");
	printf("1 - Add offer.\n");
	printf("2 - Delete offer.\n");
	printf("3 - Update offer.\n");
	printf("4 - List offers.\n");
	printf("5 - Sort by price offers containing string.\n");
	printf("6 - Display offers with type and departure date after.\n");
	printf("7 - Undo.\n");
	printf("8 - Redo.\n");
	printf("******************************************************\n");
}

void addOfferUI(UI* ui)
{
	char type[50], destination[50], departure_date[50];
	double price = 0;
	printf("Type of offer to add: ");
	int scanf_result = scanf("%49s", type);
	printf("Destination of offer to add: ");
	scanf_result = scanf("%49s", destination);
	printf("Departure date of offer to add: ");
	scanf_result = scanf("%49s", departure_date);
	printf("Price of offer to add: ");
	char s[10] = { 0 };
	double r = 0;
	scanf_result = scanf("%15s", s);
	r = sscanf(s, "%lf", &price);

	int ok = 1;
	if (checkType(type) == 0)
	{
		printf("Invalid type! Should be 'seaside', 'mountain' or 'citybreak'!\n");
		ok = 0;
	}
	if (checkDestination(destination) == 0)
	{
		printf("Invalid destination! Should only contain letters!\n");
		ok = 0;
	}
	if (checkDepartureDate(departure_date) == 0)
	{
		printf("Invalid departure date! Should be an existing date!\n");
		ok = 0;
	}
	if (checkPrice(s) == 0)
	{
		printf("Invalid price! Should be a number!\n");
		ok = 0;
	}

	int res;
	if (ok == 1)
	{
		res = addOfferServ(ui->serv, type, destination, departure_date, price);
		if (res == 0)
			printf("Offer successfully added!\n");
		else
			printf("Offer with the same destination and departure date already exists!\n");
	}
}

void delOfferUI(UI* ui)
{
	char destination[50], departure_date[50];
	printf("Destination of offer to delete: ");
	int scanf_result = scanf("%49s", destination);
	printf("Departure date of offer to delete: ");
	scanf_result = scanf("%49s", departure_date);

	int ok = 1;
	if (checkDestination(destination) == 0)
	{
		printf("Invalid destination! Should only contain letters!\n");
		ok = 0;
	}
	if (checkDepartureDate(departure_date) == 0)
	{
		printf("Invalid departure date! Should be an existing date!\n");
		ok = 0;
	}

	int res;
	if (ok == 1)
	{
		res = deleteOfferServ(ui->serv, destination, departure_date);
		if (res == 0)
			printf("Offer successfully removed!\n");
		else
			printf("Offer with the same destination and departure date doesn't exist!\n");
	}
}

void updateOfferUI(UI* ui)
{
	char find_destination[50], find_departure_date[50], type[50];
	double price = 0;
	printf("Destination of offer to update: ");
	int scanf_result = scanf("%49s", find_destination);
	printf("Departure date of offer to update: ");
	scanf_result = scanf("%49s", find_departure_date);
	printf("New type of offer: ");
	scanf_result = scanf("%49s", type);
	printf("New price of offer: ");
	char s[10] = { 0 };
	double r = 0;
	scanf_result = scanf("%15s", s);
	r = sscanf(s, "%lf", &price);

	int ok = 1;
	if (checkDestination(find_destination) == 0)
	{
		printf("Invalid destination! Should only contain letters!\n");
		ok = 0;
	}
	if (checkDepartureDate(find_departure_date) == 0)
	{
		printf("Invalid departure date! Should be an existing date!\n");
		ok = 0;
	}
	if (checkType(type) == 0)
	{
		printf("Invalid type! Should be 'seaside', 'mountain' or 'citybreak'!\n");
		ok = 0;
	}
	if (checkPrice(s) == 0)
	{
		printf("Invalid price! Should be a number!\n");
		ok = 0;
	}

	int res;
	if (ok == 1)
	{
		Offer* o = createOffer(type, find_destination, find_departure_date, price);
		res = updateOfferServ(ui->serv, o);
		if (res == 0)
			printf("Offer successfully updated!\n");
		else
			printf("Offer with the same destination and departure date doesn't exist!\n");
	}
}

void listAllOffers(UI* ui)
{
	if (ui == NULL)
		return;
	OfferRepo* repo = getRepo(ui->serv);
	
	if (getRepoLength(repo) == 0)
		printf("No offers available!\n");
	else
	{
		printf("Offers:\n");
		for (int i = 0; i < getRepoLength(repo); i++)
		{
			Offer* offer = getOfferOnPos(repo, i);
			char offerString[200];
			toString(offer, offerString);
			printf("%s\n", offerString);
		}
	}
}

void sortOffersUI(UI* ui)
{
	char substr[10];
	fgets(substr, 10, stdin);
	printf("String to search for: ");
	fgets(substr, sizeof(substr), stdin);
	if (substr[0] == '\n')
		strcpy(substr, "");
	else
		substr[strcspn(substr, "\n")] = 0;
	OfferRepo* new = sortOffersServ(ui->serv, substr);
	if (new == NULL)
		return;
	if (getRepoLength(new) == 0)
	{
		printf("Offer destination containing string was not found!\n");
		destroyRepo(new);
	}
	else
	{
		printf("Sorted offers by string:\n");
		for (int i = 0; i < getRepoLength(new); i++)
		{
			Offer* offer = getOfferOnPos(new, i);
			char offerString[200];
			toString(offer, offerString);
			printf("%s\n", offerString);
		}
		free(new);
	}
}

/*
void extraOffersUI(UI* ui)
{
	OfferRepo* new = extraOffers(ui->serv);
	if (new == NULL)
		return;
	printf("Sorted offers by destination:\n");
	for (int i = 0; i < getLength(new); i++)
	{
		Offer* offer = getOfferOnPos(new, i);
		char offerString[200];
		toString(offer, offerString);
		printf("%s\n", offerString);
	}
	free(new);
}
*/

void displayOffersUI(UI* ui)
{
	char type[50], departure_date[50];
	printf("Type of offer to display: ");
	int scanf_result = scanf("%49s", type);
	printf("Departure date to consider: ");
	scanf_result = scanf("%49s", departure_date);

	int ok = 1;
	if (checkType(type) == 0)
	{
		printf("Invalid type! Should be 'seaside', 'mountain' or 'citybreak'!\n");
		ok = 0;
	}
	if (checkDepartureDate(departure_date) == 0)
	{
		printf("Invalid departure date! Should be an existing date!\n");
		ok = 0;
	}

	if (ok == 1)
	{
		int i;
		ok = 0;
		for (i = 0; i < getRepoLength(getRepo(ui->serv)); i++)
		{
			Offer* offer = getOfferOnPos(getRepo(ui->serv), i);
			if (strcmp(offer->type, type) == 0 && compareDates(departure_date, offer->departure_date) == 1)
				ok = 1;
		}
		if (ok == 0)
			printf("Offers with that type having departure after that date don't exist!\n");
		else
		{
			printf("Offers that match:\n");
			for (i = 0; i < getRepoLength(getRepo(ui->serv)); i++)
			{
				Offer* offer = getOfferOnPos(getRepo(ui->serv), i);
				if (strcmp(offer->type, type) == 0 && compareDates(departure_date, offer->departure_date) == 1)
				{
					char offerString[200];
					toString(offer, offerString);
					printf("%s\n", offerString);
				}
			}
		}
	}
}

void startUI(UI* ui)
{
	printf("Welcome to 'Happy Holidays'! Manage offers: \n");

	while (1)
	{
		printMenu();

		printf("Enter command: ");
		int command;
		char s[10] = { 0 };
		double r = 0;
		int scanf_result = scanf("%15s", s);
		r = sscanf(s, "%d", &command);

		while (validCommand(command) == 0 || checkPrice(s) == 0)
		{
			printf("Invalid command! Should be 0, 1, 2, 3, 4, 5 or 6!\n");
			printf("Enter command: ");
			scanf_result = scanf("%15s", s);
			r = sscanf(s, "%d", &command);
		}

		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{
			addOfferUI(ui);
			break;
		}
		case 2:
		{
			delOfferUI(ui);
			break;
		}
		case 3:
		{
			updateOfferUI(ui);
			break;
		}
		case 4:
		{
			listAllOffers(ui);
			break;
		}
		case 5:
		{
			sortOffersUI(ui);
			break;
		}
		case 6:
		{
			displayOffersUI(ui);
			break;
		}
		case 7:
		{
			int res = undo(ui->serv);
			if (res == 0)
				printf("Undo successful!\n");
			else if (res == 1)
				printf("Cannot undo anymore!\n");
			break;
		}
		case 8:
		{
			int res = redo(ui->serv);
			if (res == 0)
				printf("Redo successful!\n");
			else if (res == 1)
				printf("Cannot redo anymore!\n");
			break;
		}
		}
	}
}

/// <summary>
/// function to test UI
/// </summary>
void testUI()
{
	OfferRepo* r = createRepo();
	Service* s = createService(r);
	UI* u = createUI(s);
	assert(u != NULL);
	destroyUI(u);
}

/// <summary>
/// function to use all tests
/// </summary>
void testsUI()
{
	testUI();
}
