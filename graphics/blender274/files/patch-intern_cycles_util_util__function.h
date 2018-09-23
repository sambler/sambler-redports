--- intern/cycles/util/util_function.h.orig	2018-06-26 02:33:44 UTC
+++ intern/cycles/util/util_function.h
@@ -17,14 +17,33 @@
 #ifndef __UTIL_FUNCTION_H__
 #define __UTIL_FUNCTION_H__
 
-#include <boost/bind.hpp>
-#include <boost/function.hpp>
+#if (__cplusplus > 199711L) || (defined(_MSC_VER) && _MSC_VER >= 1800)
+#  include <functional>
+#else
+#  include <boost/bind.hpp>
+#  include <boost/function.hpp>
+#endif
 
 CCL_NAMESPACE_BEGIN
 
+#if (__cplusplus > 199711L) || (defined(_MSC_VER) && _MSC_VER >= 1800)
+#  define function_bind std::bind
+#  define function_null nullptr
+using std::function;
+using std::placeholders::_1;
+using std::placeholders::_2;
+using std::placeholders::_3;
+using std::placeholders::_4;
+using std::placeholders::_5;
+using std::placeholders::_6;
+using std::placeholders::_7;
+using std::placeholders::_8;
+using std::placeholders::_9;
+#else
 using boost::function;
-#define function_bind boost::bind
-
+#  define function_bind boost::bind
+#  define function_null NULL
+#endif
 CCL_NAMESPACE_END
 
 #endif /* __UTIL_FUNCTION_H__ */
