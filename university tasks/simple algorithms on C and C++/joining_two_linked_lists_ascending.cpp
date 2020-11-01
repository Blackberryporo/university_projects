#include <iostream>
#include <limits.h>

using namespace std;

struct NODE{
   int Number;
   NODE *Next;
};

NODE * MakeList(int*, int);
NODE *JoinTwoList(NODE*, NODE*);

int main(){
   int Arr1[]={2,3,5,9};
   int Arr2[]={4,6,7,11,16};
   NODE *Head1, *Head2;
   Head1=MakeList(Arr1,sizeof(Arr1)/sizeof(int));
   Head2=MakeList(Arr2,sizeof(Arr2)/sizeof(int));
   NODE *Head = JoinTwoList(Head1, Head2);
   cout << "Head";
   for(NODE* p1=Head->Next; p1!=NULL; p1=p1->Next){
      cout << " -> " << p1->Number;
   }
   return 0;
}


NODE *JoinTwoList(NODE *Head1, NODE *Head2){
// Выполнить слияние списков с головами Head1 и Head2
// Функция возвращает указатель на голову списка,
// являющегося результатом слияния
// ............................

    NODE* first = NULL;
    NODE* second = NULL;
    NODE* buf = NULL;
    NODE* Result = new NODE;
    NODE* Head = Result;
    int check = 0;

    Result->Next = NULL;
    Result->Number = INT_MAX;
    first = Head1->Next;
    second = Head2->Next;

    while (true)
    {
        if (first->Number <= second->Number && check != 1)
        {
            if (first->Next == NULL)
            {
                check = 1;
                Result->Next = first;
                buf = Result->Next;
                Result = buf;

                Result->Number = first->Number;

                continue;
            }
            Result->Next = first;
            buf = Result->Next;
            Result = buf;
            Result->Number = first->Number;
            buf = first;
            first = buf->Next;
        }
        else
        {
            if (second->Next == NULL)
            {
                Result->Next = second;
                buf = Result->Next;
                Result = buf;
                Result->Number = second->Number;
                break;
            }

            Result->Next = second;
            buf = Result->Next;
            Result = buf;
            Result->Number = second->Number;
            buf = second;
            second = buf->Next;
        }
    }

    return Head;
}



NODE * MakeList(int Arr[], int n){
// Эта функция создаёт один список
// Arr - массив чисел, которые должны быть помещены в список
// n - их количество
    NODE *Head=new NODE,*x;
    Head->Next=NULL; //Явно указываем на NULL
    Head->Number=INT_MAX; // Условное значение головы
    x=Head;
// Создание собственно списка
    for (int i = 0; i < n; i++) {
        x->Next=new NODE;
        x=x->Next;
        x->Number=Arr[i];
        x->Next = NULL;
    }

    return Head;
}
