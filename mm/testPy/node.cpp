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
            Node* last = next;
            while(last->next!=nullptr)
            {
                last = last->next;
            }
            Node* preLast = last->pre;
            while(last != nullptr)
            {
                delete last;
                last = preLast;
                preLast = last->pre;
            }
            last = nullptr;
            preLast = nullptr;
        }
    };

public:
    MyHashSet() {      
    }

     ~MyHashSet() {      
         for(int i = 0;i < 100;i++)
         {
             if(data[i]!=nullptr)
             {
                 delete data[i];
                 data[i] =  nullptr;
             }
         }
    }

    void add(int key) {
        if(contains(key))
            return;
        Node* node = data[hashFunc(key)];
        if(node==nullptr)
            node = new Node(hashFunc(key));
        Node* nodeChild = new Node(key);
        while(node->next!=nullptr)
            node = node->next;
        node->next = nodeChild;
        nodeChild->pre = node;
    }
    
    void remove(int key) {
        if(!contains(key))
            return;
        Node* node = data[hashFunc(key)];
        if(node==nullptr)
            return;
        Node* nodeNext = node->next;    
        while(nodeNext->m_nNum!=key)
        {
            nodeNext = nodeNext->next;
        }
        if(nodeNext == nullptr)
            return;
        if(nodeNext->next == nullptr)
        {            
            nodeNext->pre->next = nullptr;        
        }
        else
        {
            nodeNext->pre->next = nodeNext->next;
            nodeNext->next->pre = nodeNext->pre;           
        }
         delete nodeNext;
         nodeNext = nullptr;  
    }
    
    bool contains(int key) {
        Node* node = data[hashFunc(key)];
        if(node==nullptr)return false;
        node = node->next;
        while(node!=nullptr)
        {
            if(node->m_nNum==key)
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
    Node* data[100] = {nullptr};
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */