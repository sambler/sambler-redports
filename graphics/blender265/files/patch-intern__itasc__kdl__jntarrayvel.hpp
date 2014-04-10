--- ./intern/itasc/kdl/jntarrayvel.hpp.orig	2012-05-11 00:16:16.000000000 +0930
+++ ./intern/itasc/kdl/jntarrayvel.hpp	2014-04-09 20:59:24.219217004 +0930
@@ -51,9 +51,10 @@
         friend void Divide(const JntArrayVel& src,const double& factor,JntArrayVel& dest);
         friend void Divide(const JntArrayVel& src,const doubleVel& factor,JntArrayVel& dest);
         friend void SetToZero(JntArrayVel& array);
-        friend bool Equal(const JntArrayVel& src1,const JntArrayVel& src2,double eps=epsilon);
+        friend bool Equal(const JntArrayVel& src1,const JntArrayVel& src2,double eps);
 
     };
+    bool Equal(const JntArrayVel&, const JntArrayVel&, double = epsilon);
 }
 
 #endif
