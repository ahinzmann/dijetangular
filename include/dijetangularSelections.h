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
    DijetSelection(std::string treename="dijetangular", bool is_mc = false, float chi_max = 16, float yboost_max = 1.11, float mjj_min = 1000.);
    virtual bool passes(const uhh2::Event & event) override;
    ~DijetSelection();
private:
    float chi_max_, yboost_max_, mjj_min_;

    float weight_;
    float lheweight_;
    float puweight_;
    float lumiweight_;
    bool is_mc_;
    bool passedTrigger_;

    float dijet_mass;
    float dijet_chi;
    float dijet_yboost;
    float gendijet_mass;
    float gendijet_chi;
    float gendijet_yboost;
    TLorentzVector jet1, jet2, genjet1, genjet2, genjet3, dijet, gendijet;
    
    std::string varnames;
    std::vector<float> values;
    std::map<std::string,bool> HLT_isFired;
    double EVENT;
    double RUN;
    double LUMI;
    
    TFile* outfile;
    TNtuple* tree;
};


}
