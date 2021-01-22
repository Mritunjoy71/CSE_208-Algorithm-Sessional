#include<bits/stdc++.h>
#include<ctime>
using namespace std;
int TABLE_SIZE =10000;
int counts[3];
int seed;
struct HashNode
{
    string key;
    int value;
    HashNode *next;
    HashNode *prev;
    //HashNode *tail;
};
class probnode
{
public:
    string key;
    int value;
};

class HashMap
{
public:
    HashNode **htable, **top;
    probnode *pnode;
    bool *ifdelete;
    HashMap()
    {
        htable = new HashNode*[TABLE_SIZE];
        top = new HashNode*[TABLE_SIZE];
        pnode=new probnode[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            htable[i] = NULL;
            top[i] = NULL;
            pnode[i].key= "";
            pnode[i].value=0;
        }
    }
    ~HashMap()
    {
        delete [] htable;
        delete [] pnode;
    }

    int HashFunc1(string  key)
    {
        // int seed = 123;
        unsigned long index = 0;
        for(int i = 0; i < key.length(); i++)
        {
            index = (index * seed) + key[i];
        }
        return index % TABLE_SIZE;

    }

    int HashFunc2(string  key)
    {
        // int seed = 131;
        unsigned long index = 0;
        for(int i = 0; i < key.length(); i++)
        {
            index = (index * seed) + key[i];
        }
        return index % TABLE_SIZE;

    }
    int HashFunc3(string  key)
    {
        // int seed = 119;
        unsigned long index = 0;
        for(int i = 0; i < key.length(); i++)
        {
            index = (index * seed) + key[i];
        }
        return index % TABLE_SIZE;

    }



    void insert(string key, int value,int i)
    {
        int hash_val = HashFunc2(key);
        HashNode *entry = htable[hash_val];
        if (entry == NULL)
        {
            entry = new HashNode;
            entry->value = value;
            entry->key = key;
            entry->next = NULL;
            entry->prev = NULL;
            htable[hash_val] = entry;
            top[hash_val] = entry;
        }
        else
        {
            counts[i]=counts[i]+1;
            while (entry != NULL)
                entry = entry->next;
            entry = new HashNode;
            entry->value = value;
            entry->key = key;
            entry->next = NULL;
            entry->prev = top[hash_val];
            top[hash_val]->next = entry;
            top[hash_val] = entry;

            // cout<<"succ\n";
        }
    }

    void removekey(string key)
    {
        int hash_val = HashFunc2(key);
        HashNode *entry = htable[hash_val];
        if (entry == NULL)
        {
            cout<<"No Element found at key: "<<key<<endl;
            return;
        }

        while (entry != NULL)
        {
            if(entry->key==key)
            {
                if(entry->prev==NULL &&entry->next!=NULL)
                {
                    entry->next->prev=NULL;
                    htable[hash_val]=entry->next;
                    delete entry;
                    break;
                }
                if(entry->prev!=NULL && entry->next!=NULL)
                {
                    entry->prev->next=entry->next;
                    entry->next->prev=entry->prev;
                    delete entry;
                    break;
                }
                if (entry->next == NULL)
                {
                    if (entry->prev == NULL)
                    {
                        htable[hash_val] = NULL;
                        top[hash_val] = NULL;
                        delete entry;
                        break;
                    }
                    else
                    {
                        top[hash_val] = entry->prev;
                        top[hash_val]->next = NULL;
                        delete entry;
                        entry = top[hash_val];
                    }
                }
            }
            entry = entry->next;
        }
    }


    void getkey(string key)
    {
        int hash_val = HashFunc2(key);
        bool flag = false;
        HashNode* entry = htable[hash_val];
        if (entry != NULL)
        {
            while (entry != NULL)
            {
                if (entry->key == key)
                {
                    flag = true;
                    break;
                }

                entry = entry->next;
            }
        }
        /* if (flag)
                 {
                     cout<<"Element found at key "<<key<<": ";
                     cout<<entry->value<<endl;
                 }
                 */
        /* else
             cout<<"No Element found at key "<<key<<endl;
             */
    }




    ///Linear probing part

    void probinsert(string key,int value,int k)
    {
        int hash_val=HashFunc2(key);
        int hv;
        if(pnode[hash_val].value==0)
        {
            pnode[hash_val].key=key;
            pnode[hash_val].value=value;
            // cout<<hash_val<<"   "<<pnode[hash_val].key<<" "<<pnode[hash_val].value<<endl;

        }
        // cout<<pnode[hash_val].key<<endl;
        //cout<<pnode[hash_val].value<<endl;
        else
        {
            counts[k]++;
            for(int i=1; i<TABLE_SIZE; i++)
            {
                hv=(hash_val+i) %TABLE_SIZE;
                if(pnode[hv].value==0)
                {
                    pnode[hv].key=key;
                    pnode[hv].value=value;
                    // cout<<hv<<"   "<<pnode[hv].key<<" "<<pnode[hv].value<<endl;
                    break;
                }
            }
        }
    }

    void probsearch(string key)
    {
        int hash_val=HashFunc2(key);
        int hv;
        int flag;
        if(pnode[hash_val].key=="")
        {
            flag=0 ;
        }
        else
        {
            if(pnode[hash_val].key==key &&pnode[hash_val].value!=0)
            {
                flag=1;
               // cout<<key <<" is found at "<<hv<<" value "<<pnode[hv].value<<endl ;
            }
            else
            {
                for(int i=1; i<TABLE_SIZE; i++)
                {
                    hv=(hash_val+i)%TABLE_SIZE;

                    if(pnode[hv].key==key && pnode[hv].value!=0)
                    {
                        flag=1 ;
                       // cout<<key <<" is found at "<<hv<<" value "<<pnode[hv].value<<endl ;
                        break;
                    }

                }
            }
        }
      //  if(flag==0)
        //    cout<<key<<" is not found\n"  ;


    }

    void probdelete(string key)
    {
        int hash_val=HashFunc2(key);
        int flag,hv;
        if(pnode[hash_val].key=="" && pnode[hash_val].value==0)
        {
            flag=0;

        }
        else
        {
            if(pnode[hash_val].key==key && pnode[hash_val].value!=0)
            {
                flag=1;
                pnode[hash_val].value=0;
            }
            else
            {
                for(int i=1; i<TABLE_SIZE; i++)
                {

                    hv=(hash_val+i)%TABLE_SIZE;
                    if(pnode[hv].key=="" && pnode[hv].value==0)
                    {
                        flag=0;
                        break;
                    }
                    else
                    {
                        if(pnode[hv].key==key && pnode[hv].value!=0)
                        {
                            flag=1 ;
                            pnode[hv].value=0;
                        }

                    }
                }

            }
        }
        if(flag==0)
            cout<<key<<" does not existed\n"  ;
        else
            cout<<key <<" is deleted at "<<hv<<" value "<<pnode[hv].value<<endl ;


    }


    void probprint()
    {
        for(int i=0; i<TABLE_SIZE; i++)
        {
            if(pnode[i].key!="" && pnode[i].value!=0)
                cout<<i<<"  "<<pnode[i].key<<"  "<<pnode[i].value<<endl;
        }
    }


    void printhash()
    {
        int i;
        for(i=0; i<TABLE_SIZE; i++)
        {
            if(top[i]!=NULL)
            {
                HashNode *temp=htable[i];
                while(temp)
                {
                    cout<<i<<"  "<<temp->key<<" "<<temp->value<<"\n";
                    //printf("%d  %c  %d\n",i,temp->key,temp->value) ;
                    temp=temp->next;
                }
            }
        }
    }
};

                               ///MAIN FUNCTION

int main()
{
    counts[0]=counts[1]=counts[2]=0 ;
    srand(time(0));
    int i,j,k;
    int arr[3];
    arr[0]=131;
    arr[1]=137;
    arr[2]=119;

    printf("chaining->\n");
    for(k=0; k<3; k++)
    {
        seed=arr[k];
        HashMap hash;
        for(i=1; i<=TABLE_SIZE; i++)
        {
            string rs(5,'A');

            for (  j = 0; j <5; j++)
            {
                rs[j]='A'+(rand())%26;

            }
            hash.insert(rs,i,k);
        }

        // hash.printhash();
        printf("For hash function %d :\n",k+1);
        cout<<"collision is "<<counts[k]<<endl;

        clock_t tStart = clock() ;
        for(i=1; i<=TABLE_SIZE; i++)
        {
            string rs(5,'A');

            for ( j = 0; j <5; j++)
            {
                rs[j]='A'+(rand())%26;
            }
            hash.getkey(rs);
        }

        printf("Time taken: %lf s\n", ((clock() - tStart))/(double)CLOCKS_PER_SEC)  ;


    }
    printf("\n");


    ///  Linear probing

    counts[0]=counts[1]=counts[2]=0 ;
    printf("Linear probing->\n");
    for(k=0; k<3; k++)
    {
        seed=arr[k];
        HashMap hash;
        for(i=1; i<=TABLE_SIZE; i++)
        {
            string rs(5,'A');

            for (  j = 0; j <5; j++)
            {
                rs[j]='A'+(rand())%26;

            }
            hash.probinsert(rs,i,k);
        }

        // hash.printhash();
        printf("For hash function %d :\n",k+1);
        cout<<"collision is "<<counts[k]<<endl;


         clock_t tStart = clock() ;
         for(i=1; i<TABLE_SIZE; i++)
         {
             string rs(5,'A');

             for ( j = 0; j <5; j++)
             {
                 rs[j]='A'+(rand())%26;
             }
             hash.probsearch(rs);
         }

         printf("Time taken: %lf s\n", (clock() - tStart)/(double)CLOCKS_PER_SEC)  ;



    }
    printf("\n");


    return 0;
}






