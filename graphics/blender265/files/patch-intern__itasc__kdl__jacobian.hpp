--- ./intern/itasc/kdl/jacobian.hpp.orig	2012-05-11 00:16:16.000000000 +0930
+++ ./intern/itasc/kdl/jacobian.hpp	2014-04-09 20:59:24.216216945 +0930
@@ -45,7 +45,7 @@
         bool operator ==(const Jacobian& arg);
         bool operator !=(const Jacobian& arg);
         
-        friend bool Equal(const Jacobian& a,const Jacobian& b,double eps=epsilon);
+        friend bool Equal(const Jacobian& a,const Jacobian& b,double eps);
         
 
         ~Jacobian();
@@ -63,6 +63,7 @@
 
 
     };
+    bool Equal(const Jacobian&, const Jacobian&, double = epsilon);
 }
 
 #endif
