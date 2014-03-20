--- ./extern/carve/include/carve/mesh_ops.hpp.orig	2014-03-05 07:25:21.726191870 +1030
+++ ./extern/carve/include/carve/mesh_ops.hpp	2014-03-05 07:25:51.856186891 +1030
@@ -24,6 +24,26 @@
 #include <iostream>
 #include <fstream>
 
+// Support for latest Clang/LLVM on FreeBSD which does have different libcxx.
+//
+// copied from lib/triangulator.cpp
+//
+// TODO(sergey): Move it some some more generic header with platform-specific
+//               declarations.
+
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
+
 namespace carve {
   namespace mesh {
     namespace detail {
@@ -580,7 +600,7 @@
           std::vector<VertexInfo *> queue;
 
           void checkheap() {
-#ifdef __GNUC__
+#if defined(HAVE_IS_HEAP)
             CARVE_ASSERT(std::__is_heap(queue.begin(), queue.end(), order_by_score()));
 #endif
           }
