#include<iostream>
#include<stdio.h>
#include <fstream>
using namespace std;

struct Node{
	int key;
	int counter = 1;
	Node *left;
	Node *right;
};

Node *RNP = NULL;
Node *temp = NULL;

Node * createdNode(){
	Node *temp = new Node;
	cout<<"\n enter the key: ";
	cin>>temp->key;
	temp->left = NULL;
	temp->right = NULL;
	
	return temp;
}

Node * createdNodeFromFile(int data) {
	Node *temp = new Node;
	temp->key = data;
	temp->left = NULL;
	temp->right = NULL;
	
	return temp;
}

void insert(){
	if(RNP == NULL)
	 RNP = createdNode();
  else{
	  Node *temp = createdNode();
	  Node *CN = RNP;
  	bool inserted = false;
  	while(!inserted){
  		if(temp->key == CN->key){
  		  CN->counter++;
  		  break;
			}
  		else if(temp->key > CN->key){
  			if(CN->right == NULL){
  				CN->right = temp;
  				inserted = true;
				}
				else{
					CN = CN->right;
				}
			}
			else{
  			if(CN->left == NULL){
  				CN->left = temp;
  				inserted = true;
				}
				else{
					CN = CN->left;
				}
			}
		}
	}
}

void insertFromFile(int data){
	if(RNP == NULL)
	 RNP = createdNodeFromFile(data);
  else{
	  Node *temp = createdNodeFromFile(data);
	  Node *CN = RNP;
  	bool inserted = false;
  	while(!inserted){
  		if(temp->key == CN->key){
  		  CN->counter++;
  		  break;
			}
  		else if(temp->key > CN->key){
  			if(CN->right == NULL){
  				CN->right = temp;
  				inserted = true;
				}
				else{
					CN = CN->right;
				}
			}
			else{
  			if(CN->left == NULL){
  				CN->left = temp;
  				inserted = true;
				}
				else{
					CN = CN->left;
				}
			}
		}
	}
}

void in_order(Node *CN, int space, int pos){
	if(CN != NULL){
    in_order(CN->left, space-1, -1);
    for (int i = 0; i < space; i++) {
      cout<<"\t";
    }
    cout<<CN->key<<"("<<CN->counter<<")";
    if (pos == 0) {
        cout << "\n";
    }
    if (pos == -1) {
        cout << "\\\n";
        printf("\033[0;32m");
    }
    else {
        cout << "\n";
        cout << "\033[0;34m";
    }
    in_order(CN->right, space-1, 1);
	}

  else  {
    cout << "\033[0m";
  }
}


void deleteNode(Node *CN, int key){
	if(CN == NULL)
	 cout<<"\n nothing to be deleted !";
    else if(key == RNP->key){
	 	Node *rc = CN->right;
	 	Node *lc = CN->left;
	 	
	 	if(rc != NULL && lc != NULL){
	 		RNP = rc;
	 		Node *n = rc;
	 		while(n->left != NULL)
	 		  n = n->left;
		  	n->left = lc;
		 }
		 else if(rc != NULL){
		 	RNP = rc;
		 }
		 else if(lc != NULL){
		 	RNP = lc;
		 }
		 else
		  RNP = NULL;
	 }
	else{
		if(key > CN->key){
	 		temp = CN;
	 		deleteNode(CN->right, key);
		}
	  	if(key < CN->key){
	  		temp = CN;
	  		deleteNode(CN->left, key);
		}
		else{
			Node *r = CN->right;
			Node *l = CN->left;
			
			if(r != NULL && l != NULL){
				Node *n = r;
				while(n->left != NULL) {
					n = n->left;
				}
		    	n->left = l;
		    	if(key > temp->key) {
				temp->right = r;
				}  
        		else {
					temp->left = r;
				}
			}

			else if(r != NULL){
		    	if(key > temp->key)
		      		temp->right = r;
        		else
          			temp->left = r;
			}

			else if(l != NULL){
		    	if(key > temp->key) {
					temp->right = l;
				}
        		else {
					temp->left = l;
				}
			}

			else{
		    	if(key > temp->key) {
					temp->right = NULL;
				}
        		else {
					temp->left = NULL;
				}
			}
		}
	 }
}

void uploadFile() {
	ifstream myFile;
	string fileName;
	string data;

	cout<<"\nenter name of the file: ";
	cin>>fileName;

	myFile.open(fileName);
	while (getline(myFile, data)) {
		insertFromFile(stoi(data));
	}

	myFile.close(); 
}

int main(){
	int repeat = 0, choise, pos;
	string fileName;
  	int range = 7;
	while(repeat == 0){
		cout<<"\n enter 1 to insert";
		cout<<"\n enter 2 to display";
		cout<<"\n enter 3 to delete";
		cout<<"\n enter 4 to upload file";
		cout<<"\n enter 0 to exit";
		cout<<"\nyour input : ";
		cin>>choise;
		switch(choise){
			case 1:
				insert();
				break;
			case 2:
				in_order(RNP, range, pos);
				break;
			case 3: 
				int k;
				cout<<"\n enter the node key:";
				cin>>k;
			  	deleteNode(RNP, k);
				break;
			case 4:
				uploadFile();
				break;
			case 0:
				repeat = 1;
				break;
			default:
				cout<<"\n unknown";
		}
	}
}




