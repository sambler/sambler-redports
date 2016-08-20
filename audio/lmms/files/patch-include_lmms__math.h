--- include/lmms_math.h.orig	2016-02-17 05:57:44 UTC
+++ include/lmms_math.h
@@ -26,6 +26,7 @@
 #ifndef LMMS_MATH_H
 #define LMMS_MATH_H
 
+#include <math.h>
 #include <stdint.h>
 #include "lmms_constants.h"
 #include "lmmsconfig.h"
@@ -34,7 +35,6 @@
 #include <cmath>
 using namespace std;
 
-#if defined (LMMS_BUILD_WIN32) || defined (LMMS_BUILD_APPLE) || defined(LMMS_BUILD_HAIKU)  || defined (__FreeBSD__)
 #ifndef isnanf
 #define isnanf(x)	isnan(x)
 #endif
@@ -53,7 +53,6 @@ using namespace std;
 #ifndef exp10f
 #define exp10f(x) powf( 10.0f, x )
 #endif
-#endif
 
 #ifdef __INTEL_COMPILER
 
