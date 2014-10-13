--- intern/cycles/kernel/kernel_types.h.orig	2014-10-12 21:44:48 UTC
+++ intern/cycles/kernel/kernel_types.h
@@ -542,7 +542,7 @@
 typedef struct ShaderClosure {
 	ClosureType type;
 	float3 weight;
-#ifndef __APPLE__
+#if !defined(__APPLE__) && !defined(__FreeBSD__)
 	float sample_weight;
 #endif
 	float data0;
@@ -551,7 +551,7 @@
 
 	float3 N;
 	float3 T;
-#ifdef __APPLE__
+#if defined(__APPLE__) || defined(__FreeBSD__)
 	float sample_weight;
 #endif
 #ifdef __OSL__
