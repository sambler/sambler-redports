--- lib/Alembic/AbcGeom/IGeomParam.h.orig	2014-03-28 01:06:30 UTC
+++ lib/Alembic/AbcGeom/IGeomParam.h
@@ -235,7 +235,11 @@ ITypedGeomParam<TRAITS>::ITypedGeomParam

     AbcA::CompoundPropertyReaderPtr parent =
         GetCompoundPropertyReaderPtr( iParent );
+#if defined(_LIBCPP_VERSION)
+    ABCA_ASSERT( parent != CompoundPropertyReaderPtr(NULL),
+#else
     ABCA_ASSERT( parent != NULL,
+#endif
                  "NULL CompoundPropertyReader passed into "
                  << "ITypedGeomParam ctor" );

