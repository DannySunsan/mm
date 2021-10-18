#pragma once
class MyHashSet {
    struct Node
    {
        int m_nNum;
        Node* pre;
        Node* next;
        Node(int nNum)
        {
            pre = nullptr;
            next = nullptr;
            m_nNum = nNum;
        }
        ~Node()
        {
            if (next == nullptr)
                return;
            Node* last = next;
            while (last->next != nullptr)
            {
                last = last->next;
            }
            Node* preLast = last->pre;
            while (last != nullptr)
            {              
                preLast = last->pre;
                //do not delete head
                if (preLast == nullptr)
                    break;
                delete last;
                last = preLast;
                if (preLast != nullptr)
                {
                    preLast->next = nullptr;
                }                 
            }
            last = nullptr;
            preLast = nullptr;
        }
    };

public:
    MyHashSet() {
    }

    ~MyHashSet() {
        for (int i = 0; i < 100; i++)
        {
            if (data[i] != nullptr)
            {
                delete data[i];
                data[i] = nullptr;
            }
        }
    }

    void add(int key) {
        if (contains(key))
            return;
        Node* node = data[hashFunc(key)];
        if (node == nullptr)
            data[hashFunc(key)] = node = new Node(hashFunc(key));
        Node* nodeChild = new Node(key);
        while (node->next != nullptr)
            node = node->next;
        node->next = nodeChild;
        nodeChild->pre = node;
    }

    void remove(int key) {
        if (!contains(key))
            return;
        Node* node = data[hashFunc(key)];
        Node* nodeNext = node->next;
        if (node == nullptr|| nodeNext == nullptr)
            return;
        
        while (nodeNext->m_nNum != key)
        {
            //找尾巴
            if (nodeNext->next == nullptr)
                return;
            nodeNext = nodeNext->next;           
        }
        
        if (nodeNext->next == nullptr)
        {
            nodeNext->pre->next = nullptr;
        }
        else
        {
            nodeNext->pre->next = nodeNext->next;
            nodeNext->next->pre = nodeNext->pre;
        }
        //删除节点时会默认析构掉关联的节点
        nodeNext->pre = nullptr;
        nodeNext->next = nullptr;

        delete nodeNext;
        nodeNext = nullptr;
    }

    bool contains(int key) {
        Node* node = data[hashFunc(key)];
        if (node == nullptr)return false;
        node = node->next;
        while (node != nullptr)
        {
            if (node->m_nNum == key)
                return true;
            node = node->next;
        }
        return false;
    }
    int hashFunc(int Key)
    {
        return Key % 100;
    }
private:
    Node* data[100] = { nullptr };
};