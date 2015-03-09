--- lib/Alembic/AbcCoreHDF5/Tests/ArrayPropertyTests.cpp.orig	2013-07-01 23:15:03 UTC
+++ lib/Alembic/AbcCoreHDF5/Tests/ArrayPropertyTests.cpp
@@ -1221,7 +1221,11 @@ void testEmptyArray()

         ABCA::BasePropertyReaderPtr bp = parent->getProperty( 0 );
         TESTING_ASSERT(bp->isArray());
+#if defined(_LIBCPP_VERSION)
+        TESTING_ASSERT(bp->asScalarPtr() == ABCA::BasePropertyReaderPtr(NULL));
+#else
         TESTING_ASSERT(bp->asScalarPtr() == NULL);
+#endif
         TESTING_ASSERT(bp->getParent() == parent);
         ABCA::ArrayPropertyReaderPtr ap = bp->asArrayPtr();
         TESTING_ASSERT(ap->getNumSamples() == 0);
@@ -1318,7 +1322,11 @@ void testEmptyArray()
         {
             ABCA::BasePropertyReaderPtr bp = parent->getProperty( i );
             TESTING_ASSERT(bp->isArray());
+#if defined(_LIBCPP_VERSION)
+            TESTING_ASSERT(bp->asScalarPtr() == ABCA::BasePropertyReaderPtr(NULL));
+#else
             TESTING_ASSERT(bp->asScalarPtr() == NULL);
+#endif
             TESTING_ASSERT(bp->getParent() == parent);
             ABCA::ArrayPropertyReaderPtr ap = bp->asArrayPtr();
             if (ap->getName() == "veryEmptyInt32")
