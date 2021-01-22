#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>

using namespace std;
#define   read(x)     freopen(x, "r", stdin)
#define   write(x)    freopen(x, "w", stdout)

#define NEG_INFINITE -99999999
#define INFINITE 99999999
#define MAX_N 100
#define MAX_JOBS 100

int n, nJobs;
int job[MAX_JOBS];

class MinTimeData{
protected:
    /**
    * In this problem we must determine the minimum possible time to perform the jobs.
    * So we must keep track of the minimum time while determining all the possible
    * solutions.
    *
    * To do so, we need to remember the minimum possible time of the solutions explored
    * so far. That's why "minTime" variable comes.
    *
    * Again we also need to know the solution which gives the minimum time. So we use
    * minSol[][] and minCursor[] to keep track of the optimal solution.
    */
    static int minTime;
    static int minSol[MAX_N][MAX_JOBS];
    static int minCursor[MAX_N];
public:
    static void printSol(){
        cout<<"Min Time: "<<minTime<<endl;
        cout<<"Solution:"<<endl;
        for (int j = 0; j < n; ++j){
            cout<<j<<": ";
            for (int i = 0; i < minCursor[j]; ++i) {
                cout<<minSol[j][i]<<", ";
            }
            cout<<endl;
        }
    }
};

int MinTimeData::minTime ;
int MinTimeData::minSol[MAX_N][MAX_JOBS];
int MinTimeData::minCursor[MAX_N];

class MinTimeBB:private MinTimeData{
    /**
     * In backtracking, we must have a way to store the partial solution.
     * In this case, we need a 2D array to store the partial solution. It is sol[][]
     * In case of any array, we must remember the its size. that's why cursor[].
     * cursor[i] = the size of the array sol[i]
     * */
    int sol[MAX_N][MAX_JOBS];
    int cursor[MAX_N];

    int getSum(int i){
        int sum = 0;
        for (int j = 0; j < cursor[i]; ++j){
            sum += sol[i][j];
        }
        return sum;
    }

    int getMaxSum(){
        int maxSum = NEG_INFINITE;
        for (int i = 0; i < n; ++i) {
            maxSum = max(maxSum, getSum(i));
        }
        return maxSum;
    }

    int getMinSum(){
        int minSum = INFINITE;
        for (int i = 0; i < n; ++i) {
            minSum = min(minSum, getSum(i));
        }
        return minSum;
    }

    void copySolution(){
        for (int i = 0; i < n; ++i) {
            minCursor[i] = cursor[i];
        }
        for (int j = 0; j < n ; ++j) {
            for (int i = 0; i < cursor[j]; ++i) {
                minSol[j][i] = sol[j][i];
            }
        }
    }

    int lowerBound(int i){
        int earliestTime = getMinSum();
        double sum = 0;
        for (int j = i; j < nJobs; ++j){
            sum += job[j];
        }
        return (earliestTime +(int)ceil(sum / n));
    }

public:
    MinTimeBB(){
        //initialize the cursor[] array
        for (int i = 0; i < n; ++i){
            cursor[i] = 0;
        }
    }

    int calMinTime(int i){

        if(i == nJobs){
            int t = getMaxSum();
            if(t < minTime){
                minTime = t;
                copySolution();
            }
            return t;
        }
        int lb = lowerBound(i);
        if(lowerBound(i) >= minTime){
            return INFINITE;
        }
        int LocalMinTime = INFINITE;
        for (int j = 0; j < n; ++j) {
            sol[j][cursor[j]++] = job[i];
            LocalMinTime = min(LocalMinTime, calMinTime(i + 1));
            cursor[j]--;
        }
        return LocalMinTime;
    }


};

bool cmp(int a, int b){
    return a > b;
}

class MinTimeGreedy:private MinTimeData{
    int sum[MAX_N];
public:
    MinTimeGreedy(){
        for (int i = 0; i < n; ++i) {
            sum[i] = 0;
        }
    }
    int getMinSumProcessor(){
        int min_i = 0;
        int min_sum = sum[0];
        for (int i = 1; i < n; ++i){
            if(min_sum > sum[i]){
                min_i = i;
                min_sum = sum[i];
            }
        }
        return min_i;
    }
    void calMinTime(){
        sort(job, job + nJobs, cmp);

        for (int i = 0; i < n; ++i){
            sum[i] = 0;
        }

        for (int j = 0; j < nJobs; ++j){
            int i = getMinSumProcessor();
            sum[i] += job[j];
            minSol[i][minCursor[i]++] = job[j];
        }

        int maxSum = sum[0];
        for (int k = 1; k < n; ++k) {
            if(maxSum < sum[k]) maxSum = sum[k];
        }
        minTime = maxSum;
    }
};

int main(){
    read("D:\\BUET\\CSE 208 - Algo\\Offline\\Offline - 4\\input.txt");

    cin>>n>>nJobs;
    for (int i = 0; i < nJobs; ++i){
        cin>>job[i];
    }

    MinTimeGreedy gd;
    gd.calMinTime();
    MinTimeBB bb;
    bb.calMinTime(0);
    MinTimeData::printSol();

    return 0;
}



