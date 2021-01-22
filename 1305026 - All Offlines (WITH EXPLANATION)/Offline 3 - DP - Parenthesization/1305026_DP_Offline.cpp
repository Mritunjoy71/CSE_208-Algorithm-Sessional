
#include <bits/stdc++.h>
using namespace std;

struct node
{
	double val, l, r, k;
};

vector<node> matrix[101][101];
vector<int> paren_pos[101][101];
double num[101];
char op[100];

double fill_matrix ( int n )
{

	for ( int i = 1; i <= n; i++ )
	{
		node p;
		p.val = num[i];

		matrix[i][i].push_back ( p );
	}

	for ( int l = 2; l <= n; l++ )
	{
		for ( int i = 1; i <= n - l + 1; i++ )
		{
			int j = i + l - 1;

			for ( int k = i; k < j; k++ )
			{

				int l_size = matrix[i][k].size();
				int r_size = matrix[k + 1][j].size();
				char ch = op[k];

				for ( int x = 0; x < l_size; x++ )
				{
					for ( int y = 0; y < r_size; y++ )
					{
						double l = matrix[i][k][x].val;
						double r = matrix[k + 1][j][y].val;

						node p;
						p.l = l;
						p.r = r;
						p.k = k;

						if ( ch == 'x' )
						{
							p.val = l * r;
							( matrix[i][j] ).push_back ( p );
						}

						else if ( ch == '+' )
						{
							p.val = l + r;
							( matrix[i][j] ).push_back ( p );
						}

						paren_pos[i][j].push_back ( k );
					}
				}
			}
		}
	}
}

void print_paren ( int start, int end, int val )
{
	if ( start == end )
	{
		cout << num[start];
	}

	else
	{
		int k;
		double l, r;

		int size = matrix[start][end].size();

		for ( int i = 0; i <= size; i++ )
		{
			if ( matrix[start][end][i].val == val )
			{
				k = matrix[start][end][i].k;
				l = matrix[start][end][i].l;
				r = matrix[start][end][i].r;
				break;
			}
		}

		cout << "( ";
		print_paren ( start, k, l );

		cout << " " << op[k] << " ";

		print_paren ( k + 1, end, r );
		cout << " )";
	}

}



int main()

{
	freopen ( "in_off.txt", "r", stdin );

	int n, k, cnt = 0;
	cin >> n;

	for ( int i = 1; i <= n; i++ )
	{
		cin >> num[i];
	}

	cin >> op + 1;
	cin >> k;

	cout << "" << endl;

	for ( int i = 1; i < n; i++ )
	{
		cout << num[i] << " " << op[i] << " ";
	}

	cout << num[n] << endl << endl;

	fill_matrix ( n );

	int size = ( matrix[1][n] ).size();

	for ( int i = 0; i < size; i++ )
	{
		if ( matrix[1][n][i].val == k )
		{
			cout << "YES" << endl << endl;
			cout << k << " = ";
			print_paren ( 1, n, k );
			cout << endl << endl;
			break;
		}
	}

	for ( int i = 0; i < size; i++ )
	{
		if ( matrix[1][n][i].val == k )
		{
			cnt++;
		}
	}

	cout << "Total number of ways = " << cnt << endl;

	return 0;
}
