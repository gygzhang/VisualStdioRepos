#include"PloynomialSequence.h"

int main(void) {
	SqeList la,lb;
	InitializeSqeList(&la);
	InitializeSqeList(&lb);
	printf("The frist Ploynomial begins\n");
	CreatList(&la);
	getchar();
	printf("The second Ploynomial begins\n");
	CreatList(&lb);
	printf("the two ploynomial are:\n");
	PrintList(la);
	PrintList(lb);
	GetMenu();
	
	//PrintList(la);
	SelectMethod(&la,lb);

	/*Item item;
	item.coefficient = 5;
	item.exponent = 2;
	//InsertList(&la, item);
	InsertList(&la, -1,1);
	InsertList(&la, 1, 3);
	//InsertList(&la, 1, 3);

	InsertList(&lb, 2, 5);
	InsertList(&lb, 4, 7);
	InsertList(&lb, 2, 8);
	//InsertList(&lb, -1, 1);*/

	//PrintList(la);
	//PrintList(lb);
	//Remove(&list, 2);
	//GetMinAndChop(&list);
	//SortList(&list);
	//ConcatenateList(&la, lb);//ok
	//PrintList(la);
	//DistinguishList(&la);
	//ExecuteAdd(&la, lb);
	//ReverseSign(&la);
	//ExecuteSub(&la, lb);

	//BUG:if use the function SingleItemMultiplyList(item, la) twice,
	//will find that the data in List la are gabage data ,because
	/*SqeList lc = SingleItemMultiplyList(item, la);
	PrintList(lc);
	printf("\n--%p--\n", &la);
	lc = SingleItemMultiplyList(item, la);
	printf("\n--%p--\n", &la);
	PrintList(la);*/

	//@Test CopyList(&lc, la);  ok
	/*SqeList lc;
	InitializeSqeList(&lc);
	CopyList(&lc, la);
	PrintList(lc);
	PrintList(la);*/

	//@Test ImplementsMultiplicationWithPMethod(&la, lb, SingleItemMultiplyList);
	/*ImplementsMultiplicationWithPMethod(&la, lb, SingleItemMultiplyList);
	PrintList(la);*/

	//@Test ExecuteMul
	/*ExecuteMul(&la, lb);
	PrintList(la);*/

	//@Test GetMinAndChop(&la)
	/**Item itemz = GetMinAndChop(&la);
	PrintList(la);
	itemz = GetMinAndChop(&la);
	PrintList(la);
	itemz = GetMinAndChop(&la);
	PrintList(la);
	itemz = GetMinAndChop(&la);
	PrintList(la);*/

	system("pause");

}
