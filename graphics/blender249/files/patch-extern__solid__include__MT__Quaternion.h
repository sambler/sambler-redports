--- ./extern/solid/include/MT/Quaternion.h.orig	2013-10-22 23:11:05 UTC
+++ ./extern/solid/include/MT/Quaternion.h
@@ -158,7 +158,7 @@
 
 		Quaternion<Scalar> inverse() const
 		{
-			return conjugate / length2();
+			return conjugate() / length2();
 		}
 		
 		Quaternion<Scalar> slerp(const Quaternion<Scalar>& q, const Scalar& t) const
