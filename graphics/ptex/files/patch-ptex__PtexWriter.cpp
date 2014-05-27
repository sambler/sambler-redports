--- ./ptex/PtexWriter.cpp.orig	2014-05-27 14:01:14.677938262 +0930
+++ ./ptex/PtexWriter.cpp	2014-05-27 14:01:17.778535863 +0930
@@ -66,6 +66,7 @@
 #include <algorithm>
 #include <iostream>
 #include <sstream>
+#include <unistd.h>
 
 #include "Ptexture.h"
 #include "PtexUtils.h"
