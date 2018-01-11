--- servers/visual_server.cpp.orig	2018-01-10 13:45:37 UTC
+++ servers/visual_server.cpp
@@ -440,9 +440,9 @@ Error VisualServer::_surface_set_data(Ar
 					for (int i = 0; i < p_vertex_array_len; i++) {
 
 						int8_t vector[4] = {
-							CLAMP(src[i].x * 127, -128, 127),
-							CLAMP(src[i].y * 127, -128, 127),
-							CLAMP(src[i].z * 127, -128, 127),
+							static_cast<int8_t>CLAMP(src[i].x * 127, -128, 127),
+							static_cast<int8_t>CLAMP(src[i].y * 127, -128, 127),
+							static_cast<int8_t>CLAMP(src[i].z * 127, -128, 127),
 							0,
 						};
 
@@ -475,10 +475,10 @@ Error VisualServer::_surface_set_data(Ar
 					for (int i = 0; i < p_vertex_array_len; i++) {
 
 						uint8_t xyzw[4] = {
-							CLAMP(src[i * 4 + 0] * 127, -128, 127),
-							CLAMP(src[i * 4 + 1] * 127, -128, 127),
-							CLAMP(src[i * 4 + 2] * 127, -128, 127),
-							CLAMP(src[i * 4 + 3] * 127, -128, 127)
+							static_cast<uint8_t>CLAMP(src[i * 4 + 0] * 127, -128, 127),
+							static_cast<uint8_t>CLAMP(src[i * 4 + 1] * 127, -128, 127),
+							static_cast<uint8_t>CLAMP(src[i * 4 + 2] * 127, -128, 127),
+							static_cast<uint8_t>CLAMP(src[i * 4 + 3] * 127, -128, 127)
 						};
 
 						copymem(&vw[p_offsets[ai] + i * p_stride], xyzw, 4);
