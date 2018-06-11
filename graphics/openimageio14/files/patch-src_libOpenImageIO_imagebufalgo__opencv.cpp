--- src/libOpenImageIO/imagebufalgo_opencv.cpp.orig	2018-06-11 18:55:12 UTC
+++ src/libOpenImageIO/imagebufalgo_opencv.cpp
@@ -66,17 +66,17 @@ ImageBufAlgo::from_IplImage (ImageBuf &d
 #ifdef USE_OPENCV
     TypeDesc srcformat;
     switch (ipl->depth) {
-    case IPL_DEPTH_8U :
+    case int(IPL_DEPTH_8U) :
         srcformat = TypeDesc::UINT8;  break;
-    case IPL_DEPTH_8S :
+    case int(IPL_DEPTH_8S) :
         srcformat = TypeDesc::INT8;  break;
-    case IPL_DEPTH_16U :
+    case int(IPL_DEPTH_16U) :
         srcformat = TypeDesc::UINT16;  break;
-    case IPL_DEPTH_16S :
+    case int(IPL_DEPTH_16S) :
         srcformat = TypeDesc::INT16;  break;
-    case IPL_DEPTH_32F :
+    case int(IPL_DEPTH_32F) :
         srcformat = TypeDesc::FLOAT;  break;
-    case IPL_DEPTH_64F :
+    case int(IPL_DEPTH_64F) :
         srcformat = TypeDesc::DOUBLE;  break;
     default:
         DASSERT (0 && "unknown IplImage type");
