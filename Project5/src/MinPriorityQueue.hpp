#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

#include <stdexcept>
#include <algorithm>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

template<typename KeyT, typename T>
class MinPriorityQueue {
private:
    struct node {
        std::unique_ptr<node> lhs = nullptr;
        std::unique_ptr<node> rhs = nullptr;
        node* parent = nullptr;
        KeyT key = KeyT();
        T item = T();
        std::size_t ht = 1;
        node* sibling() const;
        void swap(node&);
        bool operator<(const node& rhs) const noexcept;
    };

    std::size_t sz = 0;
    std::unique_ptr<node> head = nullptr;
    bool auto_rebalance = false;

    void update_heights(node* cur) noexcept;
    std::size_t optimal_height(std::size_t sz) const noexcept;
    bool balance(node* cur, std::size_t ht);
public:
	/**
     * MinPriorityQueue constructor
     */
	MinPriorityQueue();

    /**
     * MinPriorityQueue destructor. Must delete any allocated memory.
     */
    ~MinPriorityQueue();

	/**
     * Returns the number of items in the minPQ.
	 * @return  The integer number of items on the MinPriorityQueue ADT.
     */
	int size() const;

	/**
     *  Returns the height of the minPQ.
	 *  @return  The integer height of the MinPriorityQueue internal
     *           binary tree ADT.
     */
	int height() const;

	/**
     * Determines whether this MinPriorityQueue is empty.
	 * @return True if the MinPriorityQueue has no items, or false if not.
     */
	bool isEmpty() const;

	/**
     * Pushes a new entry onto the top of the MinPriorityQueue.
	 * @post        If successful, item is inserted into the
     *              MinPriorityQueue based on the Value.
	 * @param key   The key (of datatype KeyT) to be inserted
     *              into the MinPriorityQueue.
	 * @param item   The item (of datatype T) to be inserted
     *              into the MinPriorityQueue.
	 * @return      True if insert was successful, or false if not.
     */
	bool insert(const KeyT& key, const T& item);

	/**
     * Returns the min value from the MinPriorityQueue. Doesn't delete the node.
     * Throws an exception of type logic_error if the MinPriorityQueue is empty.
	 * @return  Value of KeyT that was on the root of the MinPriorityQueue.
     */
	KeyT getMinValue() const throw(std::logic_error);

	/**
     * Returns the item associated with min value from the MinPriorityQueue.
     * Doesn't delete the node.
     * Throws an exception of type logic_error if the MinPriorityQueue is empty.
	 * @return  Item of T that was on the root of the MinPriorityQueue.
     */
	T getMinItem() const throw(std::logic_error);

	/**
     * Deletes the min item off of from the MinPriorityQueue.
	 * The MinPriorityQueue size is decreased by 1.
     * Throws an exception of type logic_error if the queue is empty.
	 * @return  True of min node is deleted successfully, false otherwise.
     */
	bool deleteMin() throw(std::logic_error);

	/**
     * Deletes all entries on the MinPriorityQueue.
	 * @post  MinPriorityQueue contains no items, and the size of the
     *        queue is 0.
     */
	void clear();

	/**
     * Turns on/off automatic rebalancing of the heap. If on, the height of
	 * the heap should always be no more than twice the optimal heap height.
	 * The optimal heap size function can be used to compute the optimal
     * heap size.
	 * @param val  A boolean val, true turns on automatic rebalancing,
     *             false otherwise.
     */
	void setAutoRebalance(bool val);

	/**
     * Attempts to rebalance the MinPriorityQueue so that its height is less
     * than or equal to the integer maxHeight. The items and values in the
     * MinPriorityQueue remain unchanged.
	 * @return  True if the MinPriorityQueue was successfully rebalanced,
     *          false otherwise.
     */
	bool rebalance(int maxHeight);

	/**
     * Your function to print out the MinPriorityQueue in some sort of
     * meaningful manner for debugging.
     */
	void printTree();
};

#include "MinPriorityQueue.tpp"
#endif
