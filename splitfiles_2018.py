import os
for i in range(100):
 for f in ["dijetChiRun2018_RunA_RunII_102X-v1.root",
               "dijetChiRun2018_RunB_RunII_102X-v1.root",
               "dijetChiRun2018_RunC_RunII_102X-v1.root",
               "dijetChiRun2018_RunD1_RunII_102X-v1.root",
	       "dijetChiRun2018_RunD2_RunII_102X-v1.root"	       
               ]:
  print "rooteventselector --recreate -f "+str(i*1000000+1)+" -l "+str((i+1)*1000000)+" "+f+":tree "+f.replace("v1","v1-"+str(i))
