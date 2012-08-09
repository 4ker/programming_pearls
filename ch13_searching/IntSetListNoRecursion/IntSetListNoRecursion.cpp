/*
file name: IntSetListNoRecursion.cpp
purpose: 
	利用链表，实现顺序插入排序(链表insert"不"使用递归函数)。
creator: guangwei jiang
create time: 2012-08-09

modify history:
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <set>
 
using namespace std;

// notes: bigrand should at least 64bits
unsigned long long bigrand()
{
	return RAND_MAX*rand() + rand();
}

class IntSetListNoRecursion {	
private:
	int n;
	struct node{
		int val;
		node *next;
		node(int v, node *p){val = v; next = p;}
	};
	node *head, *sentinel;
public:
	IntSetListNoRecursion (int maxelements, int maxval)
	{
		sentinel = head = new node(maxval, 0);
		n = 0;
	}
	int size() {return n;}
	node *insert(node *p, int t)
	{
		node * p_head;

		p_head = p;

		if (p->val > t)
		{
			// case 1: the "t" is min value, so insert head
			p_head = new node(t, p);
			n++;
		}
		else if (p->val < t)
		{
			// case 2: the "t" is not min value, and insert in the middle of the list
			for (; p->next->val < t; p = p->next)
				;
			p->next = new node(t, p->next);
			n++;
		}
		
		return p_head;
	}
	void insert (int t)
	{
		head = insert(head, t);
	}
	void report(int *v)
	{
		int i = 0;
		node *p;

		for (p = head; p != sentinel; p = p->next)
			v[i++] = p->val;
	}
};

/*
 * parameter: 
 *		m - the max number of elements
 *		n - the max value
 */
void gensets (int m, int n)
{
	int *v = new int[m];
	IntSetListNoRecursion S(m, n);

	srand((int)time(0));

	while (S.size() < m)
		  S.insert(bigrand()%n);
	
	S.report(v);
	for (int i = 0; i < m; i++)
	{
		cout << v[i] << "\t";
		if ((i+1)%10 == 0)
			cout << "\n";
	}
}

int main()
{
	clock_t start, finish;
	double duration;
	int m, n;

	m = 100000;
	n = 10000000;

	start = clock();
	gensets(m, n);
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n" << "m="<< m << ", n=" << n << ", ";
	cout << "Cost time: " << duration << " seconds \n";
	cout << "\n";

	return 0;
}
