#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <stack>

using namespace std;


class Graph{
    bool spojny = false;
    bool drzewo = false;
    bool cykle = false;
    int liczba_w;
    int liczba_k;
    vector<vector<int>> krawedzie;
    set<int> odwiedzone;
    set<int> czerwone;
    set<int> zielone;

    public:
    void setliczba_w(int liczba_w){
        this->liczba_w = liczba_w;
    };

    void setliczba_k(int liczba_k){
        this->liczba_k = liczba_k;
    };

    void setKrawedzie(vector<vector<int>> loadedKrawedzie){
        this->krawedzie = loadedKrawedzie;
    };

    vector<vector<int>> getkrawedzie(){
        return this->krawedzie;
    }

    int getliczba_k(){
        return this->liczba_k;
    }

    int getliczba_w(){
        return this->liczba_w;
    }

    void newcheckGraph(){
        for(auto krawedz : krawedzie){
            odwiedzone.insert(krawedz[0]);
            odwiedzone.insert(krawedz[1]);

            cout<<"krawedz " << krawedz[0] << " dalej " << krawedz[1] << " odwiedzone " << odwiedzone.size() << endl;
        }

    }

    void checkGraph(){
        int current_W = krawedzie[1][0];
        int previosW;
        stack<int> dfsStack;
        dfsStack.push(0);
        dfsStack.push(current_W);
        czerwone.insert(current_W);
        
        while(odwiedzone.size() < liczba_w){
            int znaleziony_sasiad = 0;
            if(znaleziony_sasiad = searchFristNotVisitedNeighbor(current_W)){
                cout<<"Znaleziony sasiad " << znaleziony_sasiad << endl;
                dfsStack.push(znaleziony_sasiad);
                if(czerwone.count(current_W)){
                    zielone.insert(znaleziony_sasiad);
                } else{
                    czerwone.insert(znaleziony_sasiad);
                }
                odwiedzone.insert(znaleziony_sasiad);
                previosW = current_W;
                current_W = znaleziony_sasiad;
                
            }else if(current_W == 0 && odwiedzone.size() < liczba_w){
                cout<<"koniec"<<endl;
                break;
            }
            else{
                cout<< current_W <<" nie ma kolejnego nieodwiedzonego sasiada"<<endl;
                dfsStack.pop();
                current_W = dfsStack.top();
                dfsStack.pop();
                previosW = dfsStack.top();
                dfsStack.push(current_W);
                cout<<"Powrot do " << current_W << " z poprzednim " << previosW << endl;

            }
        }
        cout<<"KONIEC: znaleziono " << odwiedzone.size() << " z " << liczba_w << endl;
    };

    void printGraph(){
        cout<<"Liczba wierzcholkow " << liczba_w << " liczba krawedzi " << liczba_k <<endl;
        for(int i = 0; i < krawedzie.size(); i++){
            cout<<krawedzie[i][0]<<" "<<krawedzie[i][1]<<endl;
        }
    };

    int searchFristNotVisitedNeighbor(int current_W){
        for(int i = 1; i < krawedzie.size(); i++){
            for(int j = 0; j < 2; j++){
                if(krawedzie[i][j] == current_W && !zielone.count(krawedzie[i][(j+1)%2]) && !czerwone.count(krawedzie[i][(j+1)%2])){
                    return krawedzie[i][(j+1)%2];
                }
            }
        }
        return 0;
    }


};

class Graphs{

    vector<Graph> grafy;
    int liczbaGrafow = 0;
    string filename;

    public:
    Graphs(string filename){
        this->filename = filename;
        loadGraphsFromFile();
    };

    void loadGraphsFromFile(){
        ifstream file(filename);
        if(file.is_open()){
            file>>liczbaGrafow;
            for(int i = 0; i<liczbaGrafow; i++){
                Graph currentGraph;
                int liczba_w, liczba_k;
                file>>liczba_w>>liczba_k;
                currentGraph.setliczba_w(liczba_w);
                currentGraph.setliczba_k(liczba_k);
                vector<vector<int>> currentKrawedzie;
                for(int j = 0; j<currentGraph.getliczba_k(); j++)
                {   
                    vector<int> currentRow;
                    int v1, v2;
                    file>>v1>>v2;
                    currentRow.push_back(v1);
                    currentRow.push_back(v2);
                    cout<<"current row" << v1 <<" " << v2 << endl;
                    currentKrawedzie.push_back(currentRow);
                }
                currentGraph.setKrawedzie(currentKrawedzie);
                grafy.push_back(currentGraph);
            }
        }
        else{
            cout<< filename << " - Nie ma takiego pliku!" << endl;
            exit(1);
        }
        file.close();
    
    }

    void loadFromConsole(){
        cout<<"Podaj liczbe grafow " << endl;
        cin>>liczbaGrafow;
        for(int i = 0; i<liczbaGrafow; i++){
            Graph currentGraph;
            int liczba_w, liczba_k;
            cout<<"Podaj liczbe wierzcholkow i krawedzi"<<endl;
            cin>>liczba_w>>liczba_k;
            currentGraph.setliczba_w(liczba_w);
            currentGraph.setliczba_k(liczba_k);
            vector<vector<int>> currentKrawedzie;
            for(int j = 0; j<currentGraph.getliczba_k(); j++)
            {   
                vector<int> currentRow;
                int v1, v2;
                cout<<"Podaj krawedz "<< j+1 << " dla grafu nr " << i+1<<endl;
                cin>>v1>>v2;
                currentRow.push_back(v1);
                currentRow.push_back(v2);
                //cout<<"current row" << v1 <<" " << v2 << endl;
                currentKrawedzie.push_back(currentRow);
            }
            currentGraph.setKrawedzie(currentKrawedzie);
            grafy.push_back(currentGraph);
        }
    }

    Graphs* printGraphs(){

        for(int i = 0; i< liczbaGrafow; i++){
            cout<<"Graf numer " << i+1 << endl;
            grafy[i].printGraph();
            cout<<endl;
        }
        return this;
    }

    Graphs* checkGraphs(){
        for(int i = 0; i< liczbaGrafow; i++){
            cout<<"Graf numer " << i+1 << endl;
            grafy[i].checkGraph();
            cout<<endl;
        }
        return this;
    }

};


int main(){
    Graphs* grafy = new Graphs("dane.txt");
    grafy->printGraphs()->checkGraphs();
   
    
    return 0;
}