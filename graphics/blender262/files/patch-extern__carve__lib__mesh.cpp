--- ./extern/carve/lib/mesh.cpp.orig	2013-10-23 01:53:44.228023179 +1030
+++ ./extern/carve/lib/mesh.cpp	2013-10-23 01:53:51.403016942 +1030
@@ -243,15 +243,20 @@
 
       bool FaceStitcher::EdgeOrderData::Cmp::operator()(const EdgeOrderData &a, const EdgeOrderData &b) const {
         int v = carve::geom3d::compareAngles(edge_dir, base_dir, a.face_dir, b.face_dir);
-        double da = carve::geom3d::antiClockwiseAngle(base_dir, a.face_dir, edge_dir);
-        double db = carve::geom3d::antiClockwiseAngle(base_dir, b.face_dir, edge_dir);
-        int v0 = v;
-        v = 0;
-        if (da < db) v = -1;
-        if (db < da) v = +1;
-        if (v0 != v) {
-          std::cerr << "v0= " << v0 << " v= " << v << " da= " << da << " db= " << db << "  " << edge_dir << " " << base_dir << " " << a.face_dir << b.face_dir << std::endl;
+
+#if defined(CARVE_DEBUG)
+        {
+          double da = carve::geom3d::antiClockwiseAngle(base_dir, a.face_dir, edge_dir);
+          double db = carve::geom3d::antiClockwiseAngle(base_dir, b.face_dir, edge_dir);
+          int v_cmp = 0;
+          if (da < db) v_cmp = -1;
+          if (db < da) v_cmp = +1;
+          if (v_cmp != v) {
+            std::cerr << "v= " << v << " v_cmp= " << v_cmp << " da= " << da << " db= " << db << "  edge_dir=" << edge_dir << " base_dir=" << base_dir << " a=" << a.face_dir << " b=" << b.face_dir << std::endl;
+          }
         }
+#endif
+
         if (v < 0) return true;
         if (v == 0) {
           if (a.is_reversed && !b.is_reversed) return true;
@@ -327,9 +332,14 @@
             CARVE_ASSERT(erev[0][i]->v2() == erev[j][i]->v2());
           }
 
-          std::sort(result[i].begin(),
-                    result[i].end(),
-                    EdgeOrderData::Cmp(base->v2()->v - base->v1()->v, result[i][0].face_dir));
+          geom::vector<3> sort_dir;
+          if (opts.opt_avoid_cavities) {
+            sort_dir = base->v1()->v - base->v2()->v;
+          } else {
+            sort_dir = base->v2()->v - base->v1()->v;
+          }
+
+          std::sort(result[i].begin(), result[i].end(), EdgeOrderData::Cmp(sort_dir, result[i][0].face_dir));
         }
       }
 
@@ -751,11 +761,15 @@
           }
         }
       }
+
+      FaceStitcher::FaceStitcher(const MeshOptions &_opts) : opts(_opts) {
+      }
     }
   }
 
 
 
+
   // construct a MeshSet from a Polyhedron, maintaining on the
   // connectivity information in the Polyhedron.
   mesh::MeshSet<3> *meshFromPolyhedron(const poly::Polyhedron *poly, int manifold_id) {
@@ -1201,3 +1215,4 @@
 
 
 
+
