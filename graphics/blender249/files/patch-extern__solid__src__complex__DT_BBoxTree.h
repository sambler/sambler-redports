--- ./extern/solid/src/complex/DT_BBoxTree.h.orig	2013-10-22 23:40:38.746022145 +1030
+++ ./extern/solid/src/complex/DT_BBoxTree.h	2013-10-22 23:40:43.723017954 +1030
@@ -31,6 +31,20 @@
 #include "DT_CBox.h"
 
 
+inline DT_CBox computeCBox(const DT_Convex *p)
+{
+    return DT_CBox(p->bbox()); 
+}
+
+inline DT_CBox computeCBox(MT_Scalar margin, const MT_Transform& xform) 
+{
+    const MT_Matrix3x3& basis = xform.getBasis();
+    return DT_CBox(MT_Point3(MT_Scalar(0.0), MT_Scalar(0.0), MT_Scalar(0.0)), 
+                   MT_Vector3(basis[0].length() * margin, 
+                              basis[1].length() * margin, 
+                              basis[2].length() * margin));
+}
+
 class DT_BBoxTree {
 public:
     enum NodeType { INTERNAL = 0, LEAF = 1 };
