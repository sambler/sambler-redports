--- ./extern/carve/lib/intersect.cpp.orig	2013-10-23 01:52:30 UTC
+++ ./extern/carve/lib/intersect.cpp
@@ -41,6 +41,7 @@
 #include <carve/timing.hpp>
 #include <carve/colour.hpp>
 
+#include <memory>
 
 
 
@@ -114,7 +115,7 @@
     ordered_vertices.reserve(std::distance(beg, end));
   
     for (; beg != end; ++beg) {
-      carve::mesh::MeshSet<3>::vertex_t *v = (*beg);
+      carve::mesh::MeshSet<3>::vertex_t *v = *beg;
       ordered_vertices.push_back(std::make_pair(carve::geom::dot(v->v - base, dir), v));
     }
   
@@ -130,6 +131,37 @@
     }
   }
 
+  template<typename iter_t>
+  void orderEdgeIntersectionVertices(iter_t beg, const iter_t end,
+                                     const carve::mesh::MeshSet<3>::vertex_t::vector_t &dir,
+                                     const carve::mesh::MeshSet<3>::vertex_t::vector_t &base,
+                                     std::vector<carve::mesh::MeshSet<3>::vertex_t *> &out) {
+    typedef std::vector<std::pair<std::pair<double, double>, carve::mesh::MeshSet<3>::vertex_t *> > DVVector;
+    DVVector ordered_vertices;
+
+    ordered_vertices.reserve(std::distance(beg, end));
+  
+    for (; beg != end; ++beg) {
+      carve::mesh::MeshSet<3>::vertex_t *v = (*beg).first;
+      double ovec = 0.0;
+      for (carve::csg::detail::EdgeIntInfo::mapped_type::const_iterator j = (*beg).second.begin(); j != (*beg).second.end(); ++j) {
+        ovec += (*j).second;
+      }
+      ordered_vertices.push_back(std::make_pair(std::make_pair(carve::geom::dot(v->v - base, dir), -ovec), v));
+    }
+
+    std::sort(ordered_vertices.begin(), ordered_vertices.end());
+
+    out.clear();
+    out.reserve(ordered_vertices.size());
+    for (DVVector::const_iterator
+           i = ordered_vertices.begin(), e = ordered_vertices.end();
+         i != e;
+         ++i) {
+      out.push_back((*i).second);
+    }
+  }
+
 
 
   /** 
@@ -346,7 +378,7 @@
   return hooks[hook_num].size() > 0;
 }
 
-void carve::csg::CSG::Hooks::intersectionVertex(const carve::mesh::MeshSet<3>::vertex_t *vertex,
+void carve::csg::CSG::Hooks::intersectionVertex(const meshset_t::vertex_t *vertex,
                                                 const IObjPairSet &intersections) {
   for (std::list<Hook *>::iterator j = hooks[INTERSECTION_VERTEX_HOOK].begin();
        j != hooks[INTERSECTION_VERTEX_HOOK].end();
@@ -355,8 +387,8 @@
   }
 }
 
-void carve::csg::CSG::Hooks::processOutputFace(std::vector<carve::mesh::MeshSet<3>::face_t *> &faces,
-                                               const carve::mesh::MeshSet<3>::face_t *orig_face,
+void carve::csg::CSG::Hooks::processOutputFace(std::vector<meshset_t::face_t *> &faces,
+                                               const meshset_t::face_t *orig_face,
                                                bool flipped) {
   for (std::list<Hook *>::iterator j = hooks[PROCESS_OUTPUT_FACE_HOOK].begin();
        j != hooks[PROCESS_OUTPUT_FACE_HOOK].end();
@@ -365,8 +397,8 @@
   }
 }
 
-void carve::csg::CSG::Hooks::resultFace(const carve::mesh::MeshSet<3>::face_t *new_face,
-                                        const carve::mesh::MeshSet<3>::face_t *orig_face,
+void carve::csg::CSG::Hooks::resultFace(const meshset_t::face_t *new_face,
+                                        const meshset_t::face_t *orig_face,
                                         bool flipped) {
   for (std::list<Hook *>::iterator j = hooks[RESULT_FACE_HOOK].begin();
        j != hooks[RESULT_FACE_HOOK].end();
@@ -425,7 +457,7 @@
          j != je;
          ++j) {
       const IObj &i_tgt = ((*j).first);
-      carve::mesh::MeshSet<3>::vertex_t *i_pt = ((*j).second);
+      meshset_t::vertex_t *i_pt = ((*j).second);
 
       vertex_intersections[i_pt].insert(std::make_pair(i_src, i_tgt));
     }
@@ -499,7 +531,7 @@
 
   carve::TimingBlock block(GROUP_INTERSECTONS);
   
-  std::vector<carve::mesh::MeshSet<3>::vertex_t *> vertices;
+  std::vector<meshset_t::vertex_t *> vertices;
   detail::VVSMap graph;
 #if defined(CARVE_DEBUG)
   std::cerr << "groupIntersections()" << ": vertex_intersections.size()==" << vertex_intersections.size() << std::endl;
@@ -521,7 +553,7 @@
 
   vertex_intersections_octree.addVertices(vertices);
       
-  std::vector<carve::mesh::MeshSet<3>::vertex_t *> out;
+  std::vector<meshset_t::vertex_t *> out;
   for (size_t i = 0, l = vertices.size(); i != l; ++i) {
     // let's find all the vertices near this one. 
     out.clear();
@@ -546,7 +578,7 @@
     open.insert((*i).first);
     while (open.size()) {
       detail::VSet::iterator t = open.begin();
-      const carve::mesh::MeshSet<3>::vertex_t *o = (*t);
+      const meshset_t::vertex_t *o = (*t);
       open.erase(t);
       i = graph.find(o);
       CARVE_ASSERT(i != graph.end());
@@ -568,6 +600,19 @@
 }
 
 
+static void recordEdgeIntersectionInfo(carve::mesh::MeshSet<3>::vertex_t *intersection,
+                                       carve::mesh::MeshSet<3>::edge_t *edge,
+                                       const carve::csg::detail::VFSMap::mapped_type &intersected_faces,
+                                       carve::csg::detail::Data &data) {
+  carve::mesh::MeshSet<3>::vertex_t::vector_t edge_dir = edge->v2()->v - edge->v1()->v;
+  carve::csg::detail::EdgeIntInfo::mapped_type &eint_info = data.emap[edge][intersection];
+
+  for (carve::csg::detail::VFSMap::mapped_type::const_iterator i = intersected_faces.begin(); i != intersected_faces.end(); ++i) {
+    carve::mesh::MeshSet<3>::vertex_t::vector_t normal = (*i)->plane.N;
+    eint_info.insert(std::make_pair((*i), carve::geom::dot(edge_dir, normal)));
+  }
+}
+
 
 void carve::csg::CSG::intersectingFacePairs(detail::Data &data) {
   static carve::TimingName FUNC_NAME("CSG::intersectingFacePairs()");
@@ -575,30 +620,36 @@
 
   // iterate over all intersection points.
   for (VertexIntersections::const_iterator i = vertex_intersections.begin(), ie = vertex_intersections.end(); i != ie; ++i) {
-    carve::mesh::MeshSet<3>::vertex_t *i_pt = ((*i).first);
+    meshset_t::vertex_t *i_pt = ((*i).first);
     detail::VFSMap::mapped_type &face_set = (data.fmap_rev[i_pt]);
-
+    detail::VFSMap::mapped_type src_face_set;
+    detail::VFSMap::mapped_type tgt_face_set;
     // for all pairs of intersecting objects at this point
     for (VertexIntersections::data_type::const_iterator j = (*i).second.begin(), je = (*i).second.end(); j != je; ++j) {
       const IObj &i_src = ((*j).first);
       const IObj &i_tgt = ((*j).second);
 
-      // work out the faces involved. this updates fmap_rev.
-      facesForObject(i_src, data.vert_to_edges, face_set);
-      facesForObject(i_tgt, data.vert_to_edges, face_set);
+      src_face_set.clear();
+      tgt_face_set.clear();
+      // work out the faces involved.
+      facesForObject(i_src, data.vert_to_edges, src_face_set);
+      facesForObject(i_tgt, data.vert_to_edges, tgt_face_set);
+      // this updates fmap_rev.
+      std::copy(src_face_set.begin(), src_face_set.end(), set_inserter(face_set));
+      std::copy(tgt_face_set.begin(), tgt_face_set.end(), set_inserter(face_set));
 
       // record the intersection with respect to any involved vertex.
       if (i_src.obtype == IObj::OBTYPE_VERTEX) data.vmap[i_src.vertex] = i_pt;
       if (i_tgt.obtype == IObj::OBTYPE_VERTEX) data.vmap[i_tgt.vertex] = i_pt;
 
       // record the intersection with respect to any involved edge.
-      if (i_src.obtype == IObj::OBTYPE_EDGE) data.emap[i_src.edge].insert(i_pt);
-      if (i_tgt.obtype == IObj::OBTYPE_EDGE) data.emap[i_tgt.edge].insert(i_pt);
+      if (i_src.obtype == IObj::OBTYPE_EDGE) recordEdgeIntersectionInfo(i_pt, i_src.edge, tgt_face_set, data);
+      if (i_tgt.obtype == IObj::OBTYPE_EDGE) recordEdgeIntersectionInfo(i_pt, i_tgt.edge, src_face_set, data);
     }
 
     // record the intersection with respect to each face.
     for (carve::csg::detail::VFSMap::mapped_type::const_iterator k = face_set.begin(), ke = face_set.end(); k != ke; ++k) {
-      carve::mesh::MeshSet<3>::face_t *f = (*k);
+      meshset_t::face_t *f = (*k);
       data.fmap[f].insert(i_pt);
     }
   }
@@ -606,8 +657,8 @@
 
 
 
-void carve::csg::CSG::_generateVertexVertexIntersections(carve::mesh::MeshSet<3>::vertex_t *va,
-                                                         carve::mesh::MeshSet<3>::edge_t *eb) {
+void carve::csg::CSG::_generateVertexVertexIntersections(meshset_t::vertex_t *va,
+                                                         meshset_t::edge_t *eb) {
   if (intersections.intersects(va, eb->v1())) {
     return;
   }
@@ -621,14 +672,14 @@
 
 
 
-void carve::csg::CSG::generateVertexVertexIntersections(carve::mesh::MeshSet<3>::face_t *a,
-                                                        const std::vector<carve::mesh::MeshSet<3>::face_t *> &b) {
-  carve::mesh::MeshSet<3>::edge_t *ea, *eb;
+void carve::csg::CSG::generateVertexVertexIntersections(meshset_t::face_t *a,
+                                                        const std::vector<meshset_t::face_t *> &b) {
+  meshset_t::edge_t *ea, *eb;
 
   ea = a->edge;
   do {
     for (size_t i = 0; i < b.size(); ++i) {
-      carve::mesh::MeshSet<3>::face_t *t = b[i];
+      meshset_t::face_t *t = b[i];
       eb = t->edge;
       do {
         _generateVertexVertexIntersections(ea->v1(), eb);
@@ -641,18 +692,15 @@
 
 
 
-void carve::csg::CSG::_generateVertexEdgeIntersections(carve::mesh::MeshSet<3>::vertex_t *va,
-                                                       carve::mesh::MeshSet<3>::edge_t *eb) {
+void carve::csg::CSG::_generateVertexEdgeIntersections(meshset_t::vertex_t *va,
+                                                       meshset_t::edge_t *eb) {
   if (intersections.intersects(va, eb)) {
     return;
   }
 
-  if (std::min(eb->v1()->v.x, eb->v2()->v.x) - carve::EPSILON > va->v.x ||
-      std::max(eb->v1()->v.x, eb->v2()->v.x) + carve::EPSILON < va->v.x ||
-      std::min(eb->v1()->v.y, eb->v2()->v.y) - carve::EPSILON > va->v.y ||
-      std::max(eb->v1()->v.y, eb->v2()->v.y) + carve::EPSILON < va->v.y ||
-      std::min(eb->v1()->v.z, eb->v2()->v.z) - carve::EPSILON > va->v.z ||
-      std::max(eb->v1()->v.z, eb->v2()->v.z) + carve::EPSILON < va->v.z) {
+  carve::geom::aabb<3> eb_aabb;
+  eb_aabb.fit(eb->v1()->v, eb->v2()->v);
+  if (eb_aabb.maxAxisSeparation(va->v) > carve::EPSILON) {
     return;
   }
 
@@ -668,14 +716,14 @@
 
 
 
-void carve::csg::CSG::generateVertexEdgeIntersections(carve::mesh::MeshSet<3>::face_t *a,
-                                                      const std::vector<carve::mesh::MeshSet<3>::face_t *> &b) {
-  carve::mesh::MeshSet<3>::edge_t *ea, *eb;
+void carve::csg::CSG::generateVertexEdgeIntersections(meshset_t::face_t *a,
+                                                      const std::vector<meshset_t::face_t *> &b) {
+  meshset_t::edge_t *ea, *eb;
 
   ea = a->edge;
   do {
     for (size_t i = 0; i < b.size(); ++i) {
-      carve::mesh::MeshSet<3>::face_t *t = b[i];
+      meshset_t::face_t *t = b[i];
       eb = t->edge;
       do {
         _generateVertexEdgeIntersections(ea->v1(), eb);
@@ -688,21 +736,21 @@
 
 
 
-void carve::csg::CSG::_generateEdgeEdgeIntersections(carve::mesh::MeshSet<3>::edge_t *ea,
-                                                     carve::mesh::MeshSet<3>::edge_t *eb) {
+void carve::csg::CSG::_generateEdgeEdgeIntersections(meshset_t::edge_t *ea,
+                                                     meshset_t::edge_t *eb) {
   if (intersections.intersects(ea, eb)) {
     return;
   }
 
-  carve::mesh::MeshSet<3>::vertex_t *v1 = ea->v1(), *v2 = ea->v2();
-  carve::mesh::MeshSet<3>::vertex_t *v3 = eb->v1(), *v4 = eb->v2();
+  meshset_t::vertex_t *v1 = ea->v1(), *v2 = ea->v2();
+  meshset_t::vertex_t *v3 = eb->v1(), *v4 = eb->v2();
 
   carve::geom::aabb<3> ea_aabb, eb_aabb;
   ea_aabb.fit(v1->v, v2->v);
   eb_aabb.fit(v3->v, v4->v);
   if (ea_aabb.maxAxisSeparation(eb_aabb) > EPSILON) return;
 
-  carve::mesh::MeshSet<3>::vertex_t::vector_t p1, p2;
+  meshset_t::vertex_t::vector_t p1, p2;
   double mu1, mu2;
 
   switch (carve::geom3d::rayRayIntersection(carve::geom3d::Ray(v2->v - v1->v, v1->v),
@@ -711,7 +759,7 @@
   case carve::RR_INTERSECTION: {
     // edges intersect
     if (mu1 >= 0.0 && mu1 <= 1.0 && mu2 >= 0.0 && mu2 <= 1.0) {
-      carve::mesh::MeshSet<3>::vertex_t *p = vertex_pool.get((p1 + p2) / 2.0);
+      meshset_t::vertex_t *p = vertex_pool.get((p1 + p2) / 2.0);
       intersections.record(ea, eb, p);
       if (ea->rev) intersections.record(ea->rev, eb, p);
       if (eb->rev) intersections.record(ea, eb->rev, p);
@@ -736,14 +784,14 @@
 
 
 
-void carve::csg::CSG::generateEdgeEdgeIntersections(carve::mesh::MeshSet<3>::face_t *a,
-                                                    const std::vector<carve::mesh::MeshSet<3>::face_t *> &b) {
-  carve::mesh::MeshSet<3>::edge_t *ea, *eb;
+void carve::csg::CSG::generateEdgeEdgeIntersections(meshset_t::face_t *a,
+                                                    const std::vector<meshset_t::face_t *> &b) {
+  meshset_t::edge_t *ea, *eb;
 
   ea = a->edge;
   do {
     for (size_t i = 0; i < b.size(); ++i) {
-      carve::mesh::MeshSet<3>::face_t *t = b[i];
+      meshset_t::face_t *t = b[i];
       eb = t->edge;
       do {
         _generateEdgeEdgeIntersections(ea, eb);
@@ -756,8 +804,8 @@
 
 
 
-void carve::csg::CSG::_generateVertexFaceIntersections(carve::mesh::MeshSet<3>::face_t *fa,
-                                                       carve::mesh::MeshSet<3>::edge_t *eb) {
+void carve::csg::CSG::_generateVertexFaceIntersections(meshset_t::face_t *fa,
+                                                       meshset_t::edge_t *eb) {
   if (intersections.intersects(eb->v1(), fa)) {
     return;
   }
@@ -772,12 +820,12 @@
 
 
 
-void carve::csg::CSG::generateVertexFaceIntersections(carve::mesh::MeshSet<3>::face_t *a,
-                                                      const std::vector<carve::mesh::MeshSet<3>::face_t *> &b) {
-  carve::mesh::MeshSet<3>::edge_t *ea, *eb;
+void carve::csg::CSG::generateVertexFaceIntersections(meshset_t::face_t *a,
+                                                      const std::vector<meshset_t::face_t *> &b) {
+  meshset_t::edge_t *eb;
 
   for (size_t i = 0; i < b.size(); ++i) {
-    carve::mesh::MeshSet<3>::face_t *t = b[i];
+    meshset_t::face_t *t = b[i];
     eb = t->edge;
     do {
       _generateVertexFaceIntersections(a, eb);
@@ -788,15 +836,15 @@
 
 
 
-void carve::csg::CSG::_generateEdgeFaceIntersections(carve::mesh::MeshSet<3>::face_t *fa,
-                                                     carve::mesh::MeshSet<3>::edge_t *eb) {
+void carve::csg::CSG::_generateEdgeFaceIntersections(meshset_t::face_t *fa,
+                                                     meshset_t::edge_t *eb) {
   if (intersections.intersects(eb, fa)) {
     return;
   }
 
-  carve::mesh::MeshSet<3>::vertex_t::vector_t _p;
+  meshset_t::vertex_t::vector_t _p;
   if (fa->simpleLineSegmentIntersection(carve::geom3d::LineSegment(eb->v1()->v, eb->v2()->v), _p)) {
-    carve::mesh::MeshSet<3>::vertex_t *p = vertex_pool.get(_p);
+    meshset_t::vertex_t *p = vertex_pool.get(_p);
     intersections.record(eb, fa, p);
     if (eb->rev) intersections.record(eb->rev, fa, p);
   }
@@ -804,12 +852,12 @@
 
 
 
-void carve::csg::CSG::generateEdgeFaceIntersections(carve::mesh::MeshSet<3>::face_t *a,
-                                                    const std::vector<carve::mesh::MeshSet<3>::face_t *> &b) {
-  carve::mesh::MeshSet<3>::edge_t *ea, *eb;
+void carve::csg::CSG::generateEdgeFaceIntersections(meshset_t::face_t *a,
+                                                    const std::vector<meshset_t::face_t *> &b) {
+  meshset_t::edge_t *eb;
 
   for (size_t i = 0; i < b.size(); ++i) {
-    carve::mesh::MeshSet<3>::face_t *t = b[i];
+    meshset_t::face_t *t = b[i];
     eb = t->edge;
     do {
       _generateEdgeFaceIntersections(a, eb);
@@ -820,9 +868,9 @@
 
 
 
-void carve::csg::CSG::generateIntersectionCandidates(carve::mesh::MeshSet<3> *a,
+void carve::csg::CSG::generateIntersectionCandidates(meshset_t *a,
                                                      const face_rtree_t *a_node,
-                                                     carve::mesh::MeshSet<3> *b,
+                                                     meshset_t *b,
                                                      const face_rtree_t *b_node,
                                                      face_pairs_t &face_pairs,
                                                      bool descend_a) {
@@ -840,12 +888,12 @@
     }
   } else {
     for (size_t i = 0; i < a_node->data.size(); ++i) {
-      carve::mesh::MeshSet<3>::face_t *fa = a_node->data[i];
+      meshset_t::face_t *fa = a_node->data[i];
       carve::geom::aabb<3> aabb_a = fa->getAABB();
       if (aabb_a.maxAxisSeparation(b_node->bbox) > carve::EPSILON) continue;
 
       for (size_t j = 0; j < b_node->data.size(); ++j) {
-        carve::mesh::MeshSet<3>::face_t *fb = b_node->data[j];
+        meshset_t::face_t *fb = b_node->data[j];
         carve::geom::aabb<3> aabb_b = fb->getAABB();
         if (aabb_b.maxAxisSeparation(aabb_a) > carve::EPSILON) continue;
 
@@ -869,17 +917,17 @@
 
 
 
-void carve::csg::CSG::generateIntersections(carve::mesh::MeshSet<3> *a,
+void carve::csg::CSG::generateIntersections(meshset_t *a,
                                             const face_rtree_t *a_rtree,
-                                            carve::mesh::MeshSet<3> *b,
+                                            meshset_t *b,
                                             const face_rtree_t *b_rtree,
                                             detail::Data &data) {
   face_pairs_t face_pairs;
   generateIntersectionCandidates(a, a_rtree, b, b_rtree, face_pairs);
 
   for (face_pairs_t::const_iterator i = face_pairs.begin(); i != face_pairs.end(); ++i) {
-    carve::mesh::MeshSet<3>::face_t *f = (*i).first;
-    carve::mesh::MeshSet<3>::edge_t *e = f->edge;
+    meshset_t::face_t *f = (*i).first;
+    meshset_t::edge_t *e = f->edge;
     do {
       data.vert_to_edges[e->v1()].push_back(e);
       e = e->next;
@@ -961,13 +1009,13 @@
   static carve::TimingName FUNC_NAME("CSG::divideIntersectedEdges()");
   carve::TimingBlock block(FUNC_NAME);
 
-  for (detail::EVSMap::const_iterator i = data.emap.begin(), ei = data.emap.end(); i != ei; ++i) {
-    carve::mesh::MeshSet<3>::edge_t *edge = (*i).first;
-    const detail::EVSMap::mapped_type &vertices = (*i).second;
-    std::vector<carve::mesh::MeshSet<3>::vertex_t *> &verts = data.divided_edges[edge];
-    orderVertices(vertices.begin(), vertices.end(),
-                  edge->v2()->v - edge->v1()->v, edge->v1()->v,
-                  verts);
+  for (detail::EIntMap::const_iterator i = data.emap.begin(), ei = data.emap.end(); i != ei; ++i) {
+    meshset_t::edge_t *edge = (*i).first;
+    const detail::EIntMap::mapped_type &int_info = (*i).second;
+    std::vector<meshset_t::vertex_t *> &verts = data.divided_edges[edge];
+    orderEdgeIntersectionVertices(int_info.begin(), int_info.end(),
+                                  edge->v2()->v - edge->v1()->v, edge->v1()->v,
+                                  verts);
   }
 }
 
@@ -985,7 +1033,7 @@
          i = data.fmap.begin(), ie = data.fmap.end();
        i != ie;
        ++i) {
-    carve::mesh::MeshSet<3>::face_t *face_a = (*i).first;
+    meshset_t::face_t *face_a = (*i).first;
     const detail::FVSMap::mapped_type &face_a_intersections = ((*i).second);
     face_b_set.clear();
 
@@ -998,7 +1046,7 @@
              k = data.fmap_rev[*j].begin(), ke = data.fmap_rev[*j].end();
            k != ke;
            ++k) {
-        carve::mesh::MeshSet<3>::face_t *face_b = (*k);
+        meshset_t::face_t *face_b = (*k);
         if (face_a != face_b && face_b->mesh->meshset != face_a->mesh->meshset) {
           face_b_set.insert(face_b);
         }
@@ -1010,10 +1058,10 @@
            j = face_b_set.begin(), je = face_b_set.end();
          j != je;
          ++j) {
-      carve::mesh::MeshSet<3>::face_t *face_b = (*j);
+      meshset_t::face_t *face_b = (*j);
       const detail::FVSMap::mapped_type &face_b_intersections = (data.fmap[face_b]);
 
-      std::vector<carve::mesh::MeshSet<3>::vertex_t *> vertices;
+      std::vector<meshset_t::vertex_t *> vertices;
       vertices.reserve(std::min(face_a_intersections.size(), face_b_intersections.size()));
 
       // record the points of intersection between face_a and face_b
@@ -1027,7 +1075,7 @@
       std::cerr << "face pair: "
                 << face_a << ":" << face_b
                 << " N(verts) " << vertices.size() << std::endl;
-      for (std::vector<carve::mesh::MeshSet<3>::vertex_t *>::const_iterator i = vertices.begin(), e = vertices.end(); i != e; ++i) {
+      for (std::vector<meshset_t::vertex_t *>::const_iterator i = vertices.begin(), e = vertices.end(); i != e; ++i) {
         std::cerr << (*i) << " " << (*i)->v << " ("
                   << carve::geom::distance(face_a->plane, (*i)->v) << ","
                   << carve::geom::distance(face_b->plane, (*i)->v) << ")"
@@ -1039,8 +1087,8 @@
 
       // if there are two points of intersection, then the added edge is simple to determine.
       if (vertices.size() == 2) {
-        carve::mesh::MeshSet<3>::vertex_t *v1 = vertices[0];
-        carve::mesh::MeshSet<3>::vertex_t *v2 = vertices[1];
+        meshset_t::vertex_t *v1 = vertices[0];
+        meshset_t::vertex_t *v2 = vertices[1];
         carve::geom3d::Vector c = (v1->v + v2->v) / 2;
 
         // determine whether the midpoint of the implied edge is contained in face_a and face_b
@@ -1068,7 +1116,7 @@
 
       // otherwise, it's more complex.
       carve::geom3d::Vector base, dir;
-      std::vector<carve::mesh::MeshSet<3>::vertex_t *> ordered;
+      std::vector<meshset_t::vertex_t *> ordered;
 
       // skip coplanar edges. this simplifies the resulting
       // mesh. eventually all coplanar face regions of two polyhedra
@@ -1083,8 +1131,8 @@
         // for each possible edge in the ordering, test the midpoint,
         // and record if it's contained in face_a and face_b.
         for (int k = 0, ke = (int)ordered.size() - 1; k < ke; ++k) {
-          carve::mesh::MeshSet<3>::vertex_t *v1 = ordered[k];
-          carve::mesh::MeshSet<3>::vertex_t *v2 = ordered[k + 1];
+          meshset_t::vertex_t *v1 = ordered[k];
+          meshset_t::vertex_t *v2 = ordered[k + 1];
           carve::geom3d::Vector c = (v1->v + v2->v) / 2;
 
 #if defined(CARVE_DEBUG)
@@ -1128,7 +1176,7 @@
 
     carve::line::PolylineSet intersection_graph;
     intersection_graph.vertices.resize(vertices.size());
-    std::map<const carve::mesh::MeshSet<3>::vertex_t *, size_t> vmap;
+    std::map<const meshset_t::vertex_t *, size_t> vmap;
 
     size_t j = 0;
     for (detail::VSet::const_iterator i = vertices.begin(); i != vertices.end(); ++i) {
@@ -1198,9 +1246,9 @@
  * @param b_edge_count 
  * @param hooks 
  */
-void carve::csg::CSG::calc(carve::mesh::MeshSet<3> *a,
+void carve::csg::CSG::calc(meshset_t *a,
                            const face_rtree_t *a_rtree,
-                           carve::mesh::MeshSet<3> *b,
+                           meshset_t *b,
                            const face_rtree_t *b_rtree,
                            carve::csg::VertexClassification &vclass,
                            carve::csg::EdgeClassification &eclass,
@@ -1263,27 +1311,27 @@
 
 #if defined(CARVE_DEBUG_WRITE_PLY_DATA)
   {
-    std::string out("/tmp/a_split.ply");
-    writePLY(out, faceLoopsToPolyhedron(a_face_loops), false);
+    std::auto_ptr<carve::mesh::MeshSet<3> > poly(faceLoopsToPolyhedron(a_face_loops));
+    writePLY("/tmp/a_split.ply", poly.get(), false);
   }
   {
-    std::string out("/tmp/b_split.ply");
-    writePLY(out, faceLoopsToPolyhedron(b_face_loops), false);
+    std::auto_ptr<carve::mesh::MeshSet<3> > poly(faceLoopsToPolyhedron(b_face_loops));
+    writePLY("/tmp/b_split.ply", poly.get(), false);
   }
 #endif
 
-  checkFaceLoopIntegrity(a_face_loops);
-  checkFaceLoopIntegrity(b_face_loops);
+  // checkFaceLoopIntegrity(a_face_loops);
+  // checkFaceLoopIntegrity(b_face_loops);
 
 #if defined(CARVE_DEBUG)
   std::cerr << "classify" << std::endl;
 #endif
   // initialize some classification information.
-  for (std::vector<carve::mesh::MeshSet<3>::vertex_t>::iterator
+  for (std::vector<meshset_t::vertex_t>::iterator
          i = a->vertex_storage.begin(), e = a->vertex_storage.end(); i != e; ++i) {
     vclass[map_vertex(data.vmap, &(*i))].cls[0] = POINT_ON;
   }
-  for (std::vector<carve::mesh::MeshSet<3>::vertex_t>::iterator
+  for (std::vector<meshset_t::vertex_t>::iterator
          i = b->vertex_storage.begin(), e = b->vertex_storage.end(); i != e; ++i) {
     vclass[map_vertex(data.vmap, &(*i))].cls[1] = POINT_ON;
   }
@@ -1354,8 +1402,8 @@
  * 
  * @return 
  */
-carve::mesh::MeshSet<3> *carve::csg::CSG::compute(carve::mesh::MeshSet<3> *a,
-                                                  carve::mesh::MeshSet<3> *b,
+carve::mesh::MeshSet<3> *carve::csg::CSG::compute(meshset_t *a,
+                                                  meshset_t *b,
                                                   carve::csg::CSG::Collector &collector,
                                                   carve::csg::V2Set *shared_edges_ptr,
                                                   CLASSIFY_TYPE classify_type) {
@@ -1374,13 +1422,13 @@
   size_t a_edge_count;
   size_t b_edge_count;
 
-  face_rtree_t *a_rtree = face_rtree_t::construct_STR(a->faceBegin(), a->faceEnd(), 4, 4);
-  face_rtree_t *b_rtree = face_rtree_t::construct_STR(b->faceBegin(), b->faceEnd(), 4, 4);
+  std::auto_ptr<face_rtree_t> a_rtree(face_rtree_t::construct_STR(a->faceBegin(), a->faceEnd(), 4, 4));
+  std::auto_ptr<face_rtree_t> b_rtree(face_rtree_t::construct_STR(b->faceBegin(), b->faceEnd(), 4, 4));
 
   {
     static carve::TimingName FUNC_NAME("CSG::compute - calc()");
     carve::TimingBlock block(FUNC_NAME);
-    calc(a, a_rtree, b, b_rtree, vclass, eclass,a_face_loops, b_face_loops, a_edge_count, b_edge_count);
+    calc(a, a_rtree.get(), b, b_rtree.get(), vclass, eclass,a_face_loops, b_face_loops, a_edge_count, b_edge_count);
   }
 
   detail::LoopEdges a_edge_map;
@@ -1448,11 +1496,11 @@
     classifyFaceGroupsEdge(shared_edges,
                            vclass,
                            a,
-                           a_rtree,
+                           a_rtree.get(),
                            a_loops_grouped,
                            a_edge_map,
                            b,
-                           b_rtree,
+                           b_rtree.get(),
                            b_loops_grouped,
                            b_edge_map,
                            collector);
@@ -1461,20 +1509,20 @@
     classifyFaceGroups(shared_edges,
                        vclass,
                        a,
-                       a_rtree,
+                       a_rtree.get(),
                        a_loops_grouped,
                        a_edge_map,
                        b,
-                       b_rtree,
+                       b_rtree.get(),
                        b_loops_grouped,
                        b_edge_map,
                        collector);
     break;
   }
 
-  carve::mesh::MeshSet<3> *result = collector.done(hooks);
+  meshset_t *result = collector.done(hooks);
   if (result != NULL && shared_edges_ptr != NULL) {
-    std::list<carve::mesh::MeshSet<3> *> result_list;
+    std::list<meshset_t *> result_list;
     result_list.push_back(result);
     returnSharedEdges(shared_edges, result_list, shared_edges_ptr);
   }
@@ -1495,15 +1543,15 @@
  * 
  * @return 
  */
-carve::mesh::MeshSet<3> *carve::csg::CSG::compute(carve::mesh::MeshSet<3> *a,
-                                                  carve::mesh::MeshSet<3> *b,
+carve::mesh::MeshSet<3> *carve::csg::CSG::compute(meshset_t *a,
+                                                  meshset_t *b,
                                                   carve::csg::CSG::OP op,
                                                   carve::csg::V2Set *shared_edges,
                                                   CLASSIFY_TYPE classify_type) {
   Collector *coll = makeCollector(op, a, b);
   if (!coll) return NULL;
 
-  carve::mesh::MeshSet<3> *result = compute(a, b, *coll, shared_edges, classify_type);
+  meshset_t *result = compute(a, b, *coll, shared_edges, classify_type);
      
   delete coll;
 
@@ -1524,9 +1572,9 @@
  * 
  * @return 
  */
-bool carve::csg::CSG::sliceAndClassify(carve::mesh::MeshSet<3> *closed,
-                                       carve::mesh::MeshSet<3> *open,
-                                       std::list<std::pair<FaceClass, carve::mesh::MeshSet<3> *> > &result,
+bool carve::csg::CSG::sliceAndClassify(meshset_t *closed,
+                                       meshset_t *open,
+                                       std::list<std::pair<FaceClass, meshset_t *> > &result,
                                        carve::csg::V2Set *shared_edges_ptr) {
   if (!closed->isClosed()) return false;
   carve::csg::VertexClassification vclass;
@@ -1541,10 +1589,10 @@
   size_t a_edge_count;
   size_t b_edge_count;
 
-  face_rtree_t *closed_rtree = face_rtree_t::construct_STR(closed->faceBegin(), closed->faceEnd(), 4, 4);
-  face_rtree_t *open_rtree = face_rtree_t::construct_STR(open->faceBegin(), open->faceEnd(), 4, 4);
+  std::auto_ptr<face_rtree_t> closed_rtree(face_rtree_t::construct_STR(closed->faceBegin(), closed->faceEnd(), 4, 4));
+  std::auto_ptr<face_rtree_t> open_rtree(face_rtree_t::construct_STR(open->faceBegin(), open->faceEnd(), 4, 4));
 
-  calc(closed, closed_rtree, open, open_rtree, vclass, eclass,a_face_loops, b_face_loops, a_edge_count, b_edge_count);
+  calc(closed, closed_rtree.get(), open, open_rtree.get(), vclass, eclass,a_face_loops, b_face_loops, a_edge_count, b_edge_count);
 
   detail::LoopEdges a_edge_map;
   detail::LoopEdges b_edge_map;
@@ -1562,18 +1610,18 @@
   halfClassifyFaceGroups(shared_edges,
                          vclass,
                          closed,
-                         closed_rtree,
+                         closed_rtree.get(),
                          a_loops_grouped,
                          a_edge_map,
                          open,
-                         open_rtree,
+                         open_rtree.get(),
                          b_loops_grouped,
                          b_edge_map,
                          result);
 
   if (shared_edges_ptr != NULL) {
-    std::list<carve::mesh::MeshSet<3> *> result_list;
-    for (std::list<std::pair<FaceClass, carve::mesh::MeshSet<3> *> >::iterator it = result.begin(); it != result.end(); it++) {
+    std::list<meshset_t *> result_list;
+    for (std::list<std::pair<FaceClass, meshset_t *> >::iterator it = result.begin(); it != result.end(); it++) {
       result_list.push_back(it->second);
     }
     returnSharedEdges(shared_edges, result_list, shared_edges_ptr);
@@ -1593,10 +1641,10 @@
  * @param hooks 
  * @param shared_edges_ptr 
  */
-void carve::csg::CSG::slice(carve::mesh::MeshSet<3> *a,
-                            carve::mesh::MeshSet<3> *b,
-                            std::list<carve::mesh::MeshSet<3> *> &a_sliced,
-                            std::list<carve::mesh::MeshSet<3> *> &b_sliced,
+void carve::csg::CSG::slice(meshset_t *a,
+                            meshset_t *b,
+                            std::list<meshset_t *> &a_sliced,
+                            std::list<meshset_t *> &b_sliced,
                             carve::csg::V2Set *shared_edges_ptr) {
   carve::csg::VertexClassification vclass;
   carve::csg::EdgeClassification eclass;
@@ -1610,10 +1658,10 @@
   size_t a_edge_count;
   size_t b_edge_count;
 
-  face_rtree_t *a_rtree = face_rtree_t::construct_STR(a->faceBegin(), a->faceEnd(), 4, 4);
-  face_rtree_t *b_rtree = face_rtree_t::construct_STR(b->faceBegin(), b->faceEnd(), 4, 4);
+  std::auto_ptr<face_rtree_t> a_rtree(face_rtree_t::construct_STR(a->faceBegin(), a->faceEnd(), 4, 4));
+  std::auto_ptr<face_rtree_t> b_rtree(face_rtree_t::construct_STR(b->faceBegin(), b->faceEnd(), 4, 4));
 
-  calc(a, a_rtree, b, b_rtree, vclass, eclass,a_face_loops, b_face_loops, a_edge_count, b_edge_count);
+  calc(a, a_rtree.get(), b, b_rtree.get(), vclass, eclass,a_face_loops, b_face_loops, a_edge_count, b_edge_count);
 
   detail::LoopEdges a_edge_map;
   detail::LoopEdges b_edge_map;
@@ -1648,7 +1696,7 @@
     delete all;
   }
   if (shared_edges_ptr != NULL) {
-    std::list<carve::mesh::MeshSet<3> *> result_list;
+    std::list<meshset_t *> result_list;
     result_list.insert(result_list.end(), a_sliced.begin(), a_sliced.end());
     result_list.insert(result_list.end(), b_sliced.begin(), b_sliced.end());
     returnSharedEdges(shared_edges, result_list, shared_edges_ptr);
@@ -1666,3 +1714,4 @@
   vertex_intersections.clear();
   vertex_pool.reset();
 }
+
