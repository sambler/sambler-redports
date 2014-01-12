--- ./extern/carve/lib/triangulator.cpp.orig	2012-01-30 19:15:12.000000000 +1030
+++ ./extern/carve/lib/triangulator.cpp	2014-01-12 20:22:52.843779394 +1030
@@ -27,6 +27,18 @@
 
 #include <algorithm>
 
+// Indicates whether __is_heap is available
+#undef HAVE_IS_HEAP
+
+#ifdef __GNUC__
+// NeyBSD doesn't have __is_heap
+#  ifndef __NetBSD__
+#    define HAVE_IS_HEAP
+#    ifdef _LIBCPP_VERSION
+#      define __is_heap is_heap
+#    endif  // _LIBCPP_VERSION
+#  endif  // !__NetBSD__
+#endif  // __GNUC__
 
 namespace {
   // private code related to hole patching.
@@ -122,8 +134,8 @@
     std::vector<vertex_info *> queue;
 
     void checkheap() {
-#ifdef __GNUC__
-      CARVE_ASSERT(std::__is_heap(queue.begin(), queue.end(), vertex_info_ordering()));
+#if defined(HAVE_IS_HEAP)
+       CARVE_ASSERT(std::__is_heap(queue.begin(), queue.end(), vertex_info_ordering()));
 #endif
     }
 
