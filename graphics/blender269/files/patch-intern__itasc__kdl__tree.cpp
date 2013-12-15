--- intern/itasc/kdl/tree.cpp.orig	2013-12-14 21:34:36.114308593 +1030
+++ intern/itasc/kdl/tree.cpp	2013-12-14 21:35:49.161307553 +1030
@@ -64,7 +64,7 @@
         return false;
     pair<SegmentMap::iterator, bool> retval;
     //insert new element
-	TreeElement elem(segment, parent, nrOfJoints);
+	TreeElement elem(segment, *parent, nrOfJoints);
 	std::pair<std::string, TreeElement> val(segment_name, elem);
 
     retval = segments.insert(val);
