--- ./src/include/OpenImageIO/image_view.h.orig	2014-05-21 14:38:59.403229714 +0930
+++ ./src/include/OpenImageIO/image_view.h	2014-05-21 14:47:08.794229733 +0930
@@ -32,13 +32,27 @@
 
 #pragma once
 
-#ifndef __STDC_LIMIT_MACROS
-# define __STDC_LIMIT_MACROS  /* needed for some defs in stdint.h */
-#endif
-
 #include <vector>
 #include <stdexcept>
-#include <stdint.h>
+
+// We're including stdint.h to get int64_t and INT64_MIN. But on some
+// platforms, stdint.h only defines them if __STDC_LIMIT_MACROS is defined,
+// so we do so. But, oops, if user code included stdint.h before this file,
+// and without defining the macro, it may have had ints one and only include
+// and not seen the definitions we need, so at least try to make a helpful
+// compile-time error in that case.
+// And very old MSVC 9 versions don't even have stdint.h.
+#if defined(_MSC_VER) && _MSC_VER < 1600
+   typedef __int64 int64_t;
+#else
+#  ifndef __STDC_LIMIT_MACROS
+#    define __STDC_LIMIT_MACROS  /* needed for some defs in stdint.h */
+#  endif
+#  include <stdint.h>
+#  if ! defined(INT64_MIN)
+#    error You must define __STDC_LIMIT_MACROS prior to including stdint.h
+#  endif
+#endif
 
 #include "oiioversion.h"
 #include "strided_ptr.h"
@@ -59,7 +73,12 @@
     typedef T& reference;
     typedef const T& const_reference;
     typedef int64_t stride_t;
+#ifdef INT64_MIN
     static const stride_t AutoStride = INT64_MIN;
+#else
+    // Some systems don't have INT64_MIN defined. Sheesh.
+    static const stride_t AutoStride = (-9223372036854775807LL-1)
+#endif
 
     /// Default ctr -- points to nothing
     image_view () { init(); }
@@ -74,8 +93,8 @@
     /// bytes).
     image_view (T *data, int nchannels,
               int width, int height, int depth=1,
-              ptrdiff_t chanstride=AutoStride, ptrdiff_t xstride=AutoStride,
-              ptrdiff_t ystride=AutoStride, ptrdiff_t zstride=AutoStride) {
+              stride_t chanstride=AutoStride, stride_t xstride=AutoStride,
+              stride_t ystride=AutoStride, stride_t zstride=AutoStride) {
         init (data, nchannels, width, height, depth,
               chanstride, xstride, ystride, zstride);
     }
@@ -101,10 +120,10 @@
     int height() const { return m_height; }
     int depth() const { return m_depth; }
 
-    ptrdiff_t chanstride() const { return m_chanstride; }
-    ptrdiff_t xstride() const { return m_xstride; }
-    ptrdiff_t ystride() const { return m_ystride; }
-    ptrdiff_t zstride() const { return m_zstride; }
+    stride_t chanstride() const { return m_chanstride; }
+    stride_t xstride() const { return m_xstride; }
+    stride_t ystride() const { return m_ystride; }
+    stride_t zstride() const { return m_zstride; }
 
     const T* data() const { return m_data; }
 
@@ -113,12 +132,12 @@
 private:
     const T * m_data;
     int m_nchannels, m_width, m_height, m_depth;
-    ptrdiff_t m_chanstride, m_xstride, m_ystride, m_zstride;
+    stride_t m_chanstride, m_xstride, m_ystride, m_zstride;
 
     void init (T *data, int nchannels,
                int width, int height, int depth=1,
-               ptrdiff_t chanstride=AutoStride, ptrdiff_t xstride=AutoStride,
-               ptrdiff_t ystride=AutoStride, ptrdiff_t zstride=AutoStride) {
+               stride_t chanstride=AutoStride, stride_t xstride=AutoStride,
+               stride_t ystride=AutoStride, stride_t zstride=AutoStride) {
         m_data = data;
         m_nchannels = nchannels;
         m_width = width;  m_height = height;  m_depth = depth;
