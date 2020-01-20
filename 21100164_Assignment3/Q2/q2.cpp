#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

/*
For this problem I'm using a binary search tree, based on the immune cell count of the day.
complexity of the findLarger is O(log n)
It looks for each value (total n), all the values that have lesser day number and greater immune cell number than a particular value.
so the overall compleixity is O(n log n)
*/

struct day{
	int name;
	int count;

	struct day* left;
	struct day* right;
	day(int i, int j){
		name = i;
		count = j;
		left = NULL;
		right = NULL;
	}
};
vector<pair<int,int>> result;
struct day* days = NULL;
struct day* insert(struct day* &days, int na, int key) 
{ 
    /* If the tree is empty, return a new node */
    if (days == NULL){
		struct day* d = new day(na,key);
		days = d;
		return days; 
	}
    /* Otherwise, recur down the tree */
    if (key < days->count) 
        days->left  = insert(days->left, na, key); 
    else if (key > days->count) 
        days->right = insert(days->right, na, key);    
  
    /* return the (unchanged) node pointer */
    return days; 
}
void findLarger(int num, int key, struct day* days){
	if(days == NULL){
		return;
	}
	if(days->right != NULL){
	if(key < days->right->count && num > days->right->name){
		findLarger(num, key, days->right);
	}}
	if(days->left != NULL){
	if(key < days->left->count && num > days->left->name){
		findLarger(num, key, days->left);
	}}
	if(days->count > 2*key){
		result.push_back(make_pair(num, days->name));
	}

}

void print(){
	cout<<"Failed Trials "<<result.size()<<endl;
	for(int i = 0; i< result.size(); i++){
		if(i > 0 && result[i].first > result[i-1].first){
			cout<<endl;
		}
		cout<<"("<<result[i].first<<","<<result[i].second<<")";
	}
}
int main(int argc, char** argv)
{
	if(argc < 2){
		exit(-1);
	}
	ifstream inFile;
	//  argv[1] = "test32.txt";
	inFile.open(argv[1]);
	if(inFile.fail()){
		exit(-1);
	}
	string line = "";
	int n = 0;
	getline(inFile, line);
	if(line[0] == 'n'){
		n = stoi(line.substr(2, line.find('\0')));
	}
	int* values = new int[n];
	getline(inFile, line);
	for(int i = 0; line.size() != 0; i++){
		string temp = line.substr(0, line.find(' '));
		if(line.size() == temp.size()){
			line = "";
		}
		else{
			line = line.substr(temp.size()+1, line.find('\0'));
		}
		values[i] = stoi(temp);
		insert(days, i, stoi(temp));
	}
	inFile.close();
	for(int i = 0 ; i<n; i++){
		//cout<< i<<endl;
		findLarger(i,values[i], days);
	}
	print();
	return 0;
}
