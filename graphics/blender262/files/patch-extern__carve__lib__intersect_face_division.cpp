--- ./extern/carve/lib/intersect_face_division.cpp.orig	2013-10-23 01:53:05 UTC
+++ ./extern/carve/lib/intersect_face_division.cpp
@@ -719,6 +719,10 @@
           unassigned--;
         }
       }
+
+      if (!removed.size())
+        throw carve::exception("Failed to merge holes");
+
       for (std::set<int>::iterator f = removed.begin(); f != removed.end(); ++f) {
         for (unsigned i = 0; i < containing_faces.size(); ++i) {
           containing_faces[i].erase(std::remove(containing_faces[i].begin(),
@@ -1106,7 +1110,8 @@
         }
 
         // copy up to the end of the path.
-        std::copy(base_loop.begin() + pos, base_loop.begin() + e1_1, std::back_inserter(out));
+		if (pos < e1_1)
+			std::copy(base_loop.begin() + pos, base_loop.begin() + e1_1, std::back_inserter(out));
 
         CARVE_ASSERT(base_loop[e1_1] == p1.back());
         std::copy(p1.rbegin(), p1.rend() - 1, std::back_inserter(out));
@@ -1742,3 +1747,4 @@
   }
   return generated_edges;
 }
+
