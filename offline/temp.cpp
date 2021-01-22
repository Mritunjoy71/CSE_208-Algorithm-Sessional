#include <iostream>
#include <ctime>
using namespace std ;
void time_search(){
    clock_t start = clock() ;
    for(int i=0;i<10000;i++){
    }
    cout<<clock()-start/(double)CLOCKS_PER_SEC ;
}

int main(){
    time_search() ;
    return 0 ;
}