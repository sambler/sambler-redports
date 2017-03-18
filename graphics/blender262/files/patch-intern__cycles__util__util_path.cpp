--- ./intern/cycles/util/util_path.cpp.orig	2013-10-14 16:20:15 UTC
+++ ./intern/cycles/util/util_path.cpp
@@ -26,7 +26,11 @@
 
 #include <stdio.h>
 
-#define BOOST_FILESYSTEM_VERSION 2
+#include <boost/version.hpp>
+
+#if (BOOST_VERSION < 104400)
+# define BOOST_FILESYSTEM_VERSION 2
+#endif
 
 #include <boost/filesystem.hpp> 
 #include <boost/algorithm/string.hpp>
@@ -60,7 +64,11 @@
 
 string path_filename(const string& path)
 {
+#if (BOOST_FILESYSTEM_VERSION == 2)
 	return boost::filesystem::path(path).filename();
+#else
+	return boost::filesystem::path(path).filename().string();
+#endif
 }
 
 string path_dirname(const string& path)
