#include<bits\stdc++.h>
using namespace std;

void global_allignment(char *s,char *t,int m,int n,int mat,int mis,int gap)
{
    int i,j;
    int diag,up,left;
    int **table=new int*[n+1];
    for(i=0; i<n+1; i++)
        table[i]=new int[m+1];
    for(i=0; i<=m; i++)
        table[0][i]=i*gap;
    for(i=0; i<=n; i++)
        table[i][0]=i*gap;

    for(i=1; i<n+1; i++)
    {
        for(j=1; j<m+1; j++)
        {
            if(t[i-1]==s[j-1])
                diag=table[i-1][j-1]+mat;
            else
                diag=table[i-1][j-1]+mis;
            up=table[i-1][j]+gap;
            left=table[i][j-1]+gap;
            table[i][j]=max(diag,max(up,left));

        }
    }
    for(i=0; i<=n; i++)
    {
        for(j=0; j<=m; j++)
        {
            printf("%d\t",table[i][j]) ;
        }
        printf("\n");
    }

    string A="";
    string B="";
    //cout<<A<<endl;
    //cout<<B;
    i=n;
    j=m;
    while(i>0 ||j>0)
    {
        int p=0;
        if(t[i-1]==s[j-1])
            p=mat;
        else
            p=mis;
        if(i>0 && j>0 &&table[i][j]==table[i-1][j-1]+p)
        {
            A=t[i-1]+A;
            B=s[j-1]+B;
            i--;
            j--;
        }
        else if(i>0 && table[i][j]==table[i-1][j]+gap)
        {
            A=t[i-1]+A;
            B="_"+B;
            i--;
        }
        else
        {
            A="_"+A;
            B=s[j-1]+B ;
            j--;
        }
    }


    cout<<B<<endl;
    cout<<A<<endl;
    cout<<table[n][m]<<"\n";


}

void local_allignment(char *s,char *t,int m,int n,int mat,int mis,int gap)
{
    int i,j;
    int diag,up,left;
    int **table=new int*[n+1];
    for(i=0; i<n+1; i++)
        table[i]=new int[m+1];
    for(i=0; i<m+1; i++)
        table[0][i]=0;
    for(i=0; i<n+1; i++)
        table[i][0]=0;

    for(i=1; i<n+1; i++)
    {
        for(j=1; j<m+1; j++)
        {
            if(t[i-1]==s[j-1])
                diag=table[i-1][j-1]+mat;
            else
                diag=table[i-1][j-1]+mis;
            up=table[i-1][j]+gap;
            left=table[i][j-1]+gap;
            int maxm;
            maxm=max(diag,max(up,left));
            if(maxm<0)
                table[i][j]=0;
            else
                table[i][j]=maxm;


        }
    }
    for(i=0; i<=n; i++)
    {
        for(j=0; j<=m; j++)
        {
            printf("%d\t",table[i][j]) ;
        }
        printf("\n");
    }

    //cout<<table[n][m]<<"\n";
    int ii,jj,k,l;
    int max = table[0][0];
    for (int ii = 0; ii <= n; ii++)
    {
        for (int jj = 0; jj <= m; jj++)
        {
            if (table[ii][jj] >= max)
            {
                max = table[ii][jj];
                k=ii;
                l=jj;

            }
        }
    }

    string A="";
    string B="";
    //cout<<A<<endl;
    //cout<<B;
    i=k;
    j=l;
    //cout<<i<<endl<<j;
    while(i>0 ||j>0)
    {
        if(table[i][j]==0)
            break;
        int p=0;
        if(t[i-1]==s[j-1])
            p=mat;
        else
            p=mis;
        if(i>0 && j>0 &&table[i][j]==table[i-1][j-1]+p)
        {
            A=t[i-1]+A;
            B=s[j-1]+B;
            i--;
            j--;
        }
        else if(i>0 && table[i][j]==table[i-1][j]+gap)
        {
            A=t[i-1]+A;
            B="_"+B;
            i--;
        }
        else
        {
            A="_"+A;
            B=s[j-1]+B ;
            j--;
        }
    }


    cout<<B<<endl;
    cout<<A<<endl;
    cout<<max<<endl;

}


int main ()
{
    int m,n,mat,mis,gap;
    while(1)
    {
        scanf("%d%d%d%d%d",&m,&n,&mat,&mis,&gap);
        char *s,*t;
        s=new char[m];
        t=new char[n];
        scanf("%s",s);
        scanf("%s",t);
        global_allignment(s,t,m,n,mat,mis,gap);
        local_allignment(s,t,m,n,mat,mis,gap);
    }
    return 0;

}
