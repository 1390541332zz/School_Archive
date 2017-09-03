#include <cstdint>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <sstream>

class Bitset{
public:
  /*
   * Bitset() - Default Constructor.
   *
   * Initialises the bitset with an initial width of 8 bits and all bits
   * set to 0.
   */
  Bitset();

  /*
   * Bitset() - Constructor with size.
   * @size: Size of the bitset to initialise.
   *
   * Initialises the bitset with an initial width of @size times 8 bits. All
   * bits are set to 0.
   *
   * Error Handling: If @size is negative, the bitset is rendered invalid.
   */
  Bitset(intmax_t size);

  /*
   * Bitset() - Constructor with value assignment.
   * @value: A string containing plain text MSB-first binary to be copied.
   *
   * Initialises the bitset with sufficient space to hold the binary in @value.
   * Assigns the contents of the bitset to be equivalent to the contents of
   * @value.
   *
   * Error Handling: If @value contains any character other than 0 or 1, the
   * bitset is rendered invalid.
   */
  Bitset(const std::string & value);

  /*
   * ~Bitset() - Deconstructor.
   *
   * Deallocates any dynamically allocated memory and renders the object
   * ready for deletion.
   */
  ~Bitset();

  /*
   * size() - Returns the size of the bitset.
   *
   * Return: The size of the bitset in number of bits.
   */
  intmax_t size() const;

  /*
   * good() - Validates Bitset.
   *
   * Return: Whether the bitset is valid and/or safe to use.
   */
  bool good() const;

  /*
   * set() - Sets the bit at @index to 1.
   * @index: The index of the bit to access.
   *
   * Error Handling: If @index is out of the bounds of the bitset, the bitset
   * is rendered invalid.
   *
   * Return: The return type is void.
   */
  void set(intmax_t index);

  /*
   * reset() - Sets the bit at @index to 0.
   * @index: The index of the bit to access.
   *
   * Error Handling: If @index is out of the bounds of the bitset, the bitset
   * is rendered invalid.
   *
   * Return: The return type is void.
   */
  void reset(intmax_t index);

  /*
   * toggle() - Inverts the bit at @index.
   * @index: The index of the bit to access.
   *
   * Error Handling: If @index is out of the bounds of the bitset, the bitset
   * is rendered invalid.
   *
   * Return: The return type is void.
   */
  void toggle(intmax_t index);

  /*
   * test() - Determines the state of the bit at @index.
   * @index: The index of the bit to access.
   *
   * Error Handling: If @index is out of the bounds of the bitset, the bitset
   * is rendered invalid and false is returned.
   *
   * Return: Whether the bit at @index is set.
   */
  bool test(intmax_t index);

  /*
   * asString() - Provides a plain text binary representation of the bitset.
   *
   * Return: A plain text MSB-first binary representation of the bitset.
   */
  std::string asString() const;

  //Disabled Methods.
  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;
private:
  uint8_t* arr = nullptr;
  size_t sz = 0;

  /*
   * invalidate() - Renders the bitset invalid and unusable.
   */
  void invalidate();
};
