--- intern/cycles/kernel/osl/osl_closures.h.orig	2017-10-31 14:22:48 UTC
+++ intern/cycles/kernel/osl/osl_closures.h
@@ -72,7 +72,7 @@ void name(RendererServices *, int id, vo
 #define CCLOSURE_PREPARE_STATIC(name, classname) static CCLOSURE_PREPARE(name, classname)
 
 #define CLOSURE_FLOAT3_PARAM(st, fld) \
-	{ TypeDesc::TypeVector, reckless_offsetof(st, fld), NULL, sizeof(OSL::Vec3) }
+	{ TypeDesc::TypeVector, (int)reckless_offsetof(st, fld), NULL, sizeof(OSL::Vec3) }
 
 #define TO_VEC3(v) OSL::Vec3(v.x, v.y, v.z)
 #define TO_COLOR3(v) OSL::Color3(v.x, v.y, v.z)
