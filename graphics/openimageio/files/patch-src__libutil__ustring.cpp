--- ./src/libutil/ustring.cpp.orig	2014-06-07 13:38:39.000000000 +0930
+++ ./src/libutil/ustring.cpp	2014-06-24 14:13:44.743536077 +0930
@@ -67,8 +67,20 @@
 typedef null_lock<null_mutex> ustring_write_lock_t;
 #endif
 
+#if defined(__i386__) && !defined(__clang__) && !defined(_MSC_VER)
+#if ((10000*__GNUC__ + 100*__GNUC_MINOR__ + __GNUC_PATCHLEVEL__) < 40300)
+// On a 32bit build using gcc4.2, make_unique() seg faults with the
+// concurrent map enabled, so turn it off. More recent gcc seems ok. That
+// old a gcc on 32 bit systems is a pretty rare combination, so we're not
+// going to sweat the lower performance of turning off the concurrent map
+// for that increasingly rare case.
+#define USE_CONCURRENT_MAP 0
+#endif
+#endif
 
+#ifndef USE_CONCURRENT_MAP
 #define USE_CONCURRENT_MAP 1
+#endif
 
 #if USE_CONCURRENT_MAP
 typedef unordered_map_concurrent <string_view, ustring::TableRep *, Strutil::StringHash, Strutil::StringEqual, 8> UstringTable;
