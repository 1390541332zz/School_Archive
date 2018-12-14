// Interface definition for an ordered list using 0-based indexing
#ifndef _ABSTRACT_LIST_HPP_
#define _ABSTRACT_LIST_HPP_

template <typename T>
class AbstractList {
public:

  // determine if a list is empty
  virtual bool isEmpty() const noexcept = 0;

  // return current length of the list
  virtual std::size_t getLength() const noexcept = 0;

  // insert item at position in the list using 0-based indexing
  // throws std::range_error if position is invalid
  virtual void insert(std::size_t position, const T& item) = 0;

  // remove item at position in the list using 0-based indexing
  // throws std::range_error if position is invalid
  virtual void remove(std::size_t position) = 0;

  // remove all items from the list
  virtual void clear() noexcept = 0 ;

  // get a copy of the item at position using 0-based indexing
  // throws std::range_error if position is invalid
  virtual T getEntry(std::size_t position) const = 0;

  // set the value of the item at position using 0-based indexing
  // throws std::range_error if position is invalid
  virtual void setEntry(std::size_t position, const T& newValue) = 0;
};

#endif