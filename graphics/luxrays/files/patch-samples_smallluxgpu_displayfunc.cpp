--- samples/smallluxgpu/displayfunc.cpp.orig	2012-04-20 15:48:02.000000000 +0930
+++ samples/smallluxgpu/displayfunc.cpp	2012-04-20 15:48:09.000000000 +0930
@@ -435,7 +435,9 @@
 
 // Used only when OpenGL Interoperability is enabled
 void idleFunc() {
+#if !defined(LUXRAYS_DISABLE_OPENCL)
 	assert (HasOpenGLInterop());
+#endif
 
 	double raysSec = 0.0;
 	const vector<IntersectionDevice *> &intersectionDevices = config->GetIntersectionDevices();
