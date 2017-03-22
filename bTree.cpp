#include <iostream>
//#include "bTree.h"

using namespace std;

template<typename T>
bTree<T>::bTree(int t):
	root(new Node<T>(t, true)), degree(t) {}

template<typename T>
void bTree<T>::insert(T* x)
{
	if(root->keys[0] == NULL)
	{		
		root = new Node<T>(degree, true);
		root->keys[0] = x;
		root->numKeys = 1;
	}
	
	else
	{
		if(root->numKeys == 2*degree - 1)
		{			
			Node<T>* s = new Node<T>(degree, false);
			s->children[0] = root;
			s->splitChild(0, root);
			
			int i = 0;
			if (*(s->keys[0]) < *x)
				i++;
			s->children[i]->insertNonFull(x);
			
			root = s;
		}
		
		else
		{	
			root->insertNonFull(x);
		}
	}
}

template<typename T>
Node<T>* bTree<T>::search(T* x)
{
	return root->search(x);
}

template<typename T>	
void bTree<T>::remove(T* x)
{
	if(!root)
	{
		std::cout << "The tree is empty.";
		return;
	}
	
	root->remove(x);
	
	if(root->numKeys == 0)
	{
		Node<T>* temp = root;
		if(root -> isLeaf)
			root = NULL;
		else 
			root = root->children[0];
		delete(temp);
	}
	
	return;
}

template<typename T>
void bTree<T>::clear()
{
	Node<T>* tempNode = root;
	Node<T>** tempKids = tempNode->children;
	
	for(int i = 0; i < 2*degree - 1; i++)
	{
		tempNode = tempKids[i];
		delete tempNode;
	}
}
	
template<typename T>
void bTree<T>::display()
{
	if(root != NULL)
		root->traverse();
}

template<typename T>
void bTree<T>::deltree()
{
	root = NULL;
}

template<typename T>
bTree<T>::~bTree()
{
	deltree();
}

//for testing
/*int main()
{
	bTree<int> x(2);
	int value1, value2, value3, value4, value5;
	int* first;
	int* second;
	int* third;
	int* fourth;
	int* fifth;
	int* pointer;
	first = &value1;
	second = &value2;
	third = &value3;
	fourth = &value4;
	fifth = &value5;
	
	*first = 2;
	*second = 1;
	*third = 15;
	*fourth = 10;
	*fifth = 3;
	
	x.insert(first);
	x.insert(second);
	x.insert(third);
	x.insert(fourth);
	x.insert(fifth);
	//x.display();
	//cout << (x.search(fourth) == NULL);
	//x.remove(fourth);
	//x.clear();
	x.display();
}*/