
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct Point
{
	double x, y;
};

struct Point P[1000001];
long long int n;

double d;
struct Point p1, p2;

int comparator_X ( const void* a, const void* b )
{
	struct Point *p1 = ( struct  Point * ) a,  *p2 = ( struct Point * ) b;

	if ( p1->x >= p2->x )
	{
		return 1;
	}

	return 0;
}

int comparator_Y ( const void* a, const void* b )
{
	struct Point *p1 = ( struct  Point * ) a,  *p2 = ( struct Point * ) b;

	if ( p1->y >= p2->y )
	{
		return 1;
	}

	return 0;
}

double dist ( struct Point p, struct Point q )
{
	double dx = p.x - q.x;
	double dy = p.y - q.y;

	return sqrt ( dx * dx + dy * dy );
}



double divide_and_conquer ( struct Point P_x_sorted[], struct Point P_y_sorted[], long long int n )
{
	if ( n <= 3 )
	{
		for ( long long int i = 0; i < n - 1; i++ )
		{
			for ( long long int j = i + 1; j < n; j++ )
			{
				if ( dist ( P_x_sorted[i], P_x_sorted[j] ) < d )
				{
					p1 = P_x_sorted[i];
					p2 = P_x_sorted[j];
					d = dist ( p1, p2 );
				}
			}
		}

		return d;
	}

	long long int mid = n / 2;

	Point P_left_y_sorted[mid + 1];
	Point P_right_y_sorted[n - mid - 1];
	long long int l = 0, r = 0;

	for ( long long int i = 0; i < n; i++ )
	{
		if ( P_y_sorted[i].x <= P_x_sorted[mid].x )
		{
			P_left_y_sorted[l++] = P_y_sorted[i];
		}

		else
		{
			P_right_y_sorted[r++] = P_y_sorted[i];
		}
	}

	double delta_left = divide_and_conquer ( P_x_sorted, P_left_y_sorted, mid );
	double delta_right = divide_and_conquer ( P_x_sorted + mid, P_right_y_sorted, n - mid );


	d = min ( delta_left, delta_right );

	Point strip[n];
	long long int s = 0;

	for ( long long int i = 0; i < n; i++ )
	{
		if ( abs ( P_y_sorted[i].x - P_x_sorted[mid].x ) < d )
		{
			strip[s] = P_y_sorted[i];
			s++;
		}
	}

	for ( long long int i = 0; i < s; ++i )
	{
		for ( long long  int j = i + 1; j < s && ( strip[j].y - strip[i].y ) < d; ++j )
			if ( dist ( strip[i], strip[j] ) < d )
			{
				d = dist ( strip[i], strip[j] );
				p1 = strip[i];
				p2 = strip[j];
			}
	}

	return d;
}


double initiator ( struct Point P[], long long int n )
{
	d = DBL_MAX;
	struct Point P_x_sorted[n];
	struct Point P_y_sorted[n];

	for ( long long int i = 0; i < n; i++ )
	{
		P_x_sorted[i] = P[i];
		P_y_sorted[i] = P[i];
	}

	qsort ( P_x_sorted, n, sizeof ( Point ), comparator_X );
	qsort ( P_y_sorted, n, sizeof ( Point ), comparator_Y );

	return divide_and_conquer ( P_x_sorted, P_y_sorted, n );
}

int main()
{
	//freopen ( "in.txt", "r", stdin );
	//freopen ( "dnc_out.txt", "w", stdout );

	while ( cin >> n && n )
	{
		//cin >> n;

		for ( long long  int i = 0; i < n; i++ )
		{
			cin >> P[i].x;
			cin >> P[i].y;
		}

		//long long int start_time = GetTickCount();
		double d = initiator ( P, n );
		//cout << GetTickCount() - start_time << endl;


		long long int a, b;

		for ( long long int i = 0; i < n; i++ )
		{
			if ( p1.x == P[i].x && p1.y == P[i].y )
			{
				a = i;
			}

			if ( p2.x == P[i].x && p2.y == P[i].y )
			{
				b = i;
			}
		}


		cout << "Point 1 :	{ " << p1.x << ", " << p1.y << " }" << endl << endl;
		cout << "Point 2 :	{ " << p2.x << ", " << p2.y << " }" << endl << endl;
		cout << "Minimum Distance :  " << d << endl << endl;

	}

	return 0;
}
