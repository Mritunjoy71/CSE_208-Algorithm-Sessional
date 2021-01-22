#include<bits/stdc++.h>
#define INFINITY 99999
#define NULL_VALUE -99999
int main()
{

    int n,m,i,j,k,u,v,w,flag=1;
    scanf("%d%d",&n,&m);
    int dist[n][n];
    int **path;
    path=new int*[n];
    for (i=0;i<n;i++)
        path[i]=new int[n];
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            path[i][j]=NULL_VALUE;
            if(i==j)
                dist[i][j]=0 ;
            else
                dist[i][j]= 0;

        }
    }
    for(i=0; i<m; i++)
    {
        scanf("%d%d",&u,&v);
        if(flag==0)
        {
            path[u][v]=u;
            dist[u][v]=1;
        }
        else
        {
            path[u-1][v-1]=u;
            dist[u-1][v-1]=1;
        }

    }
    printf("\n\nINITIAL GRAPH:\n");

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(dist[i][j]==INFINITY)

                printf("Inf\t");
            else
                printf("%d\t",dist[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

    for(k=0; k<n; k++)
    {
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                if(dist[i][j]!=0)
                {
                    dist[i][j]=dist[i][j]+dist[i][j]*dist[k][j];
                    path[i][j]=path[k][j];
                }
            }
        }
    }

    ///*****************Print************
    printf("All pair shortest path:\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(dist[i][j]==INFINITY)

                printf("Inf\t");
            else
                printf("%d\t",dist[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

    printf("Predecessor Matrix:\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(path[i][j]==NULL_VALUE)
                printf("null\t");
            else
                printf("%d\t",path[i][j]);
        }
        printf("\n");
    }



    return 0;

}
