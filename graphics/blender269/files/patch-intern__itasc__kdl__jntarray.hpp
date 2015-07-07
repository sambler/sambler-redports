--- intern/itasc/kdl/jntarray.hpp.orig	2012-06-07 08:16:41 UTC
+++ intern/itasc/kdl/jntarray.hpp
@@ -209,12 +209,12 @@ class MyTask : public RTT::TaskContext
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
 
