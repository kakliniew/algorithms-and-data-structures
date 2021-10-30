#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <stack>

using namespace std;

vector<vector<vector<int>>> loadFromFile(string filename){
    vector<vector<vector<int>>> matrixes;
    ifstream file(filename);
    if(file.is_open()){
        int liczba_zestawow;
        file>>liczba_zestawow;
        for(int i = 0; i<liczba_zestawow; i++){
            int liczba_w, liczba_k;
            vector<vector<int>> currentGraph;
            file>>liczba_w>>liczba_k;
            currentGraph.push_back(vector<int>{liczba_w,liczba_k});
            for(int j = 0; j<liczba_k; j++)
            {   
                vector<int> currentRow;
                int v1, v2;
                file>>v1>>v2;
                currentRow.push_back(v1);
                currentRow.push_back(v2);
                //cout<<"current row" << v1 <<" " << v2 << endl;
                currentGraph.push_back(currentRow);
            }
            matrixes.push_back(currentGraph);
        }
    }
    else{
        cout<< filename << " - Nie ma takiego pliku!" << endl;
        exit(1);
    }
    file.close();
    return matrixes;
}

void printGraphs(vector<vector<vector<int>>> matrixes){
    for(int i = 0; i< matrixes.size(); i++){
        cout<<"Graf nr " << i+1 <<endl;
        for(int j = 0; j<matrixes[i].size(); j++){
           cout<<matrixes[i][j][0]<<" "<<matrixes[i][j][1]<<endl;
        }
        cout<<endl;
    }

}

int searchFristNotVisitedNeighbor(vector<vector<int>> matrix, set<int> odwiedzone_zielone, set<int> odwiedzone_czerwone, int current_W){
    for(int i = 1; i < matrix.size(); i++){
        for(int j = 0; j < 2; j++){
            if(matrix[i][j] == current_W && !odwiedzone_zielone.count(matrix[i][(j+1)%2]) && !odwiedzone_czerwone.count(matrix[i][(j+1)%2])){
                return matrix[i][(j+1)%2];
            }
        }
    }
    return 0;
}

void doDfs(vector<vector<int>> matrix){
    int liczba_w = matrix[0][0];
    int liczba_k = matrix[0][1];
    set<int> odwiedzone_zielone;
    set<int> odwiedzone_czerwone;
    int current_W = matrix[1][0];
    stack<int> dfsStack;
    dfsStack.push(0);
    dfsStack.push(current_W);
    odwiedzone_czerwone.insert(current_W);
    int previosW;
    while(odwiedzone_czerwone.size() + odwiedzone_czerwone.size() < liczba_w){
        int znaleziony_sasiad = 0;
        if(znaleziony_sasiad = searchFristNotVisitedNeighbor(matrix, odwiedzone_zielone, odwiedzone_czerwone, current_W)){
            cout<<"Znaleziony sasiad " << znaleziony_sasiad << endl;
            dfsStack.push(znaleziony_sasiad);
            if(odwiedzone_czerwone.count(current_W)){
                odwiedzone_zielone.insert(znaleziony_sasiad);
            } else{
                odwiedzone_czerwone.insert(znaleziony_sasiad);
            }
            previosW = current_W;
            current_W = znaleziony_sasiad;
            
        }else if(current_W == 0){
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
    cout<<"KONIEC: znaleziono " << odwiedzone_czerwone.size() + odwiedzone_czerwone.size() << " z " << liczba_w << endl;
    
}

vector<vector<vector<int>>> loadFromStdIn(){
    vector<vector<vector<int>>> matrixes;
    int liczba_zestawow;
    cout<<"Podaj liczbe zestawow testowych "<<endl;
    cin>>liczba_zestawow;
    for(int i = 0; i<liczba_zestawow; i++){
        int liczba_w, liczba_k;
        cout<<"Podaj liczbe wierzcholkow, a po spacji liczbe krawedzi dla zestawu nr "<<i+1<<endl;
        cin>>liczba_w>>liczba_k;
        vector<vector<int>> currentGraph;
        currentGraph.push_back(vector<int>{liczba_w,liczba_k});
        for(int j = 0; j<liczba_k; j++)
        {   
            vector<int> currentRow;
            int v1, v2;
            cout<<"Podaj krawedz nr "<< j+1 << " dla zestawu nr "<< i+1<<endl;
            cin>>v1>>v2;
            currentRow.push_back(v1);
            currentRow.push_back(v2);
            cout<<"Wprowadzona krawedz " << v1 <<" " << v2 << endl;
            currentGraph.push_back(currentRow);
        }
        matrixes.push_back(currentGraph);
    }
    
    return matrixes;
}

int main(){
    vector<vector<vector<int>>> matrixes = loadFromFile("dane.txt");
    printGraphs(matrixes);
    doDfs(matrixes[1]);

    return 0;
}