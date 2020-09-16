#include <stdio.h>
#define MAX 20

int cuenta(int arr[],int ini, int n)
{
	int medio,cont=0;

	medio=(n+ini)/2;	

	if(ini>=n)
    {    
		if(arr[ini]==0)	return 1;
                if(arr[ini]!=0) return 0;
	}
	else 
	{   
		cont=cont+cuenta(arr,ini,medio);
		cont=cont+cuenta(arr,medio+1,n);
		return cont;
	}
}

int cuenta_0(int A[], int k,int ini, int fin, int contador){
    if(ini>fin)return contador;
    int med=(ini+fin)/2;
    if(A[med]>=k)
        return cuenta_0(A,k,ini,med-1,contador);
    else
        return cuenta_0(A,k,med+1,fin,med-ini+1+contador);


}

void cuenta_merge(int* arr, int begin, int end, int elem, int* count)
{
    if (begin == end) {
        if (arr[begin] == elem) {
            (*count)++;
        }
        return;
    }
    int mid = (begin + end) / 2;

    cuenta_merge(arr, begin, mid, elem, count);
    cuenta_merge(arr, mid + 1, end, elem, count);
}


int main()
{
    int A[MAX]={1,1,1,1,1,3,3,5,5,6,6,6,6,7,8,9,10},k=5, n=17;
    printf(" %i ",cuenta_0(A,k,0,n-1,0));
	return 0;
}
