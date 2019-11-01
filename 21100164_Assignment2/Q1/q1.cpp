#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
bool sort_condition(const pair<int,int> &pair1,const pair<int,int> &pair2);
void print(int** finalMatrix, int n);
int * sorted_indeces(int *vec, int n);
int getSum(int * data, int n);
int cTo_int(char charectar);
void split(string str, int *& data);

int main(int argc, char** argv){
	if(argc<2){
		exit (1);
	}
	int n; //stores the number of chemicals
	std::string fname = argv[argc-1];
	std::ifstream inFile;
	string str="";
	inFile.open(argv[1]);
	if(inFile.fail()){
		exit(1);
	}
	getline(inFile, str);
	n=cTo_int(str[2]);
	int **data= new int*[2];
	data[0]=new int[n];
	data[1]=new int[n];
	int i=0;
	while (getline(inFile, str)) {
		split(str, data[i]);
		i++;
  	}
  	int totalRows=getSum(data[0],n);
  	int totalCols=getSum(data[1],n);

    int **finalMatrix=new int *[n];
	for(int i=0; i<n; i++){
  		finalMatrix[i]=new int[n];
 	 	for (int j=0; j<n; j++){
  			finalMatrix[i][j]=0;
  		}
	}
	int *sorted_row=sorted_indeces(data[0], n);
    if(totalRows=totalCols && (totalCols < (n*n))){

    	for (int i=0; i<n; i++){
    		int *sorted_col=sorted_indeces(data[1], n);
    		for (int j = 0; j <data[0][sorted_row[i]]; j++){	
    			if(data[1][sorted_col[j]]>0){
					finalMatrix[sorted_row[i]][sorted_col[j]]=1;
    				data[1][sorted_col[j]]=data[1][sorted_col[j]]-1;
    			}
    		}
    	}
	}
	if(getSum(data[1], n)>0){
		cout<<"Not Possible"<<endl;
	}
	else{
		print(finalMatrix, n);
	}
	return 0;
}
void print(int** finalMatrix, int n){
	vector<int> row;
	vector<vector <int> > list(n,row);
	for (int i=0; i<n; i++){
		for (int j=0; j<n; j++){
			if(finalMatrix[i][j]==1){
				  list[i].push_back(j);
  			}
		}
	}
	for(int i=0;i<list.size();i++){
		if(!list[i].empty()){
			for(int j=0;j<list[i].size()-1;j++){
			cout<<"("<<i+1<<","<<list[i][j]+1<<") ";
		}
			cout<<"("<<i+1<<","<<list[i][list[i].size()-1]+1<<")"<<endl;
		}
	}
}
int cTo_int(char charectar){
	return charectar-48;
}

void split(string str, int *& data){
	int length=str.length()-4;
	if(length>=1){
		string reactions=str.substr (4,length);
		int j=0;
		for (int i=0; i<length; i=i+2){
			data[j]=cTo_int(reactions[i]);
			j++;
		}
	}
}

int getSum(int * data, int n){
	int s=0;
	for (int i=0; i<n ; i++){
		s+=data[i];
	}
	return s;
}

bool sort_condition(const pair<int,int> &pair1,const pair<int,int> &pair2)
{
	return(pair2.first < pair1.first);
}

int * sorted_indeces(int *vec, int n){
	vector<pair<int,int> > list;
	for(int i = 0; i < n; i++){
		list.push_back(make_pair(vec[i],i));
	}
	sort(list.begin(),list.end(), sort_condition);
	int *index=new int[n];
	for(int i = 0; i < n; i++){
		index[i]=(list[i].second);
	}
	return index;
}
