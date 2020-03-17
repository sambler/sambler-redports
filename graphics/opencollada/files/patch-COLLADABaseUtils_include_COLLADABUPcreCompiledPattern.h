--- COLLADABaseUtils/include/COLLADABUPcreCompiledPattern.h.orig	2018-12-02 20:01:55 UTC
+++ COLLADABaseUtils/include/COLLADABUPcreCompiledPattern.h
@@ -13,8 +13,7 @@
 
 #include "COLLADABUPrerequisites.h"
 
-struct real_pcre;
-typedef struct real_pcre pcre;
+#include "pcre.h"

 
 namespace COLLADABU
