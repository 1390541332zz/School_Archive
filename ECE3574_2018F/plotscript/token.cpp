#include "token.hpp"

// system includes
#include <cctype>
#include <iostream>

// define constants for special characters
const char OPENCHAR = '(';
const char CLOSECHAR = ')';
const char COMMENTCHAR = ';';
const char QUOTECHAR = '"';

Token::Token(TokenType t)
    : m_type(t)
{
}

Token::Token(std::string const & str)
    : m_type(STRING)
    , value(str)
{
}

Token::TokenType Token::type() const
{
    return m_type;
}

std::string Token::asString() const
{
    switch (m_type) {
    case OPEN:
        return "(";
    case CLOSE:
        return ")";
    case QUOTE:
        return "\"";
    case STRING:
        return value;
    }
    return "";
}

// add token to sequence unless it is empty, clears token
void store_ifnot_empty(std::string & token, TokenSequenceType & seq)
{
    if (!token.empty()) {
        seq.emplace_back(token);
        token.clear();
    }
}

TokenSequenceType tokenize(std::istream & seq)
{
    TokenSequenceType tokens;
    std::string token;

    while (true) {
        char c = seq.get();
        if (seq.eof()) {
            break;
        }

        if (c == COMMENTCHAR) {
            // chomp until the end of the line
            while ((!seq.eof()) && (c != '\n')) {
                c = seq.get();
            }
            if (seq.eof()) {
                break;
            }
        } else if ((c == QUOTECHAR) && (tokens.empty() || ((!tokens.empty()) && (tokens.back().type() != Token::TokenType::QUOTE)))) {
            store_ifnot_empty(token, tokens);
            tokens.push_back(Token::TokenType::QUOTE);
            token.push_back(QUOTECHAR);
        } else if ((c == QUOTECHAR) && (!tokens.empty()) && (tokens.back().type() == Token::TokenType::QUOTE)) {
            tokens.pop_back();
            token.push_back(QUOTECHAR);
            store_ifnot_empty(token, tokens);
        } else if ((!tokens.empty()) && (tokens.back().type() == Token::TokenType::QUOTE)) {
            token.push_back(c);
        } else if (c == OPENCHAR) {
            store_ifnot_empty(token, tokens);
            tokens.push_back(Token::TokenType::OPEN);
        } else if (c == CLOSECHAR) {
            store_ifnot_empty(token, tokens);
            tokens.push_back(Token::TokenType::CLOSE);
        } else if (std::isspace(c) != 0) {
            store_ifnot_empty(token, tokens);
        } else {
            token.push_back(c);
        }
    }
    store_ifnot_empty(token, tokens);
    return tokens;
}
