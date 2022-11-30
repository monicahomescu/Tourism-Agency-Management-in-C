#include "Offer.h"
#include "OfferRepository.h"
#include "Service.h"
#include "UI.h"
#include "DynamicArray.h"
#include "Operation.h"
#include <crtdbg.h>

int main()
{
	testsOffer();
	testsOfferRepo();
	testsService();
	testsUI();
	testsDynamicArray();
	testsOperation();

	OfferRepo* repo = createRepo();

	Offer* o1 = createOffer("seaside", "Dubai", "10/12/2022", 890);
	addOffer(repo, o1);
	Offer* o2 = createOffer("mountain", "Colorado", "01/06/2022", 920);
	addOffer(repo, o2);
	Offer* o3 = createOffer("citybreak", "Rome", "28/10/2022", 430);
	addOffer(repo, o3);
	Offer* o4 = createOffer("citybreak", "London", "16/04/2022", 235);
	addOffer(repo, o4);
	Offer* o5 = createOffer("mountain", "Montana", "08/07/2022", 895);
	addOffer(repo, o5);
	Offer* o6 = createOffer("citybreak", "Venice", "23/11/2022", 370);
	addOffer(repo, o6);
	Offer* o7 = createOffer("seaside", "Thailand", "19/09/2022", 960);
	addOffer(repo, o7);
	Offer* o8 = createOffer("mountain", "Utah", "27/10/2022", 790);
	addOffer(repo, o8);
	Offer* o9 = createOffer("seaside", "Rome", "19/09/2022", 285);
	addOffer(repo, o9);
	Offer* o10 = createOffer("citybreak", "Tokyo", "03/12/2022", 1060);
	addOffer(repo, o10);

	Service* serv = createService(repo);

	UI* ui = createUI(serv);

	startUI(ui);

	destroyUI(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}