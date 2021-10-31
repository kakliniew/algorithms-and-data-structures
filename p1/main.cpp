#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <stack>

using namespace std;


class Graph{            // klasa, do przechowywania informacji o grafie, krawedzie w wektorze wektorow(wewnetrzny wektor zawiera dwie liczby int)
    bool spojny = true;
    bool drzewo = false;
    bool cykle = false;
    bool dwudzielny = true;
    int liczba_w;
    int liczba_k;
    int spojny_counter = 1;
    vector<vector<int>> krawedzie;
    set<int> odwiedzone;
    set<int> czerwone;
    set<int> zielone;
    set<int> usedKrawedzie;

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


    void checkGraph(){
        int current_W = krawedzie[0][0];  //od pierwszego wierzcholka
        int previosW;
        stack<int> dfsStack;        // stos do DFS
        dfsStack.push(0);
        dfsStack.push(current_W);
        czerwone.insert(current_W);
        odwiedzone.insert(current_W);
        
        while(odwiedzone.size() < liczba_w){                // szukamy az wszystkie wierzcholki przerobimy
            int znaleziony_sasiad;
            if(znaleziony_sasiad = searchFirstNotVisitedNeighbor(current_W)){
                dfsStack.push(znaleziony_sasiad);
                odwiedzone.insert(znaleziony_sasiad);
                previosW = current_W;
                current_W = znaleziony_sasiad;
                oznaczWierzcholki(znaleziony_sasiad, previosW);  //jak zielony to nowy czerwony i odwrotnie
                
            }else if(current_W == 0 && odwiedzone.size() < liczba_w){  //gdy nie ma sasiadow, a nie odwiedzilismy wszystkich
                spojny = false;
                current_W = searchFirstNotVisited();
                previosW = 0;
                spojny_counter++;
                dfsStack.push(current_W);
                czerwone.insert(current_W);
                odwiedzone.insert(current_W);
                
            }
            else{  // nie ma kolejnych nieodwiedzonych sasiadow to wracamy
                dfsStack.pop();
                current_W = dfsStack.top();
                dfsStack.pop();
                previosW = dfsStack.top();
                dfsStack.push(current_W);
            
            }
        }
        checkUsedKrawedzie();   //sprawdzamy, czy kazda krawedz zostala uzyta, jesli nie to cykl
        checkDwudzielnosc();    //sprawdzamy, czy wszystkie krawedzie lacza wierzchloki innych kolorow
        cout<<"Dwudzielnosc " << boolToStringPolish(dwudzielny) << endl;
        cout<<"Spojny " << boolToStringPolish(spojny) << " (" << spojny_counter << ")" << endl;
        cout<<"Cykle " << boolToStringPolish(cykle) << endl;
        cout<<"Drzewo " << boolToStringPolish(czyDrzewo())<<endl;
    };

    void printGraph(){
        cout<<"Liczba wierzcholkow " << liczba_w << " liczba krawedzi " << liczba_k <<endl;
        cout<<"Krawedzie: " << endl;
        for(int i = 0; i < krawedzie.size(); i++){
            cout<<krawedzie[i][0]<<" "<<krawedzie[i][1]<<endl;
        }
    };

    int searchFirstNotVisitedNeighbor(int current_W){
        for(int i = 0; i < krawedzie.size(); i++){
            for(int j = 0; j < 2; j++){
                if(!usedKrawedzie.count(i)){
                    if(krawedzie[i][j] == current_W ){
                        if(!odwiedzone.count(krawedzie[i][(j+1)%2])){
                            usedKrawedzie.insert(i);
                            return krawedzie[i][(j+1)%2];
                        }
                        else{
                            cykle = true;
                        }
                    }
                }
            }
        }
        return 0;
    }

    int searchFirstNotVisited(){
        for(int i = 1; i< liczba_w; i++){
            if(!odwiedzone.count(i)){
                return i;
            }
        }
        return 0;
    }

    void oznaczWierzcholki(int current_W, int previos_W){
        if(zielone.count(previos_W)){
            czerwone.insert(current_W);
        }else{
            zielone.insert(current_W);
        }
    }

    void checkDwudzielnosc(){
        for(auto krawedz : krawedzie){
            if(zielone.count(krawedz[0])){
                if(!czerwone.count(krawedz[1])){
                    dwudzielny = false;
                }
            }else{
                if(!zielone.count(krawedz[1])){
                    dwudzielny = false;
                }
            }
        }
    }

    string boolToStringPolish(bool value){
        if(value){
            return "TAK";
        }
        else{
            return "NIE";
        }
    }

    bool czyDrzewo(){
        if(spojny && !cykle){
            return true;
        }else{
            return false;
        }
    }

    void checkUsedKrawedzie(){
        for(int i = 0; i < krawedzie.size(); i++){
            if(!usedKrawedzie.count(i)){
                cykle = true;
            }
        }
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

    Graphs(){
        cout<<"Program do sprawdzania grafo1w" << endl;
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
            cout<<"Podaj liczbe wierzcholkow i krawedzi dla grafu " << i + 1<<endl;
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

    Graphs* checkLoadSourceAndLoad(){
        int wybor;
        cout<<"Jak chcesz zaladowac graf" << endl;
        cout<<"1. z pliku " << endl;
        cout<<"2. wpisujac w konsole " << endl;
        cin>>wybor;
        switch(wybor){
            case 1:{
                cout<<"Podaj nazwe pliku"<< endl;
                cin >> filename;
                loadGraphsFromFile();
                break;
            }
            case 2:{
                loadFromConsole();
                break;
            }
            default: {
                cout<<"Niepoprawny wybor "<< endl;
                exit(1);
            }
  
        }
        return this;

    }
};


int main(){
    Graphs* grafy = new Graphs();
    grafy->checkLoadSourceAndLoad()->printGraphs()->checkGraphs();;
    
    return 0;
}