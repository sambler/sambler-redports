--- ./extern/carve/include/carve/geom3d.hpp.orig	2013-10-23 01:38:56.602021836 +1030
+++ ./extern/carve/include/carve/geom3d.hpp	2013-10-23 01:39:27.512017985 +1030
@@ -206,9 +206,22 @@
      *         * +1, if a is ordered after b around, rotating about direction.
      */
     inline int compareAngles(const Vector &direction, const Vector &base, const Vector &a, const Vector &b) {
-      const double d1 = carve::geom3d::orient3d(carve::geom::VECTOR(0,0,0), direction, a, b);
-      const double d2 = carve::geom3d::orient3d(carve::geom::VECTOR(0,0,0), direction, base, a);
-      const double d3 = carve::geom3d::orient3d(carve::geom::VECTOR(0,0,0), direction, base, b);
+      // double d1 = carve::geom3d::orient3d(carve::geom::VECTOR(0,0,0), direction, a, b);
+      // double d2 = carve::geom3d::orient3d(carve::geom::VECTOR(0,0,0), direction, base, a);
+      // double d3 = carve::geom3d::orient3d(carve::geom::VECTOR(0,0,0), direction, base, b);
+
+#if defined(CARVE_USE_EXACT_PREDICATES)
+      // which is equivalent to the following (which eliminates a
+      // vector subtraction):
+      double d1 = carve::geom3d::orient3d(direction, b, a,    carve::geom::VECTOR(0,0,0));
+      double d2 = carve::geom3d::orient3d(direction, a, base, carve::geom::VECTOR(0,0,0));
+      double d3 = carve::geom3d::orient3d(direction, b, base, carve::geom::VECTOR(0,0,0));
+#else
+      // dotcross = a . (b x c)
+      double d1 = carve::geom::dotcross(direction, b, a   );
+      double d2 = carve::geom::dotcross(direction, a, base);
+      double d3 = carve::geom::dotcross(direction, b, base);
+#endif
 
       // CASE: a and b are coplanar wrt. direction.
       if (d1 == 0.0) {
