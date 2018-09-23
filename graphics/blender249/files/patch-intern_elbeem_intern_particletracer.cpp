--- intern/elbeem/intern/particletracer.cpp.orig	2018-09-11 18:24:58 UTC
+++ intern/elbeem/intern/particletracer.cpp
@@ -231,7 +231,7 @@ void ParticleTracer::checkDumpTextPositi
 		if(mDumpTextFile.length()>1) {   
 			boutfilename << mDumpTextFile <<  ".cpart2"; 
 		} else {                           
-			boutfilename << boutfilename <<"_particles" <<  ".cpart2"; 
+			boutfilename << "_particles" <<  ".cpart2"; 
 		}
 		debMsgStd("ParticleTracer::checkDumpTextPositions",DM_MSG,"T-Dumping: "<< this->getName() <<", particles:"<<mParts.size()<<" "<< " to "<<boutfilename.str()<<" " , 7);
 
