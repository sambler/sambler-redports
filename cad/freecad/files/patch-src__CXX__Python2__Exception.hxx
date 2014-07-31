--- ./src/CXX/Python2/Exception.hxx.orig	2014-07-14 01:03:02.000000000 +0930
+++ ./src/CXX/Python2/Exception.hxx	2014-07-29 14:42:03.564400466 +0930
@@ -44,6 +44,15 @@
 #include "CXX/IndirectPythonInterface.hxx"
 
 #include <string>
+
+#undef toupper
+#undef tolower
+#undef isupper
+#undef islower
+#undef isspace
+#undef isalpha
+#undef isalnum
+
 #include <iostream>
 
 // This mimics the Python structure, in order to minimize confusion
