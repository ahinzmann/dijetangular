import os
for i in range(100):
 for f in ["dijetChiRun2017_RunB_17Nov2017-v1.root",
               "dijetChiRun2017_RunC_17Nov2017-v1.root",
               "dijetChiRun2017_RunD_17Nov2017-v1.root",
               "dijetChiRun2017_RunE_17Nov2017-v1.root",
               "dijetChiRun2017_RunF_17Nov2017-v1.root",
               ]:
  print "rooteventselector --recreate -f "+str(i*1000000+1)+" -l "+str((i+1)*1000000)+" "+f+":tree "+f.replace("v1","v1-"+str(i))
