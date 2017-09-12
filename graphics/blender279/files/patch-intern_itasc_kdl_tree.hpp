--- intern/itasc/kdl/tree.hpp.orig	2016-05-19 17:00:23 UTC
+++ intern/itasc/kdl/tree.hpp
@@ -34,7 +34,7 @@ namespace KDL
     //Forward declaration
     class TreeElement;
     // Eigen allocator is needed for alignment of Eigen data types
-    typedef std::map<std::string,TreeElement, std::less<std::string>, Eigen::aligned_allocator<std::pair<std::string, TreeElement> > > SegmentMap;
+    typedef std::map<std::string,TreeElement, std::less<std::string>, Eigen::aligned_allocator<std::pair<const std::string, TreeElement> > > SegmentMap;
 
     class TreeElement
     {
