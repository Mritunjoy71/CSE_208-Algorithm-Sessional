#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define MAX_NUM 25
#define MAX_SET 25
#define INF 1000000000

int total_set, total_num;
int cnt[MAX_NUM];
int all_subsets[MAX_SET][MAX_NUM], num_of_elements[MAX_SET];
int ans;
int track[MAX_SET];
int final [MAX_SET];

void update()
{
	for ( int i = 0; i < MAX_SET; i++ )
	{
		final[i] = track[i];
	}
}

void print()
{
	for ( int i = 0; i < MAX_SET; i++ )
	{
		if ( final[i] )
		{
			cout << "{ ";
			int j;

			for ( j = 0; j < num_of_elements[i] - 1; j++ )
			{
				cout << all_subsets[i][j] << ", ";
			}

			cout << all_subsets[i][j] << " }" << endl;
		}
	}
}

void BACKTRACK ( int now, int c )
{
	if ( now == total_set )
	{
		int total = 0;
		memset ( cnt, 0, sizeof ( cnt ) );

		for ( int  i = 0; i < total_set; i++ )
		{
			if ( !track[i] )
				continue;

			for ( int j = 0; j < num_of_elements[i]; j++ )
			{
				if ( !cnt[all_subsets[i][j]] )
					total++;

				cnt[all_subsets[i][j]] = 1;
			}
		}

		if ( total == total_num )
		{
			if ( c < ans )
			{
				ans = c;
				update();
			}
		}

		return ;
	}

	if ( c >= ans )
		return ;

	track[now] = 0;
	BACKTRACK ( now + 1, c );
	track[now] = 1;
	BACKTRACK ( now + 1, c + 1 );
}

int main()
{
	ans = INF;
	cin >> total_num;
	cin >> total_set;

	for ( int i = 0; i < total_set; i++ )
	{
		cin >> num_of_elements[i];

		for ( int j = 0; j < num_of_elements[i]; j++ )
			cin >> all_subsets[i][j];
	}

	BACKTRACK ( 0, 0 );
	cout << ans << endl << endl;
	print();
	return 0;
}
