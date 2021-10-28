#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
     vector<vector<vector<int>>> matrixes2 = loadFromStdIn();

    return 0;
}