import os
for f in ["dijetChiUL18_RunA_RunII_106X_v1",
               "dijetChiUL18_RunB_RunII_106X_v1",
               "dijetChiUL18_RunC_RunII_106X_v1",
	       "dijetChiUL18_RunD_RunII_106X_v1"	       
               ]:
 mult=40
 for i in range(5000/mult):
  files=""
  for j in range(mult):
   files+=" workdir/"+f+"_"+str(i*mult+j)+"_tree.root"
  print "hadd -f -k "+f+"-"+str(i)+".root"+files
