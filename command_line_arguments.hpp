struct args {
    std::string ifile;
    std::string ofile;
    std::map<std::string, bool> bool_args;
    std::map<std::string, int> int_args;
};

class CommandLineArguments {
private:
    struct args arglist;
public:    
    //Parses the arguments
    CommandLineArgumnts(int argc, char** argv);
    
    //Set the input file
    setIFile(std::string const & dir);
    
    //Set the output file
    setOFile(std::string const & dir);

    //Add Boolean Arg
    setBool(std::string const & param);

    //Add Int Arg
    setInt(std::string const & param);
    
    //Add String Arg
    setString(std::string const & param);

    //Retrieves the parsed argument struct
    struct args const & arglist() const noexcept;
};
