import os
for i in range(100):
 for f in ["dijetChiRun2016_RunB_RunII_102X-v1.root",
               "dijetChiRun2016_RunC_RunII_102X-v1.root",
               "dijetChiRun2016_RunD_RunII_102X-v1.root",
               "dijetChiRun2016_RunE_RunII_102X-v1.root",
	       "dijetChiRun2016_RunF_RunII_102X-v1.root",	       
	       "dijetChiRun2016_RunG_RunII_102X-v1.root",	       
	       "dijetChiRun2016_RunH_RunII_102X-v1.root",	       
               ]:
  print "rooteventselector --recreate -f "+str(i*1000000+1)+" -l "+str((i+1)*1000000)+" "+f+":tree "+f.replace("v1","v1-"+str(i))
