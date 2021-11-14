#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <stack>
#include <conio.h>

using namespace std;


class Graph{            // klasa, do przechowywania informacji o grafie, 
    int liczba_w;       //liczba wierzcholkow
    int liczba_k;       // liczba kolorow
    vector<vector<int>> macierz_sasiadow;       //macierz sasiedztwa
    stack<int> odwiedzone;              // stos do przegladania wierzcholkow i cofania
    vector<int> colors;         //aktualne kolorowanie
    vector<set<int>> odwiedzoneZVertex;     // zablokowane z danego wierzcholka bo juz pokolorane i odwieodzone
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


    void checkGraph(int current_W){
        colors.resize(liczba_w, 0);
        odwiedzoneZVertex.resize(liczba_w);
        odwiedzone.push(current_W);
        colors[current_W] = 1;
        while(!end){ 
            int newNeighbor = findNeighborNotPaintedNotAlreadyVisited(current_W);
            bool foundNext = newNeighbor != current_W;
            if(foundNext){          // jesli znalazlo nastepny to dodaj do stosu odwiedzonych, oznacz jako odwiedzony i ustaw jako aktualny
                odwiedzone.push(newNeighbor);
                odwiedzoneZVertex[current_W].insert(newNeighbor);
                current_W = newNeighbor;
            }
            if(!foundNext || !paintVertexIfPossible(current_W)){ // jesli nie ma nastepnego lub malowanie aktualnego niemozliwe to cofaj
                int oldCurrent = current_W;
                odwiedzoneZVertex[current_W].clear();
                odwiedzone.pop();
                current_W = odwiedzone.top();
                odwiedzoneZVertex[current_W].insert(oldCurrent);
                colors[oldCurrent] = 0;             //wyczysc kolorowanie
            }
            if(odwiedzone.size() == 1){         // jesli wrocilismy do poczatku to konczymy bez skutku
                end = true;
            }
            if(odwiedzone.size() == liczba_w){          //jesli dostarlismy do ostatniego to konczymy i wyswietlamy malowanie
                paintedAll = true;  
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


    bool paintVertexIfPossible(int current_W){
        vector<int> freeColors(liczba_k + 1,0);
        freeColors[0] = 1;
        for(int neighbor : findNeighbors(current_W)){
           if(colors[neighbor] != 0){
               freeColors[colors[neighbor]] = 1;
           }
        }
        for(int i = 1; i< freeColors.size(); i++){
            if(freeColors[i] == 0){
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

   int findNeighborNotPaintedNotAlreadyVisited(int current_W){  // znajdz sasiada aktualnego wierzcholka, ktory nie jest pokolorowany i nie byl juz odwiedzany
        for(int i = 0; i < liczba_w; i++){

            if(macierz_sasiadow[current_W][i] == 1 && colors[i] == 0 && !odwiedzoneZVertex[current_W].count(i)){
               return i;
            }
        }
        return current_W;
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


};

class Graphs{

    vector<Graph> grafy;
    int liczbaGrafow = 0;

    public:
    Graphs(){
        cout<<"Program do kolorowania grafow" << endl;
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
            cout<<"Graf numer " << i+1 << endl;
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