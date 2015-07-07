--- extern/libmv/third_party/ceres/internal/ceres/collections_port.h.orig	2013-02-25 08:59:26 UTC
+++ extern/libmv/third_party/ceres/internal/ceres/collections_port.h
@@ -33,11 +33,12 @@
 #ifndef CERES_INTERNAL_COLLECTIONS_PORT_H_
 #define CERES_INTERNAL_COLLECTIONS_PORT_H_
 
+#include <utility>
 #if defined(CERES_NO_TR1)
 #  include <map>
 #  include <set>
 #else
-#  if defined(_MSC_VER)
+#  if defined(_MSC_VER) || defined(_LIBCPP_VERSION)
 #    include <unordered_map>
 #    include <unordered_set>
 #  else
@@ -45,7 +46,6 @@
 #    include <tr1/unordered_set>
 #  endif
 #endif
-#include <utility>
 #include "ceres/integral_types.h"
 #include "ceres/internal/port.h"
 
@@ -71,11 +71,19 @@ struct HashSet : set<K> {};
 namespace ceres {
 namespace internal {
 
+#if defined(_LIBCPP_VERSION)
+template<typename K, typename V>
+struct HashMap : std::unordered_map<K, V> {};
+
+template<typename K>
+struct HashSet : std::unordered_set<K> {};
+#else
 template<typename K, typename V>
 struct HashMap : std::tr1::unordered_map<K, V> {};
 
 template<typename K>
 struct HashSet : std::tr1::unordered_set<K> {};
+#endif
 
 #if defined(_WIN32) && !defined(__MINGW64__) && !defined(__MINGW32__)
 #define GG_LONGLONG(x) x##I64
@@ -135,7 +143,11 @@ inline uint64 Hash64NumWithSeed(uint64 n
 
 // Since on some platforms this is a doubly-nested namespace (std::tr1) and
 // others it is not, the entire namespace line must be in a macro.
+#if defined(_LIBCPP_VERSION)
+namespace std {
+#else
 CERES_HASH_NAMESPACE_START
+#endif
 
 // The outrageously annoying specializations below are for portability reasons.
 // In short, it's not possible to have two overloads of hash<pair<T1, T2>
@@ -160,7 +172,11 @@ struct hash<pair<T, T> > {
   static const size_t min_buckets = 8;  // 4 and 8 are defaults.
 };
 
+#if defined(_LIBCPP_VERSION)
+}
+#else
 CERES_HASH_NAMESPACE_END
+#endif
 
 #endif  // CERES_NO_TR1
 
