
#include <bits/stdc++.h>
using namespace std;

double max_matrix[101][101];
double min_matrix[101][101];
int paren_pos[101][101];
double num[101];
char op[100];

double Eval ( int i, int j, int k, char op, char mode )
{

	double u, v, w, x;

	if ( op == '+' )
	{
		u =  max_matrix[i][k] + max_matrix[k + 1][j] ;
		v =  max_matrix[i][k] + min_matrix[k + 1][j] ;
		w =  min_matrix[i][k] + max_matrix[k + 1][j] ;
		x =  min_matrix[i][k] + min_matrix[k + 1][j] ;
	}

	else if ( op == 'x' )
	{
		u =  max_matrix[i][k] * max_matrix[k + 1][j] ;
		v =  max_matrix[i][k] * min_matrix[k + 1][j] ;
		w =  min_matrix[i][k] * max_matrix[k + 1][j] ;
		x =  min_matrix[i][k] * min_matrix[k + 1][j] ;


	}

	if ( mode == 'M' )
	{
		return max ( max ( u, v ), max ( w, x ) );
	}

	else if ( mode == 'm' )
	{
		return min ( min ( u, v ), min ( w, x ) );
	}

}

double fill_matrix ( int n )
{
	double maximum, minimum;

	for ( int i = 1; i <= n; i++ )
	{
		max_matrix[i][i] = num[i];
		min_matrix[i][i] = num[i];
	}

	for ( int l = 2; l <= n; l++ )
	{
		for ( int i = 1; i <= n - l + 1; i++ )
		{
			int j = i + l - 1;
			maximum = -99999;
			minimum = 99999;

			int p;

			for ( int k = i; k < j; k++ )
			{
				if ( op[k] == '+' )
				{
					double d = maximum;
					maximum = max ( maximum, Eval ( i, j, k, '+', 'M' ) );
					minimum = min ( minimum, Eval ( i, j, k, '+', 'm' ) );

					if ( maximum > d )
					{
						paren_pos[i][j] = k;
					}
				}

				else if ( op[k] == 'x' )
				{
					double d = maximum;
					maximum = max ( maximum, Eval ( i, j, k, 'x', 'M' ) );
					minimum = min ( minimum, Eval ( i, j, k, 'x', 'm' ) );

					if ( maximum > d )
					{
						paren_pos[i][j] = k;
					}
				}
			}

			max_matrix[i][j] = maximum;
			min_matrix[i][j] = minimum;
		}
	}
}

void print_paren ( int i, int j )
{
	if ( i == j )
	{
		cout << " " << num[i] << " ";
	}

	else
	{
		cout << "( ";
		print_paren ( i, paren_pos[i][j] );
		cout << " " << op[paren_pos[i][j]] << " ";
		print_paren ( paren_pos[i][j] + 1, j );
		cout << " )";

	}
}


int main()

{
	freopen ( "in_online.txt", "r", stdin );

	int n;
	cin >> n;

	for ( int i = 1; i <= n; i++ )
	{
		cin >> num[i];
	}

	cin >> op + 1;

	fill_matrix ( n );
	cout << max_matrix[1][n] << endl;
	cout << "" << endl;

	for ( int i = 1; i <= n; i++ )
	{
		for ( int j = 1; j <= n; j++ )
		{
			cout.width ( 5 );
			cout << max_matrix[i][j] << "   ";
		}

		cout << endl;
	}

	cout << "" << endl << endl;

	print_paren ( 1, n );

	return 0;
}
