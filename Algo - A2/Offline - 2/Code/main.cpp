#include <iostream>
#include <stdio.h>

using namespace std;

class Solver{
    const static int maxN = 100;

    int mat[maxN][maxN];
    int n, curX, curY;

    struct Point{
        int x; //row
        int y;//column
        Point(){}
        Point(int x, int y){
            this->x = x;
            this->y = y;
        }
        void setPoint(int x, int y){
            this->x = x;
            this->y = y;
        }
    };

    bool  isEqual(Point a, Point b){
        return a.x == b.x && a.y == b.y;
    }

    Point minimal(Point p, Point s, Point e){
        //it is assumed that the matrix is at least 2x2
        Point ret(p.x, p.y);
        int val = mat[p.x][p.y];

        if(p.x == s.x){ //first row
            if(p.y == s.y){//upper left corner
                if(val > mat[p.x][p.y + 1]){
                    ret.setPoint(p.x, p.y + 1);
                }
                else if(val > mat[p.x + 1][p.y]){
                    ret.setPoint(p.x + 1, p.  y);
                }
            }
            else if(p.y == e.y){//upper right corner
                if(val > mat[p.x][p.y - 1]){
                    ret.setPoint(p.x, p.y);
                }
                else if(val > mat[p.x + 1][p.y]){
                    ret.setPoint(p.x + 1, p.y);
                }
            }
            else{
                if (val > mat[p.x][p.y - 1]){
                    ret.setPoint(p.x, p.y - 1);
                }
                else if(val > mat[p.x + 1][p.y]){
                    ret.setPoint(p.x + 1, p.y);
                }
                else if(val > mat[p.x][p.y + 1]){
                    ret.setPoint(p.x, p.y + 1);
                }
            }
        }
        else if(p.x == e.x){
            if(p.y == s.y){//lower left corner
               if(val > mat[p.x][p.y + 1]){
                   ret.setPoint(p.x, p.y + 1);
               } else if (val > mat[p.x - 1][p.y]){
                   ret.setPoint(p.x - 1, p.y);
               }
            }
            else if(p.y == e.y){//lower right corner
                if(val > mat[p.x][p.y - 1]){
                    ret.setPoint(p.x, p.y - 1);
                }
                else if (val > mat[p.x - 1][p.y]){
                    ret.setPoint(p.x - 1, p.y);
                }
            }
            else{
                if(val > mat[p.x][p.y - 1]){
                    ret.setPoint(p.x, p.y - 1);
                }
                else if (val > mat[p.x - 1][p.y]){
                    ret.setPoint(p.x - 1, p.y);
                }
                else if (val > mat[p.x][p.y + 1]){
                    ret.setPoint(p.x, p.y + 1);
                }
            }
        }
        else if(p.y == s.y){
            if(val > mat[p.x][p.y + 1]){
                ret.setPoint(p.x, p.y + 1);
            }
            else if (val > mat[p.x + 1][p.y]){
                ret.setPoint(p.x + 1, p.y);
            }
            else if (val > mat[p.x - 1][p.y]){
                ret.setPoint(p.x - 1, p.y);
            }
        }
        else if(p.y == e.y){
            if(val > mat[p.x][p.y - 1]){
                ret.setPoint(p.x, p.y - 1);
            }
            else if (val > mat[p.x + 1][p.y]){
                ret.setPoint(p.x + 1, p.y);
            }
            else if (val > mat[p.x - 1][p.y]){
                ret.setPoint(p.x - 1 , p.y);
            }
        }
        else {//internal cell
            if(val > mat[p.x][p.y + 1]){
                ret.setPoint(p.x, p.y + 1);
            }
            else if (val > mat[p.x][p.y - 1]){
                ret.setPoint(p.x, p.y - 1);
            }
            else if (val > mat[p.x + 1][p.y]){
                ret.setPoint(p.x + 1, p.y);
            }
            else if (val > mat[p.x - 1][p.y]){
                ret.setPoint(p.x - 1, p.y);
            }
        }

        return ret;
    }


public:
    Solver(int n){
        this->n = n;
        curX = 0;
        curY = 0;
    }

    void insert(int entry){
        mat[curX][curY] = entry;
        if(curY == n - 1) {
            curY = 0;
            curX++;
        }
        else{
            curY++;
        }
    }

    Point solveHelper(Point s, Point e){ //incomplete
        if(isEqual(s, e)) return s;

        int minValue = mat[s.x][s.y];
        Point minPoint(s.x, s.y);
        int midX = s.x + (e.x - s.x) / 2, midY = s.y + (e.y - s.y) / 2;

        int i, j;
        i = s.x;
        j = s.y + 1;
        for(;j <= e.y;j++){
            int t = mat[i][j];
            if(mat[i][j] < minValue){
                minPoint.setPoint(i, j);
                minValue = mat[i][j];
            }
        }

        i = e.x;
        j = s.y;
        for(;j <= e.y;j++){
            if(mat[i][j] < minValue){
                minPoint.setPoint(i, j);
                minValue = mat[i][j];
            }
        }

        i = s.x + 1;
        j = s.y;
        for(;i < e.x;i++){
            if(mat[i][j] < minValue){
                minPoint.setPoint(i, j);
                minValue = mat[i][j];
            }
        }

        i = s.x + 1;
        j = e.y;
        for(;i < e.x;i++){
            if(mat[i][j] < minValue){
                minPoint.setPoint(i, j);
                minValue = mat[i][j];
            }
        }

        i = s.x + 1;
        j = midY;
        for(;i < e.x;i++){
            if(mat[i][j] < minValue){
                minPoint.setPoint(i, j);
                minValue = mat[i][j];
            }
        }

        i = midX;
        j = s.y + 1;
        for(;j <= e.y;j++){
            if(mat[i][j] < minValue){
                minPoint.setPoint(i, j);
                minValue = mat[i][j];
            }
        }

        Point t = minimal(minPoint, s, e);
        if(isEqual(t, minPoint)){
            return minPoint;
        }
        else{
            Point t_s, t_e;
            if(t.x < midX){
                if(t.y <midY){ //first quadrant
                    t_s.setPoint(s.x + 1, s.y + 1);
                    t_e.setPoint(midX - 1, midY - 1);
                }
                else{//2nd quadrant
                    t_s.setPoint(s.x + 1 , midY + 1);
                    t_e.setPoint(midX - 1 , e.y - 1);

                }
            }
            else{
                if(t.y < midY){ //3rd quadrant
                    t_s.setPoint( midX + 1 , s.y + 1);
                    t_e.setPoint( e.x - 1, midY - 1);
                }
                else{//4th quadrant
                    t_s.setPoint( midX + 1, midY + 1);
                    t_e.setPoint(e.x - 1, e.y - 1);
                }
            }
            return  solveHelper(t_s, t_e);
        }
    }

    void printLocalMinimal(){
        Point s(0, 0), e(n- 1, n - 1);
        Point t =  solveHelper(s, e);
        cout<<"(" << t.x << ", " << t.y << ")"<<endl;
    }

};

int main(){
    int n;
    cin>>n;

    Solver sol(n);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            int t;
            cin>>t;
            sol.insert(t);
        }
    }

    sol.printLocalMinimal();

    return 0;
}