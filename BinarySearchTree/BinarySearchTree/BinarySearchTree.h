/********************************************************************
 *
 * This file is part of the Data structures and algorithms in C++ package
 *
 * Author: Atanas Semerdzhiev
 * URL: https://github.com/semerdzhiev/sdp-samples
 *
 */

#pragma once

#include <functional>
#include <stack>

template <typename ElementType, typename Compare = std::less<ElementType>>
class BinarySearchTree
{
private:
    struct Node
    {
        ElementType data;
        Node* left;
        Node* right;     

        Node(const ElementType& value)
            : data(value), left(nullptr), right(nullptr)
        {
            // Nothing to do here
        }
    };


public:
    class Iterator
    {
        std::stack<Node*> walk;
        Node* root;

    public:
        Iterator(Node* root)
            : root(root)
        {
            if(root)
                pushAndExpand(root);
        }

        ElementType& Current()
        {
            if (EndReached())
                throw std::exception();

            return walk.top()->data;
        }

        void Rewind()
        {
            walk = std::stack<Node*>();
            
            if (root)
               pushAndExpand(root);
        }

        void MoveNext()
        {
            if (walk.empty())
                return;

            Node* p = walk.top();
            walk.pop();
            
            if (p->right)
                pushAndExpand(p->right);
        }

        bool EndReached() const
        {
            return walk.empty();
        }

    private:
        
        void pushAndExpand(Node* p)
        {
            walk.push(p);
            
            while (p->left)
            {
                walk.push(p->left);
                p = p->left;
            }
        }

    };


private:
    Node* rootNode;
    size_t size;
    Compare comesBefore;

public:
    BinarySearchTree()
        : rootNode(nullptr), size(0)
    {
        // Nothing to do here
    }

    ~BinarySearchTree()
    {
        Clear();
    }

    BinarySearchTree(const BinarySearchTree & other)
        : rootNode(nullptr), size(0)
    {
        CopyFrom(other);
    }

    BinarySearchTree& operator=(const BinarySearchTree & other)
    {
        if (this != &other)
        {
            Clear();
            CopyFrom(other);
        }

        return *this;
    }

    void Insert(const ElementType& item)
    {
        Node** current = &rootNode;

        while(*current)
        {
            if ((*current)->data > item)
                current = &(*current)->left;
            else
                current = &(*current)->right;
        }

        // Here current should point to a pointer, whose value is nullptr
        *current = new Node(item);
        ++size;
    }

    void Remove(const ElementType& item)
    {
        Node **pp = findPointerToNode(item);

        if (!pp)
            return; // The tree does not contain the item

        Node *temp = *pp; // remember where the box is

        if ((*pp)->left && (*pp)->right)
        { // two successors
            Node** pmin = findPointerToMinNode(&(*pp)->right);
            *pp = *pmin;
            *pmin = (*pmin)->right;
            (*pp)->left = temp->left;
            (*pp)->right = temp->right;
        }
        else
        { // 1 or zero successors
            *pp = (*pp)->left ? (*pp)->left : (*pp)->right;
        }

        delete temp; // free the box
        --size;
    }

    bool Contains(const ElementType& item) const
    {
        const Node* p = rootNode;

        while (p)
        {
            if (p->data == item)
                return true;

            p = (item < p->data) ? p->left : p->right;
        }

        return false;
    }

    void Clear()
    {
        if (Empty())
            return;

        /*
        NodeIterator ni = getNodeIterator();

        do
        {
            Node* p = ni.Current();
            ni.MoveNext();
            delete p;
        
        } while (!ni.EndReached());
        */

        std::stack<Node*> walk;
        walk.push(rootNode);

        Node* p = nullptr;

        while (!walk.empty())
        {
            p = walk.top();
            walk.pop();

            if (p->left)
                walk.push(p->left);
            if (p->right)
                walk.push(p->right);

            delete p;
        }

        size = 0;
        rootNode = nullptr;
    }

    size_t Size() const
    {
        return size;
    }

    bool Empty() const
    {
        return size == 0;
    }

    Iterator GetIterator()
    {
        return Iterator(rootNode);
    }


private:
    void CopyFrom(const BinarySearchTree & other)
    {

    }

    Node** findPointerToNode(const ElementType& item)
    {
        Node** pp = &rootNode;

        while (*pp)
        {
            if ((*pp)->data == item)
                return pp;

            pp = (item < (*pp)->data) ? &(*pp)->left : &(*pp)->right;
        }

        return nullptr;
    }

    Node** findPointerToMinNode(Node** root)
    {
        if (!root)
            throw std::exception();

        Node** pp = root;

        while ((*pp)->left)
            pp = &(*pp)->left;

        return pp;
    }
};
