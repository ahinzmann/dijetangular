# dijetangular

run the analysis and copy the data:

sframe_main config/dijetangular.xml

cd /nfs/dust/cms/user/hinzmann/dijetangular

sframe_batch.py /afs/desy.de/user/h/hinzmann/uhh102/CMSSW_10_2_10/src/UHH2/dijetangular/config/dijetangular_YEAR.xml -s

python /afs/desy.de/user/h/hinzmann/uhh102/CMSSW_10_2_10/src/UHH2/dijetangular/add_samples_YEAR.py

source /afs/desy.de/user/h/hinzmann/uhh102/CMSSW_10_2_10/src/UHH2/dijetangular/add_samples_YEAR.sh

python /afs/desy.de/user/h/hinzmann/uhh102/CMSSW_10_2_10/src/UHH2/dijetangular/splitfiles_YEAR.py

source /afs/desy.de/user/h/hinzmann/uhh102/CMSSW_10_2_10/src/UHH2/dijetangular/copy-to-dcache-YEAR.sh

kinit -l 1094 hinzmann@CERN.CH
xrdcp dijetChiRun2017_*v1-* root://eosuser.cern.ch//eos/user/h/hinzmann/dijetangular/

#scp dijetChiRun2017_Run* lxplus.cern.ch:/afs/cern.ch/work/h/hinzmann/public/forJingyu/data2017
