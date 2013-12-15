--- intern/itasc/kdl/treejnttojacsolver.cpp.orig	2013-12-14 21:34:36.318308532 +1030
+++ intern/itasc/kdl/treejnttojacsolver.cpp	2013-12-14 21:42:48.003306761 +1030
@@ -28,16 +28,16 @@
         return -1;
 
     //Lets search the tree-element
-    SegmentMap::const_iterator it = tree.getSegments().find(segmentname);
+    SegmentMap::value_type const* it = tree.getSegmentPtr(segmentname);
 
     //If segmentname is not inside the tree, back out:
-    if (it == tree.getSegments().end())
+    if (!it)
         return -2;
 
     //Let's make the jacobian zero:
     SetToZero(jac);
 
-    SegmentMap::const_iterator root = tree.getSegments().find("root");
+    SegmentMap::value_type const* root = tree.getSegmentPtr("root");
 
     Frame T_total = Frame::Identity();
 	Frame T_local, T_joint;
