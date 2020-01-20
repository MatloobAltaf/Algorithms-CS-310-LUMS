#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
struct node{
    int weight;
    string name;
    node* left;
    node* right;
};
struct store{
    string val1;
    string val2;
    int cWeight;

};

class ancestry{
    private:
        int h;
        node* root;
    public:
        ancestry(string filename);
        ~ancestry();
        node* insert(vector<pair<string,int>> weights, int size, int index);
        vector<store> maxPair(node* treeNode);
        bool hasPath(node *root, vector<int>& arr, string x);
        void printPath(node *root, string x);
        void print();
        void printTree(node* treeNode);
        void deleteNode(node* treeNode);

};
ancestry::ancestry(string filename){
    ifstream inFile;
    inFile.open(filename);
    if(inFile.fail()){
        exit(1);
    }
    string line = "";
    vector<pair<string,int>> hopes;
    
    getline(inFile, line);
    h = stoi(line.substr(2, line.find('\0')));
    getline(inFile, line);
    for(int i = i; line.size() != 0; i++){
        string temp = line.substr(0, line.find(' '));
		if(line.size() == temp.size()){
			line = "";
		}
		else{
			line = line.substr(temp.size()+1, line.find('\0'));
		}
		hopes.push_back(make_pair(to_string(i), stoi(temp)));
    }
    inFile.close();
    root = insert(hopes, (1<<(h+1))-1, 0);
    hopes.clear();
}
ancestry::~ancestry(){
    deleteNode(root);
}
void ancestry::deleteNode(node* treeNode){
    if(treeNode){
        deleteNode(treeNode->left);
        deleteNode(treeNode->right);
        delete treeNode;
    }
}
node* ancestry::insert(vector<pair<string,int>> weights, int size, int index){
    if (index >= size){
        return 0;
    }
    else{
        node* temp = new node;
        temp->weight = weights[index].second;
        temp->name = weights[index].first;
        int tNodes = 2*(index);
        temp->left = insert(weights, size, tNodes+1);
        temp->right = insert(weights, size, tNodes+2);
        return temp;
    }
}
void ancestry::print(){

    // printTree(root);
    // cout<<"\n\n\n";
    vector<store> final = maxPair(root);
    cout<<"(xi,xj) = ("<<final[1].val1<<","<<final[1].val2<<")"<<endl;
    cout<<"Ancestry "<<final[1].val1<<" = ";
    printPath(root, final[1].val1);
    cout<<"Ancestry "<<final[1].val2<<" = ";
    printPath(root, final[1].val2);    
	cout << "Value of Max Ancestry ("<<final[1].val1 << "," << final[1].val2 << ") = " << final[1].cWeight <<endl;

}
vector<store> ancestry::maxPair(node* treeNode){
    if(treeNode->left == 0 && treeNode->right == 0){
        store temp;
        temp.val1 = treeNode->name;
        temp.val2 = "";
        temp.cWeight = treeNode->weight;
        vector<store> result;
        result.push_back(temp);
        return result;
    }
    else{
        vector<store> leftResult = maxPair(treeNode->left);
        vector<store> rightResult = maxPair(treeNode->right);
        vector<store> pairSet;
        if(leftResult.size() > 1){
            pairSet.push_back(leftResult[1]);
        }
        if(rightResult.size() > 1){
            pairSet.push_back(rightResult[1]);
        }
        store temp;
        temp.val1 = leftResult[0].val1;
        temp.val2 = rightResult[0].val1;
        temp.cWeight = leftResult[0].cWeight + rightResult[0].cWeight;
        pairSet.push_back(temp);

        store maxPair =pairSet[0];
        store maxSingle;

        for(int i=0; i<pairSet.size(); i++){
            if(pairSet[i].cWeight > maxPair.cWeight){
                maxPair = pairSet[i];
            }
        } 
        if(leftResult[0].cWeight > rightResult[0].cWeight){
            maxSingle = leftResult[0];
        }
        else
        {
            maxSingle = rightResult[0];
        }

        vector<store> result;
        maxPair.cWeight += treeNode->weight;
        maxSingle.cWeight += treeNode->weight;

        result.push_back(maxPair);
        result.push_back(maxSingle);

        return result;
        
    }
}

//this snipet of code is taken from gfg to print the output


// Returns true if there is a path from root 
// to the given node. It also populates  
// 'arr' with the given path 
bool ancestry::hasPath(node *root, vector<int>& arr, string x) 
{ 
    // if root is NULL 
    // there is no path 
    if (!root) 
        return false; 
      
    // push the node's value in 'arr' 
    arr.push_back(root->weight);     
      
    // if it is the required node 
    // return true 
    if (root->name == x)     
        return true; 
      
    // else check whether the required node lies 
    // in the left subtree or right subtree of  
    // the current node 
    if (hasPath(root->left, arr, x) || 
        hasPath(root->right, arr, x)) 
        return true; 
      
    // required node does not lie either in the  
    // left or right subtree of the current node 
    // Thus, remove current node's value from  
    // 'arr'and then return false     
    arr.pop_back(); 
    return false;             
} 
  
// function to print the path from root to the 
// given node if the node lies in the binary tree 
void ancestry::printPath(node *root, string x) 
{ 
    // vector to store the path 
    vector<int> arr; 
      
    // if required node 'x' is present 
    // then print the path 
    if (hasPath(root, arr, x)) 
    { 
        cout<<"{";
        for (int i=0; i<arr.size()-1; i++)     
            cout << arr[i] << ", "; 
        cout << arr[arr.size() - 1]<<"}"<<endl;     
    } 
      
    // 'x' is not present in the binary tree  
    // else
    //     cout << "No Path"; 
}
void ancestry::printTree(node* treeNode){
    if(treeNode == NULL){
        return;
    }
    cout<<treeNode->name<<"\t"<<treeNode->weight<<endl;
    printTree(treeNode->left);
    printTree(treeNode->right);
}
int main(int argc, char** argv){
    if(argc < 2){   
        exit(1);
    }
    // argv[1] = "test14.txt"; 
    ancestry obj(argv[1]);
    obj.print();
	return 0;
}