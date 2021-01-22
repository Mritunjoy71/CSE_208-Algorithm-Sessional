#include<bits/stdc++.h>
using namespace std;
struct node
{
    int key;
    node *parent;
    char color;
    node *left;
    node *right;
};
struct node* makeNode(int key)
{
    node * Node =new node();
    Node->key = key;
    Node->left =NULL;
    Node->right = NULL;
    Node->parent=NULL;
    Node->color='r';
    return Node;
}
class redblackT
{
    struct node *q;
public :
    struct node *root;
    redblackT()
    {
        root= NULL;
        q=NULL;
    }

    void insertkey(int key)
    {
        struct node *p,*q;
        struct node *t=makeNode(key);
        p=root;
        q=NULL;
        if(root==NULL)
        {
            root=t;
            root->color='b';
        }
        else
        {
            while(p!=NULL)
            {
                q=p;
                if(t->key < p->key)
                    p=p->left;
                else
                    p=p->right;
            }
            t->parent=q;
            if(t->key < q->key)
                q->left=t;
            else
                q->right=t;
        }
        if(root!=t)
            insertfixup(t);

    }

    void leftrotate( struct node *x)
    {
        if(x->right==NULL)
            return ;
        else
        {
            node *y=x->right;
            if(y->left!=NULL)
            {
                x->right=y->left;
                y->left->parent=x;
            }
            else
                x->right=NULL;
            if(x->parent!=NULL)
                y->parent=x->parent;
            if(x->parent==NULL)
                root=y;
            else
            {
                if(x==x->parent->left)
                    x->parent->left=y;
                else
                    x->parent->right=y;
            }
            y->left=x;
            x->parent=y;
        }


    }

    void rightrotate( struct node *x)
    {

        if(x->left==NULL)
            return ;
        else
        {
            node *y=x->left;
            if(y->right!=NULL)
            {
                x->left=y->right;
                y->right->parent=x;
            }
            else
                x->left=NULL;
            if(x->parent!=NULL)
                y->parent=x->parent;
            if(x->parent==NULL)
                root=y;
            else
            {
                if(x==x->parent->left)
                    x->parent->left=y;
                else
                    x->parent->right=y;
            }
            y->right=x;
            x->parent=y;
        }


    }


    void insertfixup( struct node *z)
    {
        /* if(root==z)
         {
             z->color='b';
             return;
         }
         */
        while(z!=root && z->parent->color=='r')
        {
            //cout<<"done \n";
            if(z->parent==z->parent->parent->left)
            {
                //cout<<"done 1\n";
                struct node *y=z->parent->parent->right;
                //cout<<"done 2\n";
                if(y!=NULL && y->color=='r')
                {
                    //  cout<<"done 3\n";
                    z->parent->color='b';
                    y->color='b' ;
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                    //cout<<"done 3---\n";
                }

                else
                {
                    //cout<<"done 4\n";
                    if(z==z->parent->right)
                    {
                        //  cout<<"done 5\n";
                        z=z->parent;
                        leftrotate(z);
                        //cout<<"done 5--\n";
                    }
                    z->parent->color='b';
                    z->parent->parent->color='r';
                    rightrotate(z->parent->parent);
                    //cout<<"done 6\n";
                }

            }
            else
            {
                //cout<<"done 7\n";
                struct node *y=z->parent->parent->left;
                //cout<<"done 8\n";
                if(y!=NULL && y->color=='r')
                {
                    //  cout<<"done 8\n";
                    z->parent->color='b';
                    y->color='b' ;
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                    //cout<<"done 9\n";
                }
                else
                {
                    //cout<<"done 10\n";
                    if(z==z->parent->left)
                    {
                        //  cout<<"done 11\n";
                        z=z->parent;
                        rightrotate(z);
                        //cout<<"done 11--\n";
                    }
                    z->parent->color='b';
                    z->parent->parent->color='r';
                    leftrotate(z->parent->parent);
                    //cout<<"done 12\n";
                }

            }
        }
        root->color='b';


    }
    node* rbt_successor(node *x)
    {
        node *y=NULL;
        if(x->left!=NULL)
        {
            y=x->left;
            while(y->right!=NULL)
                y=y->right;
        }
        else
        {
            y=x->right;
            while(y->left!=NULL)
                y=y->left;
        }
        return y;
    }
    node* lookup(int key)
    {
        if(root==NULL)
        {
            cout<<"Empty Red Black Tree\n" ;
            return NULL ;
        }
        node *x=root;
        node* flag=NULL;
        while(x!=NULL&& flag==NULL)
        {
            if(x->key==key)
            {
                flag=x;
                break;
            }
            if(flag==NULL)
            {
                if(x->key<key)
                    x=x->right;
                else
                    x=x->left;
            }
        }
        return flag;

    }

    void deletekey(int key)
    {
        if(root==NULL)
        {
            cout<<"\nEmpty Tree." ;
            return ;
        }
        node* z=lookup(key);
        if(!z)
            cout<<key <<" is not found.\n";
        else
        {
            cout<<key <<" is deleted.\n";

            node *y= NULL;
            node *x= NULL;
            if(z->left==NULL||z->right==NULL)
                y=z;
            else
                y=rbt_successor(z);

            if(y->left!=NULL)
                x=y->left;
            else
            {
                if(y->right!=NULL)
                    x=y->right;
                else
                    x=NULL;
            }

            if(x!=NULL)
                x->parent=y->parent;
            if(y->parent==NULL)
                root=x;
            else if(y==y->parent->left)
                y->parent->left=x;
            else
                y->parent->right=x;
            if(y!=z)
            {
                z->color=y->color;
                z->key=y->key;
            }
            if(y->color=='b')
                deletefixup(x);


        }

    }

    void deletefixup(node *x)
    {
        node *w;
        while(x!=root&&x->color=='b')
        {
            if(x->parent->left==x)
            {
                w=x->parent->right;
                if(w->color=='r')
                {
                    w->color='b';
                    x->parent->color='r';
                    leftrotate(x->parent);
                    w=x->parent->right;
                }
                if(w->right->color=='b'&&w->left->color=='b')
                {
                    w->color='r';
                    x=x->parent;
                }
                else
                {
                    if(w->right->color=='b')
                    {
                        w->left->color=='b';
                        w->color='r';
                        rightrotate(w);
                        w=x->parent->right;
                    }
                    w->color=x->parent->color;
                    x->parent->color='b';
                    w->right->color='b';
                    leftrotate(x->parent);
                    x=root;
                }
            }
            else
            {
                w=x->parent->left;
                if(w->color=='r')
                {
                    w->color='b';
                    x->parent->color='r';
                    rightrotate(x->parent);
                    w=x->parent->left;
                }
                if(w->left->color=='b'&&w->right->color=='b')
                {
                    w->color='r';
                    x=x->parent;
                }
                else
                {
                    if(w->left->color=='b')
                    {
                        w->right->color='b';
                        w->color='r';
                        leftrotate(w);
                        w=x->parent->left;
                    }
                    w->color=x->parent->color;
                    x->parent->color='b';
                    w->left->color='b';
                    rightrotate(x->parent);
                    x=root;
                }
            }
            x->color='b';
            root->color='b';
        }
    }
    int calcNodeHeight(node  * node)
    {
        if(node==0) return -1;
        int l, r;
        l = calcNodeHeight(node->left);
        r = calcNodeHeight(node->right);
        if(l>r) return l+1;
        else return r+1;
    }

    void printInOrder(node *node, int height)
    {
        if(node==0) return ;
        printInOrder(node->left, height-1);
        printf("%d\t",node->key);
        printInOrder(node->right, height-1);
    }


    ///display
    void disp()
    {
        display(root);
    }
    void display(node *p)
    {
        if(root==NULL)
        {
            cout<<"\nEmpty Tree.";
            return ;
        }
        if(p!=NULL)
        {
            cout<<"\n\t NODE: ";
            cout<<"\n Key: "<<p->key;
            cout<<"\n Colour: ";
            if(p->color=='b')
                cout<<"Black";
            else
                cout<<"Red";
            if(p->parent!=NULL)
                cout<<"\n Parent: "<<p->parent->key;
            else
                cout<<"\n NILL  ";
            if(p->right!=NULL)
                cout<<"\n Right Child: "<<p->right->key;
            else
                cout<<"\n NILL ";
            if(p->left!=NULL)
                cout<<"\n Left Child: "<<p->left->key;
            else
                cout<<"\n NILL  ";
            cout<<endl;
            if(p->left)
            {
                cout<<"\n\nLeft:\n";
                display(p->left);
            }

            if(p->right)
            {
                cout<<"\n\nRight:\n";
                display(p->right);
            }

        }
    }
};

int main()
{
    int ch;
    redblackT rbt;
    while(1)
    {
        printf("1. Insert key   2. Lookup(search key)   3. Delete key   4. Print keys  5. Exit\n");
        cin>>ch;
        if(ch==1)
        {
            int key;
            cin>>key ;
            rbt.insertkey(key);
        }
        if(ch==2)
        {
            int key;
            cin>>key ;
            node* flag=rbt.lookup(key);
            if(flag)
                cout<<"True\n";
            else
                cout<<"False\n" ;
        }
        if(ch==3)
        {
            int key;
            cin>>key ;
            rbt.deletekey(key);
        }
        if(ch==4)
        {
            int height=rbt.calcNodeHeight(rbt.root);
            rbt.printInOrder(rbt.root,height);
            cout<<"\n";
        }
        if(ch==5)
        {
            return 0;
        }
    }
    return 0;
}



















