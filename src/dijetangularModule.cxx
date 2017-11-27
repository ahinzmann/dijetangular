#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/dijetangular/include/dijetangularSelections.h"
#include "UHH2/dijetangular/include/dijetangularHists.h"
#include "TLorentzVector.h"

using namespace std;
using namespace uhh2;

namespace uhh2examples {

/** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
 * 
 * This is the central class which calls other AnalysisModules, Hists or Selection classes.
 * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
 */
class dijetangularModule: public AnalysisModule {
public:
    
    explicit dijetangularModule(Context & ctx);
    virtual bool process(Event & event) override;

private:
    
    std::unique_ptr<CommonModules> common;
    
    //std::unique_ptr<JetCleaner> jetcleaner;
   
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.
    std::unique_ptr<Selection> dijet_sel;
    
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_nocuts, h_dijet;
};


dijetangularModule::dijetangularModule(Context & ctx) {
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    // If needed, access the configuration of the module here, e.g.:
    string postfix = ctx.get("PostFix", "");
    cout << "PostFix in the configuration was: " << postfix << endl;
    
    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    for(auto & kv : ctx.get_all()){
        cout << " " << kv.first << " = " << kv.second << endl;
    }
    
    // 1. setup other modules. CommonModules and the JetCleaner:
    common.reset(new CommonModules());
    // TODO: configure common here, e.g. by 
    // calling common->set_*_id or common->disable_*
    common->disable_jetpfidfilter();
    common->init(ctx);
    //jetcleaner.reset(new JetCleaner(ctx, 30.0, 2.4)); 
    
    // note that the JetCleaner is only kept for the sake of example;
    // instead of constructing a jetcleaner explicitly,
    // the cleaning can also be achieved with less code via CommonModules with:
    // common->set_jet_id(PtEtaCut(30.0, 2.4));
    // before the 'common->init(ctx)' line.
    
    // 2. set up selections
    dijet_sel.reset(new DijetSelection("dijetChi"+postfix)); // see dijetangularSelections

    // 3. Set up Hists classes:
    //h_nocuts.reset(new dijetangularHists(ctx, "NoCuts"));
    h_dijet.reset(new dijetangularHists(ctx, "Dijet"));
}


bool dijetangularModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    
    cout << "dijetangularModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;
    
    // 1. run all modules other modules.
    bool pass_cm = common->process(event);
    if(!pass_cm) std::cout << "Event rejected by common modules" << std::endl;
    
    bool dijet_selection = ((pass_cm) && (dijet_sel->passes(event)));
    if(dijet_selection){
        h_dijet->fill(event);
    }
    // 2. decide whether or not to keep the current event in the output:
    return dijet_selection;
}

// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the dijetangularModule is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(dijetangularModule)

}
