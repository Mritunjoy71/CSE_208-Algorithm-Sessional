#include <iostream>
#include <cmath>
#include <stdio.h>

#define   read(x)     freopen(x, "r", stdin)
#define   write(x)    freopen(x, "w", stdout)

using namespace std;

#define MAX_N_MACHINE 100
#define MAX_BUDGET 1000

int n;
int b;
double p[MAX_N_MACHINE];
int c[MAX_N_MACHINE];
double prob[MAX_N_MACHINE][MAX_BUDGET];

struct solutionNode{
    int i;
    int n;
    int b;

    void setNull(){
        b = n = - 1;
    }

    void setValues(int i, int n, int b){
        this->i = i;
        this->n = n;
        this->b = b;
    }

    bool isNull(){
        return b == -1 && n == - 1;
    }
};

solutionNode soln[MAX_N_MACHINE][MAX_BUDGET];

inline double calcProbability(int i, int a){
    //a numbers i th machines bought
    double t =  1 - pow(1 - p[i - 1], a);
    return t;
}

double maxProb(){
    /**base case*/
    for (int i = 0; i <= b; ++i){
        prob[0][i] = 1;
        soln[0][i].setNull();
    }

    for (int i = 1; i <= n; ++i){
        int t = c[i - 1];//c[i] must not be zero. bcoz then infinitely many machine could be sold
        for (int j = 0; j < t; ++j){
            prob[i][j] = 0;
            soln[0][i].setNull();
        }
    }
    /**end of base case*/

    for (int N = 1; N <= n; ++N){
        //here i is the size of the array, c
        for (int B = c[N - 1]; B <= b; ++B){
            /*recursive*/
            int k = B / c[N - 1];
            double maxProb = -1;
            int max_b , max_n, max_i;
            for (int i = 1; i <= k; ++i){
                double d = prob[N - 1][B - c[N-1] * i] ;
                d *= calcProbability(N, i);
                if(maxProb < d){
                    max_b = B - c[N-1] * i;
                    max_n = N - 1;
                    max_i = i;
                    maxProb = d;
                }
            }
            prob[N][B] = maxProb;
            soln[N][B].setValues(max_i, max_n, max_b);
            /*end of recursion*/
        }
    }
    return prob[n][b];
}

void printDPTable(){
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= b; ++j) {
            cout.width(10);
            cout<<prob[i][j];
        }
        cout<<"\n";
    }
}

void printSolution(int n, int b){
    if(soln[n][b].isNull()){
        return;
    }
    printSolution(soln[n][b].n, soln[n][b].b);
    cout<<soln[n][b].i<<" ";
}

int main(){

    read("D:\\BUET\\CSE 208 - Algo\\Offline\\Offline - 3\\Code\\testcases.txt");
    cout<<"Enter budget: ";
    cin>>b;
    cout<<b<<endl;
    cout<<"Enter total number of stages: ";
    cin>>n;
    cout<<"Enter the costs: ";
    for (int j = 0; j < n; ++j){
        cin>>c[j];
    }

    cout<<"Enter the probabilities: ";
    for (int i = 0; i < n; ++i){
        cin>>p[i];
    }

    cout<<"\nMax probability: ";
    double ans = maxProb();
    cout<<ans<<endl;
    if(ans != 0){
        cout<<"Solution: ";
        printSolution(n, b);
        cout<<endl<<endl;
    }
    printDPTable();
    return 0;
}