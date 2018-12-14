#include "treap_bst.h"

#include <stack>
#include <stdexcept>
#include <algorithm>

template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST()
    : root(nullptr)
{
    std::random_device rd;
    rndgen.seed(rd());
}

template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::TreapBST(const TreapBST& x)
{
    root = 0;
    Node<KeyType, ValueType>* rhs = x.root;
	
    Node<KeyType, ValueType>** lhs = &root;

    std::stack< stackvar<KeyType, ValueType> > s;

    stackvar<KeyType, ValueType> rootvar;
    rootvar.rhs = rhs;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ValueType> currentvar = s.top();
        s.pop();

        Node<KeyType, ValueType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ValueType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        *curr_lhs = new Node<KeyType, ValueType>(curr_rhs->key,
						 curr_rhs->data);

        // push left subtree
        currentvar.rhs = curr_rhs->childl;
        currentvar.lhs = &((*curr_lhs)->childl);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->childr;
        currentvar.lhs = &((*curr_lhs)->childr);
        s.push(currentvar);
    }
}

template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>& TreapBST<KeyType, ValueType>::operator=(
    TreapBST x)
{
    swap(*this, x);
    return *this;
}

template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::swap(TreapBST& x, TreapBST& y)
{
    std::swap(x.root, y.root);
}

template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::deleteNode(
    typename TreapBST<KeyType, ValueType>::NodePtr node)
{
    if (node->childl != nullptr)
        deleteNode(node->childl);
    if (node->childr != nullptr)
        deleteNode(node->childr);
    delete node;
}

template <typename KeyType, typename ValueType>
TreapBST<KeyType, ValueType>::~TreapBST()
{
    if (root != nullptr) {
        deleteNode(root);
    }
}

template <typename KeyType, typename ValueType>
bool TreapBST<KeyType, ValueType>::empty()
{
    return (root == nullptr);
}

template <typename KeyType, typename ValueType>
typename TreapBST<KeyType, ValueType>::NodePtr
TreapBST<KeyType, ValueType>::binTreeSearch(KeyType theKey, bool& found)
{

    NodePtr location;
    NodePtr current;

    found = false;
    location = nullptr;
    current = root;
    while ((current != nullptr) && (!found)) {
        location = current;
        if (theKey == current->key)
            found = true;
        else {
            if (theKey < current->key)
                current = current->childl;
            else
                current = current->childr;
        }
    }

    return location;
}

template <typename KeyType, typename ValueType>
typename TreapBST<KeyType, ValueType>::NodePtr
TreapBST<KeyType, ValueType>::binTreeInsert(KeyType theKey, ValueType theData)
{
    NodePtr nodepnt;
    NodePtr location;
    NodePtr node;
    bool found;

    if (root == nullptr) { // if empty make root
        nodepnt = new Node<KeyType, ValueType>(theKey, theData);
        root = nodepnt;
        node = nodepnt;
    } else { // insert
        location = binTreeSearch(theKey, found);

        // duplicate node in TreapBST
        if (found)
            throw std::logic_error("duplicate node in TreapBST");

        nodepnt = new Node<KeyType, ValueType>(theKey, theData, location);
        if (theKey < location->key)
            location->childl = nodepnt;
        else
            location->childr = nodepnt;
        node = nodepnt;
    }

    return node;
}

template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::rotateLeft(
    typename TreapBST<KeyType, ValueType>::NodePtr& node)
{
    // std::cout << "Rotate left about node " << node->key << ", " <<
    // node->priority << std::endl;

    NodePtr a;
    NodePtr b;

    a = node->childr;
    b = node;

    if (root == b){
        root = a;
	root->parent = NULL;
    } else {
        if (b == ((b->parent)->childr)) // node is right child
            (b->parent)->childr = a;
        else // node is left child
            (b->parent)->childl = a;
        a->parent = b->parent;
    }

    // move right child's left subtree to node's right subtree
    b->childr = a->childl;
    if (a->childl != nullptr)
        (a->childl)->parent = b;

    // make node the left child of the former right child
    a->childl = b;
    a->parent = b->parent;
    b->parent = a;
    node = a;
}

template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::rotateRight(
    typename TreapBST<KeyType, ValueType>::NodePtr& node)
{
    // std::cout << "Rotate right about node " << node->key << ", " <<
    // node->priority << std::endl;

    NodePtr a;
    NodePtr b;

    a = node->childl;
    b = node;

    if (root == b) {
        root = a;
        root->parent = NULL;
    } else {
        if (b == ((b->parent)->childl)) // node is left child
            (b->parent)->childl = a;
        else // node is right child
            (b->parent)->childr = a;
        a->parent = b->parent;
    }

    // move left child's right subtree to node's left subtree
    b->childl = a->childr;
    if (a->childr != nullptr)
        (a->childr)->parent = b;

    // make node the right child of the former left child
    a->childr = b;
    a->parent = b->parent;
    b->parent = a;
    node = a;
}

template <typename KeyType, typename ValueType>
ValueType TreapBST<KeyType, ValueType>::search(const KeyType& key, bool& found)
{
    NodePtr location = binTreeSearch(key, found);

    if (found)
        return location->data;

    return ValueType();
}

template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::insert(
    const KeyType& key, const ValueType& value)
{
    NodePtr node = binTreeInsert(key, value);

    // generate a random priority for the node
    node->priority = rndgen();

    // perform rotations to bubble up the node based on priority
    while (true) {
        if (node->parent == nullptr)
            break;
        if (node->priority < node->parent->priority)
            break;

        NodePtr p = node->parent;
        if (p->childl == node) { // node is left child
            rotateRight(p);
        }
        if (p->childr == node) { // node is right child
            rotateLeft(p);
        }
        //node = p;
    }
}

template <typename KeyType, typename ValueType>
void TreapBST<KeyType, ValueType>::remove(const KeyType& key)
{
    if (empty())
        throw std::logic_error("Removal from empty TreapBST");

    bool found;
    NodePtr node = binTreeSearch(key, found);

    if (!found)
        return; // no such key, just return

    // case #3: node has two children
    while ((node->childl != nullptr) && (node->childr != nullptr)) {
        if (node->childl->priority < node->childr->priority) {
            rotateLeft(node);
            node = node->childl;
        } else {
            rotateRight(node);
            node = node->childr;
        }
    }

    // case #1: node is a leaf, just remove it
    if ((node->childl == nullptr) && (node->childr == nullptr)) {
        NodePtr p = node->parent;

        if (p == nullptr) { // one item in tree
            delete node;
            root = nullptr;
        } else {
            if (p->childl == node) { // node is a left child
                p->childl = nullptr;
            }
            if (p->childr == node) { // node is a right child
                p->childr = nullptr;
            }
            delete node;
        }
        return;
    }

    // case #2: node has a single child
    if ((node->childl != nullptr) != (node->childr != nullptr)) {
        NodePtr parent = node->parent;
        NodePtr child;
        if (node->childl != nullptr) { // the single child is left
            child = node->childl;
        } else { // the single child is right
            child = node->childr;
        }

        if (parent == nullptr) { // node is root
            delete node;
            root = child;
            child->parent = nullptr;
        } else {
            if (parent->childl == node) { // node is a left child
                parent->childl = child;
            }
            if (parent->childr == node) { // node is a right child
                parent->childr = child;
            }
            child->parent = parent;
            delete node;
        }
        return;
    }
}

template <typename KeyType, typename ValueType>
std::size_t TreapBST<KeyType, ValueType>::heightNode(
    typename TreapBST<KeyType, ValueType>::NodePtr node)
{
    std::size_t h = 0;
    if (node != nullptr) {
        std::size_t hl = heightNode(node->childl);
        std::size_t hr = heightNode(node->childr);
        h = std::max(hl, hr) + 1;
    }

    return h;
}

template <typename KeyType, typename ValueType>
std::size_t TreapBST<KeyType, ValueType>::height()
{
    return heightNode(root);
}
