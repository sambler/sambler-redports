--- ./intern/itasc/kdl/jntarrayacc.hpp.orig	2012-05-11 00:16:16.000000000 +0930
+++ ./intern/itasc/kdl/jntarrayacc.hpp	2014-04-09 20:59:24.218217467 +0930
@@ -58,9 +58,10 @@
         friend void Divide(const JntArrayAcc& src,const doubleVel& factor,JntArrayAcc& dest);
         friend void Divide(const JntArrayAcc& src,const doubleAcc& factor,JntArrayAcc& dest);
         friend void SetToZero(JntArrayAcc& array);
-        friend bool Equal(const JntArrayAcc& src1,const JntArrayAcc& src2,double eps=epsilon);
+        friend bool Equal(const JntArrayAcc& src1,const JntArrayAcc& src2,double eps);
 
     };
+    bool Equal(const JntArrayAcc&, const JntArrayAcc&, double = epsilon);
 }
 
 #endif
