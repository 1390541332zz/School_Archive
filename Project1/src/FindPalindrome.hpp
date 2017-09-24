#ifndef FINDPALINDROME_HPP
#define FINDPALINDROME_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iterator>

#define ALPHA_LENGTH 26

class FindPalindrome {

private:
    std::vector<std::string> v = {};
    std::vector<std::vector<std::string>> vpal = {};
    bool is_updated = true;

    /**
        Determines whether the string is a valid string and is not already
        contained in the object.
        @param str  The string being checked.
        @return   Whether the string is safe to use.
     */
    bool isValid(const std::string & str) const;

	/**
        recursive findPalindrome internal method.
     */
	void recursiveFindPalindromes(
            std::vector<std::string> currentCandidateVector,
			std::vector<std::string> currentStringVector);

	/**
        Determines whether the string is a palindrome.
        @param str  The string being checked.
        @return   Whether the string is a palindrome.
     */
	bool isPalindrome(const std::string & str) const;

    /**
        Updates the palindrome object and computes all possible palindromes.
     */
    void update();

public:
	/**
        Constructor for the FindPalindrome object.
     */
	FindPalindrome();

	/**
        Destroys object and frees any memory allocated by object.
     */
	~FindPalindrome();

	/**
        Returns the current number of sentence palindromes in the
	    FindPalindrome instance.
	    @return  The integer number of palindromes in the instance.
     */
	int number();

	/**
        Removes all words from this instance. The internal list
	    of sentence palindromes is cleared and any internal data
	    structures are reset.
	    @post  The instance contains no words, and the number of
	    sentence palindromes is 0.
     */
	 void clear();

	/**
        Adds a new string to this FindPalindrome instance and computes the
	    number of palindrome sentences possible. Note that the new string must
	    be unique per the definition in the project description.
	    @post  If successful, the string has been added to the FindPalindrome
	    and instance, and the sentence palindromes in the instance
	    have been recomputed.
	    @param value  The string to add to the instance of FindPalindrome.
	    @return  True if addition was successful, or false if not.
     */
	bool add(const std::string & value);

	/**
        Adds a new vector of strings to this FindPalindrome instance and
	    computes the number of palindrome sentences possible. Note: You may
	    not implement this method by repeatedly calling the add(string) method
	    as this would be very inefficient. Implementing this method by repeatedly
	    calling add(string) will result in a grade of zero for the project. Again,
	    note that the strings added must be unique per the project description.
	    @post  If successful, the vector of strings has been added to the
	    FindPalindrome instance, and the sentence palindromes for the instance
	    have been recomputed.
	    @param stringVector  The vector of strings to add to the instance of
	    FindPalindrome.
	    @return  True if addition was successful, or false if not.
     */
	bool add(const std::vector<std::string> & stringVector);

	/**
        Cut test #1 to see if a palindrome is possible, if not, no need to go any
        further. See the project description for how this method is to be used.
	    @param stringVector  A vector of strings for which we want to
	    test to see if they could be reordered to form a sentence palindrome.
	    @return  True if the vector passes the test, false otherwise.
     */
	bool cutTest1(const std::vector<std::string> & stringVector);

	/**
        Cut test #2 to see if a palindrome is possible, if not, no need to go
        any further. We don't know which vector of strings has the fewer number
        characters. However, for whichever vector of strings has the fewest
        number of characters, all of those characters must appear in the
        other string vector with more (or an equal) number of each character.
        For example, if the string with the fewer number of characters has
        two 'a's and three 'b's, the other string must have at least this
        number of the characters 'a' and 'b'. The count of characters
        should be case insensitive.
        See the project description for how this method is to be used.
	    @param stringVector1  A vector of strings.
	    @param stringVector2  A vector of strings.
	    @return  True if the vector passes the test, false otherwise.
     */
	bool cutTest2(const std::vector<std::string> & stringVector1,
			      const std::vector<std::string> & stringVector2);

	/**
        Returns a vector of vectors containing all palindromes. Each
	    palindrome is returned as a vector of strings, where the strings include
	    all current strings added to the FindPalindrome instance.
	    @return  A vector containing all the items in the linked list in order.
     */
	std::vector<std::vector<std::string>> toVector();

};

#endif
