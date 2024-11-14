#include <iostream>

using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct List {
    NODE* p_head;
    NODE* p_tail;
};

void printList (List* &L) {
    NODE* cur = L->p_head;
    if (!cur) {
        cout << "empty\n";
        return;
    }
    while (cur){
        cout << cur->key << " ";
        cur = cur->p_next;
    }
    cout << "\n";
}

NODE* createNode(int data)
{
    NODE* tmp = new NODE {data, nullptr};
    return tmp;
}

List* createList(NODE* p_node)
{
    List* tmp = new List {p_node, p_node};
    return tmp;
}

bool addHead(List* &L, int data)
{
    //Add new Node before Head
    NODE*tmp = new NODE {data, L->p_head};
    L->p_head = tmp;

    //Check if the head is the tail too
    if (L->p_head->p_next == nullptr) {
        L->p_tail = L->p_head;
    }
    return 1;
}

bool addTail(d_List* &L, int data)
{
    d_NODE* tmp = new d_NODE {data, nullptr, L->pTail};
    if (L->pTail == nullptr) { // If the list is empty, set the new node as both head and tail
        L->pHead = tmp = L->pTail;
    } else {
        L->pTail->pNext = tmp;
        L->pTail = tmp;
    }
    return true;
}

void removeHead(List* &L)
{
    NODE* tmp = L->p_head;
    L->p_head = L->p_head->p_next;
    delete tmp;

    if (!L->p_head) L->p_tail = nullptr;
}

void removeTail(List* &L)
{
    //check if there's only 1 node in list
    if (L->p_head == L->p_tail) {
        delete L->p_tail;
        L->p_head = nullptr;
        L->p_tail = nullptr;
        return;
    }

    //move to the node next to tail
    NODE* cur = L->p_head;
    while (cur->p_next != L->p_tail)
        cur = cur->p_next;
    //delete tail
    delete L->p_tail;
    L->p_tail = cur;
}

void removeAll(List* &L) {
    while (L->p_head) {
        NODE* tmp = L->p_head;
        L->p_head = L->p_head->p_next;
        delete tmp;
    }
}

void removeBefore(List* &L, int val)
{
    if (!L->p_head || L->p_head->key == val)
        return;

    if (L->p_head->p_next->key == val)
        return removeHead(L);

    NODE* cur = L->p_head;

    while (cur->p_next->p_next) {
        if (cur->p_next->p_next->key == val) {
            NODE* tmp = cur->p_next;
            cur->p_next = tmp->p_next;
            delete tmp;
            return;
        }
        cur = cur->p_next;
    }
}

void romveAfter(List* &L, int val)
{
    NODE* cur = L->p_head;
    while (cur->key != val)
        cur = cur->p_next;

    NODE* tmp = cur->p_next;
    cur->p_next = tmp->p_next;
    delete tmp;

    if (cur->p_next == nullptr)
        L->p_tail = cur;
}

bool addPos(List* &L, int data, int pos)
{
    //check if add to head
    if (pos == 0) {
        addHead (L, data);
        return 1;
    }

    NODE* cur = L->p_head;
    for (int i=1; i<pos; ++i) {
        cur = cur->p_next;
        if (cur->p_next == nullptr) break;
    }


    if (cur == L->p_tail) {
        addTail(L, data);
        return 1;
    }

    cur->p_next = new NODE {data, cur->p_next};

    return 1;
}
void removePos(List* &L, int pos)
{
    //check if add to head
    if (pos == 0) {
        removeHead (L);
        return;
    }

    NODE* cur = L->p_head;
    for (int i=1; i<pos; ++i) {
        cur = cur->p_next;
        if (cur->p_next == nullptr) return;
    }

    if (cur->p_next == L->p_tail) {
        delete L->p_tail;
        L->p_tail = cur;
        cur->p_next = nullptr;
        return;
    }

    NODE* tmp = cur->p_next;
    cur->p_next = tmp->p_next;
    delete tmp;
}

bool addBefore(List* &L, int data, int val)
{
    if (L->p_head->key == val) {
        addHead(L, data);
        return 1;
    }
    NODE* cur = L->p_head;
    while (cur->p_next) {
        if (cur->p_next->key == val) {
            cur->p_next = new NODE {data, cur->p_next};
            return 1;
        }
        cur = cur->p_next;
    }
}

bool addAfter(List* &L, int data, int val)
{
    NODE* cur = L->p_head;
    while (cur) {
        if (cur->key == val) {
            cur->p_next = new NODE {data, cur->p_next};
            if (cur == L->p_tail)
                L->p_tail = cur->p_next;
            return 1;
        }
        cur = cur->p_next;
    }
}

int countElements(List* L)
{
    if (!L->p_head) return 0;
    int cnt = 0;
    NODE* cur = L->p_head;
    while (cur) {
        cur = cur->p_next;
        cnt++;
    }
    return cnt;
}

bool removeElement(List* &L, int key)
{
    while (L->p_head && L->p_head->key == key) {
        removeHead(L);
    }

    NODE* cur = L->p_head;
    while (cur && cur->p_next) {
        if (cur->p_next->key == key) {
            NODE* tmp = cur->p_next;
            cur->p_next = tmp->p_next;
            delete tmp;
            if (cur->p_next == nullptr)
                L->p_tail = cur;
        }
        else cur = cur->p_next;
    }
}

void removeDuplicate(List* &L)
{
    NODE* cur = L->p_head;
    while (cur && cur->p_next) {
        List* l = new List {cur->p_next, L->p_tail};
        removeElement(l, cur->key);
        cur->p_next = l->p_head;

        if (!l->p_tail)
            L->p_tail = cur;
        else L->p_tail = l->p_tail;

        cur = cur->p_next;
    }
}

List* reverseList(List* L) {
    List* rL = new List {nullptr, nullptr};  // Create a new list for the reversed nodes

    NODE* cur = L->p_head;

    while (cur) {
        // Update the pointers of the reversed list
        if (!rL->p_head) {
            // If the reversed list is empty, set the new node as both head and tail
            rL->p_head = new NODE {cur->key, nullptr};
            rL->p_tail = new NODE {cur->key, nullptr};
        } else {
            // Add the new node to the front of the reversed list
            addHead(rL, cur->key);
        }
        cur = cur->p_next;  // Move to the next node in the original list
    }

    return rL;
}


int main()
{
    NODE* node = createNode(3);
    List* lis = createList(node);
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

    List* l = new List;
    l = reverseList(lis);
    printList(l);
    cout << lis->p_tail->key;

}
