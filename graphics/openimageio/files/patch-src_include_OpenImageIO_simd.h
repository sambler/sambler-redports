--- src/include/OpenImageIO/simd.h.orig	2015-03-13 05:24:56 UTC
+++ src/include/OpenImageIO/simd.h
@@ -1120,10 +1120,10 @@ OIIO_FORCEINLINE int4 blend0 (const int4
 #if defined(OIIO_SIMD_SSE)
     return _mm_and_si128(_mm_castps_si128(mask), a.simd());
 #else
-    return int4 (mask[0] & a[0],
-                 mask[1] & a[1],
-                 mask[2] & a[2],
-                 mask[3] & a[3]);
+    return int4 (mask[0] ? a[0] : 0.0f,
+                 mask[1] ? a[1] : 0.0f,
+                 mask[2] ? a[2] : 0.0f,
+                 mask[3] ? a[3] : 0.0f);
 #endif
 }
 
@@ -1647,10 +1647,12 @@ public:
     float4 xyz0 () const {
 #if defined(OIIO_SIMD_SSE) && OIIO_SIMD_SSE >= 4
         return _mm_insert_ps (m_vec, _mm_set_ss(0.0f), 3<<4);
-#else
+#elif defined(OIIO_SIMD_SSE) /* SSE2 */
         float4 tmp = m_vec;
         tmp[3] = 0.0f;
         return tmp;
+#else
+        return float4 (m_val[0], m_val[1], m_val[2], 0.0f);
 #endif
     }
 
