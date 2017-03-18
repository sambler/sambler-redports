--- ./extern/carve/include/carve/geom_impl.hpp.orig	2013-10-23 01:39:54 UTC
+++ ./extern/carve/include/carve/geom_impl.hpp
@@ -396,7 +396,7 @@
       // Compute a . (b x c)
       return
         (a.x * b.y * c.z + a.y * b.z * c.x + a.z * b.x * c.y) -
-        (a.x * b.z * c.y + a.y * b.x * c.z + a.z * b.y * c.x);
+        (a.x * c.y * b.z + a.y * c.z * b.x + a.z * c.x * b.y);
     }
 
 
