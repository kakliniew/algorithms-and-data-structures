#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


class Problem{          
    
    vector<pair<int,int>> points;
    int liczbaW = 0;
    pair<int, int> special_point;
    pair<int, int> helpful_point = make_pair(1000001, 1000001);

    public:
    void printPoints(){
        for(int i = 0; i < points.size(); i++){
            cout<< points[i].first << " " << points[i].second << endl;
        }
    };

    void addPoint(int x, int y){
        points.push_back(make_pair(x,y));
    }

    void addSpecialPoint(int x, int y){
        special_point = make_pair(x,y);
    }

    void setLiczbaW(int liczbaX){
        liczbaW = liczbaX;
    }

    bool checkIfInside(){
        int counter = 0;
        for(int i = 0; i < liczbaW ; i++){
            int j = (i+1) % (liczbaW);

            if(checkEndOfPoint(points[i].first, points[j].first, special_point.first, points[i].second, points[j].second, special_point.second)){
                return true;
            }
    
            int d1 = countDet(points[i].first, points[j].first, special_point.first, points[i].second, points[j].second, special_point.second);
            int d2 = countDet(points[i].first, points[j].first, helpful_point.first, points[i].second, points[j].second, helpful_point.second);
            int d3 = countDet(special_point.first, helpful_point.first, points[i].first, special_point.second, helpful_point.second, points[i].second);
            int d4 = countDet(special_point.first, helpful_point.first, points[j].first, special_point.second, helpful_point.second, points[j].second);
           
           if((d1>0&&d2<0||d1<0&&d2>0)&&(d3>0&&d4<0||d3<0&&d4>0))
            {
                counter ++;
            }

        }   

        return counter%2 != 0;
    }

    void printResult(){
        if(checkIfInside()) cout << "TAK" << endl;
        else cout << "NIE" << endl;
    }   

    int countDet(int x0, int x1, int x2, int y0, int y1, int y2){
        return x0*y1 + x1*y2 + x2*y0 - x1*y0 - x2*y1 - x0*y2;
    }

    bool checkEndOfPoint(int x0, int x1, int x2, int y0, int y1, int y2){
        return (x0 == x2 && y0 == y2) || (x1 == x2 && y1 == y2);
    }

};


class Problems{

    vector<Problem> problemy;
    int liczbaProblemow = 0;

    public:
    Problems(){
        loadFromStdIn();
    };

    
    Problems* loadFromStdIn(){
        string current;
        getline(cin, current);
        istringstream iss(current);
        iss>>liczbaProblemow;
        for(int i = 0; i < liczbaProblemow; i++){
            Problem* problem = new Problem();
            getline(cin, current);
            int x,y, liczbaX;
            istringstream iss(current);
            iss>>liczbaX;
            problem->setLiczbaW(liczbaX);
            iss>>x;
            iss>>y;
            problem->addSpecialPoint(x,y);
            for(int j = 0; j < liczbaX; j++){
                getline(cin, current);
                istringstream iss(current);
                iss>>x;
                iss>>y;
                problem->addPoint(x,y);
            }
            problemy.push_back(*problem);
        }
        return this;
    }


    void printResults(){
        for(int i = 0; i< problemy.size(); i++){
            problemy[i].printResult();
        }

    }

     void printProblems(){
        for(int i = 0; i< problemy.size(); i++){
            cout<<"numer problemu " << i+1 << endl;
            problemy[i].printPoints();
        }

    }



};


int main(){

    Problems* problems = new Problems();
    // problems->printProblems();
    problems->printResults();
    
   
    
    return 0;
}