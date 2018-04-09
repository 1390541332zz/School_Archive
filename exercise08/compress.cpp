#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <type_traits>

#include "treap_bst.h"

typedef std::string WordType;
typedef uint32_t IndexType;
typedef TreapBST<WordType, IndexType> CompressTreeType;
typedef TreapBST<IndexType,WordType> DecompressTreeType;

CompressTreeType writeDictionary(const std::string & ifname, const std::string & ofname){

  CompressTreeType bst;
  IndexType count = 1;
  
  const char null = 0; 
  
  std::ifstream ifs(ifname);
  std::ofstream ofs(ofname, std::ios::binary);
  
  WordType word;
  bool found;
  while(!ifs.eof()){
    ifs >> word;
    bst.search(word, found);
    if(!found){
      bst.insert(word,count);
      
      // write to the output binary file
      ofs.write(reinterpret_cast<const std::fstream::char_type*>(&count), sizeof count);
      ofs.write(reinterpret_cast<const std::fstream::char_type*>(word.data()), word.length());
      ofs.write(&null, 1);
      ++count;
    }
  }

  // append entry closing the dictionary
  // 0 index and empty string
  count = 0;
  ofs.write(reinterpret_cast<const std::fstream::char_type*>(&count), sizeof count);

  ifs.close();
  ofs.close();
  
  return bst;
}

DecompressTreeType readDictionary(std::ifstream & ifs){

  DecompressTreeType bst;
  
  IndexType count;
  char byte;
  WordType word;
  while(!ifs.eof()){
    
    ifs.read(reinterpret_cast<std::fstream::char_type*>(&count), sizeof count);    
    if(count == 0) break;

    ifs.read(reinterpret_cast<std::fstream::char_type*>(&byte), 1);
    word.clear();
    while(byte != 0){
      word.push_back(byte);
      ifs.read(reinterpret_cast<std::fstream::char_type*>(&byte), 1);
    }

    //std::clog << count << " " << word << std::endl;
    bst.insert(count, word);
  }
  
  return bst;
}

bool compress(const std::string & ifname, const std::string & ofname){

  bool ok = true;
  
  CompressTreeType bst = writeDictionary(ifname, ofname);

  // append compressed stream
  std::ifstream ifs(ifname);
  // TODO fix meto match decompress design (not use append)
  std::ofstream ofs(ofname, std::ios::binary | std::ios::app);
  
  WordType word;
  bool found;
  while(!ifs.eof()){
    ifs >> word;
    if(ifs.eof()) continue;
    IndexType index = bst.search(word, found);
    if(!found){
      std::cerr << "Internal Error: key not in dictionary" << std::endl;
      ok = false;
      break;
    }
    //std::cout << index << " ";
    ofs.write(reinterpret_cast<const std::fstream::char_type*>(&index), sizeof index);
  }

  ofs.close();
  ifs.close();
  
  return ok;
}

bool decompress(const std::string & ifname, const std::string & ofname){

  bool ok = true;

  std::ifstream ifs(ifname, std::ios::binary);
  
  DecompressTreeType bst = readDictionary(ifs);

  // write decompressed stream
  std::ofstream ofs(ofname);

  WordType word;
  bool found;
  while(!ifs.eof()){
    IndexType index;
    ifs.read(reinterpret_cast<std::fstream::char_type*>(&index), sizeof index);

    if(ifs.eof()) continue;
	
    //std::cout << index << " ";
    
    WordType word = bst.search(index, found);
    if(!found){
      std::cerr << "Internal Error: key not in dictionary" << std::endl;
      ok = false;
      break;
    }
    ofs << word << " ";
  }
  ofs << "\n";
  
  ofs.close();
  ifs.close();
  
  return ok;
}

int main(int argc, char* argv[])
{
  bool deflag = false;
  int offset = 0;
  // check command line arguments
  if(argc > 1){
    if(std::string(argv[1]) == "-d"){
      deflag = true;
      offset = 1;
    }
  }
  if(argc != 3+offset){
    std::cerr << "Error: incorrect number of command line arguments.\n" << std::endl;
    return EXIT_FAILURE;
  }
  
  std::string infilename = argv[1+offset];
  std::string outfilename = argv[2+offset];
  
  bool ok;

  if(deflag){
    ok = decompress(infilename, outfilename);
  }
  else{
    ok = compress(infilename, outfilename);
  }
  
  // TODO: have the application print the decompressed size or ratio?
  // open file seek to end, take difference
  // or just have tehm dump in a readme with observations about compression ratio
  
  return (ok ? EXIT_SUCCESS : EXIT_FAILURE);
}
