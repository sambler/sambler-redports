--- intern/itasc/kdl/treefksolverpos_recursive.hpp.orig	2013-12-14 21:34:36 UTC
+++ intern/itasc/kdl/treefksolverpos_recursive.hpp
@@ -45,7 +45,7 @@
     private:
         const Tree tree;
         
-        Frame recursiveFk(const JntArray& q_in, const SegmentMap::const_iterator& it, const SegmentMap::const_iterator& baseit);
+        Frame recursiveFk(const JntArray& q_in, SegmentMap::value_type const* it, SegmentMap::value_type const* baseit);
     };
 
 }
