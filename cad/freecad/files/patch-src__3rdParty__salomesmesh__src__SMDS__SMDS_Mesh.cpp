--- ./src/3rdParty/salomesmesh/src/SMDS/SMDS_Mesh.cpp.orig	2014-07-14 01:03:02.000000000 +0930
+++ ./src/3rdParty/salomesmesh/src/SMDS/SMDS_Mesh.cpp	2014-07-29 14:42:02.869399981 +0930
@@ -47,6 +47,7 @@
 #include <sys/sysinfo.h>
 #endif
 #endif
+#include <sys/wait.h>
 
 // number of added entitis to check memory after
 #define CHECKMEMORY_INTERVAL 1000
