--- ./extern/eltopo/common/predicates.cpp.orig	2013-11-18 16:19:19.000000000 +1030
+++ ./extern/eltopo/common/predicates.cpp	2013-11-18 16:27:03.000000000 +1030
@@ -8,7 +8,7 @@
 
 static void print_hex( double d )
 {
-    std::_Ios_Fmtflags originalFlags = std::cout.flags();
+    std::ios_base::fmtflags originalFlags = std::cout.flags();
     
     assert( sizeof(double) == 2 * sizeof(long int) );
     
