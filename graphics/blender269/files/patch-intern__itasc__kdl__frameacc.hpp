--- ./intern/itasc/kdl/frameacc.hpp.orig	2012-05-11 00:16:16.000000000 +0930
+++ ./intern/itasc/kdl/frameacc.hpp	2014-04-09 20:59:24.211217472 +0930
@@ -78,9 +78,9 @@
     IMETHOD friend VectorAcc operator / (const VectorAcc& r2,const doubleAcc& r1);
 
 
-    IMETHOD friend bool Equal(const VectorAcc& r1,const VectorAcc& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const Vector& r1,const VectorAcc& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const VectorAcc& r1,const Vector& r2,double eps=epsilon);
+    IMETHOD friend bool Equal(const VectorAcc& r1,const VectorAcc& r2,double eps);
+    IMETHOD friend bool Equal(const Vector& r1,const VectorAcc& r2,double eps);
+    IMETHOD friend bool Equal(const VectorAcc& r1,const Vector& r2,double eps);
     IMETHOD friend VectorAcc operator - (const VectorAcc& r);
     IMETHOD friend doubleAcc dot(const VectorAcc& lhs,const VectorAcc& rhs);
     IMETHOD friend doubleAcc dot(const VectorAcc& lhs,const Vector& rhs);
@@ -132,9 +132,9 @@
     IMETHOD friend RotationAcc operator* (const RotationAcc& r1,const RotationAcc& r2);
     IMETHOD friend RotationAcc operator* (const Rotation& r1,const RotationAcc& r2);
     IMETHOD friend RotationAcc operator* (const RotationAcc& r1,const Rotation& r2);
-    IMETHOD friend bool Equal(const RotationAcc& r1,const RotationAcc& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const Rotation& r1,const RotationAcc& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const RotationAcc& r1,const Rotation& r2,double eps=epsilon);
+    IMETHOD friend bool Equal(const RotationAcc& r1,const RotationAcc& r2,double eps);
+    IMETHOD friend bool Equal(const Rotation& r1,const RotationAcc& r2,double eps);
+    IMETHOD friend bool Equal(const RotationAcc& r1,const Rotation& r2,double eps);
     IMETHOD TwistAcc Inverse(const TwistAcc& arg) const;
     IMETHOD TwistAcc Inverse(const Twist& arg) const;
     IMETHOD TwistAcc operator * (const TwistAcc& arg) const;
@@ -170,9 +170,9 @@
     IMETHOD friend FrameAcc operator * (const FrameAcc& f1,const FrameAcc& f2);
     IMETHOD friend FrameAcc operator * (const Frame& f1,const FrameAcc& f2);
     IMETHOD friend FrameAcc operator * (const FrameAcc& f1,const Frame& f2);
-    IMETHOD friend bool Equal(const FrameAcc& r1,const FrameAcc& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const Frame& r1,const FrameAcc& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const FrameAcc& r1,const Frame& r2,double eps=epsilon);
+    IMETHOD friend bool Equal(const FrameAcc& r1,const FrameAcc& r2,double eps);
+    IMETHOD friend bool Equal(const Frame& r1,const FrameAcc& r2,double eps);
+    IMETHOD friend bool Equal(const FrameAcc& r1,const Frame& r2,double eps);
 
     IMETHOD TwistAcc  Inverse(const TwistAcc& arg) const;
     IMETHOD TwistAcc  Inverse(const Twist& arg) const;
@@ -226,9 +226,9 @@
      // the new point.
      // Complexity : 6M+6A
 
-     IMETHOD friend bool Equal(const TwistAcc& a,const TwistAcc& b,double eps=epsilon);
-     IMETHOD friend bool Equal(const Twist& a,const TwistAcc& b,double eps=epsilon);
-     IMETHOD friend bool Equal(const TwistAcc& a,const Twist& b,double eps=epsilon);
+     IMETHOD friend bool Equal(const TwistAcc& a,const TwistAcc& b,double eps);
+     IMETHOD friend bool Equal(const Twist& a,const TwistAcc& b,double eps);
+     IMETHOD friend bool Equal(const TwistAcc& a,const Twist& b,double eps);
 
 
      IMETHOD Twist GetTwist() const;
@@ -240,10 +240,18 @@
 };
 
 
-
-
-
-
+IMETHOD bool Equal(const VectorAcc&,   const VectorAcc&,   double = epsilon);
+IMETHOD bool Equal(const Vector&,      const VectorAcc&,   double = epsilon);
+IMETHOD bool Equal(const VectorAcc&,   const Vector&,      double = epsilon);
+IMETHOD bool Equal(const RotationAcc&, const RotationAcc&, double = epsilon);
+IMETHOD bool Equal(const Rotation&,    const RotationAcc&, double = epsilon);
+IMETHOD bool Equal(const RotationAcc&, const Rotation&,    double = epsilon);
+IMETHOD bool Equal(const FrameAcc&,    const FrameAcc&,    double = epsilon);
+IMETHOD bool Equal(const Frame&,       const FrameAcc&,    double = epsilon);
+IMETHOD bool Equal(const FrameAcc&,    const Frame&,       double = epsilon);
+IMETHOD bool Equal(const TwistAcc&,    const TwistAcc&,    double = epsilon);
+IMETHOD bool Equal(const Twist&,       const TwistAcc&,    double = epsilon);
+IMETHOD bool Equal(const TwistAcc&,    const Twist&,       double = epsilon);
 
 #ifdef KDL_INLINE
 #include "frameacc.inl"
