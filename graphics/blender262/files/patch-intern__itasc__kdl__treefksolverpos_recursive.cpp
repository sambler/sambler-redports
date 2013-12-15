--- intern/itasc/kdl/treefksolverpos_recursive.cpp.orig	2013-12-14 21:34:36.218309107 +1030
+++ intern/itasc/kdl/treefksolverpos_recursive.cpp	2013-12-14 21:41:38.122310772 +1030
@@ -35,22 +35,22 @@
 
     int TreeFkSolverPos_recursive::JntToCart(const JntArray& q_in, Frame& p_out, const std::string& segmentName, const std::string& baseName)
     {      
-		SegmentMap::const_iterator it = tree.getSegment(segmentName); 
-		SegmentMap::const_iterator baseit = tree.getSegment(baseName); 
+		SegmentMap::value_type const* it = tree.getSegmentPtr(segmentName);
+		SegmentMap::value_type const* baseit = tree.getSegmentPtr(baseName);
         
         if(q_in.rows() != tree.getNrOfJoints())
     	    	return -1;
-        else if(it == tree.getSegments().end()) //if the segment name is not found
+        else if(!it) //if the segment name is not found
          	return -2;
-        else if(baseit == tree.getSegments().end()) //if the base segment name is not found
+        else if(!baseit) //if the base segment name is not found
          	return -3;
         else{
-			p_out = recursiveFk(q_in, it, baseit);	
-        	return 0;        	
+			p_out = recursiveFk(q_in, it, baseit);
+        	return 0;
         }
     }
 
-	Frame TreeFkSolverPos_recursive::recursiveFk(const JntArray& q_in, const SegmentMap::const_iterator& it, const SegmentMap::const_iterator& baseit)
+	Frame TreeFkSolverPos_recursive::recursiveFk(const JntArray& q_in, SegmentMap::value_type const* it, SegmentMap::value_type const* baseit)
 	{
 		//gets the frame for the current element (segment)
 		const TreeElement& currentElement = it->second;
@@ -60,8 +60,7 @@
 		}
 		else{
 			Frame currentFrame = currentElement.segment.pose(((JntArray&)q_in)(currentElement.q_nr));
-			SegmentMap::const_iterator parentIt = currentElement.parent;
-			return recursiveFk(q_in, parentIt, baseit) * currentFrame;
+			return recursiveFk(q_in, currentElement.parent, baseit) * currentFrame;
 		}
 	}
 
