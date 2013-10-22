--- ./extern/solid/src/complex/DT_Complex.cpp.orig	2009-09-02 00:53:23.000000000 +0930
+++ ./extern/solid/src/complex/DT_Complex.cpp	2013-10-22 23:45:32.289017855 +1030
@@ -118,20 +118,6 @@
     return MT_BBox(center - extent, center + extent);
 }
 
-inline DT_CBox computeCBox(const DT_Convex *p)
-{
-    return DT_CBox(p->bbox()); 
-}
-
-inline DT_CBox computeCBox(MT_Scalar margin, const MT_Transform& xform) 
-{
-    const MT_Matrix3x3& basis = xform.getBasis();
-    return DT_CBox(MT_Point3(MT_Scalar(0.0), MT_Scalar(0.0), MT_Scalar(0.0)), 
-                   MT_Vector3(basis[0].length() * margin, 
-                              basis[1].length() * margin, 
-                              basis[2].length() * margin));
-} 
-
 void DT_Complex::refit()
 {
     DT_RootData<const DT_Convex *> rd(m_nodes, m_leaves);
