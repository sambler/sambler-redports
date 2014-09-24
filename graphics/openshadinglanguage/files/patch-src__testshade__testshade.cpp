--- src/testshade/testshade.cpp.orig	2014-07-30 17:38:26 UTC
+++ src/testshade/testshade.cpp
@@ -731,7 +731,7 @@
         int num_layers = 0;
         shadingsys->getattribute (shadergroup.get(), "num_layers", num_layers);
         if (num_layers > 0) {
-            std::vector<const char *> layers (num_layers, NULL);
+            std::vector<const char *> layers ((size_t)num_layers, NULL);
             shadingsys->getattribute (shadergroup.get(), "layer_names",
                                       TypeDesc(TypeDesc::STRING, num_layers),
                                       &layers[0]);
