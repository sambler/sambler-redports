--- lib/Alembic/Util/Foundation.h.orig	2014-03-28 01:06:30 UTC
+++ lib/Alembic/Util/Foundation.h
@@ -39,7 +39,7 @@
 // tr1/memory is not avaliable in Visual Studio.
 #if !defined(_MSC_VER)
 
-#if defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L
+#if defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L || defined(_LIBCPP_VERSION)
 #include <unordered_map>
 #else
 #include <tr1/memory>
@@ -111,7 +111,7 @@ using boost::static_pointer_cast;
 using boost::weak_ptr;
 using boost::unordered_map;
 #define ALEMBIC_LIB_USES_BOOST
-#elif defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L
+#elif defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L || defined(_LIBCPP_VERSION)
 using std::dynamic_pointer_cast;
 using std::enable_shared_from_this;
 using std::shared_ptr;
