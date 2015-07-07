--- intern/itasc/kdl/jacobian.hpp.orig	2009-07-14 15:36:21 UTC
+++ intern/itasc/kdl/jacobian.hpp
@@ -45,7 +45,7 @@ namespace KDL
         bool operator ==(const Jacobian& arg);
         bool operator !=(const Jacobian& arg);
         
-        friend bool Equal(const Jacobian& a,const Jacobian& b,double eps=epsilon);
+        friend bool Equal(const Jacobian& a,const Jacobian& b,double eps);
         
 
         ~Jacobian();
@@ -63,6 +63,7 @@ namespace KDL
 
 
     };
+    bool Equal(const Jacobian&, const Jacobian&, double = epsilon);
 }
 
 #endif
