import os
for f in ["dijetChiUL16preVFP_RunB_ver1_RunII_106X_v1",
               "dijetChiUL16preVFP_RunB_ver2_RunII_106X_v1",
               "dijetChiUL16preVFP_RunC_RunII_106X_v1",
               "dijetChiUL16preVFP_RunD_RunII_106X_v1",
	       "dijetChiUL16preVFP_RunE_RunII_106X_v1",		  
	       "dijetChiUL16preVFP_RunF_HIPM_RunII_106X_v1",		  
               ]:
 mult=40
 for i in range(2000/mult):
  files=""
  for j in range(mult):
   files+=" workdir/"+f+"_"+str(i*mult+j)+"_tree.root"
  print "hadd -f -k "+f+"-"+str(i)+".root"+files
