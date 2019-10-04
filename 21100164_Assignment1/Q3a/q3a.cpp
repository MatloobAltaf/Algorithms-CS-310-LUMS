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
#include <stack>
#include <queue>
#include "Tokenizer.cpp"

using namespace std;

struct vars{
    set<int> visited;
    set<int> cycle;
    queue<int> order;
    stack<int> cycleList;
};

int dfs(int** data, int root, int n, struct vars* v){
	if(root == -1){
		for(int i=0; i<n; i++){
			for(int j=0; j<n;j++){
				if(data[i][j] == 1){
					root = i;
					if(dfs(data, root, n, v)==1)
						return 1;
				}
			}
		}
	}
	if(v->cycle.find(root) == v->cycle.end()){
		v->cycle.insert(root);
		v->cycleList.push(root);
		for(int i=0; i<n; i++){
			if(data[root][i] == 1){
				data[root][i] = 0;
				if(dfs(data, i, n, v) == 1){
					return 1;
				}
			}
		}
		v->cycleList.pop();
		return 0;
	}
	else{
		v->cycleList.push(root);
		return 1; 
	}
}

bool leadersQueue(int** data, int* degrees, int n, int counter, struct vars* v){
	bool state = 0;
    int zDegree = -1;
	for(int i=0; i<n; i++)
	{
		if(degrees[i] == 0 && (v->visited.find(i) == v->visited.end())){
			zDegree = i;
			counter++;
			break;
		}
		if(counter == n){
			return state;
		}
	}
	if(zDegree == -1){
		state = 1;
		dfs(data, -1, n, v);
		return state;
	}
	v->order.push(zDegree);
	v->visited.insert(zDegree);
	for(int i=0; i<n; i++){
		if(data[zDegree][i] == 1){
			data[zDegree][i] = 0;
			degrees[i]--;
		}
	}
	leadersQueue(data, degrees, n, counter, v);
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
    int *degrees = new int[n];
	for(int i=0; i<n; i++){
		int degree = 0;
		for(int j=0; j<n; j++){
			if(data[j][i] == 1){
				degree++;
			}
		}
		degrees[i] = degree;
	}
	if(leadersQueue(data, degrees, n, counter, v) == 0){
		cout<<"Yes"<<endl;
		cout<<v->order.front();
		v->order.pop();
		while(!v->order.empty()){
			cout<<" "<<v->order.front();
			v->order.pop();
		}
		cout<<endl;
	}
	else {
		stack<int> ans;
		while(!v->cycleList.empty()){
			ans.push(v->cycleList.top());
			v->cycleList.pop();
		}
		cout<<"No"<<endl;
		cout<<ans.top();
		ans.pop();
		while(!ans.empty()){
			cout<<"->"<<ans.top();
			ans.pop();
		}
		cout<<endl;
	}

    return 0; 
} 