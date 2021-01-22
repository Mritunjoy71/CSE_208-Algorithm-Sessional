#include<bits/stdc++.h>
using  namespace std;
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
#define MAX_TREE_HT 100
int n,**G;

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
    void enqueue(int item); //insert item in the queue
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


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
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
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
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

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    bool directed ;
    int *color;
    int  *dist;
    int *parent;
    int  *start;
    int *finish;
    int time;

public:
    ArrayList  * adjList ;
    int nVertices;
    int nEdges;
    Graph(bool dir = true);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    int  bfs(int source); //will run bfs in the graph

};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ; //set direction of the graph
    color=0;
    dist=0;
    parent=0;
    start=0;
    finish=0;


}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    color=new int[n];
    dist=new int[n];
    parent=new int[n];
    start=new int[n];
    finish=new int[n];

}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed)
    {
        adjList[v].insertItem(u) ;
    }

}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    if(!directed)
    {
        adjList[u].removeItem(v);
        adjList[v].removeItem(u);
    }
    else
        adjList[u].removeItem(v);


}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false; //vertex out of range
    if(adjList[u].searchItem(v)!=NULL_VALUE)
        return true;
    else
        return false;



}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices ) return NULL_VALUE; //vertex out of range
    return adjList[u].getLength();

}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices);
    {
        printf("Wrong input\n");
        return false;
    }
    int len=adjList[u].getLength();
    for (int i =0; i<len; i++)
    {
        if(adjList[v].searchItem(adjList[u].getItem(i))!=NULL_VALUE)
        {
            return true;
            break;
        }
    }
    return false;


}

int  Graph::bfs(int source,int t)
{

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GRAY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u;
        u=q.dequeue();
        int v;
        for(int j=0; j<adjList[u].getLength(); j++)
        {
            v=adjList[u].getItem(j);
            if(color[v]==WHITE)
            {
                color[v]=GRAY;
                dist[v]=dist[u]+1;
                parent[v]=u;
                q.enqueue(v);
            }

        }
        color[u]=BLACK;
    }
    if(color[t]!=WHITE)
        return 1;
    else
        return 0;
}



void Graph::printGraph()
{
    //dfs();
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));

        }
        printf("\n");
        //printf("\t");
        //printf(":(%d/%d)\n",start[i],finish[i]);

    }
}

Graph::~Graph()
{
    if(adjList) delete[] adjList;
    adjList=0;
    if(color) delete[] color;
    color=0;
    if(dist) delete[] dist;
    dist=0;
    if(parent) delete[] parent;
    parent=0;
    if(start) delete[] start;
    start=0;
    if(finish) delete[] finish;
    finish=0;
    exit(0);

}



//**********************Graph class ends here******************************


int fordFulkerson(int **G,int s,int t)
{
     int u, v;

    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates
                     // residual capacity of edge from i to j (if there
                     // is an edge. If rGraph[i][j] is 0, then there is not)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];

    int parent[V];  // This array is filled by BFS and to store path

    int max_flow = 0;  // There is no flow initially

    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}


int main()
{
    int i,m;
    Graph g;
    scanf("%d", &n);
    g.setnVertices(n);
    scanf("%d",&m);
    int u,v,w;
    G=new int*[n];
    for(i=0;i<n;i++)
        G[i]=new int [n];
    for(i=0; i<m; i++)
    {
        scanf("%d %d %d",&u,&v,&w);
        g.addEdge(u,v);
        G[u][v]=w;
    }
    printf("The source? ");
    int s;
    scanf("%d",&s);
    int t;
    printf("the sink? ");
    scanf("%d",&t);
    printf("maximum flow is %d\n",fordFulkerson(G,s,t));

    return 0;
}
