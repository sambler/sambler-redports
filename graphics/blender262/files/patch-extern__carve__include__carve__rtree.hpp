--- ./extern/carve/include/carve/rtree.hpp.orig	2013-10-23 01:49:04 UTC
+++ ./extern/carve/include/carve/rtree.hpp
@@ -49,8 +49,6 @@
 
       aabb_t getAABB() const { return bbox; }
 
-
-
       struct data_aabb_t {
         aabb_t bbox;
         data_t data;
@@ -164,6 +162,17 @@
         _fill(begin, end, typename std::iterator_traits<iter_t>::value_type());
       }
 
+      ~RTreeNode() {
+        if (child) {
+          RTreeNode *next = child;
+          while (next) {
+            RTreeNode *curr = next;
+            next = next->sibling;
+            delete curr;
+          }
+        }
+      }
+
 
 
       // functor for ordering nodes by increasing aabb midpoint, along a specified axis.
@@ -499,3 +508,4 @@
 
   }
 }
+
