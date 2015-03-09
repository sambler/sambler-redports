--- lib/Alembic/Abc/IObject.cpp.orig	2013-07-01 23:15:03 UTC
+++ lib/Alembic/Abc/IObject.cpp
@@ -549,7 +549,11 @@ void IObject::initInstance()
     m_object = targetObject;

     // initialize the full name to the instance full name
+#if defined(_LIBCPP_VERSION)
+    if ( m_instanceObject != ObjectReaderPtr(0) )
+#else
     if ( m_instanceObject != 0 )
+#endif
     {
         m_instancedFullName = m_instanceObject->getFullName();
     }
