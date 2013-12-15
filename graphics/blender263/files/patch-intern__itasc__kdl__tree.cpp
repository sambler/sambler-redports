--- intern/itasc/kdl/tree.cpp.orig	2012-05-11 00:16:16.000000000 +0930
+++ intern/itasc/kdl/tree.cpp	2013-12-14 22:02:52.014307471 +1030
@@ -61,7 +61,7 @@
     pair<SegmentMap::iterator, bool> retval;
     //insert new element
     retval = segments.insert(make_pair(segment_name, TreeElement(segment,
-            parent, nrOfJoints)));
+            *parent, nrOfJoints)));
     //check if insertion succeeded
     if (!retval.second)
         return false;
