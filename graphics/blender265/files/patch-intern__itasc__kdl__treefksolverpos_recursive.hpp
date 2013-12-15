--- intern/itasc/kdl/treefksolverpos_recursive.hpp.orig	2013-12-14 21:34:36.267310374 +1030
+++ intern/itasc/kdl/treefksolverpos_recursive.hpp	2013-12-14 21:42:02.960307127 +1030
@@ -45,7 +45,7 @@
     private:
         const Tree tree;
         
-        Frame recursiveFk(const JntArray& q_in, const SegmentMap::const_iterator& it, const SegmentMap::const_iterator& baseit);
+        Frame recursiveFk(const JntArray& q_in, SegmentMap::value_type const* it, SegmentMap::value_type const* baseit);
     };
 
 }
