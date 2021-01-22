
#include <bits/stdc++.h>
using namespace std;

int main()
{
	struct edge
	{
		int u, v, weight;
	};

	int nVertices, nEdges, source;

	cout << "No. of vertices :    ";
	cin >> nVertices;

	cout << "No. of edges :       ";
	cin >> nEdges;

	cout << endl << endl;

	edge edges[nEdges];
	int dist[nVertices], parent[nVertices];

	for ( int i = 0; i < nVertices; i++ )
	{
		dist[i] = INT_MAX;
		parent[i] = -1;
	}

	for ( int i = 0; i < nEdges; i++ )
	{
		cout << "Edge " << i + 1 << " :  ";
		cin >> edges[i].u >> edges[i].v >> edges[i].weight;
	}

	cout << "Source :      ";
	cin >> source;
	dist[source] = 0;

	int u, v, weight;

	for ( int i = 0; i < nVertices - 1; i++ )
	{
		for ( int j = 0; j < nEdges; j++ )
		{
			u = edges[j].u;
			v = edges[j].v;
			weight = edges[j].weight;

			if ( dist[v] > dist[u] + weight )
			{
				dist[v] = dist[u] + weight;
				parent[v] = u;
			}
		}
	}

	for ( int j = 0; j < nEdges; j++ )
	{

		u = edges[j].u;
		v = edges[j].v;
		weight = edges[j].weight;

		if ( dist[v] > dist[u] + weight )
		{
			cout << "Negative weight cycle present" << endl;
		}
	}

	cout  << endl;
	cout << "Vertex       Distance      Parent" << endl;
	cout << "________________________________" << endl;

	for ( int i = 0; i < nVertices; i++ )
	{
		cout << "  " << i << "		" << dist[i] << "	    " << parent[i] << endl;
	}

	return 0;
}
