--- intern/itasc/kdl/jntarrayacc.hpp.orig	2009-07-14 15:36:21 UTC
+++ intern/itasc/kdl/jntarrayacc.hpp
@@ -58,9 +58,10 @@ namespace KDL
         friend void Divide(const JntArrayAcc& src,const doubleVel& factor,JntArrayAcc& dest);
         friend void Divide(const JntArrayAcc& src,const doubleAcc& factor,JntArrayAcc& dest);
         friend void SetToZero(JntArrayAcc& array);
-        friend bool Equal(const JntArrayAcc& src1,const JntArrayAcc& src2,double eps=epsilon);
+        friend bool Equal(const JntArrayAcc& src1,const JntArrayAcc& src2,double eps);
 
     };
+    bool Equal(const JntArrayAcc&, const JntArrayAcc&, double = epsilon);
 }
 
 #endif
