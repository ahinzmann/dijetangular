import os
for f in ["dijetChiRun2018_RunA_RunII_102X_v1",
               "dijetChiRun2018_RunB_RunII_102X_v1",
               "dijetChiRun2018_RunC_RunII_102X_v1",
	       "dijetChiRun2018_RunD_RunII_102X_v1"	       
               ]:
 mult=40
 for i in range(5000/mult):
  files=""
  for j in range(mult):
   files+=" workdir/"+f+"_"+str(i*mult+j)+"_tree.root"
  print "hadd -f -k "+f+"-"+str(i)+".root"+files
