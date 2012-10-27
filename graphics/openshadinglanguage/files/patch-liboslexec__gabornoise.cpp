--- ./liboslexec/gabornoise.cpp.orig	2012-08-31 06:58:32.000000000 +0930
+++ ./liboslexec/gabornoise.cpp	2012-10-27 15:54:13.741663728 +1030
@@ -67,7 +67,7 @@
     }
     // Return uniform on [0,1)
     float operator() () {
-        return (m_seed *= 3039177861) / float(UINT_MAX);
+        return (m_seed *= 3039177861u) / float(UINT_MAX);
     }
     // Return poisson distribution with the given mean
     int poisson (float mean) {
