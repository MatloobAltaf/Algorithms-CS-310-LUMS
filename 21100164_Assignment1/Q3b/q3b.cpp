/*
My algorithm uses the Depth First Search (DFS) method to check if the graph. 
can be dissided into two or not (bipartite).
The time complexity of the algorithm will be O(V+E).
To store my data, I use an Adjacency Matrix, which means the that
the space complexity of the algorithm will be O(V^2) but this gisses me faster and
more efficient lookups.s that I have used include sets, stacks and queues. The 
functions using the sets have a time complexity of O(V*log(V)). The functions
using the sets and queses have a time complexity of O(1)
*/
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <queue>
#include "Tokenizer.cpp"

using namespace std;

struct vars{
    set<int> visited;
    queue<int> order;
	queue<int> rows;
	int nRows = 0;
};

bool leadersInRows(int** data, int* degrees, int n, int counter, struct vars* v){
	bool state = 0;
	int sDegree = -1;
	v->order.push(-1);
	int hello = 0;
	for(int i=0; i<n; i++)
	{
		if(counter == n && hello == 0){
			return state;
		}
		if(degrees[i] == 0 && (v->visited.find(i) == v->visited.end())){
			v->rows.push(i);
			counter++;
			hello = 1;
		}
	}
	if(v->rows.empty()){
		state = 1;
		return state;
	}
	while(!v->rows.empty()){
		sDegree = v->rows.front();
		v->rows.pop();
		v->order.push(sDegree);
		v->visited.insert(sDegree);
		for(int i=0; i<n; i++){
			if(data[sDegree][i] == 1){
				data[sDegree][i] = 0;
				degrees[i]--;
			}
		}
	}
	v->nRows++;
	leadersInRows(data, degrees, n, counter, v);
}
int main(int argc, char** argv) 
{ 
  if(argc<2){
		exit (1);
	}
	int n; //stores the size of vertices
	string fname = argv[argc-1];
	ifstream inFile;
	inFile.open(fname.c_str());
	if(inFile.fail()){
		exit(1);
	}
	string line;
	getline(inFile, line);
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
	//Parse the file using Tokenizer to fill the matrix.	
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
    struct vars* v = new vars;
    int counter = 0;
    int *degrees = new int [n];
	for(int i=0; i<n; i++){
		int degree = 0;
		for(int j=0; j<n; j++){
			if(data[j][i] == 1){
				degree++;
			}
		}
		degrees[i] = degree;
	}

	if(leadersInRows(data, degrees, n, counter, v)== 0){
		cout<<"Yes"<<endl;
		cout<<"R "<<v->nRows<<endl;
		v->order.pop();
		int t1;
		t1 = v->order.front();
		v->order.pop();
		if(v->order.front() == -1){
			cout<<t1;
		}
		else{
			cout<<t1<<" ";
		}
		while(!v->order.empty()){
			if(v->order.front() == -1){
				cout<<endl;
				v->order.pop();
			}
			if(v->order.empty()){
				break;
			}
			int t2 = v->order.front();
			v->order.pop();
			if(v->order.front()==-1){
				cout<<t2;
			}
			else{
				cout<<t2<<" ";
			}
		}
	}
	else {
		cout<<"No"<<endl;
	}


	return 0;
} 