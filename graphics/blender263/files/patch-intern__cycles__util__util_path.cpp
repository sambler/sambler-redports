--- ./intern/cycles/util/util_path.cpp.orig	2012-05-11 00:14:09.000000000 +0930
+++ ./intern/cycles/util/util_path.cpp	2014-04-09 20:59:24.208216528 +0930
@@ -26,7 +26,11 @@
 
 #include <stdio.h>
 
+#include <boost/version.hpp>
+
+#if (BOOST_VERSION < 104400)
 #define BOOST_FILESYSTEM_VERSION 2
+#endif
 
 #include <boost/filesystem.hpp> 
 #include <boost/algorithm/string.hpp>
@@ -60,7 +64,11 @@
 
 string path_filename(const string& path)
 {
+#if BOOST_FILESYSTEM_VERSION == 2
 	return boost::filesystem::path(path).filename();
+#else
+	return boost::filesystem::path(path).filename().string();
+#endif
 }
 
 string path_dirname(const string& path)
