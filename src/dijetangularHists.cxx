#include "UHH2/dijetangular/include/dijetangularHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

dijetangularHists::dijetangularHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here
  // jets
  book<TH1F>("dijet_mass", "M_{jj}", 130, 0, 13000);  
  book<TH1F>("chi_1900_2400", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_2400_3000", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_3000_3600", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_3600_4200", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_4200_4800", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_4800_5400", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_5400_6000", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_6000_6600", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_6600_7200", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_7200_13000", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_6000_13000", "#chi_{dijet}", 15, 1, 16);
  book<TH1F>("chi_6600_13000", "#chi_{dijet}", 15, 1, 16);

  // primary vertices
  book<TH1F>("N_pv", "N^{PV}", 100, 0, 100);
}


void dijetangularHists::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  double weight = event.weight;

  if(event.jets->size() < 2) return;
  const auto & j1 = event.jets->at(0);
  const auto & j2 = event.jets->at(1);
  jet1.SetPtEtaPhiE( j1.pt(), j1.eta(), j1.phi(), j1.energy() );
  jet2.SetPtEtaPhiE( j2.pt(), j2.eta(), j2.phi(), j2.energy() );
  dijet=jet1+jet2;

  dijet_mass = dijet.M();
  dijet_chi = exp(fabs(jet1.Rapidity()-jet2.Rapidity()));
  dijet_yboost = fabs(jet1.Rapidity()+jet2.Rapidity())/2.0;
  
  hist("dijet_mass")->Fill(dijet_mass,weight); 
  if((dijet_mass>=1900)&&(dijet_mass<2400))
    hist("chi_1900_2400")->Fill(dijet_chi,weight);
  if((dijet_mass>=2400)&&(dijet_mass<3000))
    hist("chi_2400_3000")->Fill(dijet_chi,weight);
  if((dijet_mass>=3000)&&(dijet_mass<3600))
    hist("chi_3000_3600")->Fill(dijet_chi,weight);
  if((dijet_mass>=3600)&&(dijet_mass<4200))
    hist("chi_3600_4200")->Fill(dijet_chi,weight);
  if((dijet_mass>=4200)&&(dijet_mass<4800))
    hist("chi_4200_4800")->Fill(dijet_chi,weight);
  if((dijet_mass>=4800)&&(dijet_mass<5400))
    hist("chi_4800_5400")->Fill(dijet_chi,weight);
  if((dijet_mass>=5400)&&(dijet_mass<6000))
    hist("chi_5400_6000")->Fill(dijet_chi,weight);
  if((dijet_mass>=6000)&&(dijet_mass<6600))
    hist("chi_6000_6600")->Fill(dijet_chi,weight);
  if((dijet_mass>=6600)&&(dijet_mass<7200))
    hist("chi_6600_7200")->Fill(dijet_chi,weight);
  if((dijet_mass>=7200)&&(dijet_mass<13000))
    hist("chi_7200_13000")->Fill(dijet_chi,weight);
  if((dijet_mass>=6000)&&(dijet_mass<13000))
    hist("chi_6000_13000")->Fill(dijet_chi,weight);
  if((dijet_mass>=6600)&&(dijet_mass<13000))
    hist("chi_6600_13000")->Fill(dijet_chi,weight);
  
  int Npvs = event.pvs->size();
  hist("N_pv")->Fill(Npvs, weight);
}

dijetangularHists::~dijetangularHists(){}
