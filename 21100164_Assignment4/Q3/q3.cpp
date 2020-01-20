#include <iostream> 
#include <string.h>
#include <fstream>
#include <vector>

/*
Recurrence Relation:
optimalCuts({}) = 0;
optimalCuts({x}) = length of x;
optimalcuts({x:xs}) = min(length+optimaCuts(n, {y} for all y<n)+optimalCuts(length-n, {(y)-n} for all y>n)) for all n in {x:xs}
length is the length of the specific rod being passed to the function while the second argument is the vector 
containing all the cuts present on that specific rod. 

Time-complexity = O(mlog(m)), there are mlog(m) subproblems which take O(1).
*/



using namespace std; 
vector<int> optimalCuts(vector<int>, vector<int>);
vector<int> addCut(int, vector<int>);
vector<int> removeCut(int, vector<int>);
int locator(int, vector<int>);
int main(int argc, char** argv) 
{ 
	//Answering Format
	//Grader is not Endline or Space Sensitive
	if(argc != 2){
		exit(1);
	}
	// argv[1] = "test13.txt";
	int n;
	string line;
	vector<int> data;
	vector<int> cuts;
	
	ifstream inFile;
	inFile.open(argv[1]);
	getline(inFile, line);
	n = stoi(line.substr(2, line.find('\0')));
	getline(inFile, line);
	line = line.substr(2, line.find('\0'));
	while(line.size() != 0){
		string temp = line.substr(0, line.find(' '));
		if(line.size() == temp.size()){
			line = "";
		}
		else{
			line = line.substr(temp.size()+1, line.find('\0'));
		}
		data.push_back(stoi(temp));
	}
	inFile.close();
	cuts.push_back(0); cuts.push_back(n);

	vector<int> result = optimalCuts(cuts, data);
	string ans;
	ans +="Optimal cut ordering: ";
	for(int i = result.size()-1; i > 1; i--){
		ans += to_string(result[i]) + " ";
	}
	ans +=  to_string(result[1]) + "\nLeast Cost: ";
	ans += to_string(result[0]) + "\n";

   	cout<<ans;
    return 0; 
} 


int locator(int position, vector<int> cuts){
	for(int i = 0; i < cuts.size(); i++){
		if(position < cuts[i]){
			return i;
		}
	}
	return -1;
}
vector<int> addCut(int value, vector<int> cuts){
	cuts.push_back(value);
	int loop = cuts.size()-1;
	while(cuts[loop-1] > cuts[loop]){
		swap(cuts[loop], cuts[loop-1]);
		loop--;
	}
	return cuts;
}
vector<int> removeCut(int index, vector<int> cuts){
	cuts[index] = cuts[cuts.size()-1];
	cuts.pop_back();
	return cuts;
}
vector<int> optimalCuts(vector<int> cuts, vector<int> set){
	//base case
	if(set.size() == 1){
		int position = locator(set[0], cuts);
		vector<int> result;
		result.push_back(cuts[position] - cuts[position-1]);
		result.push_back(set[0]);
		return result;
	}
	else{
		int min, minimumCost, minIndex;
		vector<int> minIndexVector;
		for(int i = 0; i < set.size(); i++){
			int position = locator(set[i], cuts);
			int newCost = cuts[position] - cuts[position-1];
			vector<int> valVector = optimalCuts(addCut(set[i], cuts), removeCut(i, set));
			int value = valVector[0];
			if(i == 0 || value < min){
				min = value;
				minIndexVector = valVector;
				minIndex = i;
				minimumCost = newCost;
			}
			// else if(value < min){

			// }
		}
		minIndexVector.push_back(set[minIndex]);
		minIndexVector[0] += minimumCost;
		return minIndexVector;
	}
}