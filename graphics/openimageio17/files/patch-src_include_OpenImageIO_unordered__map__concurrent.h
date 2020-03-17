--- src/include/OpenImageIO/unordered_map_concurrent.h.orig	2019-05-14 23:52:47 UTC
+++ src/include/OpenImageIO/unordered_map_concurrent.h
@@ -73,7 +73,7 @@ OIIO_NAMESPACE_BEGIN
 /// lock and obtain a lock on the next bin.
 ///
 
-template<class KEY, class VALUE, class HASH=boost::hash<KEY>,
+template<class KEY, class VALUE, class HASH=std::hash<KEY>,
          class PRED=std::equal_to<KEY>, size_t BINS=16,
          class BINMAP=unordered_map<KEY,VALUE,HASH,PRED> >
 class unordered_map_concurrent {
