--- ./intern/itasc/kdl/tree.hpp.orig	2013-10-29 22:35:50.000000000 +1030
+++ ./intern/itasc/kdl/tree.hpp	2013-10-29 22:35:56.000000000 +1030
@@ -46,8 +46,10 @@
     typedef std::map<std::string,TreeElement> SegmentMap;
 #  else
     // Eigen allocator is needed for alignment of Eigen data types
-    typedef std::map<std::string,TreeElement, std::less<std::string>, Eigen::aligned_allocator<std::pair<std::string, TreeElement> > > SegmentMap;
+    typedef std::map<std::string,TreeElement, std::less<std::string>, Eigen::aligned_allocator<std::pair<std::string, TreeElement > > SegmentMap;
 #  endif /* MAC_OS_X_VERSION_MIN_REQUIRED */
+#elif defined(_LIBCPP_VERSION)
+    typedef std::map<std::string,std::unique_ptr<TreeElement>, std::less<std::string>, Eigen::aligned_allocator<std::pair<std::string, std::unique_ptr<TreeElement> > > > SegmentMap;
 #else
     // Eigen allocator is needed for alignment of Eigen data types
     typedef std::map<std::string,TreeElement, std::less<std::string>, Eigen::aligned_allocator<std::pair<std::string, TreeElement> > > SegmentMap;
