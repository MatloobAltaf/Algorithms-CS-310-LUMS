#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
/*
Recurrence relation:
interLeaving(x, y, z == x+y) = true
interLeving(x, y, z != x+y) = false
interLeaving({0, 0, 0) = (interLeaving(x+1,y,z+1))||(interLeaving(x, y+1, z+1)) 

The first argument is indexF, the second is indexS and the third is indexR. We initialize the function by calling interleaving( 0, 0 , 0).

Time-complexity = O(z)^2, there are O(z)^2 which take O(1) time.
x is the size if first string, y is for second and z is for third.
*/



//variables
	string first = "";
	string second = "";
	string result = "";
	string ans = "";
	int character = 0;

bool interLeaving(int, int, int);
int main(int argc, char** argv)
{
	if(argc < 2){
		exit(1);
	}
	// argv[1] = "test34.txt";
	ifstream inFile;
	inFile.open(argv[1]);
	getline(inFile, first);
	getline(inFile, second);
	getline(inFile, result);
	inFile.close();
	bool valid = false;
	if(first.size()+second.size() == result.size());{
		valid = interLeaving(0, 0, 0);
	}
	if(valid){
		ans = "VALID" + ans;
	}
	else{
		ans = "INVALID";
	}
	cout<<ans<<endl;
	
	return 0;
}
bool interLeaving(int indexF, int indexS, int indexR){
	if(indexR == result.size()){
		return true;
	}
	else if(first[indexF] != result[indexR] && second[indexS] != result[indexR]){
		return false;
	}
	else{
		//if the last character added was from S1 then for next character, check first in S1 then in S2
		if(character == 1 || character == 0){
			if(first[indexF] == result[indexR]){
				if(character == 1){
					ans.append(1, first[indexF]);
				}
				else{
					character = 1;
					ans += "\n1:";
					ans.append(1, first[indexF]);
				}
				return interLeaving(indexF+1, indexS, indexR+1);
			}
			else{
				if(character == 2){
					ans.append(1, second[indexS]);
				}
				else{
					character = 2;
					ans += "\n2:";
					ans.append(1,second[indexS]);
				}
				return interLeaving(indexF, indexS+1, indexR+1);
			}
		}
		//Similarly, if the last character added was from S2 then for next character, check first in S2 then in S1
		else{
			if(second[indexS] == result[indexR]){
				if(character == 2){
					ans.append(1, second[indexS]);
				}
				else{
					character = 2;
					ans += "\n2:";
					ans.append(1,second[indexS]);
				}
				return interLeaving(indexF, indexS+1, indexR+1);
			}
			else{
				if(character == 1){
					ans.append(1, first[indexF]);
				}
				else{
					character = 1;
					ans += "\n1:";
					ans.append(1, first[indexF]);
				}
				return interLeaving(indexF+1, indexS, indexR+1);
			}
		}
		
	}
}