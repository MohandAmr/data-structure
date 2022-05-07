#include <iostream>
#include<algorithm>
#include <sstream>
#include <string>
using namespace std;
template <class t>
class node {


public:
	t data;
	node<t>* next;
	node() {

		this->next = nullptr;
	}	node(t node_data , node<t>* ptr= nullptr) {
		data = node_data;
		next = ptr;
	}
};
template<class t>
class list {
public:
	node<t>* head;
	node<t>* tail;

	list() :head(nullptr), tail(nullptr) {}


	list(t data, int initial_size) {
			node<t>* newnode = new node<t>(data);
			head = tail= newnode;
			while (--initial_size) {
				node<t>* newnode = new node<t>(data);
				tail->next = newnode;
				tail = newnode;
			}
	}
	list<t>& operator = (list<t> &another_list) {
		iterator itr = another_list.begin();
		int c = another_list.size();
		while (c--) {
			this->push_back(*itr);
			if(c)
			itr++;
			else { break; }
		}
		return *this;
	}
	class iterator/*: public list */{

	public:
		node<t>* nodePtr;
		node<t>* headitr;
		iterator(node<t>* newPtr) : nodePtr(newPtr) {}
		iterator()  {
			nodePtr = nullptr;
			headitr =nullptr;
		}
		void operator++(int) {
			iterator temp = *this;
			try {
				if (nodePtr->next) {
					nodePtr = nodePtr->next;

				}
				else {

					throw 505;

				}
			}
			catch (...) {
				cout << "out of range\n";
			}
		}

		/*iterator operator--(int) {

			node<t>* temp = head;
			try {

				if (this->nodePtr != temp) {
					while (temp->next != this->nodePtr) {
						temp = temp->next;
					}
					this->nodePtr = temp;
				}
				else {
				throw 505;
				}

			}
			catch (...) {
				cout << "out of range\n";
			}
		}*/

		t operator*() {
			return nodePtr->data;
	}
		bool operator!=(const iterator itr)  {
			return nodePtr != itr.nodePtr;
		}
		bool operator==(const iterator itr) {
			return nodePtr == itr.nodePtr;
		}

	};

	 int size() {
		node<t>* temp = head;
		int c = 0;
		while (temp) {
			c++;
			temp = temp->next;
		}
		return c;
	 }
	void display() {
		node<t>* temp = head;
		while (temp)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	void push_back(t data) {
		node<t>* newnode = new node<t>(data);
		if (!head) {
			head = newnode;
		}
		else
		{
			node<t>* temp= head;
			while (temp->next) {
				temp = temp->next;
			}
			temp->next = newnode;
			tail = newnode;

		}
}
	void insert(iterator position, const t& value) {
		node<t>* newNode = new node<t>(value, position.nodePtr->next);
		if (position.nodePtr == head) {
			node<t>* temp = new node<t>;
			temp->data = value;
			temp->next = head;
			head = temp;
			return;
		}
		else if (position.nodePtr == tail) {
			tail->next = newNode;
			return;
		}
		node<t>* pre = new node<t>;
		node<t>* cur = new node<t>;
		node<t>* temp = new node<t>;
		cur = head;
		while (pre->next!=position.nodePtr)
		{
			pre = cur;
			cur = cur->next;
		}
		temp->data = value;
		pre->next = temp;
		temp->next = cur;

	}
	  iterator begin()  {
		return iterator(head);
	}
	iterator end() {
		return iterator(tail);
	}

	iterator erase(iterator position) {
		node<t>* temp = head;
		if (position.nodePtr == head) {
			head = head->next;
			free(temp);
		}
		else {
			while (temp->next != position.nodePtr) {
				temp = temp->next;
			}
			temp->next = temp->next->next;
			free(position.nodePtr);
		}
		return position;
	}
	~list() {
		while (head->next != nullptr) {
			node<t>* temp = head;
			head = head->next;
			free (temp);
		}
		free( head);
	}



};



int main() {


	list <int >mylist(1,2);
	mylist.display();//1 1
	cout <<"Size= " << mylist.size() << endl;//2
	mylist.push_back(4);
	mylist.push_back(3);
	mylist.push_back(2);
	mylist.push_back(1);
	mylist.display();//1 1 4 3 2 1


	 list<int>::iterator it = mylist.begin();
	 cout<<"Size= " << mylist.size()<<endl;//6
	 it++; //it=1
	 it++;//it=5
	 it++;//it=2
	 it++;//it=4
	 it++;//it=3
	 cout <<  *it<<endl;//print the last elemet (3)
	 mylist.insert(it, 7);//insert 7 after 3
	 mylist.display();//1 1 4 3 2 1 7

	 it++;//it=7
	 it++;//out of range


	 mylist.erase(it);//remove the last elemnet (7)
	 mylist.display();//1 1 4 3 2 1
	 it= mylist.end();
	 list<int>::iterator it2 = mylist.end();
	 cout << *it2 << endl;//1

		 cout << (it == it2)<<endl ;// True print--> 1

		 list<int> l2;
		 l2 = mylist;//operator=
		 l2.display();//1 1 4 3 2 1

}
