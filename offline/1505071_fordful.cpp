#include<bits/stdc++.h>
#define NULL_VALUE -999999
using namespace std;
#define NULL_VALUE -999999
int n, **G,**rG,**fG ;
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

bool bfs(int s, int t, int parent[])
{
    bool visited[n];
    memset(visited, 0, sizeof(visited));
    Queue q;
    q.enqueue(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.dequeue();

        for (int v=0; v<n; v++)
        {
            if (visited[v]==false && rG[u][v] > 0)
            {
                q.enqueue(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return (visited[t] == true);
}
void dfs(int s, bool visited[])
{
    visited[s] = true;
    for (int i = 0; i < n; i++)
        if (rG[s][i] && !visited[i])
            dfs(i, visited);
}

int fordFulkerson( int s, int t)
{
    int u, v,parent[n];

    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
            rG[u][v] = G[u][v];

    int max_flow = 0;
    while (bfs(s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rG[u][v]);
        }

        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            fG[u][v]+=path_flow;
            rG[u][v] -= path_flow;
            rG[v][u] += path_flow;
        }

        max_flow += path_flow;
    }



    return max_flow;
}

int main()
{
    int i,j,m;
    scanf("%d", &n);
    scanf("%d",&m);
    int u,v,w;
    G=new int*[n];
    rG=new int*[n];
    fG=new int *[n];
    for(i=0; i<n; i++)
    {
        G[i]=new int [n];
        rG[i]=new int[n];
        fG[i]=new int [n];
    }
    for(i=0; i<n; i++)
        for( j=0; j<n; j++)
        {
            G[i][j]=0;
            fG[i][j]=0;

        }
    for(i=0; i<m; i++)
    {
        scanf("%d %d %d",&u,&v,&w);
        G[u][v]=w;
    }
    printf("The source? ");
    int s;
    scanf("%d",&s);
    int t;
    printf("the sink? ");
    scanf("%d",&t);

    cout << "The maximum possible flow is " << fordFulkerson(s, t)<<endl;
    for (i=0; i<n; i++)
        for(j=0; j<n; j++)
        {
            if(fG[i][j]>0)
                printf("edge(%d,%d) flow %d\n",i,j,fG[i][j]);
        }
    bool visited[n];
    for(i=0; i<n; i++)
        visited[i]=false;
    dfs(s, visited);
    cout<<"min-cut edges\n";
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (visited[i] && !visited[j] && G[i][j])
                cout << i << " - " << j << endl;


    return 0;
}
