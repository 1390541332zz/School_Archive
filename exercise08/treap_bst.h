#ifndef _TREAP_BST_H_
#define _TREAP_BST_H_

#include <random>

template <typename KeyType, typename ValueType>
class TreapBST
{
public:
    // constructor
    TreapBST();

    // copy constructor
    TreapBST(const TreapBST& x);

    // copy-assignment
    TreapBST& operator=(TreapBST x);

    // swap
    void swap(TreapBST& x, TreapBST& y);

    // destructor
    ~TreapBST();

    bool empty();

    ValueType search(const KeyType& key, bool& found);

    void insert(const KeyType& key, const ValueType& value);

  void remove(const KeyType& key);
  
    std::size_t height();

private:
    // random number generator
    std::mt19937 rndgen;

    template <typename K, typename V>
    struct Node {
        K key;
        V data;
        std::mt19937::result_type priority;
        Node* parent;
        Node* childl;
        Node* childr;

        Node(const K& k, const V& d, Node* p = nullptr)
            : key(k)
            , data(d)
            , parent(p)
            , childl(nullptr)
            , childr(nullptr)
        {
        }
    };

    template <typename K, typename I>
    struct stackvar {
        Node<K, I>* rhs;
        Node<K, I>** lhs;
    };
    
    typedef Node<KeyType, ValueType>* NodePtr;

    NodePtr root;

    NodePtr binTreeSearch(KeyType theKey, bool& found);
    NodePtr binTreeInsert(KeyType theKey, ValueType theData);
    void rotateLeft(NodePtr& node);
    void rotateRight(NodePtr& node);
    void deleteNode(NodePtr node);
    std::size_t heightNode(NodePtr node);
};

#include "treap_bst.txx"

#endif // _TREAP_BST_H_
