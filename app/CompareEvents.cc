//C++ INCLUDES
#include <iostream>
//ROOT INCLUDES
#include <TFile.h>
#include <TTree.h>
//LOCAL INCLUDES
#include "ntp1.hh"
#include "aux.hh"

int main( int argc, char* argv[] )
{

  if( ParseCommandLine( argc, argv, "-help" ) != "" )
    {
      std::cout << "======================[HELP]=======================" << std::endl;
      Usage();
      return 0;
    }
  
  if ( argc < 3 )
    {
      std::cerr << "[ERROR]: insufficient command line arguments provided" << std::endl;
      Usage();
      return 0;
    }
  
  std::string fname1 = "";
  std::string fname2 = "";

  fname1 = ParseCommandLine( argc, argv, "-file1=" );
  fname2 = ParseCommandLine( argc, argv, "-file2=" );

  std::map < std::string, evt > map1 = MakeMap( fname1 );
  std::map < std::string, evt > map2 = MakeMap( fname2 );
  CreateDiff( map1, map2, "HggRazorMissing.txt" );
  CreateDiff( map2, map1, "SusyHggTreeMissing.txt" );
  
  return 0;
};
