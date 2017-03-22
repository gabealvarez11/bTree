#ifndef BTREE_H
#define BTREE_H
#include <iostream>

template <class T>
struct Node
{
	Node(){}
	
	T** keys;
	int degree;
	Node<T>** children;
	int numKeys;
	bool isLeaf;
	
	Node(int _degree, bool _isLeaf)
	{
		degree = _degree;
		isLeaf = _isLeaf;
		
		keys = new T*[2*degree-1];
		children = new Node<T>*[2*degree];
		
		numKeys = 0;
	}
	
	~Node()
	{
		delete keys;
		delete children;
	}
	
	Node<T>* search(T* x)
	{
		int i = 0;
		while(i < numKeys && *x > *keys[i])
			i++;
		
		if(*keys[i]==*x)
		{
			return this;
		}
		
		if(isLeaf == true)
		{
			std::cout << "yep";
			return NULL;
		}
		
		return children[i]->search(x);
	}
	
	void traverse()
	{
		int i;
		for(i = 0; i < numKeys; i++)
		{
			if(children[i] != NULL)
			{
				if(isLeaf == false && children[i] != NULL)
				{
					children[i]->traverse();
				}
				
				std::cout << *keys[i];
			}
		}
		
		/*if(isLeaf == false && children[i] != NULL)
		{
			children[i]->traverse();
		}*/
	}
	
	void insertNonFull(T* x)
	{
		int i = numKeys - 1;
		
		if(isLeaf == true)
		{			
			while(i >= 0 && *keys[i] > *x)
			{
				keys[i+1] = keys[i];
				i--;
			}
			
			keys[i+1] = x;
			numKeys++;
		}
		
		else
		{
			while(i >= 0 && *keys[i] > *x)
				i--;
			
			if(children[i+1]->numKeys == 2*degree - 1)
			{
				splitChild(i + 1, children[i+1]);
				
				if(*keys[i+1] < *x)
					i++;
			}
			
			children[i+1]->insertNonFull(x);
		}
	}
	
	void splitChild(int i, Node<T>* y)
	{		
		Node<T>* z = new Node(y->degree, y->isLeaf);
		z->numKeys = degree - 1;
		
		for(int j = 0; j < degree - 1; j++)
			(z->keys[j]) = (y->keys[j+degree]);
		
		if(y->isLeaf == false)
		{
			for(int j = 0; j < degree; j++)
				(z->children[j]) = (children[j+degree]);
		}
		
		y->numKeys = degree - 1;
		
		for(int j = numKeys; j >= i + 1; j--)
			(children[j+1]) = (children[j]);
		
		children[i+1] = z;
		
		for(int j = numKeys - 1; j >= i; j--)
			(keys[j+1]) = (keys[j]);
		
		(keys[i]) = y->keys[degree - 1];
		
		numKeys++;
	}
	
	void remove(T* x)
	{		
		if(keys == NULL)
			return;
		
		else
		{
			bool found = false;
			int foundLoc = 0;
			
			for(int i = 0; i < 2*degree - 1; i++)
			{
				if(keys[i] != NULL && *keys[i] == *x)
				{
					found = true;
					foundLoc = i;
				}
			}
			
			if(found == false)
			{
				for(int k = 0; k < numKeys; k++)
				{
					if(children[k] != NULL)
						children[k]->remove(x);
				}
			}
			
			else
			{
				delete keys[foundLoc];
			}
			
			return;
		}
	}
};

template <class T>
class bTree
{
	private:
		Node<T>* root;
		int degree;

	public :		
		bTree(int);
		void insert (T* x);
		Node<T>* search (T* x);
		void remove (T* x);
		void clear ();
		void display ();
		void deltree ();
		~bTree();
};

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
		std::cout << "the tree is empty";
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

#endif