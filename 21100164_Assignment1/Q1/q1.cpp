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
set<int> white;
set<int> black;
set<int> cycle;

stack<int> cycleList;
};
int ifNotBipartite(int** data, int start, int no, int issue, int n, struct vars* v){
	v->cycleList.push(start);
	v->cycle.insert(start);
	for(int i=0; i<n; i++){
		if(data[start][i] == 1){
			if(i == issue){
				if(no%2 == 1){
					v->cycleList.push(issue);
					return 1;
				}
			}
			else if(v->cycle.find(i) == v->cycle.end()){
				if(ifNotBipartite(data, i, no+1, issue, n, v) == 1){
					return 1;
				}
			}
		}
	}
	v->cycleList.pop();
	v->cycle.erase(start);
	return 0;
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

bool isBipartite(int n, int** data, struct vars* v){
	bool state = 0;
	queue<int> q1;
	queue<int> q2;
	q1.push(0);
	char color = 'w';
	while(!q1.empty()){
		int iss = q1.front();
		q1.pop();
		if(color == 'w'){
			if(v->black.find(iss) != v->black.end()){
				state = 1;
				ifNotBipartite(data, iss, 1, iss, n, v);
				return state;
			}
		} 
		else{
			if(v->white.find(iss) != v->white.end()){
				state = 1;
				ifNotBipartite(data, iss, 1, iss, n, v);
				return state;
			}
		}
		if(v->visited.find(iss) == v->visited.end()){
			v->visited.insert(iss);
			if(color == 'w'){
				v->white.insert(iss);
			}
			else{
				v->black.insert(iss);
			}
		}
		for(int i = 0; i<n; i++){
			if(data[iss][i] == 1){
				if(v->visited.find(i) == v->visited.end()){
					q2.push(i);
				}
			}
		}
		if(q1.empty()){
			while(!q2.empty()){
				q1.push(q2.front());
				q2.pop();
			}
			if(color == 'w'){
				color = 'b';
			}
			else{
				color = 'w';
			}							
		}
	}
	return state;
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
	 struct vars* v = new vars;
	if(isBipartite(n, data, v) == 0){
		cout << "Yes" << endl;
		set<int>::iterator iter;
		iter = v->white.begin();
		cout <<*iter ;
		iter++;
		for(; iter!=v->white.end(); iter++)
		{
			cout << " " << *iter;
		}
		cout << endl;
		iter = v->black.begin();
		cout <<*iter ;
		iter++;
		for(; iter!=v->black.end(); iter++)
		{
			cout << " " << *iter;
		}
		cout << endl;
		 
	}
	else{
		cout << "No" << endl;
		cout<<v->cycleList.top();
		v->cycleList.pop();
		while(!v->cycleList.empty()){
			cout<<"->"<<v->cycleList.top();
			v->cycleList.pop();
		}
		cout<<endl;
	}
	//print(n, data);
	return 0;
}