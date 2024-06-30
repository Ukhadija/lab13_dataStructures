#pragma once
#pragma once
#include <iostream>
using namespace std;

template <class T>
struct node
{
	T data;
	node <T>* next;

	node<T>(T d) {
		data = d;
		next = NULL;
	}
	node<T>() {
		data = 0;
		next = NULL;
	}
};

template <class T>
class Queue {
private:
	node<T>* front;
	node<T>* rear;
public:
	Queue()
	{
		front = NULL;
		rear = NULL;
	}

	void enqueue(T d)
	{
		node<T>* temp = new node<T>(d);
		/*temp->data = d;
		temp->next = NULL;*/
		if (front == NULL || rear == NULL)
		{
			front = temp;
			rear = temp;
		}
		else
		{
			//node<T>* temp1 = rear;
			rear->next = temp;
			//temp->next = NULL;
			rear = temp;
		}
	}

	T dequeue()
	{
		if (front == NULL || rear == NULL) {
			return NULL;
		}
		else {
			node <T>* temp = front;
			front = front->next;
			return temp->data;
		}
	}

	int Front()
	{
		return front->data;
	}

	bool isEmpty()
	{
		if (front == NULL && rear == NULL)
		{
			return true;
		}
		return false;
	}

	void Display()
	{
		node<T>* p = front;
		while (p != NULL)
		{
			cout << p->data << " ";
			p = p->next;

		}
		cout << endl;
	}
};

struct AvlNode
{
	int data;
	AvlNode* left;
	AvlNode* right;
	int height;


	AvlNode() {
		height = 0;
		data = 0;
		left = NULL;
		right = NULL;
	}

	AvlNode(int data)
	{
		height = 0;
		this->data = data;
		left = NULL;
		right = NULL;
	}
};


class AVL
{
private:
	AvlNode* root;

public:
	AVL()
	{
		root = NULL;
	}

	int getHeight(AvlNode* N)
	{
		if (N == NULL)
			return 0;
		else {
			/* compute the depth of each subtree */
			int l = getHeight(N->left);
			int r = getHeight(N->right);

			/* use the larger one */
			if (l > r)
				return (l + 1);
			else
				return (r + 1);
		}
	}
	int MAX(int n1, int n2)
	{
		if (n1 > n2)
		{
			return n1;
		}
		return n2;
	}

	AvlNode* getRoot()
	{
		return root;
	}

	AvlNode* LL(AvlNode* node1) //single rotate with right
	{
		AvlNode* node2;
		node2 = node1->right;
		node1->right = node2->left;
		node2->left = node1;
		node1->height = MAX(getHeight(node1->left), getHeight(node1->right))+1;
		node2->height = MAX(getHeight(node2->right), node1->height) + 1 ;
		return node2;
	}
	
	AvlNode* RR(AvlNode* node1)
	{
		AvlNode* node2;
		node2 = node1->left;
		node1->left = node2->right;
		node2->right = node1;
		node1->height = MAX(getHeight(node1->left), getHeight(node1->right)) + 1;
		node2->height = MAX(getHeight(node2->right), node1->height) + 1;
		return node2;
	}

	AvlNode* LR(AvlNode* node1)
	{
		node1->right = RR(node1->right);
		return LL(node1);
	}

	AvlNode* RL(AvlNode* node1)
	{
		node1->left = LL(node1->left);
		return LL(node1);
	}

	int Balance(AvlNode* m)
	{
		if (m->left && m->right)
		{
			return m->left->height - m->right->height;
		}
		if (m->left && m->right==NULL)
		{
			return m->left->height;
		}
		if (m->right && m->left == NULL)
		{
			return m->right->height;
		}
	}

	//AvlNode*  Insert(AvlNode * root, int value)
	//{
	//	if (!root) {
	//		return new AvlNode(value);
	//	}
	//	if (value > root->data) {
	//			
	//		root->right = Insert(root->right, value);
	//	}
	//	else if (value < root->data) {
	//		root->left = Insert(root->left, value);
	//	}

	//	if(Balance(root) )
	//	return root;
	//}

	AvlNode* Insert(int d, AvlNode*T)
	{
		if (T == NULL)
		{
			T = new AvlNode;
			T->data = d;
			T->left = T->right = NULL;
		}
		else if (d < T->data)
		{
			T->left = Insert(d, T->left);
			if (getHeight(T->left) - getHeight(T->right) == 2)
				if (d < T->left->data)
				{
					T = RR(T);
				}
				else
					T = RL(T);
				
		}
		else if (d > T->data)
		{
			T->right = Insert(d, T->right);
			if (getHeight(T->right) - getHeight(T->left) == 2)
			{
				if (d > T->right->data)
				{
					T = LL(T);
				}
				else
				{
					T = LR(T);
				}
			}
		}
		T->height = getHeight(T);
		return T;
	}
	
	bool retrieve(int d)
	{
		bool exists = false;
		AvlNode* temp = root;
		if (root == NULL)
		{
			return false;
		}
		else
		{
			while (temp != NULL)
			{
				if (d == temp->data)
				{
					exists = true;
					return exists;
				}
				else if (d < temp->data)
				{
					if (temp->left == NULL)
					{
						return false;
					}
					else
					{
						temp = temp->left;
					}
				}
				else if (d > temp->data)
				{
					if (temp->right == NULL)
					{
						return false;
					}
					else
					{
						temp = temp->right;
					}
				}

			}
		}
	}
	bool subtree(int* arr, int size)
	{
		bool flag = true;
		for (int i = 0; i < size; i++)
		{
			flag = retrieve(arr[i]);
			if (flag == false)
			{

				return false;
			}
		}
		return true;
	}
	void PreOrderTraversal(AvlNode* r)
	{
		if (r == NULL)
		{
			return;
		}
		cout << r->data << ",";
		PreOrderTraversal(r->left);

		PreOrderTraversal(r->right);
	}

	void InOrderTraversal(AvlNode* r)
	{
		if (r == NULL)
		{
			return;
		}
		InOrderTraversal(r->left);
		cout << r->data << ",";
		InOrderTraversal(r->right);
	}


	void PostOrderTraversal(AvlNode* r)
	{
		if (r == NULL)
		{
			return;
		}
		PostOrderTraversal(r->left);
		PostOrderTraversal(r->right);
		cout << r->data << ",";
	}
	void LevelOrder(AvlNode* n)
	{
		Queue <AvlNode*>* q = new Queue<AvlNode*>;
		//AvlNode* temp = n;
		//AvlNode* curr ;
		if (n == NULL)
			return;
		q->enqueue(n);

		while (!q->isEmpty())
		{
			AvlNode* curr = q->dequeue();
			if (curr == NULL)
			{
				break;
			}
			if (curr != NULL)
			{
				cout << curr->data << ",";
				if (curr->left != NULL)
				{
					q->enqueue(curr->left);
				}
				if (curr->right != NULL)
				{
					q->enqueue(curr->right);
				}
			}
		}
		delete q;
	}
	
	AvlNode* getMin(AvlNode* n)
	{
		//int min = 0;
		if (n == NULL)
		{
			return NULL;
		}
		AvlNode* q = n->left; //left most

		while (q->left != NULL)
		{
			q = q->left;
		}
		return q;

	}
	AvlNode* getMax(AvlNode* n)
	{
		//int min = 0;
		if (n == NULL)
		{
			return NULL;
		}
		AvlNode* q = n->right; //left most

		while (q->right != NULL)
		{
			q = q->right;
		}
		return q;
	}
	AvlNode* Delete(AvlNode* currRoot, int d)
	{
		//AvlNode* p = root;
		if (currRoot == NULL)
		{
			return currRoot;
		}
		if (currRoot->data == d)
		{
			//delete

			if (currRoot->left == NULL && currRoot->right == NULL)
			{
				return NULL;
			}
			else if (currRoot->left == NULL)
			{

				AvlNode* p = currRoot->right;
				currRoot = NULL;
				delete currRoot;
				//free(currRoot);
				return p;
			}
			else if (currRoot->right == NULL)
			{
				AvlNode* p = currRoot->left;
				currRoot = NULL;
				delete currRoot;
				return p;
			}
			else
			{
				AvlNode* p = getMin(currRoot->right);
				currRoot->data = p->data;
				currRoot->right = Delete(currRoot->right, p->data);
			}
		}
		else if (d < currRoot->data)
		{
			currRoot->left = Delete(currRoot->left, d);
		}
		else if (d > currRoot->data)
		{
			currRoot->right = Delete(currRoot->right, d);
		}

		return currRoot;
	}
	AvlNode* removeKeys(AvlNode* r, AvlNode* r1, int a, int b)
	{
		if (r == NULL)
		{
			return NULL;
		}
		removeKeys(r->left, r1, a, b);
		removeKeys(r->right, r1, a, b);
		if (!(r->data >= a && r->data <= b))
		{
			r1 = Delete(r1, r->data);

		}
		return r1;
	}


};
