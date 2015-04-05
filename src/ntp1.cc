#define ntp1_cxx
#include "ntp1.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
//C++ INCLUDES
#include <fstream>

void ntp1::Loop()
{
  std::ofstream ofs ("test.txt", std::ofstream::out);
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    ofs << runNumber << " " << eventNumber << "\n";
  }
  ofs.close();
  
};

bool ntp1::isLoosePFPUcorrJet(int i)
{
  
};

bool ntp1::isMediumPFPUcorrJet(int i)
{
  
};

bool ntp1::isTightPFPUcorrJet(int i)
{

};
