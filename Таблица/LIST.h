#include <iostream>

template<class T>
struct NODE
{
    T val;
    NODE* next;
    NODE(T _val, NODE* _next)
    {
        val = _val;
        next = _next;
    }
};

template<class T>
class LIST
{
    NODE<T>* first; NODE<T>* last;
    public:
    LIST()
    {
        first = nullptr;
        last = nullptr;
    }
    LIST(const LIST& b)
    {
        if (b.first == nullptr)
        {
            first = nullptr;
            last = first;
        }
        else
        {
            if (b.first->next != nullptr)
            {
                first = new NODE<T>(b.first->val, b.first);
                first->next = new NODE<T>(b.first->next->val, b.first->next);
                NODE<T>* tmp = b.first->next;
                NODE<T>* tmp1 = first->next;
                while (tmp->next != nullptr)
                {
                    tmp1->next = new NODE<T>(tmp->next->val, tmp->next);
                    tmp = tmp->next;
                    tmp1 = tmp1->next;
                }
                last = new NODE<T>(b.last->val, b.last);
            }
            else
            {
                first = new NODE<T>(b.first->val, b.first);
                last = first;
            }
        }

    }
    ~LIST()
    {
        DeleteAll();
    }

    //методы
    NODE<T>* GetFirst()
    {
        return first;
    }

    void Insert(NODE<T>* now, NODE<T>* insertion)
    {
        if (insertion == nullptr)
        {
            throw "Node you're tryinng to insert does not exist";
        }
        //finding previous element
        NODE<T>* Runner = first;
        bool sflag = false;
        NODE<T>* previous;
        while ((Runner != nullptr) && (Runner -> next != now))
        {
            Runner = Runner -> next;
        }
        if (Runner)
        {
            previous = Runner;
            sflag = true;
        }
        
        if (not(sflag))
        {
            throw "your node-destination not exist in this universe";
        }
        NODE<T>* innit = now;
        previous->next = insertion;
        insertion->next = innit;
    }
       
    void InsertFirst(T Val)
    {
        NODE<T>* p = new NODE<T>(Val,first);
        if (first == nullptr)
        {
            first = p;
            last = p;
        }
        else 
        {
            if (first -> next == nullptr)
            {
                first -> next = first;
                last = first->next;
                first = p;
            }
            else
            {
                NODE<T>* tmp = new NODE<T>(first->val,first);
                //tmp->next = first -> next;
                p->next = tmp;
                //first = nullptr;
                first = p;
            }
        }
    }

    void InsertLast(T Val)
    {
        NODE<T>* p = new NODE<T>(Val,nullptr);
        if (last == nullptr)
        {
            first = p;
            last = p;
        }
        else
        {
            last -> next = p;
            last = p;
        }
    }

    void DeleteAll()
    {
        if (first)
        {
            if (first -> next != nullptr)
            {
                NODE<T>* tmp = first;
                while (tmp->next!= nullptr)
                {
                    NODE<T>* tmp1 = tmp->next;
                    delete tmp;
                    tmp = tmp1;
                }
                first = nullptr;
            }
            else 
            {
                delete first; 
                first = nullptr;
            }
        }
    }   

    void Print()
    {
        NODE<T>* p = first;
        while (p -> next != nullptr)
        {
            std::cout << p -> val << " ";
            p = p -> next;
        }
        std::cout << p -> val;
    }
    // returns first node with that value
    NODE<T>* GeNode(T vali)
    {
        NODE<T>* p = first;
        while (p -> next != nullptr)
        {
            if (p->val == vali)
            {
                return p;
            }
            p = p->next;
        }
        if (last -> val == vali)
        {
            return last;
        }
        return nullptr;
    }
    void DeleteTheNext(NODE<T>* that)
    {
        if (that == nullptr || that -> next == nullptr)
        {
            throw "you're givin' wrong NODE or no next element is presented near there";
        }
        else //(that -> next != nullptr)
        {
            NODE<T>* tmp = that->next;
            that -> next = that -> next -> next;
            delete tmp;
        }
    }
    LIST<T> operator=(const LIST<T>& l)
    {
        if (l == *this)
        {
            return *this;
        }
        this->DeleteAll();
        if (l.first == nullptr)
        {
            first = nullptr;
            last = first;
        }
        else
        {
            if (l.first-> next != nullptr)
            {
                first = new NODE<T>(l.first->val,l.first);
                first->next = new NODE<T>(l.first->next->val,l.first->next);
                NODE<T>* tmp = l.first->next;
                NODE<T>* tmp1 = first->next;
                while (tmp -> next != nullptr)
                {
                    tmp1 -> next = new NODE<T>(tmp->next->val,tmp->next);
                    tmp = tmp -> next;
                    tmp1 = tmp1 -> next;
                }
                last = new NODE<T>(l.last->val,l.last);
            }
            else
            {
                first = new NODE<T>(l.first->val,l.first);
                last = first;
            }
        }
        return *this;
    }
    bool operator==(const LIST<T>& l) const
    {
        NODE<T>* runner = first;
        NODE<T>* runner1 = l.first;
        while (runner -> next != nullptr && runner1 -> next != nullptr)
        {
            if ((runner->next->val != runner1->next->val) || (runner == nullptr || runner1 == nullptr))
            {
                return false;
            }
            runner = runner->next;
            runner1 = runner1->next;
        }
        if (last->val == l.last->val)
        {
            return true;
        }
        return false;
    }
    bool operator!=(const LIST<T>& l) const
    {
        return !this->operator==(l);
    }
};