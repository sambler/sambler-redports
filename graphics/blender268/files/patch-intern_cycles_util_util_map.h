--- intern/cycles/util/util_map.h.orig	2017-08-06 12:06:47 UTC
+++ intern/cycles/util/util_map.h
@@ -18,13 +18,14 @@
 #define __UTIL_MAP_H__
 
 #include <map>
-#include <boost/tr1/unordered_map.hpp>
+#include <unordered_map>
 
 CCL_NAMESPACE_BEGIN
 
 using std::map;
 using std::pair;
-using std::tr1::unordered_map;
+#define CYCLES_STD_UNORDERED_MAP 1
+using std::unordered_map;
 
 CCL_NAMESPACE_END
 
