#pragma once
#include "Offer.h"

typedef enum {
	ADD,
	DELETE,
	UPDATE
} opType;

typedef struct {
	opType type;
	Offer* of;
} Operation;

Operation* createOperation(opType type,Offer* of);

void destroyOperation(Operation* o);

opType getOpType(Operation* o);

Offer* getOpObject(Operation* o);

void testsOperation();
