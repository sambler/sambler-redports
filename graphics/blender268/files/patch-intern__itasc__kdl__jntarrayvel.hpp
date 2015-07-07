--- intern/itasc/kdl/jntarrayvel.hpp.orig	2009-07-14 15:36:21 UTC
+++ intern/itasc/kdl/jntarrayvel.hpp
@@ -51,9 +51,10 @@ namespace KDL
         friend void Divide(const JntArrayVel& src,const double& factor,JntArrayVel& dest);
         friend void Divide(const JntArrayVel& src,const doubleVel& factor,JntArrayVel& dest);
         friend void SetToZero(JntArrayVel& array);
-        friend bool Equal(const JntArrayVel& src1,const JntArrayVel& src2,double eps=epsilon);
+        friend bool Equal(const JntArrayVel& src1,const JntArrayVel& src2,double eps);
 
     };
+    bool Equal(const JntArrayVel&, const JntArrayVel&, double = epsilon);
 }
 
 #endif
