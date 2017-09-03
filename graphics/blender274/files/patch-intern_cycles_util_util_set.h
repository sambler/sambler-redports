--- intern/cycles/util/util_set.h.orig	2017-08-06 12:06:41 UTC
+++ intern/cycles/util/util_set.h
@@ -18,12 +18,12 @@
 #define __UTIL_SET_H__
 
 #include <set>
-#include <boost/tr1/unordered_set.hpp>
+#include <unordered_set>
 
 CCL_NAMESPACE_BEGIN
 
 using std::set;
-using std::tr1::unordered_set;
+using std::unordered_set;
 
 CCL_NAMESPACE_END
 
