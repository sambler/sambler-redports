--- ./source/blender/src/buttons_scene.c.orig	2009-09-02 00:51:46.000000000 +0930
+++ ./source/blender/src/buttons_scene.c	2012-12-14 20:19:39.033422089 +1030
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
