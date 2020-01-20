#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
/*
Recurrence relation:
choose({}) = null
choose({x}) = x
choose({{x:xs}) = (choose({xs})||(choose({x})) 

Time-complexity = O(n), there are O(n)^2 which take O(1) time.
*/

//Variables
struct data
{
	int node;
	vector<int> childs;
};
vector<int> result;
vector<int> removeMember(vector<int>, int);
vector<struct data> removeNode(vector<struct data>, int);
vector<struct data> flush(vector<struct data>);
void choose(vector<struct data>);
int main(int argc, char** argv)
{
	if(argc != 2){
		exit(1);
	}
	// argv[1] = "test32.txt";
	ifstream inFile;
	int n;
	string line;
	inFile.open(argv[1]);
	if(inFile.fail()){
		exit(1);
	}
	getline(inFile, line);
	n = stoi(line.substr(2, line.find('\0')));
	vector<struct data> d;
	//vector<int>* d  = new vector<int>[n];
	for(int i = 0; i<n; i++){
		struct data dt;
		dt.node = i+1;
		getline(inFile, line);
		line = line.substr(line.find(':')+2, line.find('\0'));
		while(line.size() != 0){
			string temp = line.substr(0, line.find(' '));
			if(line.size() == temp.size()){
				line = "";
			}
			else{
				line = line.substr(temp.size()+1, line.find('\0'));
			}
			dt.childs.push_back(stoi(temp));
		}
		d.push_back(dt);
	}
	inFile.close();
	

	// for(int i = 0; i<n; i++){
	// 	cout<<d[i].node<<" : ";
	// 	for(int j = 0; j< d[i].childs.size(); j++){
	// 		cout<<d[i].childs[j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	choose(d);
	sort(result.begin(), result.end());
	cout<<"Minimum Lights "<<result.size()<<endl<<"{";
	for(int i = 0; i < result.size()-1; i++){
		cout<<result[i]<<",";
	}
	cout<<result[result.size()-1]<<"}"<<endl;
	return 0;
}



vector<int> removeMember(vector<int> data, int member){
	int index = -1;
	for(int i = 0; i < data.size(); i++){
		if(data[i] == member){
			index = i;
			break;
		}
	}
	if(index == -1){
		return data;
	}
	else{
		data[index] = data[data.size()-1];
		data.pop_back();
		return data;
	}
}
vector<struct data> removeNode(vector<struct data> d, int name){
	int index = -1;
	for(int i = 0; i < d.size(); i++){
		if(d[i].node == name){
			index = i;
			break;
		}
	}
	if(index == -1){
		return d;
	}
	else{
		d[index] = d[d.size()-1];
		d.pop_back();
		return d;
	}
}
vector<struct data> flush(vector<struct data> d){
	for(int i = 0; i < d.size(); i++){
		if(d[i].childs.size() == 0){
			d = removeNode(d, d[i].node);
			i--;
		}
	}
	return d;
}
void choose(vector<struct data> d){
	d = flush(d);
	int highestNumber = 0, highestNode  = 0;
	for(int i = 0; i < d.size(); i++){
		if(d[i].childs.size() > highestNumber){
			highestNumber = d[i].childs.size();
			highestNode = d[i].node;
		}
	}
	if(highestNode == 0){
		return;
	}
	else{
		result.push_back(highestNode-1);
		d = removeNode(d, highestNode);
		for(int i = 0; i<d.size(); i++){
			d[i].childs = removeMember(d[i].childs, highestNode-1);
		}
		choose(d);
	}
}