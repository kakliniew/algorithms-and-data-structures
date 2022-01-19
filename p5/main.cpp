#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


class Problem{          
    
    vector<pair<int,int>> points;
    int maxNumber = 0;

    public:
    void printPoints(){
        for(int i = 0; i < points.size(); i++){
            cout<< points[i].first << " " << points[i].second << endl;
        }
    };

    void addPoint(int x, int y){
        points.push_back(make_pair(x,y));
    }

    void findMaxColinear(){
        for(int i = 0; i < points.size(); i++){
            for(int j = i+1; j < points.size(); j++){
                int currentColinear = 2;
                for(int k = 0; k < points.size(); k++){
                    if(k != i && k != j && checkIfColinear(i,j,k)){

                        currentColinear++;
                    } 
                }
                if(currentColinear > maxNumber) maxNumber = currentColinear;
            }
        }
        
    }
    

    bool checkIfColinear(int i, int j, int k){
        int xa = points[i].first;
        int xb = points[j].first;
        int xc = points[k].first;
        int ya = points[i].second;
        int yb = points[j].second;
        int yc = points[k].second;
        if((xb - xa)*(yc-ya) == (yb-ya)*(xc-xa)) return true;
        else return false;
    }

    int  getResult(){
        return maxNumber;
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
        string current, previos = "";
        int num1,num2;
        Problem* problem = new Problem();
        while(getline(cin, current)){
            if(current.substr(0,2).compare("--")){
                istringstream iss(current);
                iss>>num1;
                iss>>num2;
                problem->addPoint(num1,num2);
                previos = current;
                
            } else if(previos.substr(0,2).compare("--")){
                previos = current;
                problemy.push_back(*problem);
                problem = new Problem();
                liczbaProblemow++;

            }  
        }
        return this;
    }


    void printResults(){
        for(int i = 0; i< problemy.size(); i++){
            cout << i+1 << ". " << problemy[i].getResult() << endl;
        }

    }

    void makeCounting(){
        for(int i = 0; i< problemy.size(); i++){
            problemy[i].findMaxColinear();
        }

    }

};


int main(){

    Problems* problems = new Problems();
    problems->makeCounting();
    problems->printResults();
    
   
    
    return 0;
}