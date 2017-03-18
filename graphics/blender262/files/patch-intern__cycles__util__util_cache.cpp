--- ./intern/cycles/util/util_cache.cpp.orig	2013-10-14 16:20:33 UTC
+++ ./intern/cycles/util/util_cache.cpp
@@ -26,7 +26,11 @@
 #include "util_path.h"
 #include "util_types.h"
 
-#define BOOST_FILESYSTEM_VERSION 2
+#include <boost/version.hpp>
+
+#if (BOOST_VERSION < 104400)
+# define BOOST_FILESYSTEM_VERSION 2
+#endif
 
 #include <boost/filesystem.hpp> 
 #include <boost/algorithm/string.hpp>
@@ -117,7 +121,11 @@
 		boost::filesystem::directory_iterator it(dir), it_end;
 
 		for(; it != it_end; it++) {
+#if (BOOST_FILESYSTEM_VERSION == 2)
 			string filename = it->path().filename();
+#else
+			string filename = it->path().filename().string();
+#endif
 
 			if(boost::starts_with(filename, name))
 				if(except.find(filename) == except.end())
