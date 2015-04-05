#ifndef AUX_HH
#define AUX_HH 1
//C++ INCLUDES
#include <map>
#include <string>
#include <sstream>
#include <vector>
//ROOT INCLUDES
#include <TH1F.h>
//LOCAL INCLUDES
#include "ntp1.hh"

TH1F* MakeDiff( ntp1* t1, ntp1* t2, std::string var_name, std::string var_type);
bool CreateDiff( std::string file1, std::string file2, std::string tree1, std::string tree2);
bool CreateDiff( std::string file1, std::string file2, std::string tree1, std::string tree2, std::string var_list, bool _same_tree );


#endif
