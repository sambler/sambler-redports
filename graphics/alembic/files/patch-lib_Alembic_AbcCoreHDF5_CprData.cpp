--- lib/Alembic/AbcCoreHDF5/CprData.cpp.orig	2013-12-06 21:25:26 UTC
+++ lib/Alembic/AbcCoreHDF5/CprData.cpp
@@ -205,7 +205,11 @@ CprData::getPropertyHeader( AbcA::Compou
     Alembic::Util::scoped_lock l( m_subPropertyMutexes[i] );

     // read the property header stuff if we haven't yet
+#if defined(_LIBCPP_VERSION)
+    if ( m_propertyHeaders[i].header == PropertyHeaderPtr(NULL) )
+#else
     if ( m_propertyHeaders[i].header == NULL )
+#endif
     {
         uint32_t tsid = 0;

