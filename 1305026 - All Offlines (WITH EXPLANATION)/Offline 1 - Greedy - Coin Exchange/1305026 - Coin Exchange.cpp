
#include <bits/stdc++.h>
#include <ctime>
#include <windows.h>
using namespace std;

int n = 200000;
int A[200000000];

void MAX_HEAPIFY ( int A[], int i )
{
	int l, r, largest;
	l = i * 2;
	r = i * 2 + 1;

	if ( l <= n && A[l] > A[i] )
	{
		largest = l;
	}

	else
	{
		largest = i;
	}

	if ( r <= n && A[r] > A[largest] )
	{
		largest = r;
	}

	if ( largest != i )
	{
		swap ( A[i], A[largest] );
		MAX_HEAPIFY ( A, largest );
	}
}

void BUILD_HEAP ( int A[] )
{
	for ( int i = n / 2; i > 0; i-- )
	{
		MAX_HEAPIFY ( A, i );
	}
}

int EXTRACT_HEAP_MAX ( int A[] )
{
	int max = A[1];
	A[1] = A[n];
	n--;
	MAX_HEAPIFY ( A, 1 );
	return max;
}


int main()
{
	int T = 123456789;
	int x = n;

	for ( int i = 1; i <= n; i++ )
	{
		A[i] = i;
	}

	/*
		for ( int i = 1; i <= n; i++ )
		{
			cout << A[i] << endl;
		}
	*/
	long long int start_time = GetTickCount();
	BUILD_HEAP ( A );

	//cout << endl << endl << endl << endl;

	//for ( int i = 1; i <= n; i++ )
	//{
	//cout << A[i] << endl;
	//}



	for ( int i = 1; i <= x; i++ )
	{
		int p = EXTRACT_HEAP_MAX ( A );
		//cout << p << " : " << T / p << endl;
		T = T % p;
	}

	printf ( "\nExecution time : %I64d ms", GetTickCount() - start_time );
	//long long int end_time = GetTickCount();
	//cout << end_time - start_time << endl;

	return 0;
}
