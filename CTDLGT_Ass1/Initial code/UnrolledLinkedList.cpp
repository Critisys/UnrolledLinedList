#include"UnrolledLinkedList.h"

void UnrolledLinkedList::add(int val) {
	// TODO
	size++;
	if (head == NULL) {
		Node * newNode = new Node(nodeSize);
		newNode->add(val);
		head = newNode;
		tail = newNode;
		numOfNodes++;
		return;
	}
	else if (tail->isFull()) {
		Node* newNode = new Node(nodeSize);
		for (int i = getHalfNodeSize(); i < nodeSize; i++) {
			newNode->add(tail->elements[i]);
		}
		newNode->add(val);
		tail->numElements = getHalfNodeSize();
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		numOfNodes++;
		return;
	}
	else {
		tail->add(val);
		return;
	}
}

int UnrolledLinkedList::getAt(int pos) {
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
	Node * currentNode = head;
	int num = pos;
	while ((num - currentNode->numElements) >= 0) {
		num = num - currentNode->numElements;
		currentNode = currentNode->next;
	}
	return currentNode->elements[num];
}

void UnrolledLinkedList::setAt(int pos, int val) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
	
	Node * currentNode = head;
	int num = pos;
	while ((num - currentNode->numElements) >= 0) {
		num = num - currentNode->numElements;
		currentNode = currentNode->next;
	}
	currentNode->elements[num] = val;
}


void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not	
	// TODO
	// no elements
	if (head == NULL) {
		Node * newNode = new Node(nodeSize);
		newNode->add(val);
		head = newNode;;
		tail = newNode;
		size++;
		numOfNodes++;
		return;
	}
	else if (pos == size) {
		this->add(val);
		return;
	}
	// pos is not equal size

	size++;
	Node * currentNode = head;
	int num = pos;
	while ((num - currentNode->numElements) >= 0) {
		num = num - currentNode->numElements;
		currentNode = currentNode->next;
	}

	if (!currentNode->isFull()) {
		currentNode->insertAt(num, val);
		return;
	}
	else {
		if (currentNode->prev != NULL && !currentNode->prev->isFull()) {
			if (num == 0) {
				currentNode->prev->add(val);
				return;
			}
			else {
				int Temp = currentNode->elements[0];
				currentNode->removeAt(0);
				currentNode->prev->add(Temp);
				currentNode->insertAt(num - 1, val);
				return;
			}
		}

		Node * newNode = new Node(nodeSize);
		numOfNodes++;
		int Temp = currentNode->elements[currentNode->numElements - 1];
		currentNode->removeAt(currentNode->numElements - 1);
		currentNode->insertAt(num, val);
		for (int i = getHalfNodeSize(); i < currentNode->numElements; i++) {
			newNode->add(currentNode->elements[i]);
		}
		newNode->add(Temp);
		for (int i = currentNode->numElements-1; i >= getHalfNodeSize(); i--) {
			currentNode->removeAt(i);
		}
		if (currentNode == tail) {
			currentNode->next = newNode;
			newNode->prev = currentNode;
			tail = newNode;
			return;
		}
		else {
			newNode->next = currentNode->next;
			currentNode->next->prev = newNode;
			newNode->prev = currentNode;
			currentNode->next = newNode;
			return;
		}
	}
	
}

void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO

	// get the current node and its position
	

	if (numOfNodes == 1) {
		if (size == 1) {
			head->removeAt(0);
			Node * pTemp = head;
			head = NULL;
			tail = NULL;
			size--;
			numOfNodes--;
			delete pTemp;
			return;
		}
		else {
			head->removeAt(pos);
			size--;
			return;
		}
	}

	Node * currentNode = head;
	int num = pos;
	while ((num - currentNode->numElements) >= 0) {
		num = num - currentNode->numElements;
		currentNode = currentNode->next;
	}
	//remove that pos
	size--;
	if (currentNode->numElements > getHalfNodeSize()) {
		currentNode->removeAt(num);
		return;
	}
	else {
		if (currentNode == head) {
			if (currentNode->next->numElements > currentNode->next->getHalfNodeSize()) {
				currentNode->removeAt(num);
				currentNode->add(currentNode->next->elements[0]);
				currentNode->next->removeAt(0);
				return;
			}
			else {
				currentNode->removeAt(num);
				for (int i = 0; i < currentNode->numElements; i++) {
					currentNode->next->insertAt(i, currentNode->elements[i]);
				}
				for (int i = currentNode->numElements -1; i >= 0; i--) {
					currentNode->removeAt(i);
				}
				
				head = currentNode->next;
				head->prev = NULL;
				delete currentNode;
				numOfNodes--;
				return;
			}
		}
		else {
			if (currentNode->prev->numElements > getHalfNodeSize()) {
				currentNode->removeAt(num);
				currentNode->insertAt(0, currentNode->prev->elements[currentNode->prev->numElements - 1]);
				currentNode->prev->removeAt(currentNode->prev->numElements - 1);
				return;
			}
			else {
				currentNode->removeAt(num);
				for (int i = 0; i < currentNode->numElements; i++) {
					currentNode->prev->add(currentNode->elements[i]);
				}
				for (int i = currentNode->numElements - 1; i >= 0; i--) {
					currentNode->removeAt(i);
				}

				if (currentNode == tail) {
					tail = currentNode->prev;
					tail->next = NULL;
				}
				else {
					currentNode->prev->next = currentNode->next;
					currentNode->next->prev = currentNode->prev;

				}
				delete currentNode;
				numOfNodes--;
				return;
			}
		}
	}
}

int UnrolledLinkedList::firstIndexOf(int val) {
	// TODO
	Node * currentNode = head;
	int num = 0;
	while (currentNode != NULL) {
		for (int i = 0; i < currentNode->numElements; i++) {
			if (currentNode->elements[i] == val) {
				return num + i;
			}
		}
		num += currentNode->numElements;
		currentNode = currentNode->next;
	}
	return - 1;
}

int UnrolledLinkedList::lastIndexOf(int val) {
	// TODO
	Node * currentNode = tail;
	int num = size -1;
	while (currentNode != NULL) {
		for (int i = currentNode->numElements - 1; i >= 0; i--) {
			if (currentNode->elements[i] == val) {
				return num - (currentNode->numElements - 1 - i);
			}
		}
		num -= currentNode->numElements;
		currentNode = currentNode->prev;
	}
	return -1;
}

bool UnrolledLinkedList::contains(int val) {
	// TODO
	Node * currentNode = head;
	int num = -1;
	for (int i = 0; i < size; i++) {
		num++;
		if ((num + 1) > currentNode->numElements) {
			num = 0;
			currentNode = currentNode->next;
		}
		if (currentNode->elements[num] == val) {
			return true;
		}
	}
	return false;
}

void UnrolledLinkedList::reverse() {
	// TODO
	int * arr = this->toArray();
	Node * currentNode = head;
	int num = -1;
	for (int i = 0; i < size; i++) {
		num++;
		if ((num + 1) > currentNode->numElements) {
			currentNode = currentNode->next;
			num = 0;
		}
		currentNode->elements[num] = arr[size - 1 - i];
	}
}

int* UnrolledLinkedList::toArray() {
	// TODO
	if (size == 0) return NULL;
	else {
		int * arr = new int[size];
		Node * currentNode = head;
		int pos = 0;
		while (currentNode != NULL) {
			for (int i = 0; i < currentNode->numElements; i++) {
				arr[pos] = currentNode->elements[i];
				pos++;
			}
			currentNode = currentNode->next;
		}
		return arr;
	}
}