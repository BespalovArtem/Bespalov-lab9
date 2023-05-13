#include "sort.h"

void UdtMergeSort(Udt *udt)
{
	const int size = UdtSize(udt);
	Udt left, right;
	
	if (size <= 1)
		return;
	
	UdtCreate(&left, size);
	UdtCreate(&right, size);
	
	UdtPartition(udt, &left, &right);
	UdtMergeSort(&left);
	UdtMergeSort(&right);
	UdtMerge(udt, &left, &right);

	UdtDestroy(&left);
	UdtDestroy(&right);
}

void UdtPartition(Udt *udt, Udt *udt1, Udt *udt2)
{
	const int size = UdtSize(udt);
	int i;
	Udt tmp;
	UDT_TYPE cur;
	
	UdtCreate(&tmp,	size);
	
	while (!UdtEmpty(udt))
	{
		UdtPush(&tmp, UdtTop(udt));
		UdtPop(udt);
	}
	
	for (i = 0; i < size / 2; i++)
	{
		cur = UdtTop(&tmp);
		
		UdtPush(udt1, cur);
		UdtPop(&tmp);
	}
	
	for (; i < size; i++)
	{
		cur = UdtTop(&tmp);
		
		UdtPush(udt2, cur);
		UdtPop(&tmp);
	}
	
	UdtDestroy(&tmp);
}

void UdtMerge(Udt *udt, Udt *udt1, Udt *udt2)
{
	Udt tmp1, tmp2;
	
	UdtCreate(&tmp1, UdtSize(udt1));
	UdtCreate(&tmp2, UdtSize(udt2));
	
	while (!UdtEmpty(udt1))
	{
		UdtPush(&tmp1, UdtTop(udt1));
		UdtPop(udt1);
	}

	while (!UdtEmpty(udt2))
	{
		UdtPush(&tmp2, UdtTop(udt2));
		UdtPop(udt2);
	}
	
	while (!UdtEmpty(&tmp1) && !UdtEmpty(&tmp2))
	{
		if (UdtTop(&tmp1)._key <= UdtTop(&tmp2)._key)
		{
			UdtPush(udt, UdtTop(&tmp1));
			UdtPop(&tmp1);
		}
		else
		{
			UdtPush(udt, UdtTop(&tmp2));
			UdtPop(&tmp2);
		}
	}
	
	while (!UdtEmpty(&tmp1))
	{
		UdtPush(udt, UdtTop(&tmp1));
		UdtPop(&tmp1);
	}
	
	while (!UdtEmpty(&tmp2))
	{
		UdtPush(udt, UdtTop(&tmp2));
		UdtPop(&tmp2);
	}
	
	UdtDestroy(&tmp1);
	UdtDestroy(&tmp2);
}
