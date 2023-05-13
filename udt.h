#ifndef UDT_H
#define UDT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _Item
{
	float _key;
	char _str[31];
} Item;

typedef Item UDT_TYPE;

typedef struct _Udt
{
	UDT_TYPE *_data;
	int _capacity;
	int _size;
} Udt;

void UdtCreate(Udt *udt, const int capacity);
int UdtPush(Udt *udt, const UDT_TYPE value);
void UdtPop(Udt *udt);
UDT_TYPE UdtTop(const Udt *udt);
int UdtSize(const Udt *udt);
int UdtEmpty(const Udt *udt);
void UdtPrint(Udt *udt);
void UdtDestroy(Udt *udt);

#endif
