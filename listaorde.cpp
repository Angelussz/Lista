#include<iostream>
using namespace std;

template<typename T>
class nodo
{
public:
	T dato;
	nodo<T>* link;
};


template<typename T>
class linkedListIterator 
{
private:
	nodo<T> *current;
public:
	linkedListIterator(){current = NULL;}
	linkedListIterator(nodo<T> *ptr){ current = ptr;}
	T operator *();
	linkedListIterator<T> operator++();
	bool operator ==(const linkedListIterator<T>& right) const;
	bool operator !=(const linkedListIterator<T>& right) const;
};

template<typename T>
T linkedListIterator<T>::operator *()
{
	return current->dato;
}

template<typename T>
linkedListIterator<T> linkedListIterator<T>::operator++()
{
	current = current->link;
	return *this;
}
template<typename T>
bool linkedListIterator<T>::operator == (const linkedListIterator<T>& right) const
{
	return (current == right.current);
}

template<typename T>
bool linkedListIterator<T>::operator !=(const linkedListIterator<T>& right)const
{
	return (current != right.current);
}



template<typename T>
class linkedListType
{
private:
	void copyList(const linkedListType<T>& otherList);
protected:
	int count;
	nodo<T> *first;
	nodo<T> *last;
public:
	linkedListType();
	linkedListType(const linkedListType<T>& otherList);
	~linkedListType();
	const linkedListType<T> & operator = (const linkedListType<T>&);
	void initializeList();
	bool EmptyList() const ;
	void print() const ;
	int length() const; 
	void destroyList();
	T front() const;
	T back() const;
	virtual bool search(const T& searchItem)const = 0;
	virtual void insertFirst( const T& newItem) = 0;
	virtual void insertLast(const T& newItem) = 0;
	virtual void deletenodo(const T& deleteItem) = 0;
	linkedListIterator<T> begin();
	linkedListIterator<T> end();


};

template<typename T>
linkedListType<T>::linkedListType()
{
	first=NULL;
	last=NULL;
	count=0;
}


template<typename T>
linkedListType<T>::linkedListType(const linkedListType<T>& otherList)
{
	first = NULL;
	copyList(otherList);
}



template<typename T>
const linkedListType<T> & linkedListType<T>::operator = (const linkedListType<T>& otherList) //asigna la nueva lista
{
	if(this->otherList)
	{
		copyList(otherList);
	}

	return *this;
}



template<typename T>
void linkedListType<T>::destroyList()
{
	nodo<T>* temp;
	while(first!=NULL)
	{
		temp = first;
		first = first->link;
		delete temp;
	}

	delete last;
}
template<typename T>
bool linkedListType<T>::EmptyList()const
{
	return first=NULL;
}



template<typename T>
void linkedListType<T>::initializeList()
{
	destroyList();
}


template<typename T>
void linkedListType<T>::print()const
{
	nodo<T>* current;
	current = first;
	while(current)
	{
		cout<<"dato"<<current->dato<<endl;
		current=current->link;
	}
}


template<typename T>
int linkedListType<T>::length() const
{
	return count;
}



template<typename T>
T linkedListType<T>::front() const
{
	if(!first)return NULL;

	return first->dato;
}



template<typename T>
T linkedListType<T>::back() const
{
	if(!last)return NULL;

	return last->dato;
}


template<typename T>
linkedListIterator<T> linkedListType<T>::begin()
{
	linkedListIterator<T> temp(first);
	return temp;
}



template<typename T>
linkedListIterator<T> linkedListType<T>::end()
{
	linkedListIterator<T> temp(last);
	return temp;
}


template<typename T>
void linkedListType<T>::copyList(const linkedListType<T>& otherList)
{
	nodo<T>* newnodo;
	nodo<T>* current;

	if(first)
	{
		destroyList();
	}

	if(otherList.first == NULL)
	{
		first = last =NULL;
		count = 0;
	}

	else
	{
		current = otherList.first;
		count = otherList.count;
		first = new nodo<T>;
		first->dato = current->dato;
		first->link = NULL;
		last = first;
		current = current->link;

		while(current!=NULL)
		{
			newnodo = new nodo<T>;
			newnodo->dato = current->dato;
			newnodo->link = NULL;
			last->link = newnodo; 
			last = newnodo; 
			current = current->link;
		}

	}
}


template <class T>
linkedListType<T>::~linkedListType() 
{
	destroyList();
}



//CLASE DE LA LISTA DESORDENADA


template<typename T>
class  unorderedLinkedList: public linkedListType<T>
{
public:
	 bool search(const T& searchItem)const;
	 void insertFirst( const T& newItem);
	 void insertLast(const T& newItem);
	 void deletenodo(const T& deleteItem);
	
};

template<typename T>
bool  unorderedLinkedList<T>::search(const T& searchItem) const //esto tradara n de tiempo
{
	nodo<T>* current = this->first;
	bool found = false;

	current = this->first;

	while(current && !found)
	{
		if(current->dato = searchItem)
			found = true;
		else
		{
			current = current->link;
		}
	}
	return found;
}

template<typename T>
void unorderedLinkedList<T>::insertFirst(const T& newItem)
{
	nodo<T> *newnodo;
	newnodo = new nodo<T>;
	newnodo->dato = newItem;

	newnodo->link = this->first;
	newnodo = this->first;

	this->count++;

	if(!this->first)
	{
		this->last = this->first = newnodo;
	}

	
	
}



template<typename T>
void unorderedLinkedList<T>::insertLast(const T& newItem)
{
	nodo<T> *newnodo;
	newnodo = new nodo<T>;
	newnodo->dato = newItem;
	newnodo->link = NULL;

	if(!this->first)
	{
		this->last = this->first = newnodo;
	}

	else
	{
		this->last-> link = newnodo;
		this->last = newnodo; 
	}
	this->count ++;	
}


template<typename T>
void unorderedLinkedList<T>::deletenodo(const T& deleteItem)
{
	nodo<T> *current;
	nodo<T> *trailCurrent;
	bool found;

	if (this->first == NULL)
	{
		cout<<"no sale nada"<<endl;
	}
	else
	{
		if(this->first->dato == deleteItem)
		{
			current = this->first;
			this->first = this->irst->link;

			if(this->first==NULL)
			{
				this->last = NULL;
			}

			delete current;
		}

		else
		{
			trailCurrent = this->first;
			current = this->first->link;
			found = false;

			while (current != NULL && !found)
			{
				if (current->info != deleteItem)
				{
					trailCurrent = current;
					current = current-> link;
				}
				else
					found = true;
			}

			if(found)
			{
				trailCurrent ->link = current->link; 
				if(this->last==current)
				{
					this->last = trailCurrent;
				}

				delete current;
				this->count--;
			}

			else
			{
				cout<<"no se encontro valor"<<endl;
			}

		}

	}

}


//CLASS ORDERED


template <class T>
class orderedLinkedList: public linkedListType<T>
{
public:
	 bool search(const T& searchItem)const;
	 void insert(const T& newItem);
	 void insertFirst( const T& newItem);
	 void insertLast(const T& newItem);
	 void deletenodo(const T& deleteItem);
};

template<typename T>
bool orderedLinkedList<T>::search(const T& searchItem)const
{
	nodo<T> *current = this->first;
	bool found = false;
	while(current && !found)
	{
		if(current->dato == searchItem)
		{
			found = true;
		}
		else
		{
			current = current->link;
		}
	}

	if(found)
	{
		found = (current->dato == searchItem);
	}

	return found;
}

template<typename T>
void orderedLinkedList<T>::insert(const T& newItem)
{
	
	nodo<T> *current;
	nodo<T> *trailCurrent;
	nodo<T>* newnodo;

	bool found;

	newnodo = new nodo<T>;
	newnodo->dato = newItem;
	newnodo->link = NULL;

	if(!this->first)
	{
		this->first =  newnodo;
		this->last = newnodo;
		this->count++;
	}

	else
	{
		current = this->first;
		found = false;

		while(current!=NULL && !found)
		{
			if(current->dato >= newItem)
			{
				found = true;
			}

			else 
			{
				trailCurrent = current;
				current = current->link;
			}


		}

		if(current == this->first)
		{
			newnodo->link = this->first;
			this->first = newnodo;
			this->count++;
		}

		else
		{
			trailCurrent->link = newnodo;
			newnodo->link = current;
			if (current == NULL){
				this->last = newnodo;
			}							
			this->count++;
		}
	}
}

template<typename T>
void orderedLinkedList<T>::insertFirst(const T& newItem)
{
	insert(newItem);
}

template<typename T>
void orderedLinkedList<T>::insertLast(const T& newItem)
{
	insert(newItem);
}

template<typename T>
void orderedLinkedList<T>::deletenodo(const T& deleteItem)
{
	nodo<T> *current;
	nodo<T> *trailCurrent;
	bool found;

	if(this->first==nullptr)
	{
		cout<<"no hay valores"<<endl;
	}

	else
	{
		current = this->first;
		found = false;

		while(current && !found) 
		{
			if(current->dato >= deleteItem)
			{
				found = true;
			}

			else 
			{
				trailCurrent = current;
				current = current->link;
			}


		}

		if(current == NULL)
		{
			cout<<"no existe el elemento"<<endl;
		}

		else if (current->dato == deleteItem)
		{
			if(current== this->first)
			{
				this->first = this->first->link;
				if (this->first==NULL)
				{
					this->last = NULL;
				}

				delete current;
			}

			else
			{
				trailCurrent->link = current->link;
				if(current== NULL)
				{
					this->last=trailCurrent;
				}
				delete current;
			}
			this->count--;
		}

		else cout<<"no hay elementp en la lista"<<endl;

	}
}



int main()
{
	orderedLinkedList<int> list1, list2;
	int num;

	cout<<"inserta numero"<<endl;
	cin>>num;

	while (num != -999)
	{
		list1.insert(num);
		cin >> num;
	}

	cout << endl; //Line 14
	cout << "Line 15: list1: ";
	list1.print();
	cout << endl;
}
