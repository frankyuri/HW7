#include "BagInterface.h"
#include "Node.h"
#include <cstddef>
#include <string>

template<class ItemType>
class LinkedBag : public BagInterface<ItemType>
{
private:
	Node<ItemType>* headPtr; 
	int itemCount;           
	Node<ItemType>* getPointerTo(const ItemType& target) const;

public:
	LinkedBag();
	LinkedBag(const LinkedBag<ItemType>& aBag); 
	virtual ~LinkedBag();                       
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool addLast(const ItemType& newEntry);
	bool add2ndToLast(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	bool removeLast();
	bool remove2ndToLast();
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
	vector<ItemType> toVector() const;
}; 

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}  

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag)
{
	itemCount = aBag->itemCount;
	Node<ItemType>* origChainPtr = aBag->headPtr; 

	if (origChainPtr == nullptr)
		headPtr = nullptr;  
	else
	{
		headPtr = new Node<ItemType>();
		headPtr->setItem(origChainPtr->getItem());

		Node<ItemType>* newChainPtr = headPtr; 
		while (origChainPtr != nullptr)
		{
			origChainPtr = origChainPtr->getNext();

			ItemType nextItem = origChainPtr->getItem();

			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

			newChainPtr->setNext(newNodePtr);

			newChainPtr = newChainPtr->getNext();
		} 

		newChainPtr->setNext(nullptr); 
	}
} 

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
	clear();
}  

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{      
	Node<ItemType>* nextNodePtr = new Node<ItemType>();
	nextNodePtr->setItem(newEntry);
	nextNodePtr->setNext(headPtr);  
	headPtr = nextNodePtr;          
	itemCount++;

	return true;
}  // end add

template<class ItemType>
vector<ItemType> LinkedBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}  // end while

	return bagContents;
}  // end toVector

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry)
{
	Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
	if (canRemoveItem)
	{
		entryNodePtr->setItem(headPtr->getItem());

		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();

		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		itemCount--;
	}
	return canRemoveItem;
}  

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
	Node<ItemType>* nodeToDeletePtr = headPtr;
	while (headPtr != nullptr)
	{
		headPtr = headPtr->getNext();

		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;

		nodeToDeletePtr = headPtr;
	}  
	itemCount = 0;
}  

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
	int counter = 0;
	Node<ItemType>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		if (anEntry == curPtr->getItem())
		{
			frequency++;
		} // end if

		counter++;
		curPtr = curPtr->getNext();
	} 

	return frequency;
} 

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
	return (getPointerTo(anEntry) != nullptr);
}  

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const
{
	bool found = false;
	Node<ItemType>* curPtr = headPtr;

	while (!found && (curPtr != nullptr))
	{
		if (anEntry == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	} 

	return curPtr;
} 

template<class ItemType>
bool LinkedBag<ItemType>::addLast(const ItemType& newEntry)
{
	Node<ItemType>* curPtr = headPtr;
	Node<ItemType>* tmp = new Node<ItemType>();
	tmp->setItem(newEntry);
	tmp->setNext(nullptr);
	if (headPtr == nullptr) 
		headPtr=tmp;
	else {
		while (curPtr->getNext()!=nullptr)
			curPtr = curPtr->getNext();
		curPtr->setNext(tmp);
	}
	itemCount++;
	return true;
}  // end add

template<class ItemType>
bool LinkedBag<ItemType>::add2ndToLast(const ItemType& newEntry)
{
	Node<ItemType>* curPtr = headPtr, * prePtr = nullptr;
	
	Node<ItemType>* tmp = new Node<ItemType>();
	tmp->setItem(newEntry);
	tmp->setNext(nullptr);
	if (headPtr == nullptr) {
		headPtr = tmp;
	}
	else {
		while (curPtr->getNext() !=nullptr)
		{	
			prePtr = curPtr;
			curPtr = curPtr->getNext();
		}
		if (prePtr == nullptr) {
			tmp->setNext(curPtr);
			headPtr = tmp;
		}
		else
		{
			tmp->setNext(curPtr);
			prePtr->setNext(tmp);
		}
		
	}
	itemCount++;
	return true;
}  // end add

template<class ItemType>
bool LinkedBag<ItemType>::removeLast()
{
	bool canRemoveItem = !isEmpty();
	Node<ItemType>
		* curPtr = headPtr,
		* prePtr = nullptr;

	if (canRemoveItem) {
		while (curPtr->getNext()!=nullptr) {
			prePtr = curPtr;
			curPtr = curPtr->getNext();
		}
		if (prePtr == nullptr)
		{
			delete headPtr;
			headPtr = nullptr;
			itemCount--;
			return true;
		}
		prePtr->setNext(nullptr);
		itemCount--;
	}
	return canRemoveItem;
}  // end remove

template<class ItemType>
bool LinkedBag<ItemType>::remove2ndToLast()
{
	bool canRemoveItem = !isEmpty();
	Node<ItemType>
		* curPtr = headPtr,
		* prePtr = nullptr;
	if (canRemoveItem) {
		int flag = 0;
		while (curPtr->getNext()!=nullptr) {
			if (flag==0) {
				prePtr = curPtr;
			}
			else if (flag >1) {
				prePtr = prePtr->getNext();
			}
			curPtr = curPtr->getNext();
			flag++;
		}
		if (prePtr == nullptr)
		{
			delete headPtr;
			headPtr = nullptr;
			itemCount--;
			return true;
		}
		else if (flag < 2) {
			headPtr = prePtr->getNext();
			itemCount--;
			return true;
		}
		prePtr->setNext(curPtr);
		itemCount--;
	}
	return canRemoveItem;
}  // end remove

//#endif