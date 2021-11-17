import os
for f in ["dijetChiUL16postVFP_RunF_RunII_106X_v1",		  
	       "dijetChiUL16postVFP_RunG_RunII_106X_v1",		  
	       "dijetChiUL16postVFP_RunH_RunII_106X_v1",		  
               ]:
 mult=40
 for i in range(2000/mult):
  files=""
  for j in range(mult):
   files+=" workdir/"+f+"_"+str(i*mult+j)+"_tree.root"
  print "hadd -f -k "+f+"-"+str(i)+".root"+files
