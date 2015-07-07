--- intern/itasc/kdl/framevel.hpp.orig	2011-10-23 17:52:20 UTC
+++ intern/itasc/kdl/framevel.hpp
@@ -110,9 +110,9 @@ public:
     IMETHOD friend void SetToZero(VectorVel& v);
 
 
-    IMETHOD friend bool Equal(const VectorVel& r1,const VectorVel& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const Vector& r1,const VectorVel& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const VectorVel& r1,const Vector& r2,double eps=epsilon);
+    IMETHOD friend bool Equal(const VectorVel& r1,const VectorVel& r2,double eps);
+    IMETHOD friend bool Equal(const Vector& r1,const VectorVel& r2,double eps);
+    IMETHOD friend bool Equal(const VectorVel& r1,const Vector& r2,double eps);
     IMETHOD friend VectorVel operator - (const VectorVel& r);
     IMETHOD friend doubleVel dot(const VectorVel& lhs,const VectorVel& rhs);
     IMETHOD friend doubleVel dot(const VectorVel& lhs,const Vector& rhs);
@@ -166,9 +166,9 @@ public:
     IMETHOD friend RotationVel operator* (const RotationVel& r1,const RotationVel& r2);
     IMETHOD friend RotationVel operator* (const Rotation& r1,const RotationVel& r2);
     IMETHOD friend RotationVel operator* (const RotationVel& r1,const Rotation& r2);
-    IMETHOD friend bool Equal(const RotationVel& r1,const RotationVel& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const Rotation& r1,const RotationVel& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const RotationVel& r1,const Rotation& r2,double eps=epsilon);
+    IMETHOD friend bool Equal(const RotationVel& r1,const RotationVel& r2,double eps);
+    IMETHOD friend bool Equal(const Rotation& r1,const RotationVel& r2,double eps);
+    IMETHOD friend bool Equal(const RotationVel& r1,const Rotation& r2,double eps);
 
     IMETHOD TwistVel Inverse(const TwistVel& arg) const;
     IMETHOD TwistVel Inverse(const Twist& arg) const;
@@ -220,9 +220,9 @@ public:
     IMETHOD friend FrameVel operator * (const FrameVel& f1,const FrameVel& f2);
     IMETHOD friend FrameVel operator * (const Frame& f1,const FrameVel& f2);
     IMETHOD friend FrameVel operator * (const FrameVel& f1,const Frame& f2);
-    IMETHOD friend bool Equal(const FrameVel& r1,const FrameVel& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const Frame& r1,const FrameVel& r2,double eps=epsilon);
-    IMETHOD friend bool Equal(const FrameVel& r1,const Frame& r2,double eps=epsilon);
+    IMETHOD friend bool Equal(const FrameVel& r1,const FrameVel& r2,double eps);
+    IMETHOD friend bool Equal(const Frame& r1,const FrameVel& r2,double eps);
+    IMETHOD friend bool Equal(const FrameVel& r1,const Frame& r2,double eps);
 
     IMETHOD TwistVel  Inverse(const TwistVel& arg) const;
     IMETHOD TwistVel  Inverse(const Twist& arg) const;
@@ -292,9 +292,9 @@ public:
      // = Equality operators
      // do not use operator == because the definition of Equal(.,.) is slightly
      // different.  It compares whether the 2 arguments are equal in an eps-interval
-     IMETHOD friend bool Equal(const TwistVel& a,const TwistVel& b,double eps=epsilon);
-     IMETHOD friend bool Equal(const Twist& a,const TwistVel& b,double eps=epsilon);
-     IMETHOD friend bool Equal(const TwistVel& a,const Twist& b,double eps=epsilon);
+     IMETHOD friend bool Equal(const TwistVel& a,const TwistVel& b,double eps);
+     IMETHOD friend bool Equal(const Twist& a,const TwistVel& b,double eps);
+     IMETHOD friend bool Equal(const TwistVel& a,const Twist& b,double eps);
 
 // = Conversion to other entities
      IMETHOD Twist GetTwist() const;
@@ -305,6 +305,19 @@ public:
 
 };
 
+IMETHOD bool Equal(const VectorVel&,   const VectorVel&,   double = epsilon);
+IMETHOD bool Equal(const Vector&,      const VectorVel&,   double = epsilon);
+IMETHOD bool Equal(const VectorVel&,   const Vector&,      double = epsilon);
+IMETHOD bool Equal(const RotationVel&, const RotationVel&, double = epsilon);
+IMETHOD bool Equal(const Rotation&,    const RotationVel&, double = epsilon);
+IMETHOD bool Equal(const RotationVel&, const Rotation&,    double = epsilon);
+IMETHOD bool Equal(const FrameVel&,    const FrameVel&,    double = epsilon);
+IMETHOD bool Equal(const Frame&,       const FrameVel&,    double = epsilon);
+IMETHOD bool Equal(const FrameVel&,    const Frame&,       double = epsilon);
+IMETHOD bool Equal(const TwistVel&,    const TwistVel&,    double = epsilon);
+IMETHOD bool Equal(const Twist&,       const TwistVel&,    double = epsilon);
+IMETHOD bool Equal(const TwistVel&,    const Twist&,       double = epsilon);
+
 IMETHOD VectorVel diff(const VectorVel& a,const VectorVel& b,double dt=1.0) {
 	return VectorVel(diff(a.p,b.p,dt),diff(a.v,b.v,dt));
 }
