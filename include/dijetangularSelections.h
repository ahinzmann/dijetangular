#pragma once

#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/core/include/Event.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TNtuple.h"
#include <map>
#include <string>

namespace uhh2examples {
    
/* Select events with at least two jets
 */
class DijetSelection: public uhh2::Selection {
public:
    DijetSelection(std::string treename="dijetangular", float chi_max = 16, float yboost_max = 1.11, float mjj_min = 1000.);
    virtual bool passes(const uhh2::Event & event) override;
    ~DijetSelection();
private:
    float chi_max_, yboost_max_, mjj_min_;

    float weight_;
    float lheweight_;
    float puweight_;
    float lumiweight_;
    bool passedTrigger_;

    float dijet_mass;
    float dijet_chi;
    float dijet_yboost;
    TLorentzVector jet1, jet2, dijet;
    
    std::string varnames;
    std::vector<float> values;
    std::map<std::string,bool> HLT_isFired;
    
    TFile* outfile;
    TNtuple* tree;
};


}
