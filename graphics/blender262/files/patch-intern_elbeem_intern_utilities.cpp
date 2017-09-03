--- intern/elbeem/intern/utilities.cpp.orig	2017-09-01 13:49:58 UTC
+++ intern/elbeem/intern/utilities.cpp
@@ -51,7 +51,7 @@ int  getElbeemState(void) { 
 	return gElbeemState;
 }
 int  isSimworldOk(void) {
-	return (getElbeemState>=0);
+	return (getElbeemState()>=0);
 }
 
 // last error as string, acces with get/setElbeemErrorString
