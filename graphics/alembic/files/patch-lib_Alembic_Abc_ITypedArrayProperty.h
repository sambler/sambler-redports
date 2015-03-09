--- lib/Alembic/Abc/ITypedArrayProperty.h.orig	2012-10-19 17:30:50 UTC
+++ lib/Alembic/Abc/ITypedArrayProperty.h
@@ -178,13 +178,21 @@ ITypedArrayProperty<TRAITS>::ITypedArray

     AbcA::CompoundPropertyReaderPtr parent =
         GetCompoundPropertyReaderPtr( iParent );
+#if defined(_LIBCPP_VERSION)
+    ABCA_ASSERT( parent != CompoundPropertyReaderPtr(NULL),
+#else
     ABCA_ASSERT( parent != NULL,
+#endif
                  "NULL CompoundPropertyReader passed into "
                  << "ITypedArrayProperty ctor" );

     const AbcA::PropertyHeader *pheader =
         parent->getPropertyHeader( iName );
+#if defined(_LIBCPP_VERSION)
+    ABCA_ASSERT( pheader != (AbcA::PropertyHeader *)(NULL),
+#else
     ABCA_ASSERT( pheader != NULL,
+#endif
                  "Nonexistent array property: " << iName );

     ABCA_ASSERT( matches( *pheader, args.getSchemaInterpMatching() ),
