//C++ INCLUDES
#include <fstream>
#include <sstream>
//ROOT INCLUDES
#include <TString.h>
#include <TDirectory.h>
#include <TCanvas.h>
//LOCAL INCLUDES
#include "aux.hh"

TH1F* MakeDiff( ntp1* t1, ntp1* t2, std::string var_name, std::string var_type)
{
  TH1F* h_tmp = new TH1F( var_name.c_str(), var_name.c_str(), 1000, -10, 10);
  return h_tmp;
};

bool CreateDiff( std::string file1, std::string file2, std::string tree1, std::string tree2)
{
  TFile* f1 = new TFile( file1.c_str() );
  TTree* t1 = (TTree*)f1->Get( tree1.c_str() );
  TString t2_name = "t2 =" + tree2;
  t1->AddFriend( t2_name,  file2.c_str() );
  
  TCanvas* C = new TCanvas("C", "C", 640, 640);
  C->cd();
  
  std::ifstream ifs( "input/input_variables.txt", std::ifstream::in );
  if ( ifs.is_open() )
    {
      int i_histo = 0;
      while ( ifs.good() )
	{
	  std::string var;
	  ifs >> var;
	  if( ifs.eof() ) break;
	  std::stringstream tmp;
	  tmp << "( " << var << " - t2." << var << " )/" << var << " >> tmp_" << i_histo << "(100,-100, 100)";
	  std::stringstream tmp_h;
	  tmp_h << "tmp_" << i_histo;
	  
	  //t1->Draw( tmp.str().c_str() , "nPho-t2.nPho == 0 && nPerPVPho == t2.nPerPVPho", "goff");
	  t1->Draw( tmp.str().c_str() , "nPerPVPho == t2.nPerPVPho", "goff");
	  //t1->Draw( tmp.str().c_str() , "", "goff");
	  TH1F* h_tmp = (TH1F*)gDirectory->Get( tmp_h.str().c_str() );
	  if ( h_tmp->GetRMS() > 0.0 ) std::cout << var << std::endl;
	  h_tmp->Draw();
	  C->SetLogy();
	  std::string h_name = "data/"+var+".pdf";
	  C->SaveAs( h_name.c_str() );
	  i_histo++;
	}
    }
  else
    {
      std::cerr << "[ERROR]: unable to open file" << std::endl;
      return false;
    }
  
};

bool CreateDiff( std::string file1, std::string file2, std::string tree1, std::string tree2, std::string var_list, bool _same_tree = true )
{
  
  TFile* f1 = new TFile( file1.c_str() );
  TTree* t1 = (TTree*)f1->Get( tree1.c_str() );
  
  TFile* f2 = new TFile( file2.c_str() );
  TDirectoryFile* dir = (TDirectoryFile*)f2->Get("ntuples");
  //TTree* t2 = (TTree*)f2->Get( tree2.c_str() ); 
  TTree* t2 = (TTree*)dir->Get( tree2.c_str() );
  
  TString t2_name = "t2";
  t1->AddFriend( t2, t2_name );

  TCanvas* C = new TCanvas("C", "C", 640, 640);
  C->cd();

  std::ifstream ifs( var_list.c_str(), std::ifstream::in );

  if ( ifs.is_open() )
    {
      int i_histo = 0;
      while ( ifs.good() )
        {
	  if ( _same_tree )
	    {
	      std::string var;
	      ifs >> var;
	      if( ifs.eof() ) break;
	      std::stringstream tmp;
	      tmp << "( " << var << " - t2." << var << " )/" << var << " >> tmp_" << i_histo << "(100,-100, 100)";
	      std::stringstream tmp_h;
	      tmp_h << "tmp_" << i_histo;
	      
	      //t1->Draw( tmp.str().c_str() , "nPho-t2.nPho == 0 && nPerPVPho == t2.nPerPVPho", "goff");                                   
	      t1->Draw( tmp.str().c_str() , "nPerPVPho == t2.nPerPVPho", "goff");
	      //t1->Draw( tmp.str().c_str() , "", "goff");                                                                                
	      TH1F* h_tmp = (TH1F*)gDirectory->Get( tmp_h.str().c_str() );
	      if ( h_tmp->GetRMS() > 0.0 ) std::cout << var << std::endl;
	      h_tmp->Draw();
	      C->SetLogy();
	      std::string h_name = "data/"+var+".pdf";
	      C->SaveAs( h_name.c_str() );
	      i_histo++;
	    }//same tree case
	  else
	    {
	      std::string var1, var2;
              ifs >> var1 >> var2;
              if( ifs.eof() ) break;
	      std::stringstream tmp;
              tmp << "( " << var1 << " - t2." << var2 << " )/" << var1 << " >> tmp_" << i_histo << "(1000,-10, 10)";
	      std::stringstream tmp_h;
              tmp_h << "tmp_" << i_histo;

              //t1->Draw( tmp.str().c_str() , "nPho-t2.nPho == 0 && nPerPVPho == t2.nPerPVPho", "goff");                                   
              //t1->Draw( tmp.str().c_str() , "nPerPVPho == t2.nPerPVPho", "goff");
	      //t1->Draw( tmp.str().c_str() , "", "goff");                                                          
	      t1->Draw( tmp.str().c_str() , "sqrt(uncorrpxAK5PFPUcorrJet*uncorrpxAK5PFPUcorrJet+uncorrpyAK5PFPUcorrJet*uncorrpyAK5PFPUcorrJet)>21.0", "goff");  
	      TH1F* h_tmp = (TH1F*)gDirectory->Get( tmp_h.str().c_str() );
              if ( h_tmp->GetRMS() > 0.0 ) std::cout << var1 << " " << var2 << std::endl;
              h_tmp->Draw();
              C->SetLogy();
	      std::string h_name = "data/"+var2+".pdf";
              C->SaveAs( h_name.c_str() );
              i_histo++;
	    }//different tree case
        }
    }
  else
    {
      std::cerr << "[ERROR]: unable to open file" << std::endl;
      return false;
    }
  
};
