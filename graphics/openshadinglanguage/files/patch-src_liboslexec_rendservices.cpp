--- ./src/liboslexec/rendservices.cpp.orig	2015-03-13 15:36:48.428852563 +1030
+++ ./src/liboslexec/rendservices.cpp	2015-03-13 15:36:55.908851169 +1030
@@ -171,7 +171,7 @@
         texture_thread_info = context->texture_thread_info();
     bool status;
     if (texture_handle)
-        status = status = texturesys()->texture (texture_handle, texture_thread_info,
+        status = texturesys()->texture (texture_handle, texture_thread_info,
                                         options, s, t, dsdx, dtdx, dsdy, dtdy,
                                         nchannels, result, dresultds, dresultdt);
     else
