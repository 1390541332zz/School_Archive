// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <cassert>
#include <cctype>
#include <string>
#include <algorithm>
#include <iterator>
#include "XMLParser.hpp"

static const std::string illegal_chars = {
    '!', '"', '#', '$', '%', '&', '\'',
    '(', ')', '*', '+', ',', '/', ';',
    '<', '=', '>', '?', '@', '[', '\\',
    ']', '^', '`', '{', '|', '}', '~',
};

static const std::string illegal_first_chars = {
    '0', '1', '2', '3', '4', '5',
    '6', '7', '8', '9', '-', '.'
};

#define MARK_CNT 6

enum syntax_marker {
    OPEN_END    = 0,
    CLOSE_EMPTY = 1,
    OPEN_DECL   = 2,
    CLOSE_DECL  = 3,
    OPEN        = 4,
    CLOSE       = 5,
    NON_MARKER
};

static const std::string syntax_marks[] = {
    "</", "/>", "<?", "?>", "<", ">"
};

//============================================================================//

/** Extracts the token's tag name
    @param token  The tag whose name is being extracted
  */
static std::string token_name(const TokenStruct& token) {
    size_t len = token.tokenString.find_first_of(" ");
    if (len == std::string::npos) return token.tokenString;
    return token.tokenString.substr(0, len);
}

/** Serialises a StringTokenTypeTokenStruct into a string
    @param type  The object to be serialised
  */
static std::string serialise_tokenType(StringTokenType type) {
    switch (type) {
        case START_TAG:     return "START_TAG";
        case END_TAG:       return "END_TAG";
        case EMPTY_TAG:     return "EMPTY_TAG";
        case CONTENT:       return "CONTENT";
        case DECLARATION:   return "DECLARATION";
    }
    return "ERROR";
}

/** Deserialises a token type string into a StringTokenType enumeration
    @param type The string being deserialised
  */
static StringTokenType deserialise_tokenType(std::string type) {
    if (type == "START_TAG")   return START_TAG;
    if (type == "END_TAG")     return END_TAG;
    if (type == "EMPTY_TAG")   return EMPTY_TAG;
    if (type == "CONTENT")     return CONTENT;
    if (type == "DECLARATION") return DECLARATION;
    return CONTENT;
}

/** Serialises a TokenStruct into a string
    @param token  The object to be serialised
  */
static std::string serialise_token(const TokenStruct& token) {
    return '{' + serialise_tokenType(token.tokenType) + '|'
               + token_name(token) + '}';
}

/** Deserialises a token string into a TokenStruct
    @param str  The serialised data
  */
static TokenStruct deserialise_token(const std::string& str) {
    auto type_it = std::next(str.cbegin(), str.find_first_of("{"));
    auto str_it  = std::next(str.cbegin(), str.find_first_of("|"));
    auto end_it  = std::next(str.cbegin(), str.find_first_of("}"));
    std::string type_str(std::next(type_it, 1), str_it);
    std::string str_str(std::next(str_it, 1), end_it);
    TokenStruct token = {deserialise_tokenType(type_str), str_str};
    return token;
}

/** Determines if the token is valid
    @param token The token being checked
  */
static bool valid_token(const TokenStruct& token) {
    std::string name = token_name(token);
    auto illegal_it = std::find(illegal_first_chars.cbegin(),
                                illegal_first_chars.cend(), name.front());
    if (illegal_it != illegal_first_chars.cend()) return false;
    for (const auto& c : illegal_chars) {
        auto find_it = std::find(name.cbegin(), name.cend(), c);
        if (find_it != name.cend()) return false;
    }
    return true;
}

/** Locates the next syntax marker
    @param str  The string being checked
    @param it  The start iterator for the range being checked
  */
static std::string::const_iterator next_marker(const std::string& str,
                                               std::string::const_iterator it) {
    for (; it != str.cend(); it++) {
        for (const std::string& mark : syntax_marks) {
            if (mark.length() > std::distance(it, str.cend())) continue;
            if (std::equal(mark.cbegin(), mark.cend(), it)) return it;
        }
    }
    return str.cend();
}

/** Returns the type of tag made from combining the two markers
    @param lhs The first syntax marker
    @param rhs The second syntax marker
    @return a valid tag enum or CONTENT if no tag could be created.
  */
static StringTokenType marker_tag(enum syntax_marker lhs,
                                  enum syntax_marker rhs) {
    if (lhs == OPEN && rhs == CLOSE) {
        return START_TAG;
    } else if (lhs == OPEN_END && rhs == CLOSE) {
        return END_TAG;
    } else if (lhs == OPEN && rhs == CLOSE_EMPTY) {
        return EMPTY_TAG;
    } else if (lhs == OPEN_DECL && rhs == CLOSE_DECL) {
        return DECLARATION;
    } else {
        return CONTENT;
    }
}

/** Returns the type of syntax marker starting at it
    @param it  The start iterator for the range being checked
  */
static enum syntax_marker to_marker(std::string::const_iterator it) {
    for (size_t i = 0; i < MARK_CNT; i++) {
        if (std::equal(syntax_marks[i].cbegin(), syntax_marks[i].cend(), it)) {
            return static_cast<enum syntax_marker>(i);
        }
    }
    return NON_MARKER;
}

//============================================================================//

XMLParser::XMLParser() : elementNameBag(new Bag<std::string>),
                         parseStack(new Stack<std::string>),
                         tokenizedInputVector() {}

XMLParser::~XMLParser() {
    delete elementNameBag;
    delete parseStack;
}

bool XMLParser::tokenizeInputString(const std::string &inputString) {
    clear();
    if (inputString.empty()) return false;
    auto it = inputString.cbegin();
    auto next_it = next_marker(inputString, it);
    while (it != inputString.cend() && next_it != inputString.cend()) {
        auto next_it = next_marker(inputString, it);
        if (next_it == inputString.cend()) break;
        enum syntax_marker next_mark = to_marker(next_it);
        StringTokenType tag = CONTENT;
        if (!parseStack->isEmpty()) {
            std::string top = parseStack->peek();
            tag = marker_tag(to_marker(top.cbegin()), next_mark);
        }
        std::string str(it, next_it);
        TokenStruct token = {tag, str};
        switch (next_mark) {
            case OPEN: case OPEN_END: case OPEN_DECL:
                if (tag == CONTENT && it != next_it) {
                    tokenizedInputVector.push_back(token);
                }
                parseStack->push(syntax_marks[next_mark]);
                break;
            case CLOSE: case CLOSE_EMPTY: case CLOSE_DECL:
                if (parseStack->isEmpty() || tag == CONTENT) {
                    clear();
                    return false;
                }
                parseStack->pop();
                tokenizedInputVector.push_back(token);
                break;
            case NON_MARKER:
                break;
        }
        it = std::next(next_it, syntax_marks[next_mark].size());
    }
    if (!std::all_of(it, inputString.cend(), ::isspace)
    || !parseStack->isEmpty()) {
        clear();
        return false;
    }
    return true;
}

bool XMLParser::parseTokenizedInput() {
    parseStack->clear();
    if (tokenizedInputVector.empty()) return false;
    for (const auto& token : tokenizedInputVector) {
        TokenStruct top = {};
        const std::string& tok_str = token.tokenString;
        if (!parseStack->isEmpty()) top = deserialise_token(parseStack->peek());
        switch (token.tokenType) {
            case DECLARATION:
                if (!valid_token(token)) {
                    clear();
                    return false;
                }
                break;
            case START_TAG:
                if (!valid_token(token)) {
                    clear();
                    return false;
                }
                elementNameBag->add(token_name(token));
                parseStack->push(serialise_token(token));
                break;
            case END_TAG:
                if (parseStack->isEmpty()
                || !valid_token(token)
                || top.tokenType != START_TAG
                || top.tokenString != tok_str) {
                    clear();
                    return false;
                }
                parseStack->pop();
                break;
            case EMPTY_TAG:
                if (!valid_token(token)) {
                    clear();
                    return false;
                }
                elementNameBag->add(token_name(token));
                break;
            case CONTENT:
                if (std::all_of(tok_str.cbegin(), tok_str.cend(), ::isspace)) {
                    break;
                }
                if (!parseStack->isEmpty() && top.tokenType != START_TAG) {
                    clear();
                    return false;
                }
                break;
        }
    }
    if (!parseStack->isEmpty()) {
        clear();
        return false;
    }
    return true;
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const {
    return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &inputString) const {
    return elementNameBag->contains(inputString);
}

int XMLParser::frequencyElementName(const std::string &inputString) const {
    return elementNameBag->getFrequencyOf(inputString);
}

void XMLParser::clear() {
    elementNameBag->clear();
    parseStack->clear();
    tokenizedInputVector.clear();
}
