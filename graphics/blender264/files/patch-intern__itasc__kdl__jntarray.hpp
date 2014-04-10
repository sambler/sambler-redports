--- ./intern/itasc/kdl/jntarray.hpp.orig	2014-04-09 21:08:52.914218281 +0930
+++ ./intern/itasc/kdl/jntarray.hpp	2014-04-09 21:09:19.424216161 +0930
@@ -203,12 +203,12 @@
          * @return true if each element of src1 is within eps of the same
 		 * element in src2, or if both src1 and src2 have no data (ie 0==rows())
          */
-        friend bool Equal(const JntArray& src1,const JntArray& src2,double eps=epsilon);
+        friend bool Equal(const JntArray& src1,const JntArray& src2,double eps);
 
         friend bool operator==(const JntArray& src1,const JntArray& src2);
         //friend bool operator!=(const JntArray& src1,const JntArray& src2);
         };
-
+	bool Equal(const JntArray&,const JntArray&, double = epsilon);
     bool operator==(const JntArray& src1,const JntArray& src2);
     //bool operator!=(const JntArray& src1,const JntArray& src2);
 
