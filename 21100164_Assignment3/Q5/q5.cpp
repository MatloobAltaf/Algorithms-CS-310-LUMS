#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
bool decode(int a1, int a2){
	if(a1 == a2){
		return true;
	}
	else{
		return false;
	}
}
int frequency(vector<int> data, int begin, int end){
	if(begin < end){
		int mid = (begin+end)/2;
		int left = frequency(data, begin, mid);
		int right = frequency(data, mid+1, end);
		int leftCount = 0, rightCount = 0;
		for(int i = begin; i < end; i++){
			if(decode(left, data[i])){
				leftCount++;
			}
			if(decode(right, data[i])){
				rightCount++;
			}
		}
		if(leftCount > rightCount){
			return left;
		}
		else{
			return right;
		}
	}
	else{
		if(begin == end){
			return data[begin];
		}
	}
}
int main(int argc, char* argv[])
{
	if(argc < 2){
		exit(-1);
	}
	int n, input;
	string line;
	ifstream inFile;
	vector<int> data;
	// argv[1] = "test15.txt";
	inFile.open(argv[1]);
	if(inFile.fail()){
		exit(-1);
	}
	getline(inFile, line);
	n = stoi(line.substr(2, line.find('\0')));
	getline(inFile, line);
	while(inFile >> input){
		data.push_back(input);
	}
	
	int picture = frequency(data, 0, n);
	int dominantCount = 0;
	vector<int> result;
	string output = "";

	for(int i = 0; i < n; i++){
		if(decode(picture, data[i])){
			dominantCount++;
			result.push_back(i);
		}
	}
	if(dominantCount > (n/2)){
		output += "Success\nDominant Species Count " + to_string(dominantCount);
		output += "\nDominant Species Indices ";
		for(int i = 0; i < dominantCount-1; i++){
			output += to_string(result[i]) + " ";
		}
		output += to_string(result[dominantCount-1]);
	}
	else{
		output += "Failure";
	}
	cout<<output<<endl;
	return 0;
}
