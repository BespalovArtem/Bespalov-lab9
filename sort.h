#ifndef UDT_SORT_H
#define UDT_SORT_H

#include "udt.h"

void UdtMergeSort(Udt *udt);
void UdtPartition(Udt *udt, Udt *udt1, Udt *udt2);
void UdtMerge(Udt *udt, Udt *udt1, Udt *udt2);

#endif
