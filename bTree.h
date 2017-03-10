#ifndef bTree_h
#define bTree_h
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
		
		//std::cout << "hey";
		
		//std::cout << *keys[i];
		//std::cout << *x;
		if(*keys[i]==*x)
		{
			/*Node<T> temp;
			Node<T>* tempPoint;
			tempPoint = &temp;
			temp = this;
			return tempPoint;*/
			//std::cout << "this";
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
			if(isLeaf == false)
			{
				children[i]->traverse();
			}
			std::cout << *keys[i] << " ";
		}
		
		if(isLeaf == false)
		{
			children[i]->traverse();
		}
	}
	
	void insertNonFull(T* x)
	{
		int i = numKeys - 1;
		
		if(isLeaf == true)
		{
			//std::cout << "one";
			
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
			//std::cout << "two";

			while(i >= 0 && *keys[i] > *x)
				i--;
			
			//std::cout << i;
			
			//std::cout << children[i+1] -> numKeys << " ";
			//std::cout << 2*degree - 1;
			if(children[i+1]->numKeys == 2*degree - 1)
			{
				splitChild(i + 1, children[i+1]);
				
				if(*keys[i+1] < *x)
					i++;
			}
			
			//std::cout << "three";

			children[i+1]->insertNonFull(x);
		}
	}
	
	void splitChild(int i, Node<T>* y)
	{
		//std::cout << "split";
		
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
	
	//
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

#endif