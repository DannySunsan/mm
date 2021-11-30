#pragma once

class MyHashMap {
    struct Node
    {
        int m_nNum;
        Node* pre;
        Node* next;
        int value;
        Node(int nNum,int nValue)
        {
            pre = nullptr;
            next = nullptr;
            m_nNum = nNum;
            value = nValue;
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
    MyHashMap() {
    }

    ~MyHashMap() {
        for (int i = 0; i < 100; i++)
        {
            if (data[i] != nullptr)
            {
                delete data[i];
                data[i] = nullptr;
            }
        }
    }

    void put(int key,int value) {
        Node* node = data[hashFunc(key)];
        if (node == nullptr)
            data[hashFunc(key)] = node = new Node(hashFunc(key),0);

        
        while (node->next != nullptr)
        {
            node = node->next;
            if (node != nullptr && node->m_nNum == key)
            {
                node->value = value;
                return;
            }                
        }  
        Node* nodeChild = new Node(key, value);
        node->next = nodeChild;
        nodeChild->pre = node;
    }

    void remove(int key) {
        if (get(key)==-1)
            return;
        Node* node = data[hashFunc(key)];
        if (node == nullptr)
            return;
        Node* nodeNext = node->next;
        if (nodeNext == nullptr)
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
    int get(int key) {
        Node* node = data[hashFunc(key)];
        if (node == nullptr)return -1;
        node = node->next;
        while (node != nullptr)
        {
            if (node->m_nNum == key)
                return node->value;
            node = node->next;
        }
        return -1;
    }
    int hashFunc(int Key)
    {
        return Key % 100;
    }
private:
    Node* data[100] = { nullptr };
};