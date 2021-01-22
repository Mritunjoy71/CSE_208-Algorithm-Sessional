
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <iomanip>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define RED 100
#define BLUE -100

using namespace std;

class Queue
{
	int queueInitSize ;
	int queueMaxSize;
	int * data;
	int length;
	int front;
	int rear;
  public:
	Queue();
	~Queue();
	void enqueue ( int item ); //insert item in the queue
	int dequeue(); //returns the item according to FIFO
	bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
	queueInitSize = 2 ;
	queueMaxSize = queueInitSize;
	data = new int[queueMaxSize] ; //allocate initial memory
	length = 0 ;
	front = 0;
	rear = 0;
}


void Queue::enqueue ( int item )
{
	if ( length == queueMaxSize )
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;

		for ( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}

		for ( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}

		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = ( front + 1 ) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if ( length == 0 )
	{
		return true ;
	}

	else
	{
		return false ;
	}
}


int Queue::dequeue()
{
	if ( length == 0 )
	{
		return NULL_VALUE ;
	}

	int item = data[rear] ;
	rear = ( rear + 1 ) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
	if ( data )
	{
		delete[] data;    //deallocate memory
	}

	data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
  public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem ( int item ) ;
	void insertItem ( int item ) ;
	void removeItem ( int item ) ;
	void removeItemAt ( int item );
	int getItem ( int position ) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem ( int newitem )
{
	int * tempList ;

	if ( length == listMaxSize )
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;

		for ( i = 0; i < length ; i++ )
		{
			tempList[i] = list[i] ; //copy all items from list to tempList
		}

		delete[] list ; //free the memory allocated before
		list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item

	length++ ;
}

int ArrayList::searchItem ( int item )
{
	int i = 0;

	for ( i = 0; i < length; i++ )
	{
		if ( list[i] == item )
		{
			return i;
		}
	}

	return NULL_VALUE;
}

void ArrayList::removeItemAt ( int position ) //do not preserve order of items
{
	if ( position < 0 || position >= length )
	{
		return ;    //nothing to remove
	}

	list[position] = list[length - 1] ;
	length-- ;
}


void ArrayList::removeItem ( int item )
{
	int position;
	position = searchItem ( item ) ;

	if ( position == NULL_VALUE )
	{
		return ;    //nothing to remove
	}

	removeItemAt ( position ) ;
}


int ArrayList::getItem ( int position )
{
	if ( position < 0 || position >= length )
	{
		return NULL_VALUE ;
	}

	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
	if ( length == 0 )
	{
		return true;
	}

	else
	{
		return false;
	}
}

void ArrayList::printList()
{
	int i;

	for ( i = 0; i < length; i++ )
	{
		printf ( "%d ", list[i] );
	}

	printf ( "Current size: %d, current length: %d\n", listMaxSize, length );
}

ArrayList::~ArrayList()
{
	if ( list )
	{
		delete [] list;
	}

	list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

	int* color;
	int* parent;
	int* dist;

  public:
	Graph ( bool dir = false );
	~Graph();
	void setnVertices ( int n );
	void addEdge ( int u, int v );
	void removeEdge ( int u, int v );
	bool isEdge ( int u, int v );
	int getDegree ( int u );
	void printAdjVertices ( int u );
	bool hasCommonAdjacent ( int u, int v );
	int getDist ( int u, int v );
	void printGraph();
	void bfs ( int source ); //will run bfs in the graph
	void dfs ( int source ); //will run dfs in the graph
	void isConnected();
	bool color_graph();
	int getNode();
	int getcolor ( int u )
	{
		return color[u];
	}
};


Graph::Graph ( bool dir )
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices ( int n )
{
	this->nVertices = n ;

	if ( adjList != 0 )
	{
		delete[] adjList ;    //delete previous list
	}

	adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge ( int u, int v )
{
	if ( u < 0 || v < 0 || u >= nVertices || v >= nVertices )
	{
		cout << "ERROR !!!" << endl;
		return;    //vertex out of range
	}

	this->nEdges++ ;

	adjList[u].insertItem ( v ) ;

	if ( !directed )
	{
		adjList[v].insertItem ( u ) ;
	}

	cout << "SUCCESSFULL ADDED" << endl;
}

void Graph::removeEdge ( int u, int v )
{
	if ( u < 0 || v < 0 || u >= nVertices || v >= nVertices || isEdge ( u, v ) == false )
	{
		cout << "ERROR !!!";

		if ( u < 0 || v < 0 || u >= nVertices || v >= nVertices ) cout << " NODE OUT OF BOUND" << endl;

		else cout << " NO EXISTING EDGE" << endl;

		return;    //vertex out of range
	}

	this->nEdges-- ;

	adjList[u].removeItem ( v ) ;

	if ( !directed )
	{
		adjList[v].removeItem ( u ) ;
	}

	cout << "SUCCESSFULL DELETED" << endl;
}

bool Graph::isEdge ( int u, int v )
{
	//returns true if (u,v) is an edge, otherwise should return false

	return ( adjList[u].searchItem ( v ) == NULL_VALUE ? false : true );
}

int Graph::getDegree ( int u )
{
	//returns the degree of vertex u

	if ( u < 0 || u >= nVertices )
	{
		return NULL_VALUE;    //vertex out of range
	}

	return adjList[u].getLength();
}

void Graph::printAdjVertices ( int u )
{
	//prints all adjacent vertices of a vertex u

	if ( u < 0 || u >= nVertices )
	{
		return;
	}

	int i = 0, j = adjList[u].getLength();

	cout << "Adjacent to " << u << " : " ;

	for ( i = 0; i < j; i++ )
	{
		cout << adjList[u].getItem ( i ) << "  ";
	}

	cout << endl;

	/*
	cout << "Adjacent to vertex " << u << ": ";
	adjList[u].printList();
	cout << endl;
	*/

}

bool Graph::hasCommonAdjacent ( int u, int v )
{
	//returns true if vertices u and v have common adjacent vertices

	if ( u < 0 || v < 0 || u >= nVertices || v >= nVertices )
	{
		return false;    //vertex out of range
	}

	for ( int i = 0; i < adjList[u].getLength(); i++ )
	{
		for ( int j = 0; j < adjList[v].getLength(); j++ )
		{
			if ( adjList[u].getItem ( i ) == adjList[v].getItem ( j ) )
			{
				return true;
			}
		}
	}

	return false;
}

void Graph::bfs ( int source )
{
	//complete this function
	//initialize BFS variables

	color = new int[nVertices];
	dist = new int[nVertices];
	parent = new int[nVertices];

	for ( int i = 0; i < nVertices; i++ )
	{
		color[i] = WHITE ;
		parent[i] = -1 ;
		dist[i] = INFINITY ;
	}

	Queue q ;

	color[source] = GREY;
	dist[source] = 0 ;

	q.enqueue ( source ) ;

	while ( !q.empty() )
	{
		//complete this part

		int u = q.dequeue();

		for ( int n = 0; n < adjList[u].getLength(); n++ )
		{
			int v = adjList[u].getItem ( n );

			if ( color[v] == WHITE )
			{
				color[v] = GREY;
				dist[v] = dist[u] + 1;
				parent[v] = u;
				q.enqueue ( v );
			}
		}

		color[u] = BLACK;
	}

	cout << "     _________________________________________" << endl;
	cout << endl << setw ( 12 ) << "Vertex" << setw ( 10 ) << "Color" << setw ( 10 ) << "Parent" << setw ( 13 ) << "Distance" << endl;
	cout << "     _________________________________________" << endl;

	for ( int x = 0; x < nVertices; x++ )
	{
		cout << setw ( 10 ) << x << setw ( 10 ) << color[x] << setw ( 10 ) << parent[x] << setw ( 13 ) << dist[x] << endl;
	}

	cout << "     _________________________________________" << endl;
}

bool Graph::color_graph()
{
	color = new int [nVertices];

	for ( int i = 0; i < nVertices; i++ )
	{
		color[i] = WHITE;
	}

	color[0] = RED;

	for ( int i = 0; i < nVertices; i++ )
	{
		int col = color[i];

		for ( int j = 0; j < adjList[i].getLength(); j++ )
		{
			int t = adjList[i].getItem ( j );

			if ( color[t] == WHITE && col != WHITE )
			{
				color[t] = -col;
			}

			else
				if ( color[t] == col && col != WHITE )
				{
					return false;
				}
		}
	}

	for ( int i = 0; i < nVertices; i++ )
	{
		int col = color[i];

		for ( int j = 0; j < adjList[i].getLength(); j++ )
		{
			int t = adjList[i].getItem ( j );

			if ( col != WHITE )
			{
				color[t] = -col;
			}
		}
	}

	return true;
}

int Graph::getDist ( int u, int v )
{
	//returns the shortest path distance from u to v
	//must call bfs using u as the source vertex, then use distance array to find the distance

	bfs ( u );
	return dist[v];

	//return INFINITY ;
}

void Graph::printGraph()
{
	printf ( "\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges );

	for ( int i = 0; i < nVertices; i++ )
	{
		printf ( "%d:", i );

		for ( int j = 0; j < adjList[i].getLength(); j++ )
		{
			printf ( " %d", adjList[i].getItem ( j ) );
		}

		printf ( "\n" );
	}
}

Graph::~Graph()
{
	//write your destructor here

	if ( adjList ) delete[] adjList;

	adjList = 0;

	if ( color ) delete[] color;

	if ( parent ) delete[] parent;

	if ( dist ) delete[] dist;

	color = 0;
	parent = 0;
	dist = 0;
}

void Graph :: isConnected()
{
	bfs ( 0 );
	int i;

	for ( i = 0; i < nVertices; i++ )
	{
		if ( dist[i] == INFINITY )
		{
			cout << endl << "FALSE" << endl;
			return;
		}
	}

	cout << endl << "TRUE" << endl;
	return;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main ( void )
{
	int n, e;
	Graph g;
	printf ( "Enter number of vertices: " );
	scanf ( "%d", &n );
	g.setnVertices ( n );

	printf ( "Enter number of edges: " );
	cin >> e;

	while ( e-- )
	{
		int x, y;
		cin >> x >> y;
		g.addEdge ( x - 1, y - 1 );
	}



	if ( g.color_graph() == false )
	{
		cout << "NO" << endl;
		return 0;
	}

	else
	{
		cout << "YES" << endl << endl;

		for ( int i = 0; i < n; i++ )
		{
			if ( g.getcolor ( i ) == RED )
			{
				cout << i + 1 << " ";
			}
		}

		cout << endl << endl;

		for ( int i = 0; i < n; i++ )
		{
			if ( g.getcolor ( i ) == BLUE )
			{
				cout << i + 1 << " ";
			}
		}

		/*
		        for ( int i = 0; i < n; i++ )
				{
					if ( g.getcolor ( i ) == WHITE || g.getcolor ( i ) )
					{
						cout << i << " ";
					}
				}
		*/
	}
}
