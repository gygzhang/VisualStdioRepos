#include"PloynomialSequence.h"


int InitializeSqeList(SqeList* plist) {
	plist->item = (Item*)malloc(INIT_SIZE * sizeof(Item));
	if (plist->item == NULL) exit(OVERFLOW);
	plist->length = 0;
	plist->size = INIT_SIZE;
	return OK;
}

int InsertList(SqeList *plist, Item item) {
	int len;
	len = GetLength(*plist);
	if (len + 1 >= plist->size) {
		plist->size += INCREMENT;
	}
	plist->item[len].coefficient = item.coefficient;
	plist->item[len].exponent = item.exponent;
	plist->length++;
	
	return OK;
}

int InsertList(SqeList *plist, double coefficient, double exponent) {
	Item item;
	item.coefficient = coefficient;
	item.exponent = exponent;
	InsertList(plist, item);
	return OK;
}


void PrintList(SqeList list) {
	if (ListIsEmpty(list)) {
		printf("Empty List...\n");
		return;
	}
	for (int i = 0; i < list.length; i++) {
		if (list.item[i].coefficient > 1e-9 && i != 0) printf("+");
		if (list.item[i].coefficient < 1e-9) printf("-");
		printf("(%.0lf*x^%.0lf)", fabs(list.item[i].coefficient), list.item[i].exponent);
	}
	printf("\n");
}

SqeList SortList(SqeList *plist) {
	Item item;
	SqeList scan = *plist, temp;
	InitializeSqeList(&temp);
	while (plist->length > 0) {
		InsertList(&temp, GetMinAndChop(plist));
	}
	int tlength = GetLength(temp);
	for (int i = 0; i < tlength; i++) {
		InsertList(plist, temp.item[i]);
	}
	return temp;
}

Item GetMinAndChop(SqeList *plist) {
	int length = GetLength(*plist), pos = 0;
	double minexponent = plist->item->exponent;
	for (int i = 1; i < length; i++) {
		if (plist->item[i].exponent < minexponent) {
			minexponent = plist->item[i].exponent;
			pos = i;
		}
	}
	return Remove(plist, pos);
}

int GetLength(SqeList list) {
	return list.length;
}

Item Remove(SqeList *plist, int index) {
	Item item;
	int length = GetLength(*plist);
	if (length == 0) return GenerateEmptyItem();
	item.coefficient = plist->item[index].coefficient;
	item.exponent = plist->item[index].exponent;
	for (; index < length; index++) {
		plist->item[index].coefficient = plist->item[index + 1].coefficient;
		plist->item[index].exponent = plist->item[index + 1].exponent;
	}
	plist->length--;
	return item;
}

Item GenerateEmptyItem() {
	Item item;
	item.coefficient = 0;
	item.exponent = 0;
	return item;
}

void ExecuteAdd(SqeList *pla, SqeList lb) {
	ConcatenateList(pla, lb);
	DistinguishList(pla);
}

void DistinguishList(SqeList* plist) {
	int length = GetLength(*plist);
	Item item1, item2;
	SqeList temp;
	InitializeSqeList(&temp);
	item1 = GetMinAndChop(plist);
	InsertList(&temp, item1);
	while (!ListIsEmpty(*plist)) {
		item1 = GetMinAndChop(plist);

		if (item1.exponent == temp.item[temp.length - 1].exponent) {
			temp.item[temp.length - 1].coefficient += item1.coefficient;
		}
		else if (item1.exponent != temp.item[temp.length - 1].exponent) {
			InsertList(&temp, item1);
		}
		//InsertList(&temp, item1);
	}
	int tlength = GetLength(temp);
	for (int i = 0; i < tlength; i++) {
		InsertList(plist, temp.item[i]);
	}
	StripEmptyItem(plist);
}

bool ListIsEmpty(SqeList list) {
	return list.length == 0 ? true : false;
}

bool ItemIsEmpty(Item item) {
	return item.coefficient == 0 ? true : false;
}

void ConcatenateList(SqeList *pla, SqeList lb) {
	Item item;
	while (!ListIsEmpty(lb)) {
		item = GetMinAndChop(&lb);
		if (!ItemIsEmpty(item)) {
			InsertList(pla, item);
		}
	}
	SortList(pla);
}

void StripEmptyItem(SqeList *plist) {
	for (int i = 0; i < plist->length; i++) {
		if (ItemIsEmpty(plist->item[i - 1])) {
			Remove(plist, i - 1);
		}
	}
}

void ReverseSign(SqeList *plist) {
	for (int i = 0; i < plist->length; i++) {
		plist->item[i].coefficient = 0 - plist->item[i].coefficient;
	}
}

void ExecuteSub(SqeList *pla, SqeList lb) {
	ReverseSign(&lb);
	ExecuteAdd(pla, lb);
}

SqeList SingleItemMultiplyList(Item item, SqeList list) {
	SqeList tempList, save;
	Item tempItem, savetemp;

	InitializeSqeList(&save);
	CopyList(&save, list);
	//printf("kk");
	//PrintList(save);
	//printf("kk");
	if (ListIsEmpty(list)) {
		printf("SingleItemMultiplyList Empty List...\n");
		return list;
	}
	InitializeSqeList(&tempList);
	while (!ListIsEmpty(list)) {
		tempItem = GetMinAndChop(&list);
		savetemp.coefficient = tempItem.coefficient * item.coefficient;
		savetemp.exponent = tempItem.exponent + item.exponent;
		InsertList(&tempList, savetemp);
	}

	//InitializeSqeList(&list);
	CopyList(&list, save);
	return tempList;
}

void ImplementsMultiplicationWithPMethod(SqeList *pla, SqeList lb, SqeList(*p)(Item, SqeList)) {
	SqeList tempList, resultList;
	Item tempItem;
	InitializeSqeList(&tempList);
	InitializeSqeList(&resultList);

	while (!ListIsEmpty(*pla)) {
		tempItem = GetMinAndChop(pla);
		tempList = p(tempItem, lb);
		ConcatenateList(&resultList, tempList);
	}

	CopyList(pla, resultList);
	DistinguishList(pla);
	//PrintList(tempList);
}


void ExecuteMul(SqeList *pla, SqeList lb) {
	ImplementsMultiplicationWithPMethod(pla, lb, SingleItemMultiplyList);
}

void CopyList(SqeList *pla, SqeList lb) {

	for (int i = 0; i < lb.length; i++) {
		InsertList(pla, lb.item[i]);
		///BUG: Why the following code can be wrong, 
		//because the la.length not increase at all!!!

		/*pla->item[i].coefficient = lb.item[i].coefficient;
		pla->item[i].exponent = lb.item[i].exponent;*/
		//printf("--%.0lf--", pla->item[i].exponent);
	}
}

void CreatList(SqeList* plist) {
	double coefficient, exponent;
	char c=0;
	
	printf("Please decide if you want to limit the number of items?(y or n)");
	c = getchar();
	if (c) {
		switch (c)
		{
		case 'y': yes(plist);
		break;
		case 'n': no(plist);
		 break;
		default:
			printf("bad choice");
			//getchar();
			break;
		}
	}	
}
void GetMenu() {
	printf("\n-----------------Welcome----------------\n");
	printf("     1 to ExecuteAdd(la, lb)\n");
	printf("     2 to ExecuteSub(la, lb)\n");
	printf("     3 to ExecuteMul(la, lb)\n");
	printf("     4 to Input agina\n");
	printf("     q to quit \n");
}
void SelectMethod(SqeList* la, SqeList lb) {
	int i;
	SqeList lc;
	InitializeSqeList(&lc);
	printf("Please choose a selection that you want to execute(q to quit):\n");
	scanf("%d", &i);
	 {
		switch (i)
		{
		case 1:
			ExecuteAdd(la, lb);
			printf("Your choice is ExecuteAdd(la, lb),and the result is\n");
			PrintList(*la);
			break;
		case 2:
			ExecuteSub(la, lb);
			printf("Your choice is ExecuteSub(la, lb),and the result is\n");
			PrintList(*la);
			break;
		case 3:
			ExecuteMul(la, lb);
			printf("Your choice is ExecuteMul(la, lb),and the result is:\n");
			PrintList(*la);
			break;
		case 4:
			break;
		default:
			printf("Bad Choice...");
			break;
		}
	}
	printf("\nBye~~\n");


}

void yes(SqeList *plist) {
		double coefficient, exponent;
		int num=0;
		printf("how many items you want ? ");
		scanf("%ld", &num);
		printf("please input the coefficient and exponent(space to separate,q to quit)\n");
		for (int i = 0; i < num;) {
			scanf("%lf%lf", &coefficient, &exponent);
			printf("please input the coefficient and exponent(space to separate,q to quit)\n");
			if (coefficient == 0) {
				printf("the item will be ignore\n");
				continue;
			}
			else {
				InsertList(plist, coefficient, exponent);
				i++;
				/*printf("The Ploynomial:");
				PrintList(*plist);*/
			}
		}
		printf("\nends\n");
		
	}
void no(SqeList *plist) {
	double coefficient, exponent;
	printf("please input the coefficient and exponent(space to separate,q to quit)\n");
	while (scanf("%lf%lf", &coefficient, &exponent) == 2) {
		printf("please input the coefficient and exponent(space to separate,q to quit)\n");
		if (coefficient == 0) {
			printf("the item will be ignore\n");
			continue;
		}
		else {
			InsertList(plist, coefficient, exponent);
			printf("The Ploynomial:");
			PrintList(*plist);
		}
	}
}
