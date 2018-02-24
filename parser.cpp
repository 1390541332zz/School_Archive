#include "parser.hpp"
#include "parser_utilities.hpp"

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
//     Entry State: The iterator should be on the first token of
//                  the constant declaration.
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
//     Entry State: The iterator should be on the first token of 
//                  the label declaration.
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
    prog.label[label] = prog.ops.size();
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
//     Entry State: The iterator should be on the first token of
//                  the variable declaration.
//      Exit State: The iterator should be on the next token after the
//                  variable ends or the token at which it failed.
//   Program State: Each variable is appended to the end of the memory
//                  section and its label is inserted into the label map.
bool parser::parse_var()
{
    std::size_t obj_count = 0;
    std::string var = it->value().substr(0, it->value().length() - 1);
    if (prog.var_label.count(var) != 0) {
        //TODO: ERROR Variable label already exists.
        return false;
    }
    prog.var_label[var] = prog.mem.size();
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
        auto type = conv_data_type(it->value());
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
                    prog.mem.push_back(0);
                }
                break;
            case WORD: case HALF: case BYTE:
                if(!parse_ints(type)) return false;
                break;
            case ASCII: case ASCIIZ:
                if(!parse_str(type)) return false;
                break;
            case ERR:
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
//     Entry State: The iterator should be on the first token of
//                  the set of integers.
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
            prog.mem.push_back(reinterpret_cast<std::uint8_t*>(&(i.x))[j]);
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
//     Entry State: The iterator should be on the first token of
//                  the string construct (The quote).
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
    } else if ((it->type() != STRING_DELIM) || (std::next(it, 2)->type() != STRING_DELIM)) {
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
        prog.mem.push_back(it->value()[i]);
    }
    if (type == ASCIIZ) {
        prog.mem.push_back('\0');
    }
    std::advance(it, 2);
    return true;
}

// parse_instr(): Parses and initialises an instruction.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token of
//                  the instruction declaration.
//      Exit State: The iterator should be on the next token after the
//                  instruction ends or the token at which it failed.
//   Program State: The instruction is inserted at the end of the instr vector.
bool parser::parse_instr()
{
    if (it == it_end) {
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    } else if (it->type() != STRING) {
        //TODO: ERROR Unexpected token.
        return false;
    }
    auto op = conv_instr_type(it->value());
    std::array<arg, 3> args; 

    std::advance(it, 1);
    switch(op) {
        case LOAD_WORD:  case LOAD_HALF:  case LOAD_BYTE: case LOAD_ADD:
        case STORE_WORD: case STORE_HALF: case STORE_BYTE:
            if (  (!parse_arg(args[0], REG))
               || (!parse_sep())
               || (!parse_arg(args[1], MEM))) {
                return false;
            }
            break; 
        case MOVE_FROM_HI: case MOVE_FROM_LO: case MOVE_TO_HI: case MOVE_TO_LO:
            if (!parse_arg(args[0], REG)) {
                return false;
            }
            break; 
        case ADD_S:  case ADD_U:   case SUB_S:  case SUB_U:  case MUL:
        case MUL_LO: case MUL_LOU: case REM_S:  case REM_U:  case AND:
        case NOR:    case OR:      case XOR:
            if (  (!parse_arg(args[0], REG))
               || (!parse_sep())
               || (!parse_arg(args[1], REG))
               || (!parse_sep())
               || (!parse_arg(args[2], SOURCE))) {
                return false;
            }
            break; 
        case MULT_S: case MULT_U: case ABS: case NEG_S: case NEG_U:
            if (  (!parse_arg(args[0], REG))
               || (!parse_sep())
               || (!parse_arg(args[1], REG))) {
                return false;
            }
            break; 
        case BRANCH_EQ: case BRANCH_NE: case BRANCH_LT: 
        case BRANCH_LE: case BRANCH_GT: case BRANCH_GE:
            if (  (!parse_arg(args[0], REG))
               || (!parse_sep())
               || (!parse_arg(args[1], SOURCE))
               || (!parse_sep())
               || (!parse_arg(args[2], LABEL))) {
                return false;
            }
            break; 
        case LOAD_IMM:
            if (  (!parse_arg(args[0], REG))
               || (!parse_sep())
               || (!parse_arg(args[1], IMMEDIATE))) {
                return false;
            }
            break; 
        case MOVE:
            if (  (!parse_arg(args[0], REG))
               || (!parse_sep())
               || (!parse_arg(args[1], REG))) {
                return false;
            }
            break; 
        case NOT:
            if (  (!parse_arg(args[0], REG))
               || (!parse_sep())
               || (!parse_arg(args[1], SOURCE))) {
                return false;
            }
            break; 
        case JUMP:
            if (!parse_arg(args[0], LABEL)) {
                return false;
            }
            break;
        case NOP:
            break;
        case DIV_S_IND: case DIV_U_IND:
            //TODO: WRITE DIVISION CASES
            break;
        default:
            //TODO: ERROR This can't happen. Something is wrong with the parser.
            return false;
    }
    prog.ops.emplace_back(op, args[0], args[1], args[2]);
    if (it == it_end) {
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    } else if (it->type() != EOL) {
        //TODO: ERROR Statements must be terminated by a new line.
        return false;
    }
    return true;
}


// parse_sep(): Parses separators.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the separator token.
//      Exit State: The iterator should be on the next token after the
//                  separator or the token at which it failed.
//   Program State: Nothing changes with the program state.
bool parser::parse_sep()
{ 
    if (it == it_end) {
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    } else if (it->type() != SEP) {
        //TODO: ERROR Unexpected token. Was expecting a separator.
        return false;
    }
    std::advance(it, 1);
    return true;
}


// parse_arg(): Parses an argument.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token of the
//                  argument construct.
//      Exit State: The iterator should be on the next token after the
//                  argument or the token at which it failed.
//   Program State: Nothing changes with the program state however the 
//                  referenced argument a is modified to contain 
//                  the newly parsed argument.
bool parser::parse_arg(arg & a, enum arg_type type)
{
    if (it == it_end) {
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    }
    switch (type) {
        case LABEL:
            if (!parse_tag(a)) return false;
            break;
        case REG:
            if (!parse_reg(a)) return false;
            break;
        case MEM:
            if (!parse_mem(a)) return false;
            break;
        case IMMEDIATE:
            if (!parse_imm(a)) return false;
            break;
        case SOURCE:          
            if (!parse_source(a)) return false;
            break;
        default:
            //TODO: ERROR This can't happen.
            break;
    }
    if (a.type == UNDEF) {
        //TODO: ERROR Missing Argument
        return false;
    }
    return true;
}


// parse_tag(): Parses an label argument.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token of the
//                  label argument construct.
//      Exit State: The iterator should be on the next token after the
//                  label argument or the token at which it failed.
//   Program State: Nothing changes with the program state however the 
//                  referenced argument a is modified to contain 
//                  the newly parsed argument.
bool parser::parse_tag(arg & a)
{
    if (it == it_end) {
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    } else if (prog.label.count(it->value()) == 0) {
        //TODO: ERROR Label not recognised.
        return false;
    }
    a.type = LABEL;
    a.label = prog.label[it->value()]; 
    std::advance(it, 1);
    if ((it == it_end) || (!(it->type() == EOL) && !(it->type() == SEP))) {
        //TODO: ERROR Invalid argument.
        return false;
    }
    return true;
}

// parse_reg(): Parses a register argument.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token of the
//                  register argument construct.
//      Exit State: The iterator should be on the next token after the
//                  register argument or the token at which it failed.
//   Program State: Nothing changes with the program state however the 
//                  referenced argument a is modified to contain 
//                  the newly parsed argument.
bool parser::parse_reg(arg & a)
{
    if (it == it_end) {
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    } else if (conv_reg_val(it->value()) == INVALID) {
        //TODO: ERROR Invalid Register.
        return false;
    }
    a.type = REG;
    a.reg = conv_reg_val(it->value());
    std::advance(it, 1);
    if ((it == it_end) || (!(it->type() == EOL) && !(it->type() == SEP))) {
        //TODO: ERROR Invalid argument.
        return false;
    }
    return true;
}

// parse_mem(): Parses a memory argument.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token of the
//                  memory argument construct.
//      Exit State: The iterator should be on the next token after the
//                  memory argument or the token at which it failed.
//   Program State: Nothing changes with the program state however the 
//                  referenced argument a is modified to contain 
//                  the newly parsed argument.
bool parser::parse_mem(arg & a)
{ 
    if (it == it_end) {
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    }
    std::ptrdiff_t offset = 0;
    if (is_num(it->value())) {
        offset = std::stoll(it->value());
        std::advance(it, 1);
    }
    if (  (it->type() == OPEN_PAREN) 
       && (std::next(it, 2) != it_end)
       && (std::next(it, 2)->type() == CLOSE_PAREN)) {
        a.type = MEM_INDIRECT;
        std::advance(it, 1);
    } else if (offset != 0) {
        //TODO: ERROR Invalid memory argument.
        return false;
    } else {
        a.type = MEM_DIRECT;
    }
    if ((a.type == MEM_INDIRECT) && (conv_reg_val(it->value()) == INVALID)) {
        //TODO: ERROR Invalid register.
        return false;
    } else if (a.type == MEM_INDIRECT) {
        a.reg = conv_reg_val(it->value());
        a.offset = offset;
    } else if (a.type == MEM_DIRECT) {
        if (prog.var_label.count(it->value())) {
            a.mem = prog.var_label[it->value()]; 
        }
    } else {
        //TODO: ERROR This can't happen.
        return false;
    }
    std::advance(it, 1);
    if (a.type == MEM_INDIRECT) std::advance(it, 1);
    if ((it == it_end) || (!(it->type() == EOL) && !(it->type() == SEP))) {
        //TODO: ERROR Invalid argument.
        return false;
    }
    return true;
}

// parse_imm(): Parses a immediate argument.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token of the
//                  immediate argument construct.
//      Exit State: The iterator should be on the next token after the
//                  immediate argument or the token at which it failed.
//   Program State: Nothing changes with the program state however the 
//                  referenced argument a is modified to contain 
//                  the newly parsed argument.
bool parser::parse_imm(arg & a)
{ 
    if (it == it_end) {
        //TODO: ERROR Unexpectedly reached the end of file.
        return false;
    } 
    a.type = IMMEDIATE;
    if (is_num(it->value())) {
        a.imm = std::stoll(it->value());
    } else if (prog.constant.count(it->value()) != 0) {
        a.imm = prog.constant[it->value()];
    } else {
        //TODO: ERROR Invalid Constant.
        return false;
    }
    std::advance(it, 1);
    if ((it == it_end) || (!(it->type() == EOL) && !(it->type() == SEP))) {
        //TODO: ERROR Invalid argument.
        return false;
    }
    return true;
}


// parse_source(): Parses a source argument.
//     return: If the parse was successful.
//
//     Entry State: The iterator should be on the first token of the
//                  source argument construct.
//      Exit State: The iterator should be on the next token after the
//                  source argument or the token at which it failed.
//   Program State: Nothing changes with the program state however the 
//                  referenced argument a is modified to contain 
//                  the newly parsed argument.
bool parser::parse_source(arg & a)
{
    switch (it->type()) {
        case STRING:
            if (conv_reg_val(it->value()) != INVALID) {
               return (parse_reg(a));
            } else if (prog.var_label.count(it->value()) != 0) {
                return (parse_mem(a));
            } else if (prog.label.count(it->value()) != 0) {
                return (parse_tag(a));
            } else if (prog.constant.count(it->value()) != 0) {
                return (parse_imm(a));
            } else {
                //TODO: ERROR This can't happen.
                return false;
            }
        case OPEN_PAREN:
            return (parse_mem(a));
        default:
            //TODO: ERROR Invalid argument.
            return false;
    }
}

