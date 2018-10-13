#include<iostream>
#include<algorithm>
using namespace std;
class tree{
	
	class node{
		public:
		node* left;
		int key;
		node *right;
	};
	node* createNewNode(int);
	void insertKeyPrivate(int,node*);
	void preorderTraversalPrivate(node*);
	void inorderTraversalPrivate(node*);
	void postorderTraversalPrivate(node*);
	int  smallestElementPrivate(node*);
	int  largestElementPrivate(node*);
	node* findNodePrivate(int,node*);
	node* findParentNodePrivate(int,node*);
	void deleteNodePrivate(int,node*,node*);
	node* root;
	public:
	tree(){
		root=NULL;
	}
	void insert(int);
	void preorderTraversal();
	void inorderTraversal();
	void postorderTraversal();
	void smallestElement();
	void largestElement();
	void findNode(int);
	void findParentNode(int);
	void deleteNode(int);
};
tree::node* tree::createNewNode(int key){
	node* newNode=new node;
	newNode->left=NULL;
	newNode->right=NULL;
	newNode->key=key;
	return newNode;
}
void tree::insert(int key){
	insertKeyPrivate(key,root);
}
void tree::insertKeyPrivate(int key,node* current){
	if(root==NULL){
		root=createNewNode(key);
	}
	else{
		if(key<current->key){
			if(current->left!=NULL){
				insertKeyPrivate(key,current->left);
			}
			else{
				current->left=createNewNode(key);
			}
		}
		else{
			if(current->right!=NULL){
				insertKeyPrivate(key,current->right);
			}	
			else{
				current->right=createNewNode(key);
			}
		}
	}
}
void tree::preorderTraversal(){
	cout<<"preorder traversal:"<<endl;
	preorderTraversalPrivate(root);
	cout<<endl;
}
void tree::preorderTraversalPrivate(node *ptr){
	if(root==NULL){
		cout<<"sorry! tree is empty"<<endl;
	}
	else{
			cout<<ptr->key<<" ";
			if(ptr->left!=NULL){
				preorderTraversalPrivate(ptr->left);	
			}
			if(ptr->right!=NULL){
				preorderTraversalPrivate(ptr->right);	
			}
	}
}
void tree::inorderTraversal(){
	cout<<"Inorder traversal:"<<endl;
	inorderTraversalPrivate(root);
	cout<<endl;
}
void tree::inorderTraversalPrivate(node *ptr){
	if(root==NULL){
		cout<<"sorry! tree is empty"<<endl;
	}
	else{
		if(ptr->left!=NULL){
			inorderTraversalPrivate(ptr->left);
		}
		cout<<ptr->key<<" ";
		if(ptr->right!=NULL){
			inorderTraversalPrivate(ptr->right);
		}
	}
}
void tree::postorderTraversal(){
	cout<<"postorder traversal:"<<endl;
	postorderTraversalPrivate(root);
	cout<<endl;
}
void tree::postorderTraversalPrivate(node *ptr){
	if(root==NULL){
		cout<<"sorry! tree is empty"<<endl;
	}
	else{
		if(ptr->left!=NULL){
			postorderTraversalPrivate(ptr->left);
		}
		if(ptr->right!=NULL){
			postorderTraversalPrivate(ptr->right);
		}
		cout<<ptr->key<<" ";
	}
}
void  tree::smallestElement(){
	int smallest=smallestElementPrivate(root);
	cout<<"Smallest element in the tree is: "<<smallest<<endl;
}
int tree::smallestElementPrivate(node *ptr){
	if(root==NULL){
		cout<<"sorry! tree is empty"<<endl;
	}
	else{
		if(ptr->left!=NULL){
			smallestElementPrivate(ptr->left);
		}
		else{
			return ptr->key;
		}
	}
}
void tree::largestElement(){
	int largest=largestElementPrivate(root);
	cout<<"largest element in the tree is:"<<largest<<endl;
}
int tree::largestElementPrivate(node *ptr){
	if(root==NULL){
		cout<<"sorry! tree is empty"<<endl;
	}
	else{
		if(ptr->right!=NULL){
			largestElementPrivate(ptr->right);
		}
		else{
			return ptr->key;
		}
	}
}
void tree::findNode(int key){
	if(root==NULL){
		cout<<"sorry! tree is empty"<<endl;
		return;
	}
	else if(findNodePrivate(key,root)!=NULL){
		cout<<"Given data exist"<<endl;
	}
	else{
		cout<<"sorry! given data does not exist"<<endl;
	}
}
tree::node* tree::findNodePrivate(int key,node *ptr){
	if(key==ptr->key){
		return ptr;
	}
	else if(key<ptr->key){
		if(ptr->left!=NULL){
			return findNodePrivate(key,ptr->left);
		}
	}
	else{
		if(ptr->right!=NULL){
			return findNodePrivate(key,ptr->right);
		}
	}

}
void tree::findParentNode(int key){
	if(root==NULL){
		cout<<"sorry! tree is empty"<<endl;
		return;
	}
	else if(findNodePrivate(key,root)==NULL){
		cout<<"sorry! key does not exist in tree"<<endl;
		return;
	}
	else{
		cout<<"parent node of "<<key<<" is: "<<findParentNodePrivate(key,root)->key<<endl;
	}
}
tree::node* tree::findParentNodePrivate(int key,node *ptr){
	if(ptr->left==NULL and ptr->right==NULL){
		return NULL;
	}
	if((ptr->left!=NULL and ptr->left->key==key)or (ptr->right!=NULL and ptr->right->key==key)){
		return ptr;
	}
	if(key<ptr->key){
		return findParentNodePrivate(key,ptr->left);
	}
	if(key>ptr->key){
		return findParentNodePrivate(key,ptr->right);
	}
}

void tree::deleteNode(int key){
	node *temp=findNodePrivate(key,root);
	node *parent=findParentNodePrivate(key,root);
	deleteNodePrivate(key,temp,parent);
	
}
void tree::deleteNodePrivate(int key,node *ptr,node *parent){
	if(ptr->left==NULL and ptr->right==NULL){
		if(parent->left->key==key){
			parent->left=NULL;
			delete ptr;
		}
		else if(parent->right->key==key){
			parent->right=NULL;
			delete ptr;
		}
	}
	else if((ptr->left!=NULL and ptr->right==NULL)or(ptr->left==NULL and ptr->right!=NULL)){
		if(ptr->left!=NULL){
			if(parent->left->key==key){
				parent->left=ptr->left;
				delete ptr;
			}
			else{
				parent->right=ptr->left;
				delete ptr;
			}
		}
	}
	else if(ptr->left!=NULL and ptr->right!=NULL){
			int minElement=smallestElementPrivate(ptr->right);
			node *min=tree::findNodePrivate(minElement,ptr->right);
			node *minParent=findParentNodePrivate(min->key,root);
			ptr->key=min->key;
			cout<<minParent->key<<endl;
			minParent->left=NULL;
			delete min;
	}
}
int main(){
	tree obj;
	obj.insert(60);
	obj.insert(15);
	obj.insert(48);
	obj.insert(92);
	obj.insert(12);
	obj.insert(47);
	obj.insert(75);
	obj.insert(100);
	obj.preorderTraversal();
	//obj.inorderTraversal();
	//obj.postorderTraversal();
	//obj.smallestElement();
	//obj.largestElement();
	//obj.findNode(100);
	//obj.findParentNode(47);
	cout<<endl;
	obj.deleteNode(15);
	cout<<"after: "<<endl;
	obj.preorderTraversal();
	return 0;
}
