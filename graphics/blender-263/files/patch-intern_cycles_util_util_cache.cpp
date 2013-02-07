--- intern/cycles/util/util_cache.cpp.orig	2013-02-07 19:48:19.105857414 +1030
+++ intern/cycles/util/util_cache.cpp	2013-02-07 19:54:34.782860147 +1030
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
