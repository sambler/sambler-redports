--- intern/itasc/kdl/tree.cpp.orig	2012-06-03 12:00:41 UTC
+++ intern/itasc/kdl/tree.cpp
@@ -64,7 +64,7 @@ bool Tree::addSegment(const Segment& seg
         return false;
     pair<SegmentMap::iterator, bool> retval;
     //insert new element
-	TreeElement elem(segment, parent, nrOfJoints);
+	TreeElement elem(segment, *parent, nrOfJoints);
 	std::pair<std::string, TreeElement> val(segment_name, elem);
 
     retval = segments.insert(val);
