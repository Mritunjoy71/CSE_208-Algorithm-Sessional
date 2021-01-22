
#include <bits/stdc++.h>
using namespace std;

struct Edge
{
	int u, v, weight;
	bool isIncluded;
};


// A structure to represent a subset for union-find
struct Vertex
{
	int parent;
	int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find ( struct Vertex vertices[], int i )
{
	// find root and make root as parent of i (path compression)
	if ( vertices[i].parent != i )
		vertices[i].parent = find ( vertices, vertices[i].parent );

	return vertices[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union ( struct Vertex vertices[], int x, int y )
{
	int xroot = find ( vertices, x );
	int yroot = find ( vertices, y );

	// Attach smaller rank tree under root of high rank tree
	// (Union by Rank)
	if ( vertices[xroot].rank < vertices[yroot].rank )
		vertices[xroot].parent = yroot;

	else if ( vertices[xroot].rank > vertices[yroot].rank )
		vertices[yroot].parent = xroot;

	// If ranks are same, then make one as root and increment
	// its rank by one
	else
	{
		vertices[yroot].parent = xroot;
		vertices[xroot].rank++;
	}
}

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp ( const void* a, const void* b )
{
	struct Edge* a1 = ( struct Edge* ) a;
	struct Edge* b1 = ( struct Edge* ) b;
	return a1->weight > b1->weight;
}

// The main function to construct MST using Kruskal's algorithm
void KruskalMST ( Vertex vertices[], Edge edges[], int nEdges )
{

	for ( int i = 0; i < nEdges; i++ )
	{
		int u = edges[i].u;
		int v = edges[i].v;

		if ( find ( vertices, u ) != find ( vertices, v ) )
		{
			Union ( vertices, u, v );
			edges[i].isIncluded = true;
		}
	}
}

int main()
{

	int nVertices, nEdges;
	cin >> nVertices >> nEdges;

	Vertex vertices[nVertices];
	Edge edges[nEdges];

	for ( int i = 0; i < nVertices; i++ )
	{
		vertices[i].parent = i;
		vertices[i].rank = 0;
	}

	for ( int i = 0; i < nEdges; i++ )
	{
		cout << "Edge " << i + 1 << "  :  ";
		cin >> edges[i].u >> edges[i].v >> edges[i].weight;
		edges[i].isIncluded = false;
	}

	qsort ( edges, nEdges, sizeof ( Edge ), myComp );

	KruskalMST ( vertices, edges, nEdges );

	cout << endl << endl;

	for ( int i = 0; i < nEdges ; i++ )
	{
		Edge e = edges[i];

		if ( e.isIncluded == true )
		{
			cout << e.u << " -> " << e.v << "   weight = " << e.weight << endl;
		}
	}

	return 0;
}
