--- ./intern/itasc/kdl/frames.hpp.orig	2012-05-11 00:16:16.000000000 +0930
+++ ./intern/itasc/kdl/frames.hpp	2014-04-09 20:59:24.213216750 +0930
@@ -245,10 +245,10 @@
 
      //! do not use operator == because the definition of Equal(.,.) is slightly
      //! different.  It compares whether the 2 arguments are equal in an eps-interval
-     inline friend bool Equal(const Vector& a,const Vector& b,double eps=epsilon);
+     inline friend bool Equal(const Vector& a,const Vector& b,double eps);
 
 	 //! return a normalized vector
-	 inline friend Vector Normalize(const Vector& a, double eps=epsilon);
+	 inline friend Vector Normalize(const Vector& a, double eps);
 
 	 //! The literal equality operator==(), also identical.
      inline friend bool operator==(const Vector& a,const Vector& b);
@@ -258,7 +258,7 @@
      friend class Rotation;
      friend class Frame;
 };
-
+	inline Vector Normalize(const Vector&, double eps=epsilon);
 
 /**
   \brief represents rotations in 3 dimensional space.
@@ -499,7 +499,7 @@
 
      //! do not use operator == because the definition of Equal(.,.) is slightly
      //! different.  It compares whether the 2 arguments are equal in an eps-interval
-     friend bool Equal(const Rotation& a,const Rotation& b,double eps=epsilon);
+
 
 	 //! The literal equality operator==(), also identical.
      friend bool operator==(const Rotation& a,const Rotation& b);
@@ -660,7 +660,7 @@
 
      //! do not use operator == because the definition of Equal(.,.) is slightly
      //! different.  It compares whether the 2 arguments are equal in an eps-interval
-     inline friend bool Equal(const Frame& a,const Frame& b,double eps=epsilon);
+     inline friend bool Equal(const Frame& a,const Frame& b,double eps);
 
 	 //! The literal equality operator==(), also identical.
      inline friend bool operator==(const Frame& a,const Frame& b);
@@ -732,7 +732,7 @@
 
      //! do not use operator == because the definition of Equal(.,.) is slightly
      //! different.  It compares whether the 2 arguments are equal in an eps-interval
-     inline friend bool Equal(const Twist& a,const Twist& b,double eps=epsilon);
+     inline friend bool Equal(const Twist& a,const Twist& b,double eps);
 
 	 //! The literal equality operator==(), also identical.
      inline friend bool operator==(const Twist& a,const Twist& b);
@@ -895,7 +895,7 @@
 
      //! do not use operator == because the definition of Equal(.,.) is slightly
      //! different.  It compares whether the 2 arguments are equal in an eps-interval
-     inline friend bool Equal(const Wrench& a,const Wrench& b,double eps=epsilon);
+     inline friend bool Equal(const Wrench& a,const Wrench& b,double eps);
 
 	 //! The literal equality operator==(), also identical.
      inline friend bool operator==(const Wrench& a,const Wrench& b);
@@ -976,7 +976,7 @@
 
      //! do not use operator == because the definition of Equal(.,.) is slightly
      //! different.  It compares whether the 2 arguments are equal in an eps-interval
-     inline friend bool Equal(const Vector2& a,const Vector2& b,double eps=epsilon);
+     inline friend bool Equal(const Vector2& a,const Vector2& b,double eps);
 
     friend class Rotation2;
 };
@@ -1023,7 +1023,7 @@
 
      //! do not use operator == because the definition of Equal(.,.) is slightly
      //! different.  It compares whether the 2 arguments are equal in an eps-interval
-     inline friend bool Equal(const Rotation2& a,const Rotation2& b,double eps=epsilon);
+     inline friend bool Equal(const Rotation2& a,const Rotation2& b,double eps);
 };
 
 //! A 2D frame class, for further documentation see the Frames class
@@ -1064,9 +1064,18 @@
         tmp.SetIdentity();
         return tmp;
      }
-     inline friend bool Equal(const Frame2& a,const Frame2& b,double eps=epsilon);
+     inline friend bool Equal(const Frame2& a,const Frame2& b,double eps);
 };
 
+inline bool Equal(const Vector&,    const Vector&,    double = epsilon);
+       bool Equal(const Rotation&,  const Rotation&,  double = epsilon);
+inline bool Equal(const Frame&,     const Frame&,     double = epsilon);
+inline bool Equal(const Twist&,     const Twist&,     double = epsilon);
+inline bool Equal(const Wrench&,    const Wrench&,    double = epsilon);
+inline bool Equal(const Vector2&,   const Vector2&,   double = epsilon);
+inline bool Equal(const Rotation2&, const Rotation2&, double = epsilon);
+inline bool Equal(const Frame2&,    const Frame2&,    double = epsilon);
+
 IMETHOD Vector diff(const Vector& a,const Vector& b,double dt=1);
 IMETHOD Vector diff(const Rotation& R_a_b1,const Rotation& R_a_b2,double dt=1);
 IMETHOD Twist diff(const Frame& F_a_b1,const Frame& F_a_b2,double dt=1);
