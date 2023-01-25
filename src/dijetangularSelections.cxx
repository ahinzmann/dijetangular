#include "UHH2/dijetangular/include/dijetangularSelections.h"
#include "UHH2/core/include/Event.h"

#include <stdexcept>

using namespace uhh2examples;
using namespace uhh2;


DijetSelection::DijetSelection(std::string treename, bool is_mc, float chi_max, float yboost_max, float mjj_min)
   : chi_max_(chi_max), yboost_max_(yboost_max), mjj_min_(mjj_min)
   , weight_(1.)
   , lheweight_(1.)
   , puweight_(1.)
   , lumiweight_(1.)
   , is_mc_(is_mc)
   , varnames("jetAK4_pt1:jetAK4_eta1:jetAK4_y1:jetAK4_phi1:jetAK4_mass1:jetAK4_jec1:jetAK4_muf1:jetAK4_phf1:jetAK4_emf1:jetAK4_nhf1:jetAK4_chf1:jetAK4_area1:jetAK4_cm1:jetAK4_nm1:jetAK4_hof1:jetAK4_chm1:jetAK4_neHadMult1:jetAK4_phoMult1:jetAK4_nemf1:jetAK4_cemf1:jetAK4_csv1:jetAK4_IDTight1:jetAK4_pt2:jetAK4_eta2:jetAK4_y2:jetAK4_phi2:jetAK4_mass2:jetAK4_jec2:jetAK4_muf2:jetAK4_phf2:jetAK4_emf2:jetAK4_nhf2:jetAK4_chf2:jetAK4_area2:jetAK4_cm2:jetAK4_nm2:jetAK4_hof2:jetAK4_chm2:jetAK4_neHadMult2:jetAK4_phoMult2:jetAK4_nemf2:jetAK4_cemf2:jetAK4_csv2:jetAK4_IDTight2:jetAK4_pt3:jetAK4_eta3:jetAK4_y3:jetAK4_phi3:jetAK4_mass3:jetAK4_jec3:jetAK4_muf3:jetAK4_phf3:jetAK4_emf3:jetAK4_nhf3:jetAK4_chf3:jetAK4_area3:jetAK4_cm3:jetAK4_nm3:jetAK4_hof3:jetAK4_chm3:jetAK4_neHadMult3:jetAK4_phoMult3:jetAK4_nemf3:jetAK4_cemf3:jetAK4_csv3:jetAK4_IDTight3:MET_et:MET_sumEt:EVENT_event:EVENT_run:EVENT_lumiBlock:PV_N:mjj:chi:yboost") {
   if(is_mc_) varnames=varnames+":genJetAK4_pt1:genJetAK4_eta1:genJetAK4_y1:genJetAK4_phi1:genJetAK4_mass1:genJetAK4_pt2:genJetAK4_eta2:genJetAK4_y2:genJetAK4_phi2:genJetAK4_mass2:genJetAK4_pt3:genJetAK4_eta3:genJetAK4_y3:genJetAK4_phi3:genJetAK4_mass3:genWeight:nPuVtxTrue:genmjj:genchi:genyboost";
   std::string ending="_tree.root";
   std::cerr << treename+ending << std::endl;
   outfile=new TFile((treename+ending).c_str(),"RECREATE");
   tree=new TNtuple("tree","tree",varnames.c_str());
   tree->Branch("HLT_isFired","map<string,bool>",&HLT_isFired);
   tree->Branch("EVENT",&EVENT,"EVENT/D");
   tree->Branch("RUN",&RUN,"RUN/D");
   tree->Branch("LUMI",&LUMI,"LUMI/D");
}
    
bool DijetSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in

    bool jet1ID=false;
    bool jet2ID=false;
    if(event.jets->size()>0) {
      const auto & j1 = event.jets->at(0);
      jet1.SetPtEtaPhiE( j1.pt(), j1.eta(), j1.phi(), j1.energy() );
      jet1ID=((event.jets->at(0).neutralHadronEnergyFraction()<0.9)&&
	     (event.jets->at(0).neutralEmEnergyFraction()<0.9)&&
	     (event.jets->at(0).numberOfDaughters()>1)&&
	     (event.jets->at(0).muonEnergyFraction()<0.8)&&
	     ((fabs(event.jets->at(0).eta())>2.4)||
	      ((event.jets->at(0).chargedHadronEnergyFraction()>0)&&
	       (event.jets->at(0).chargedMultiplicity()>0)&&
	       (event.jets->at(0).chargedEmEnergyFraction()<0.8))));
	     
    } else { jet1.SetPtEtaPhiM(0,-999.f,-999.f,0); }
    if(event.jets->size()>1) {
      const auto & j2 = event.jets->at(1);
      jet2.SetPtEtaPhiE( j2.pt(), j2.eta(), j2.phi(), j2.energy() );
      jet2ID=((event.jets->at(1).neutralHadronEnergyFraction()<0.9)&&
	     (event.jets->at(1).neutralEmEnergyFraction()<0.9)&&
	     (event.jets->at(1).numberOfDaughters()>1)&&
	     (event.jets->at(1).muonEnergyFraction()<0.8)&&
	     ((fabs(event.jets->at(1).eta())>2.4)||
	      ((event.jets->at(1).chargedHadronEnergyFraction()>0)&&
	       (event.jets->at(1).chargedMultiplicity()>0)&&
	       (event.jets->at(1).chargedEmEnergyFraction()<0.8))));
    } else { jet2.SetPtEtaPhiM(0,-999.f,-999.f,0); }
    dijet=jet1+jet2;

    dijet_mass = dijet.M();
    dijet_chi = exp(fabs(jet1.Rapidity()-jet2.Rapidity()));
    dijet_yboost = fabs(jet1.Rapidity()+jet2.Rapidity())/2.;

    values.clear();

    if(event.jets->size()>0) {
values.insert(values.end(),{event.jets->at(0).pt(),event.jets->at(0).eta(),std::max(std::min(float(event.jets->at(0).v4().Rapidity()),999.f),-999.f),event.jets->at(0).phi(),float(event.jets->at(0).v4().mass()), event.jets->at(0).JEC_factor_raw(),event.jets->at(0).muonEnergyFraction(),event.jets->at(0).photonEnergyFraction(),-999.f,event.jets->at(0).neutralHadronEnergyFraction(), event.jets->at(0).chargedHadronEnergyFraction(),event.jets->at(0).jetArea(),float(event.jets->at(0).chargedMultiplicity()),float(event.jets->at(0).neutralMultiplicity()),-999.f,-999.f,-999.f, float(event.jets->at(0).photonMultiplicity()),event.jets->at(0).neutralEmEnergyFraction(),event.jets->at(0).chargedEmEnergyFraction(),event.jets->at(0).btag_DeepJet(),float(jet1ID)});
    } else {
      values.insert(values.end(),{-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f});
    }

    if(event.jets->size()>1) {
values.insert(values.end(),{event.jets->at(1).pt(),event.jets->at(1).eta(),std::max(std::min(float(event.jets->at(1).v4().Rapidity()),999.f),-999.f),event.jets->at(1).phi(),float(event.jets->at(1).v4().mass()), event.jets->at(1).JEC_factor_raw(),event.jets->at(1).muonEnergyFraction(),event.jets->at(1).photonEnergyFraction(),-999.f,event.jets->at(1).neutralHadronEnergyFraction(), event.jets->at(1).chargedHadronEnergyFraction(),event.jets->at(1).jetArea(),float(event.jets->at(1).chargedMultiplicity()),float(event.jets->at(1).neutralMultiplicity()),-999.f,-999.f,-999.f, float(event.jets->at(1).photonMultiplicity()),event.jets->at(1).neutralEmEnergyFraction(),event.jets->at(1).chargedEmEnergyFraction(),event.jets->at(1).btag_DeepJet(),float(jet2ID)});
    } else {
      values.insert(values.end(),{-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f});
    }

    if(event.jets->size()>2) {
      bool jet3ID=((event.jets->at(2).neutralHadronEnergyFraction()<0.9)&&
	     (event.jets->at(2).neutralEmEnergyFraction()<0.9)&&
	     (event.jets->at(2).numberOfDaughters()>1)&&
	     (event.jets->at(2).muonEnergyFraction()<0.8)&&
	     ((fabs(event.jets->at(2).eta())>2.4)||
	      ((event.jets->at(2).chargedHadronEnergyFraction()>0)&&
	       (event.jets->at(2).chargedMultiplicity()>0)&&
	       (event.jets->at(2).chargedEmEnergyFraction()<0.8))));

      values.insert(values.end(),{event.jets->at(2).pt(),event.jets->at(2).eta(),std::max(std::min(float(event.jets->at(2).v4().Rapidity()),999.f),-999.f),event.jets->at(2).phi(),float(event.jets->at(2).v4().mass()), event.jets->at(2).JEC_factor_raw(),event.jets->at(2).muonEnergyFraction(),event.jets->at(2).photonEnergyFraction(),-999.f,event.jets->at(2).neutralHadronEnergyFraction(), event.jets->at(2).chargedHadronEnergyFraction(),event.jets->at(2).jetArea(),float(event.jets->at(2).chargedMultiplicity()),float(event.jets->at(2).neutralMultiplicity()),-999.f,-999.f,-999.f, float(event.jets->at(2).photonMultiplicity()),event.jets->at(2).neutralEmEnergyFraction(),event.jets->at(2).chargedEmEnergyFraction(),event.jets->at(2).btag_DeepJet(),float(jet3ID)});
    } else {
      values.insert(values.end(),{-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f,-999.f});
    }
    values.insert(values.end(),{event.met->pt(),event.met->sumEt(),float(event.event),float(event.run),float(event.luminosityBlock),float(event.pvs->size()),dijet_mass,std::min(dijet_chi,999.f),std::min(dijet_yboost,999.f)});

    if(is_mc_) {

    assert(event.genjets); // if this fails, it probably means jets are not read in
    if(event.genjets->size()>0) {
      const auto & gj = event.genjets->at(0);
      genjet1.SetPtEtaPhiE( gj.pt(), gj.eta(), gj.phi(), gj.energy() ); } else {
      genjet1.SetPtEtaPhiM(0,-999.f,-999.f,0); }
    if(event.genjets->size()>1) {
      const auto & gj = event.genjets->at(1);
      genjet2.SetPtEtaPhiE( gj.pt(), gj.eta(), gj.phi(), gj.energy() ); } else {
      genjet2.SetPtEtaPhiM(0,-999.f,-999.f,0); }
    if(event.genjets->size()>2) {
      const auto & gj = event.genjets->at(2);
      genjet3.SetPtEtaPhiE( gj.pt(), gj.eta(), gj.phi(), gj.energy() ); } else {
      genjet3.SetPtEtaPhiM(0,-999.f,-999.f,0); }
    gendijet=genjet1+genjet2;

    gendijet_mass = gendijet.M();
    gendijet_chi = exp(fabs(genjet1.Rapidity()-genjet2.Rapidity()));
    gendijet_yboost = fabs(genjet1.Rapidity()+genjet2.Rapidity())/2.;

    values.insert(values.end(),{float(genjet1.Pt()),float(genjet1.Eta()),std::max(std::min(float(genjet1.Rapidity()),999.f),-999.f),float(genjet1.Phi()),float(genjet1.M()),
float(genjet2.Pt()),float(genjet2.Eta()),std::max(std::min(float(genjet2.Rapidity()),999.f),-999.f),float(genjet2.Phi()),float(genjet2.M()),
float(genjet3.Pt()),float(genjet3.Eta()),std::max(std::min(float(genjet3.Rapidity()),999.f),-999.f),float(genjet3.Phi()),float(genjet3.M()),
float(event.weight),event.genInfo->pileup_TrueNumInteractions(),
gendijet_mass,std::min(gendijet_chi,999.f),std::min(gendijet_yboost,999.f)});
 
      if(((event.jets->size() < 2)||(!jet1ID)||(!jet2ID)||(dijet_chi>chi_max_)||(dijet_mass<mjj_min_)||(dijet_yboost>yboost_max_))
         &&((event.genjets->size() < 2)||(gendijet_chi>chi_max_)||(gendijet_mass<mjj_min_)||(gendijet_yboost>yboost_max_))) return false;
    } else {
      if((event.jets->size() < 2)||(!jet1ID)||(!jet2ID)||(dijet_chi>chi_max_)||(dijet_mass<mjj_min_)||(dijet_yboost>yboost_max_)) return false;
    }

    HLT_isFired.clear();
    for(auto triggername : event.get_current_triggernames()) {
	Event::TriggerIndex triggerIndex=event.get_trigger_index(triggername);
        HLT_isFired[triggername]=event.passes_trigger(triggerIndex);
    }
    EVENT = event.event; // double precision
    RUN = event.run;
    LUMI = event.luminosityBlock;

    tree->Fill(&values[0]);

    return true;
}

DijetSelection::~DijetSelection() {
  outfile->Write();
  delete tree;
  delete outfile;
}
