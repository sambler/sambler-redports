--- lib/Alembic/AbcCoreOgawa/Tests/ArchiveTests.cpp.orig	2013-07-01 23:15:03 UTC
+++ lib/Alembic/AbcCoreOgawa/Tests/ArchiveTests.cpp
@@ -92,7 +92,11 @@ void testReadWriteEmptyArchive()
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
