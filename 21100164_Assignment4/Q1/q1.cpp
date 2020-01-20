#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
/*
Recurrence relation: 
highestOutput(-1) = 0
highestOutput(-2) = 0
highestOutput(m) = max(RH[m]+highestOuptu(m-2), RL[m]+highestOutput(m-1))
the highestOutp function conputes the maximum revenue for a
particular week 'm'. We pass the value of the last 
week (n-1) to compute this.

Time Complexity: O(n), there are O(n) sub-problems which take 0(1) time.
*/
vector<int> RH;
vector<int> RL;
int* values;
string* result;

void initArray(int);
int highestOutput(int);
string print(int);
int main(int argc, char** argv)
{
	if(argc != 2){
		exit(1);
	}
	// argv[1] = "test21.txt";
	fstream inFile;
	inFile.open(argv[1]);
	if(inFile.fail()){
		exit(1);
	}
	string line = "";
	int n = 0;
	getline(inFile, line);
	n = stoi(line.substr(2, line.find(' ')));
	while (!inFile.eof())
	{
		getline(inFile, line);
		if(line.size() <= 0){continue;}
		string flag = line.substr(0, line.find(' '));
		line = line.substr(flag.size()+1, line.find('\0'));
		if(flag == "RH"){
			for(int i = 0; line.size() != 0; i++){
				string temp = line.substr(0, line.find(' '));
				if(line.size() == temp.size()){
					line = "";
				}
				else{
					line = line.substr(temp.size()+1, line.find('\0'));
				}
				RH.push_back(stoi(temp));
			}
		}
		else if(flag == "RL"){
			for(int i = 0; line.size() != 0; i++){
				string temp = line.substr(0, line.find(' '));
				if(line.size() == temp.size()){
					line = "";
				}
				else{
					line = line.substr(temp.size()+1, line.find('\0'));
				}
				RL.push_back(stoi(temp));
			//insert(days, i, stoi(temp));
			}
		}
		
	}
	cout<<print(n);

	return 0;
}
void initArray(int n){
	values = new int[n];
	for(int i = 0; i < n; i++){
		values[i] = -1;
	}
	result = new string[n];
	if(RH[0] > RL[0]){
		values[0] = RH[0];
		result[0] = "High";
	}
	else{
		values[0] = RL[0];
		result[0] = "Low";
	}
}
int highestOutput(int n){
	if(values[n] == -1){
		int _rh;
		if( n > 1){
			_rh = RH[n] + highestOutput(n-2);
		}
		else{
			_rh = RH[n];
		}
		int _rl = RL[n] + highestOutput(n-1);
		if(_rh > _rl){
			values[n] = _rh;
			result[n] = "High";
		}
		else{
			values[n] = _rl;
			result[n] = "Low";
		}
		return values[n];
	}
	else{
		
		return values[n];
	}
}
string print(int n){
	initArray(n);
	int revenue = highestOutput(n-1);
	for(int i = n-1; i > 0; i--){
		if(result[i] == "High"){
			result[i-1] = "Priming";
			i--;
		}
	}
	string output = "";
	for(int i = 0; i < n; i++){
		output += "Week " + to_string(i+1) + ": ";
		if(result[i] == "High"){
			output += "High " + to_string(RH[i]) + "\n";
		}
		else if(result[i] == "Low"){
			output += "Low " + to_string(RL[i]) + "\n";
		}
		else{
			output += "Priming\n";
		}
	}
	output += "Total Revenue: " + to_string(revenue) + "\n";
	return output;
}