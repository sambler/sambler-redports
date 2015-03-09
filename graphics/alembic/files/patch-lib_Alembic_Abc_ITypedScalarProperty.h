--- lib/Alembic/Abc/ITypedScalarProperty.h.orig	2012-10-19 17:30:50 UTC
+++ lib/Alembic/Abc/ITypedScalarProperty.h
@@ -172,13 +172,21 @@ ITypedScalarProperty<TRAITS>::ITypedScal

     AbcA::CompoundPropertyReaderPtr parent =
         GetCompoundPropertyReaderPtr( iParent );
+#if defined(_LIBCPP_VERSION)
+    ABCA_ASSERT( parent != CompoundPropertyReaderPtr(NULL),
+#else
     ABCA_ASSERT( parent != NULL,
+#endif
                  "NULL CompoundPropertyReader passed into "
                  << "ITypedScalarProperty ctor" );

     const AbcA::PropertyHeader *pheader =
         parent->getPropertyHeader( iName );
+#if defined(_LIBCPP_VERSION)
+    ABCA_ASSERT( pheader != CompoundPropertyReaderPtr(NULL),
+#else
     ABCA_ASSERT( pheader != NULL,
+#endif
                  "Nonexistent scalar property: " << iName );

     ABCA_ASSERT( matches( *pheader, args.getSchemaInterpMatching() ),
