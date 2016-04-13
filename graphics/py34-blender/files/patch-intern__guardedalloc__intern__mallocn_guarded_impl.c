--- intern/guardedalloc/intern/mallocn_guarded_impl.c.orig	2014-09-12 05:52:44 UTC
+++ intern/guardedalloc/intern/mallocn_guarded_impl.c
@@ -117,6 +117,13 @@
 	short alignment;  /* if non-zero aligned alloc was used
 	                   * and alignment is stored here.
 	                   */
+#if defined(__x86_64__)
+    /* pad to get sizeof as multiples of 16 to keep alignment
+     * as the byte after this struct is the ptr used for data
+     */
+    char pad[8];
+#endif
+
 #ifdef DEBUG_MEMCOUNTER
 	int _count;
 #endif
