#include <iostream>

using namespace std;

struct d_NODE {
    int key;
    d_NODE* pNext;
    d_NODE* pPrev;
};

struct d_List {
    d_NODE* pHead;
    d_NODE* pTail;
};

void printList (d_List* &L) {
    d_NODE* cur = L->pHead;
    if (!cur) {
        cout << "empty\n";
        return;
    }
    while (cur){
        cout << cur->key << " ";
        cur = cur->pNext;
    }
    cout << "\n";
}

d_NODE* createNode(int data)
{
    d_NODE* tmp = new d_NODE {data, nullptr, nullptr};
    return tmp;
}

d_List* createList(d_NODE* p_node)
{
    d_List* tmp = new d_List {p_node, p_node};
    return tmp;
}

bool addHead(d_List* &L, int data)
{
    //Add new Node before Head
    d_NODE* tmp = new d_NODE {data, L->pHead, nullptr};
    if (L->pHead) {
        L->pHead->pPrev = tmp;
    }
    else
        L->pTail = tmp;

    L->pHead = tmp;

    return 1;
}

bool addTail(d_List* &L, int data)
{
    if (L->pTail) {
        L->pTail->pNext = new d_NODE {data, nullptr, L->pTail};
        L->pTail = L->pTail->pNext;
    }
    else {
        L->pHead = new d_NODE {data, nullptr, nullptr};
        L->pTail = pHead;
    }
    return 1;
}

void removeHead(d_List* &L)
{
    d_NODE* tmp = L->pHead;
    L->pHead = L->pHead->pNext;

    if (!L->pHead)
        L->pTail = nullptr;
    else
        L->pHead->pPrev = nullptr;

    delete tmp;
}

void removeTail(d_List* &L)
{
    // Check if there's only 1 node in the list
    if (L->pHead == L->pTail) {
        delete L->pTail;
        L->pHead = nullptr;
        L->pTail = nullptr;
        return;
    }

    // Move to the node previous to the tail
    d_NODE* cur = L->pHead;
    while (cur->pNext != L->pTail)
        cur = cur->pNext;
    // Delete tail
    delete L->pTail;
    L->pTail = cur;
    L->pTail->pNext = nullptr;
}

void removeAll(d_List* &L) {
    while (L->pHead) {
        d_NODE* tmp = L->pHead;
        L->pHead = L->pHead->pNext;
        delete tmp;
    }
    L->pTail = nullptr;
}

void removeBefore(d_List* &L, int val)
{
    if (!L->pHead || L->pHead->key == val)
        return;

    if (L->pHead->pNext && L->pHead->pNext->key == val)
        return removeHead(L);

    d_NODE* cur = L->pHead;

    while (cur->pNext->pNext) {
        if (cur->pNext->pNext->key == val) {
            d_NODE* tmp = cur->pNext;
            cur->pNext = tmp->pNext;
            if (tmp->pNext)
                tmp->pNext->pPrev = cur;
            delete tmp;
            return;
        }
        cur = cur->pNext;
    }
}

void removeAfter(d_List* &L, int val)
{
    d_NODE* cur = L->pHead;
    while (cur->key != val)
        cur = cur->pNext;

    if (cur->pNext) {
        d_NODE* tmp = cur->pNext;
        cur->pNext = tmp->pNext;
        if (tmp->pNext)
            tmp->pNext->pPrev = cur;
        else
            L->pTail = cur;
        delete tmp;
    }
}

bool addPos(d_List* &L, int data, int pos)
{
    if (pos == 0) {
        addHead(L, data);
        return true;
    }

    d_NODE* cur = L->pHead;
    for (int i = 1; i < pos; ++i) {
        cur = cur->pNext;
        if (!cur)
            break;
    }

    if (!cur || cur == L->pTail) {
        addTail(L, data);
        return true;
    }

    d_NODE* tmp = new d_NODE {data, cur->pNext, cur};
    cur->pNext->pPrev = tmp;
    cur->pNext = tmp;

    return true;
}

void removePos(d_List* &L, int pos)
{
    if (pos == 0) {
        removeHead(L);
        return;
    }

    d_NODE* cur = L->pHead;
    for (int i = 1; i < pos; ++i) {
        cur = cur->pNext;
        if (!cur || !cur->pNext)
            return;
    }

    if (!cur->pNext || cur->pNext == L->pTail) {
        delete L->pTail;
        L->pTail = cur;
        cur->pNext = nullptr;
        return;
    }

    d_NODE* tmp = cur->pNext;
    cur->pNext = tmp->pNext;
    tmp->pNext->pPrev = cur;
    delete tmp;
}


bool addBefore(d_List* &L, int data, int val)
{
    if (!L->pHead)
        return false;
    if (L->pHead->key == val) {
        addHead(L, data);
        return true;
    }

    d_NODE* cur = L->pHead;
    while (cur->pNext) {
        if (cur->pNext->key == val) {
            d_NODE* newNode = new d_NODE{ data, cur->pNext, cur };
            cur->pNext->pPrev = newNode;
            cur->pNext = newNode;
            return true;
        }
        cur = cur->pNext;
    }
    return 1;
}


bool addAfter(d_List* &L, int data, int val)
{
    d_NODE* cur = L->pHead;
    while (cur) {
        if (cur->key == val) {
            d_NODE* newNode = new d_NODE{ data, cur->pNext, cur };
            if (cur->pNext)
                cur->pNext->pPrev = newNode;
            cur->pNext = newNode;
            if (cur == L->pTail)
                L->pTail = newNode;
            return 1;
        }
        cur = cur->pNext;
    }
    return 1;
}


int countElements(d_List* L)
{
    if (!L->pHead)
        return 0;

    int cnt = 0;
    d_NODE* cur = L->pHead;
    while (cur) {
        cur = cur->pNext;
        cnt++;
    }
    return cnt;
}


bool removeElement(d_List* &L, int key)
{
    // Remove all occurrences of the key at the head of the list
    while (L->pHead && L->pHead->key == key) {
        removeHead(L);
    }

    d_NODE* cur = L->pHead;
    while (cur && cur->pNext) {
        if (cur->pNext->key == key) {
            d_NODE* tmp = cur->pNext;
            cur->pNext = tmp->pNext;
            if (tmp->pNext)
                tmp->pNext->pPrev = cur;
            else
                L->pTail = cur;
            delete tmp;
        }
        else cur = cur->pNext;
    }
    return true;
}


void removeDuplicate(d_List* &L)
{
    d_NODE* cur = L->pHead;

    while (cur && cur->pNext) {
        d_List* tempList = new d_List {cur->pNext, L->pTail};
        removeElement(tempList, cur->key);
        cur->pNext = tempList->pHead;

        if (!tempList->pHead) {
            L->pTail = cur;
        } else {
            tempList->pHead->pPrev = cur;
            L->pTail = tempList->pTail;
        }

        delete tempList;
        cur = cur->pNext;
    }
}

d_List* reverseList(d_List* L) {
    d_List* rL = new d_List {nullptr, nullptr};  // Create a new list for the reversed nodes

    d_NODE* cur = L->pHead;

    while (cur) {
        // Update the pointers of the reversed list
        if (!rL->pHead) {
            // If the reversed list is empty, set the new node as both head and tail
            rL->pHead = new d_NODE {cur->key, nullptr, nullptr};
            rL->pTail = rL->pHead;
        } else {
            // Add the new node to the front of the reversed list
            addHead(rL, cur->key);
        }

        cur = cur->pNext;  // Move to the next node in the original list
    }

    return rL;
}


int main()
{
    d_NODE* node = createNode(3);
    d_List* lis = createList(node);
    printList(lis);
    addTail(lis, 10);
    addPos(lis, 2, 1);
    printList(lis);
    addPos(lis, 10, 5);
    printList(lis);
    addBefore(lis, 5, 2);
    printList(lis);
    addAfter(lis, 5, 10);
    addTail(lis, 10);
    printList(lis);
    removeDuplicate(lis);
    printList(lis);
    cout << lis->pTail->key;
    cout << "\n";
    d_List* l = new d_List;
    l = reverseList(lis);
    printList(l);


}

