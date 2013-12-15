--- intern/itasc/Armature.cpp.orig	2013-12-14 21:34:35.877307020 +1030
+++ intern/itasc/Armature.cpp	2013-12-14 21:35:15.815307533 +1030
@@ -402,7 +402,7 @@
 	m_armlength = 0.0;
 	for (i=0; i<m_neffector; i++) {
 		length = 0.0;
-		KDL::SegmentMap::const_iterator sit = m_tree.getSegment(m_effectors[i].name);
+		KDL::SegmentMap::value_type const *sit = m_tree.getSegmentPtr(m_effectors[i].name);
 		while (sit->first != "root") {
 			Frame tip = sit->second.segment.pose(m_qKdl(sit->second.q_nr));
 			length += tip.p.Norm();
