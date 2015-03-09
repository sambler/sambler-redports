--- lib/Alembic/AbcCoreHDF5/Tests/ArchiveTests.cpp.orig	2013-02-11 22:33:24 UTC
+++ lib/Alembic/AbcCoreHDF5/Tests/ArchiveTests.cpp
@@ -108,7 +108,11 @@ void testReadWriteEmptyArchive()
         TESTING_ASSERT(m.get("geoScope") == "tasty");
         TESTING_ASSERT(archive->getName() == "ABC");
         TESTING_ASSERT(archive->getFullName() == "/");
+#if defined(_LIBCPP_VERSION)
+        TESTING_ASSERT(archive->getParent() == ABCA::ObjectReaderPtr(NULL));
+#else
         TESTING_ASSERT(archive->getParent() == NULL);
+#endif
         TESTING_ASSERT(archive->getNumChildren() == 0);

         // even though we didn't write anything make sure we intrincially have
