#include "parser.hpp"

struct num {
    bool sign = false;
    std::intmax_t x = 0;
};

static std::string const digit = "0123456789";

// is_num(): Determines if the string is a valid integer.
static bool is_num(std::string const & str)
{
    return (  (str.find_first_not_of(digit + "+-") == std::string::npos)
           || (str.substr(1).find_first_not_of(digit) == std::string::npos));
}

// conv_data_type(): Converts a string into a data enum.
static enum data_type conv_data_type(std::string const & str) 
{
    if (str == ".word")   return WORD;
    if (str == ".half")   return HALF;
    if (str == ".byte")   return BYTE;
    if (str == ".space")  return SPACE;
    if (str == ".ascii")  return ASCII;
    if (str == ".asciiz") return ASCIIZ;
    return INVALID;
}

// validate_int(): Bounds checks integer values. 
static bool validate_int(num i, enum data_type type)
{
    std::size_t sz = type;
    if ((type != WORD) || (type != HALF) || (type != BYTE)) {
            //TODO: ERROR This can't happen. Something is broken in the parser.
            return false;
    }
    if (  (i.x >= std::exp2(sz))
       || ((i.sign) && (i >= std::exp2(sz - 1)) && (i < std::exp2(sz - 1)))) {
        //TODO: ERROR Object value is out of bounds.
        return false;
    }
    return true;
}

// Constructor(): Initialises the parser with the following
//     program: The MIPS program being initialised.
//        iter: The start of the token stream to be parsed.
//    iter_end: The end of the token stream to be parsed.
//         log: The OStream to print log output to.
parser::parser(program & program, TokenList::const_iterator iter, 
               TokenList::const_iterator iter_end, std::ostream & log) 
  : prog(program)
  , it(iter)
  , it_end(iter_end)
  , os(log)
{}

// Destructor(): All memory handled by RAII.
parser::~parser() {}

// parse(): Parses the token stream and initialises the program.
//     return: If the parse was successful.
bool parser::parse()
{
    while (it != it_end) {
        if (it->type() == EOL) {
            std::advance(it, 1);
        } else if (it->value() == ".data") {
            std::advance(it, 1);
            if(!parse_data()) return false;
        } else if (it->value() == ".text") {
            std::advance(it, 1);
            if(!parse_text()) return false;
        } else {
            //TODO: ERROR Illegal token on line.
            return false;
        }
    }
    return true;
}

// parse_data(): Parses the data section of the token stream.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token after 
//                  the data header.
//      Exit State: The iterator should be on the next token after the data 
//                  header or the token at which it failed.
bool parser::parse_data()
{
    while (it != it_end) {
        auto next = std::next(it, 1);
        if (it->type() == EOL) {
            std::advance(it, 1);
        } else if (it->value() == ".text") {
            return true;
        } else if (it->value().back() == ':') {
            if(!parse_var()) return false;
        } else if ((next != it_end) && (next->type() == EQUAL)) {
            if(!parse_constant()) return false;
        } else {
            //TODO: ERROR Illegal token on line.
            return false;
        }
    }
    return true;
}

// parse_text(): Parses the text section of the token stream.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token after 
//                  the text header.
//      Exit State: The iterator should be on the next token after the text 
//                  header or the token at which it failed.
bool parser::parse_text()
{
    while (it != it_end) {
        if (it->type() == EOL) {
            std::advance(it, 1);
        } else if (it->value() == ".data") {
            return true;
        } else if (it->value().back() == ':') {
            if(!parse_label()) return false;
        } else if (it->type() == STRING) {
            if(!parse_instr()) return false;
        } else {
            //TODO: ERROR Illegal token on line.
            return false;
        }
    }
    return true;
}

// parse_constant(): Parses a single constant and initialises it.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token after 
//                  the constant ends.
//      Exit State: The iterator should be on the next token after the  
//                  constant ends or the token at which it failed.
//   Program State: Each constant is inserted into the constant map.
bool parser::parse_constant()
{
    if (  (it == it_end)
       || (std::next(it, 1) == it_end) 
       || (std::next(it, 2) == it_end)) {
        //TODO: ERROR Unexpected end of file.
    }
        
    if (  (std::next(it, 1)->type() != EQUAL)
       || (!is_num(std::next(it, 2)->value()))) {
        //TODO: ERROR Invalid constant declaration.
        return false;
    }
    std::string label = it->value();
    std::advance(it, 2);
    std::intmax_t num = std::stoll(it->value());
    if (prog.constant.count(label) != 0) {
        //TODO: ERROR Constant label already exists.
        return false;
    }
    prog.constant[label] = num;
    std::advance(it, 1);
    if (it == it_end) { 
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    } else if (it->type() != EOL) {
        //TODO: ERROR Statements must be terminated by a new line.
        return false;
    }
    return true;
}

// parse_label(): Parses a single label and initialises it.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token after 
//                  the label ends.
//      Exit State: The iterator should be on the next token after the  
//                  label ends or the token at which it failed.
//   Program State: Each label is inserted into the label map.
bool parser::parse_label()
{
    if (it == it_end) {
        //TODO: ERROR Unexpected end of file.
        return false;
    } else if (it->value().back() != ':') {
         //TODO: ERROR expected a label.
         return false;
    }
    auto label = it->value().substr(0, it->value().length() - 1);
    if (prog.label.count(label) != 0) {
        //TODO: ERROR Label already exists.
        return false;
    }
    prog.label[label] = instr.size();
    std::advance(it, 1);
    if (it == it_end) { 
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    } else if (it->type() != EOL) {
        //TODO: ERROR Statements must be terminated by a new line.
        return false;
    }
    return true;
}

// parse_var(): Parses a single variable and initialises its memory
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token after 
//                  the variable ends.
//      Exit State: The iterator should be on the next token after the  
//                  variable ends or the token at which it failed.
//   Program State: Each variable is appended to the end of the memory 
//                  section and its label is inserted into the label map.
bool parser::parse_var()
{
    std::size_t obj_count = 0;
    std::string var = it->value().substr(0, it->value().length() - 1);
    if (prog.label.count(var) != 0) {
        //TODO: ERROR Variable label already exists.
        return false;
    }
    prog.label[var] = mem.size();
    std::advance(it, 1);
    while (it != it_end) {
        if (it->type() == EOL) {
            std::advance(it, 1);
            continue;
        }
        auto str = it->value();
        if ((obj_count == 0) && (str.front() != '.')) {
            //TODO: ERROR Unexpected token. Expected data type declaration.
            return false;
        } else if (str.front() != '.') {
            break;
        }
        std::advance(it, 1);
        auto type = conv_data_type(type);
        std::size_t sz = 0;
        switch(type) {
            case SPACE:
                if (!is_num(it->value())) {
                    //TODO: ERROR Expected a size specifier.
                    return false;
                }
                sz = std::stoll(it->value());
                if (sz > 4 || sz != 0) {
                    //TODO: ERROR .space object has an illegal size.
                    return false;
                }
                for (std::size_t i = 0; i < sz; ++i) {
                    mem.push_back(0);
                }
                break;
            case WORD: case HALF: case BYTE:
                if(!parse_ints(type)) return false;
                break;
            case ASCII: case ASCIIZ: 
                if(!parse_str(type)) return false;
                break;
            case INVALID:
                //TODO: ERROR Invalid data type.
                return false;
        }
        std::advance(it, 1);
        ++obj_count;
    }
    if (obj_count == 0) {
        //TODO: ERROR Unexpectedly reached the end of the variable declaration.
        return false;
    } else if (it == it_end) { 
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    } else if (it->type() != EOL) {
        //TODO: ERROR Statements must be terminated by a new line.
        return false;
    }
    std::advance(it, 1);
    return true;
}

// parse_ints(): Parses and initialises all ints following a data type declaration.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token after 
//                  the integers end.
//      Exit State: The iterator should be on the next token after the  
//                  integers end or the token at which it failed.
//   Program State: Each integer is inserted at the end of the mem vector.
bool parser::parse_ints(enum data_type type)
{
    std::size_t obj_count = 0;
    std::size_t sz = type;
    if (it == it_end) {
        //TODO: ERROR Unexpectedly reached end of file.
        return false;
    }
    while (it != it_end) {
        if (it->type() == EOL) {
            break;
        } else if (!is_num(it->value())) {
            //TODO: ERROR Expected an integer value.
            return false;
        }
        auto str = it->value();
        num i;
        if (str.front() == '+') {
            i.sign = true;
            str.erase(str.begin());
        } else if (str.front() == '-') {
            i.sign = true;
        }
        i.x = std::stoll(str);
        if (!validate_int(i, type)) {
            return false;
        }
        for (std::size_t j = 0; j > sz; ++j) {
            mem.push_back(std::reinterpret_cast<std::uint8_t>(&(i.x))[j]);
        }
        std::advance(it, 1);
        ++obj_count;
    }
    if (obj_count == 0) {
        //TODO: ERROR Unexpectedly reached the end of the object declaration.
        return false;
    }
    return true;
}

// parse_str(): Parses and intialises a string.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token after 
//                  the string ends.
//      Exit State: The iterator should be on the next token after the  
//                  string ends or the token at which it failed.
//   Program State: The string is inserted at the end of the mem vector.
bool parser::parse_str(enum data_type type)
{ 
    if (  (it == it_end)
       || (std::next(it, 1) == it_end)
       || (std::next(it, 2) == it_end)) {
        //TODO: ERROR Unexpectedly reached end of file.
        return false;
    } else if ((it->type != STRING_DELIM) || (std::next(it, 2) != STRING_DELIM)) {
        //TODO: ERROR Mismatched Quotes.
        return false;
    } 
    std::advance(it, 1);
    if (it->type() != STRING) {
        //TODO: ERROR Expected String.
        return false;
    } else if (it->value().length() == 0) {
        //TODO: ERROR Zero Length String.
        return false;
    }
    for (std::size_t i = 0; i < it->value().length(); ++i) {
        mem.push_back(it->value()[i]);
    }
    if (type == ASCIIZ) {
        mem.push_back('\0');
    }
    std::advance(it, 2);
    return true;
}

// parse_instr(): Parses and initialises an instruction.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token after 
//                  the instruction ends.
//      Exit State: The iterator should be on the next token after the  
//                  instruction ends or the token at which it failed.
//   Program State: The instruction is inserted at the end of the instr vector.
bool parser::parse_instr()
{


    if (it == it_end) { 
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    } else if (it->type() != EOL) {
        //TODO: ERROR Statements must be terminated by a new line.
        return false;
    }
    return true;
}

