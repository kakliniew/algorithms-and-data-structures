#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <stack>
#include <queue>

using namespace std;


class Graph{            // klasa, do przechowywania informacji o grafie, 
    int liczba_w;       //liczba wierzcholkow
    int liczba_k;       // liczba kolorow
    priority_queue<pair<int,pair<int,int>>> krawedzie;       //macierz sasiedztwa
    stack<int> odwiedzone;              // stos do przegladania wierzcholkow i cofania
    vector<int> colors;         //aktualne kolorowanie
    bool end = false;
    bool paintedAll = false;        // flaga czy pokolorowano wszystkie


    public:
    void setliczba_w(int liczba_w){
        this->liczba_w = liczba_w;
    };

    void setliczba_k(int liczba_k){
        this->liczba_k = liczba_k;
    };

    void setmacierz_sasiadow(vector<vector<int>> loaded_macierz){
        this->macierz_sasiadow = loaded_macierz;
    };

    int getliczba_k(){
        return this->liczba_k;
    }

    int getliczba_w(){
        return this->liczba_w;
    }


    void checkGraph(int current_W = 0){
        colors.resize(liczba_w, 0);
        odwiedzone.push(current_W);
        set<int> onStack;
        onStack.insert(current_W);
        while(!end){ 
            if(paintVertexIfPossible(current_W, onStack)){ // czy da sie pokolorowac kolorem wyzszym niz aktualny i zeby nie przeszkadzalo na stosie

                if(checkIfAllPainted()){    //jak wszystkie to koncz
                    paintedAll = true;
                    end = true;
                }else{          //jak nie to bierz kolejny wierzcholek na stos
                    
                    current_W++;
                    odwiedzone.push(current_W);
                    onStack.insert(current_W);
                }

            }else{          //jak sie nie da kolorowac to czysc kolor i zdejmij ze stosu
             
                colors[odwiedzone.top()] = 0;
                onStack.erase(odwiedzone.top());
                odwiedzone.pop();
                current_W = odwiedzone.top();
            }
            
            if(odwiedzone.size() == 1){     // jak pusty stos to koncz bez pozytywnego rezultatu
                end = true;
            }

        }
        if(paintedAll){
            printPaintingResults(colors);
        }
        else{
            cout<<"NIE"<<endl;
        }
    }

    void printGraph(){
        cout<<"Liczba wierzcholkow " << liczba_w << " liczba kolorow " << liczba_k <<endl;
        cout<<"Macierz sasiedztwa: " << endl;
        for(int i = 0; i < macierz_sasiadow.size(); i++){
            for(int j = 0; j < macierz_sasiadow[i].size(); j++){
                cout<<macierz_sasiadow[i][j]<<" ";
            }
            cout<<endl;
        }
    };


    bool paintVertexIfPossible(int current_W, set<int> onStack){
        vector<int> freeColors(liczba_k + 1,0);
        freeColors[0] = 1;
        for(int neighbor : findNeighbors(current_W)){
            if(onStack.count(neighbor)){
                if(colors[neighbor] != 0){
                    freeColors[colors[neighbor]] = 1;
                }
            }
        }
        for(int i = 1; i< freeColors.size(); i++){
            if(freeColors[i] ==  0 && i > colors[current_W]){
                colors[current_W] = i;
                return true;
            }
        }
        return false;
    }

    void printPaintingResults(vector<int> currentColors){
        for(int i = 0; i < currentColors.size(); i++){
            cout<<currentColors[i]<<" ";
        }
        cout<<endl;
    }

  
    

   set<int> findNeighbors(int current_W){       //znajdz jakiegokolwiek sasiada aktualnego wierzcholka
       set<int> currentNeighbors;
       for(int i = 0; i< liczba_w; i++){
            if(macierz_sasiadow[current_W][i] == 1){
               currentNeighbors.insert(i);

            }
        }
        return currentNeighbors;
   }

    string boolToStringPolish(bool value){
        return value ? "TAK" : "NIE";
    }

    bool checkIfAllPainted(){
        for(int color : colors){
            if(color == 0){
                return false;
            }
        }
        return true;
    }

};

class Graphs{

    vector<Graph> grafy;
    int liczbaGrafow = 0;

    public:
    Graphs(){
       // cout<<"Program do kolorowania grafow" << endl;
        loadFromConsole();
    };


    Graphs* loadFromConsole(){
      //  cout<<"Podaj liczbe grafow " << endl;
        cin>>liczbaGrafow;
        for(int i = 0; i<liczbaGrafow; i++){
            Graph currentGraph;
            int liczba_w, liczba_k;
            cin>>liczba_w>>liczba_k;
            currentGraph.setliczba_w(liczba_w);
            currentGraph.setliczba_k(liczba_k);
            vector<vector<int>> currentKrawedzie;
            for(int j = 0; j<currentGraph.getliczba_w(); j++)
            {   
                vector<int> currentRow;
                int v1;
                for(int k = 0; k<currentGraph.getliczba_w(); k++){
                    cin>>v1;
                    currentRow.push_back(v1);
                }
                currentKrawedzie.push_back(currentRow);
            }
            currentGraph.setmacierz_sasiadow(currentKrawedzie);
            grafy.push_back(currentGraph);
        }
        return this;
    }

    Graphs* printGraphs(){

        for(int i = 0; i< liczbaGrafow; i++){
            cout<<"Graf numer " << i+1 << endl;
            grafy[i].printGraph();
        }
        return this;
    }

    Graphs* checkGraphs(int starting_W){
        for(int i = 0; i< liczbaGrafow; i++){
           // cout<<"Graf numer " << i+1 << endl;
            grafy[i].checkGraph(starting_W);
        }
        return this;
    }

};


int main(){

    Graphs* grafy = new Graphs();
    grafy->checkGraphs(0);
    
    return 0;
}