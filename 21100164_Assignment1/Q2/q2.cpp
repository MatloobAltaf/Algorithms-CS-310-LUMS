/*
My algorithm uses the Depth First Search (DFS) method
The time complexity of the algorithm will be O(V+E).
To store my data, I use an Adjacency Matrix, which means the that
the space complexity of the algorithm will be O(V^2) but this gisses me faster and
more efficient lookups.
The other data structures that I have used include vectors and arrays.
Functions of arrays and vectors used are all in O(1).
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Tokenizer.cpp"
using namespace std;
struct vars{
int* visited;
int* discoveryT;
int* subTree;
int* parent;
vector<pair<int,int>> vEdges;
vars(int n){
	visited = new int [n];
	discoveryT = new int [n];
	subTree = new int [n];
	parent = new int [n];
}
};
void bridgeFind(int** data, int n, int start, struct vars* v) {
   static int time = 0;
   v->visited[start] = true;               //make the first vertex is visited
   v->discoveryT[start] = v->subTree[start] = ++time;  //initialize discoveryTovery time and the subTree time

   for(int i = 0; i<n; i++){
      if(data[start][i]){   //for all vertex v, which is connected with start
        	if(!v->visited[i]){
            	v->parent[i] = start;    //make start node as parent
            	bridgeFind(data, n, i, v);       
            	v->subTree[start] = min(v->subTree[start], v->subTree[i]);    //when subtree from v is connected to one of parent of start node
            	if(v->subTree[i] > v->discoveryT[start]){
            		v->vEdges.push_back(make_pair(start, i));
					//cout << "("<<start<<","<<i<<")"<<endl;
				}
			}
			else if(i != v->parent[start]){    //update subTree of start for previous call
            	v->subTree[start] = min(v->subTree[start], v->discoveryT[i]);
			}
    	}
	}
}

bool bridges(int** data, int n, struct vars* v) {

   for(int i = 0; i<n; i++){
      v->visited[i] = 0;    //no node is visited
      v->parent[i] = -1;    //initially there is no parent for any node
	}
   
   for(int i = 0; i<n; i++){
    	if(!v->visited[i]){    //if any node is unvisited, the data is not connected
    		bridgeFind(data, n, i, v);
		}
	}
}

void print(int n, int** data){
	for (int i= 0; i<n; i++) {
		cout<<i;
		for (int j= 0; j<n; j++){
			if(data[i][j] == 1){
				cout<<"->"<< j;
			}
		}
		cout<<endl;
	}
}



int main(int argc, char** argv)
{
	if(argc<2){
		exit (1);
	}
	int n; //stores the number of chemicals
	string fname = argv[argc-1];
	ifstream inFile;
	inFile.open(fname.c_str());
	if(inFile.fail()){
		exit(1);
	}
	string line;
	getline(inFile, line);
	//Reads the first line to find the number of chemicals:
		if(line[0] == 'n'){
			n = stoi(line.substr(2,line.find("/0")));
		}
	//Create a n x n matrix and set the values to zero:
	int **data = new int*[n];
	for(int i = 0; i < n; i++){
		data[i] = new int[n];
		for(int j = 0; j < n; j++){
			data[i][j] = 0;
		}
	}
	//Parse the file to fill the matrix.	
	while(!inFile.eof()){
		getline(inFile, line);
		Tokenizer str;
		str.set(line, " :");
		string token;
		string index;
		if((index = str.next()) != ""){
			while((token = str.next()) != ""){
				data[stoi(index)][stoi(token)] = 1;
			}
		}
	}
	inFile.close();
	struct vars* v = new vars(n);
	bridges(data, n, v);
	if(v->vEdges.size() != 0){
		cout<<v->vEdges.size()<<endl;
		for(int i=0; i<v->vEdges.size(); i++){
			cout << "("<<v->vEdges[i].first<<","<<v->vEdges[i].second<<")"<<endl;
		}
	}
	else
	{
		cout<<v->vEdges.size()<<endl;
	}
	
	//print(n, data);
	return 0;
}

                             
