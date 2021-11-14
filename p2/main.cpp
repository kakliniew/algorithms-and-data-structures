#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <stack>
#include <conio.h>

using namespace std;


class Graph{            // klasa, do przechowywania informacji o grafie, krawedzie w wektorze wektorow(wewnetrzny wektor zawiera dwie liczby int)
    int liczba_w;
    int liczba_k;
    vector<vector<int>> macierz_sasiadow;
    stack<int> odwiedzone;
    vector<int> colors;
    vector<set<int>> odwiedzoneZVertex;
    bool comeback = false;
    bool end = false;
    bool paintedAll = false;


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
        cout<<"aktualna licza "<<current_W<<endl;
        cout<<odwiedzoneZVertex.size()<< endl;
        set<int> alreadyVisitedFromCurrent;
        while(!end){ 
            cout<<"petla in" << endl; 
            int newNeighbor = findNeighbor(current_W);
            bool foundNext = newNeighbor != current_W;
            if(foundNext){ 
            odwiedzone.push(newNeighbor);
            odwiedzoneZVertex[current_W].insert(newNeighbor);
            current_W = newNeighbor;
           
            }
            
            if(!foundNext || !paintVertex(current_W)){
                cout<<"cofamy" << endl;
                
                current_W = odwiedzone.top();
                odwiedzone.pop();
                
                // cofamy
            }
            cout<<"size stosu "<< odwiedzone.size() << endl;
            if(odwiedzone.size() == 1){
                end = true;
            }
            if(odwiedzone.size() == liczba_w){
                paintedAll = true;
                end = true;
            }
        }
        cout<<"Pokolorowano " << paintedAll<< endl;
        if(paintedAll){
            printResults(colors);
        }
        cout<<"end!"<<endl;
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


    bool paintVertex(int current_W){
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
        cout<<" Nie znaleziono kolorsu" << endl;
        return false;
    }

    void printResults(vector<int> currentColors){
        for(int i = 0; i < currentColors.size(); i++){
            cout<<currentColors[i]<<" ";
        }
        cout<<endl;
    }

   int findNeighbor(int current_W){
        for(int i = 0; i < liczba_w; i++){
            cout<<"szukamy" << current_W <<  endl;
            if(macierz_sasiadow[current_W][i] == 1 && colors[i] == 0 && !odwiedzoneZVertex[current_W].count(i)){
               cout<<"znaleziony sasiad " << current_W << " to: " << i << " odwiedzone: " << odwiedzoneZVertex[current_W].count(i)<< endl;
               return i;
            }
        }
        return current_W;
   }

   set<int> findNeighbors(int current_W){
       set<int> currentNeighbors;
       for(int i = 0; i< liczba_w; i++){
            if(macierz_sasiadow[current_W][i] == 1){
               currentNeighbors.insert(i);
               cout<<"znaleziony sasiad " << current_W << " to " << i << endl;
            }
        }
        return currentNeighbors;
   }

    string boolToStringPolish(bool value){
        if(value){
            return "TAK";
        }
        else{
            return "NIE";
        }
    }


};

class Graphs{

    vector<Graph> grafy;
    int liczbaGrafow = 0;

    public:
    Graphs(){
        cout<<"Program do sprawdzania grafo1w" << endl;
        loadFromConsole();
    };


    Graphs* loadFromConsole(){
      //  cout<<"Podaj liczbe grafow " << endl;
        cin>>liczbaGrafow;
        for(int i = 0; i<liczbaGrafow; i++){
            Graph currentGraph;
            int liczba_w, liczba_k;
           // cout<<"Podaj liczbe wierzcholkow i krawedzi dla grafu " << i + 1<<endl;
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

        for(int i = 1; i< liczbaGrafow; i++){
            cout<<"Graf numer " << i+1 << endl;
            grafy[i].printGraph();
            cout<<endl;
        }
        return this;
    }

    Graphs* checkGraphs(int starting_W){
        for(int i = 1; i< liczbaGrafow; i++){
            cout<<"Graf numer " << i+1 << endl;
            grafy[i].checkGraph(starting_W);
            cout<<endl;
        }
        return this;
    }

};


int main(){

    Graphs* grafy = new Graphs();
    grafy->printGraphs()->checkGraphs(0);
    
    return 0;
}