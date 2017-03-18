--- ./source/blender/src/buttons_scene.c.orig	2009-09-02 00:51:46 UTC
+++ ./source/blender/src/buttons_scene.c
@@ -2723,12 +2723,12 @@
 	switch (o->type) {
 	case FF_OPT_TYPE_INT:
 	case FF_OPT_TYPE_INT64:
-		val.i = o->default_val;
+		val.i = o->default_val.i64;
 		idp_type = IDP_INT;
 		break;
 	case FF_OPT_TYPE_DOUBLE:
 	case FF_OPT_TYPE_FLOAT:
-		val.f = o->default_val;
+		val.f = o->default_val.dbl;
 		idp_type = IDP_FLOAT;
 		break;
 	case FF_OPT_TYPE_STRING:
