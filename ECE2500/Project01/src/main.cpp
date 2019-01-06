
#include <fstream>
#include "parse_obj.hpp"
#include "export_disasm.hpp"

int main(int argc, char** argv)
{
    for (std::size_t i = 1; i < argc; ++i) {
        std::string f(argv[i]);
        std::ifstream ifs(f);
        std::string of = f;
        of.replace(of.find(".obj"), of.size(), ".s");
        std::ofstream ofs(of);
        asm_parser p(ifs);
        if(asm_export(ofs, p.get_result()) != 0) return -1;
    }
}
