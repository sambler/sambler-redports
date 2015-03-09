--- lib/Alembic/AbcGeom/Tests/PlayGround.cpp.orig	2013-02-11 22:33:24 UTC
+++ lib/Alembic/AbcGeom/Tests/PlayGround.cpp
@@ -198,7 +198,11 @@ void PolyMorphicAbstractPtrs()
         ReadArraySampleCachePtr cachePtr;

         if ( cachePtr ) { std::cout << "cachePtr is valid" << std::endl; }
+#if defined(_LIBCPP_VERSION)
+        if ( cachePtr != ReadArraySampleCachePtr(NULL) ) { std::cout << "cachePtr is not NULL" << std::endl; }
+#else
         if ( cachePtr != NULL ) { std::cout << "cachePtr is not NULL" << std::endl; }
+#endif
         else { std::cout << "cachePtr IS NULL" << std::endl; }
         IArchive archive( Alembic::AbcCoreHDF5::ReadArchive(), name,
                           ErrorHandler::kThrowPolicy,
