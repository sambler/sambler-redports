--- intern/cycles/util/util_path.cpp.orig	2013-02-07 19:56:43.615857497 +1030
+++ intern/cycles/util/util_path.cpp	2013-02-07 19:58:48.211857059 +1030
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
