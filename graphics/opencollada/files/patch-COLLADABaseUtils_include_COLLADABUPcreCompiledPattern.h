--- COLLADABaseUtils/include/COLLADABUPcreCompiledPattern.h.orig	2018-06-01 01:57:47 UTC
+++ COLLADABaseUtils/include/COLLADABUPcreCompiledPattern.h
@@ -13,8 +13,8 @@
 
 #include "COLLADABUPrerequisites.h"
 
-struct real_pcre;
-typedef struct real_pcre pcre;
+struct real_pcre8_or_16;
+typedef struct real_pcre8_or_16 pcre;
 
 
 namespace COLLADABU
