--- ./plugins/LadspaEffect/calf/src/organ.cpp.orig	2014-09-01 04:44:58.419454872 +0930
+++ ./plugins/LadspaEffect/calf/src/organ.cpp	2014-09-01 04:45:13.962454715 +0930
@@ -21,6 +21,7 @@
 #include <config.h>
 
 #include <calf/giface.h>
+#include <calf/fixed_point.h>
 #include <calf/organ.h>
 #include <iostream>
 
