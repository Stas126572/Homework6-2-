#pragma once



template<typename ElementType>
struct Node
{
    Node* next;
    Node* prev;
    ElementType data;
};

template<typename ElementType>
class NodesList;

template<typename ElementType>
class Iterator
{
    Node<ElementType>* I;
    friend NodesList<ElementType>;
private:
    Iterator(Node<ElementType>*I)
    {
        this->I = I;
    }

public:
    ElementType operator*()
    {
        return get();
    } 
    ElementType get()
    {
        return I->data;   
    }
};

template<typename ElementType=int>
class NodesList
{
    Node<ElementType>* last;
    Node<ElementType>* first;
    size_t size;
private:
    void insert_node(Node<ElementType>*index, ElementType element)  
    {
        Node<ElementType>* this_node = new Node<ElementType>{};
        this_node->data = element;
        

        index->next->prev = this_node;
        this_node->next = index->next;
        this_node->prev = index;
        index->next = this_node;

        size++;
    };
    ElementType erase_node(Node<ElementType>*index)  {
        index->prev->next = index->next;
        index->next->prev = index->prev;
        ElementType element = index->data;
        delete index;
        size--;
        return element;
    }
    Node<ElementType>* GetNodeOfIndex(size_t index) 
    {
        Node<ElementType>* return_element;
        size_t sredni_index = size / 2;
        if (index > sredni_index)
        {
            return_element = last;
            for (size_t i = size; i!=index; i--)
            {
                return_element = return_element->prev;
            }
        }
        else
        {
            return_element = first;
            for (int i = 0; i<index; i++)
            {
                return_element = return_element->next;
            }
        }
        return return_element;
    }
public:
    Iterator<ElementType>begin()
    {
        Iterator<ElementType>it{first};
        return it;
    }
    Iterator<ElementType>end()
    {
        Iterator<ElementType>it{last};
        return it;
    }
    void insert(ElementType element, size_t index)
    {
        insert_node(GetNodeOfIndex(index), element);
    }
    ElementType erase(size_t index) 
    {
        return erase_node(GetNodeOfIndex(index));
    };
    ElementType erase(Iterator<ElementType>it)
    {
        return erase_node(it.I);
    }
    void insert(ElementType element, Iterator<ElementType>it)
    {
        insert_node(it.I, element);
    }    
    NodesList(NodesList<ElementType>&& rv)
    {
        this->last = rv->last;
        this->first = rv->first;
        Node<ElementType>* first_rv = rv->first;
        Node<ElementType>* two;
        ElementType el;
        for (size_t i = 0; i < rv->size; i++)
        {
            first_rv->data = el;
            two = first_rv->next;
            first_rv->next = nullptr;
            first_rv = two;
        }
    }
    NodesList(const NodesList<ElementType>& nd)
    {
        Node<ElementType>*el = nd.first;
        first = new Node<ElementType>{};
        last = new Node<ElementType>{};
        first->next = last;
        last->prev = first;
        size = nd.size;
        for (int i = 0; i<nd.size-1; i++)
        {
            el = el->next;
            child_insert(last->prev, el->data);
        }
    }

    ~NodesList()
    {
        Node<ElementType>* element2;
        for (int i = 0; i<size; i++)
        {
            element2 = last->prev;
            delete last;
            last = element2;
        }
        delete element2;
 
    }
    size_t get_size() {
        return size-1;
    }
    NodesList() {
        size = 1;
        first = new Node<ElementType>{};
        last = new Node<ElementType>{};
        first->next = last;
        last->prev = first;
    }
    ElementType GetElementOfIndex(size_t index)
    {
        return GetNodeOfIndex(index+1)->data;
    }
    ElementType operator [] (size_t index) 
    {
        return GetElementOfIndex(index);
    };
    void push_back(ElementType element) {insert_node(last->prev, element);}
    ElementType pop_back() {return erase_node(last->prev);}
    void push_front(ElementType element) {insert_node(first, element);}
    ElementType pop_front() {return erase_node(first->next);}
};