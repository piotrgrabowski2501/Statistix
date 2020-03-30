// Piotr Grabowski
#include "Statistix.h"
bool expectedValue(unsigned int n, const double* x, const double* p, double (*f)(double), double &r)
{
	double sum = 0;
	for(int i = 0; i < n; i++)
	{
		if(p[i] < 0) return false;
		sum += p[i];
	}
	if(sum >= 1) return false;

	double temp = 0;
	for(int i = 0; i < n; i++)
		temp += f(x[i])*p[i];

	temp += f(x[n])*(1-sum);
	r = temp;
	return true;
}

int* temp;

void merge_(int* tab, int left, int medium, int right)
{
	int i, j;
	for(i = medium + 1; i>left; i--)
    temp[i-1] = tab[i-1];

	for(j = medium; j<right; j++)
    temp[right+medium-j] = tab[j+1];


	for(int k=left;k<=right;k++){
		if(temp[j]<temp[i])
			tab[k] = temp[j--];
		else
			tab[k] = temp[i++];
	}

}

void mergeSort(int* tab,int left, int right)
{

	if(right<=left) return;

	int medium = (right+left)/2;

	mergeSort(tab, left, medium);
	mergeSort(tab, medium+1, right);
	merge_(tab, left, medium, right);
}


bool median(unsigned int n, const int* t, int (*f)(int), bool (*p)(int), double &r)
{
	bool tempArray[n];
	int m=0;
	int* tempArray_3;
	tempArray_3 = new int[n];
	for(int i = 0; i < n; i++)
	{
		tempArray[i] = p(t[i]);
		if(tempArray[i])
		{
			m++;
			tempArray_3[i] = f(t[i]);
		}
	}

	int* tempArray_2 = new int[m];
	int j=0;

	for(int i = 0; i < n; i++)
		if(tempArray[i])
			tempArray_2[j++]=tempArray_3[i];

	temp=new int[m];

	mergeSort(tempArray_2,0,m-1);

	int k = 0;
	if(m > 0)
		k = 1;
	for(int i = 1; i < m; i++)
	{
		while(tempArray_2[i - 1] == tempArray_2[i])   i++;
		if(i < m)	tempArray_2[k++] = tempArray_2[i];
	}
	m = k;

	if(m<1) return false;

	if(m%2==0)
		r = (double)(tempArray_2[m/2-1] + tempArray_2[m / 2]) / 2;
	else
		r = tempArray_2[m/2];

	return true;
}

unsigned int gcd(unsigned int n, const int* t, int* r=nullptr)
{
	int j=0;
	int length=0;
	int* tempArray=new int[n];
	for(int i=0; i<n; i++) tempArray[i]=t[i];
	for(int i=0; i<n; i++)
	{
		if(t[i]!=0)
		{
			tempArray[j++]=t[i];
			length++;
		}
	}
	unsigned int gcd=1;
	if(length<1) return 0;

	else
	{
		for(int i=0; i<length; i++)
		{
			if(tempArray[i]<0)
				tempArray[i] *= -1;
		}

		int minn;
		minn=tempArray[0];
		for(int i=1; i<length; i++)
			if(tempArray[i]<minn) minn=tempArray[i];

		int licznik;
		for(int i=2; i<=minn; i++)
		{
			licznik=0;
			for(int j=0; j<length; j++)
				if(tempArray[j] % i == 0) licznik++;
			if(licznik==length) gcd=i;
		}

		if(r!=nullptr){
			for(int i=0; i<n; i++)
				r[i] = t[i] / gcd;
		}
	}
	return gcd;
}

unsigned int count(unsigned int n, const int* t, bool (*p)(int, int)=nullptr )
 {
 	unsigned int counter=0;
 	int* tempArray;
 	tempArray=new int[n];
 	for(int i=0; i<n; i++) tempArray[i]=t[i];
 	if(p==nullptr)
	{
		temp=new int[n];
		mergeSort(tempArray,0,n-1);

		counter = n;
		for(int i = 1; i < n;i++)
			if(tempArray[i - 1] == tempArray[i])
				counter--;
		counter *= counter;
	}
	else
	{
		temp=new int[n];
		mergeSort(tempArray,0,n-1);

		int j = 0;
		if(n > 0)
			temp[j++] = tempArray[0];
		for(int i = 1; i < n; i++)
		{
			while(tempArray[i] == tempArray[i - 1])   i++;
			if(i < n)	temp[j++] = tempArray[i];
		}
		n = j;
		for(int i=0; i<n; i++)
		{
			for(int j = 0; j < n; j++)
				if(p(temp[i],temp[j])) counter++;
		}
	}
	return counter;
 }
