import os
for f in ["dijetChiUL17_RunB_RunII_106X_v1",
               "dijetChiUL17_RunC_RunII_106X_v1",
               "dijetChiUL17_RunD_RunII_106X_v1",
               "dijetChiUL17_RunE_RunII_106X_v1",
               "dijetChiUL17_RunF_RunII_106X_v1",
               ]:
 mult=40
 for i in range(2000/mult):
  files=""
  for j in range(mult):
   files+=" workdir/"+f+"_"+str(i*mult+j)+"_tree.root"
  print "hadd -f -k "+f+"-"+str(i)+".root"+files
