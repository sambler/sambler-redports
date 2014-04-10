--- ./intern/cycles/util/util_cache.cpp.orig	2012-05-11 00:14:09.000000000 +0930
+++ ./intern/cycles/util/util_cache.cpp	2014-04-09 20:59:24.207217370 +0930
@@ -26,7 +26,11 @@
 #include "util_path.h"
 #include "util_types.h"
 
+#include <boost/version.hpp>
+
+#if (BOOST_VERSION < 104400)
 #define BOOST_FILESYSTEM_VERSION 2
+#endif
 
 #include <boost/filesystem.hpp> 
 #include <boost/algorithm/string.hpp>
@@ -117,7 +121,11 @@
 		boost::filesystem::directory_iterator it(dir), it_end;
 
 		for(; it != it_end; it++) {
+#if BOOST_FILESYSTEM_VERSION == 2
 			string filename = it->path().filename();
+#else
+			string filename = it->path().filename().string();
+#endif
 
 			if(boost::starts_with(filename, name))
 				if(except.find(filename) == except.end())
