import os
for f in ["dijetChiRun2016_RunB_RunII_102X_v1",
               "dijetChiRun2016_RunC_RunII_102X_v1",
               "dijetChiRun2016_RunD_RunII_102X_v1",
               "dijetChiRun2016_RunE_RunII_102X_v1",
	       "dijetChiRun2016_RunF_RunII_102X_v1",		  
	       "dijetChiRun2016_RunG_RunII_102X_v1",		  
	       "dijetChiRun2016_RunH_RunII_102X_v1",		  
               ]:
 mult=40
 for i in range(2000/mult):
  files=""
  for j in range(mult):
   files+=" workdir/"+f+"_"+str(i*mult+j)+"_tree.root"
  print "hadd -f -k "+f+"-"+str(i)+".root"+files
