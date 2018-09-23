--- intern/cycles/kernel/osl/osl_closures.cpp.orig	2018-02-03 15:12:45 UTC
+++ intern/cycles/kernel/osl/osl_closures.cpp
@@ -242,7 +242,11 @@ static void register_closure(OSL::Shadin
 	/* optimization: it's possible to not use a prepare function at all and
 	 * only initialize the actual class when accessing the closure component
 	 * data, but then we need to map the id to the class somehow */
+#if OSL_LIBRARY_VERSION_CODE >= 10900
+	ss->register_closure(name, id, params, prepare, NULL);
+#else
 	ss->register_closure(name, id, params, prepare, NULL, 16);
+#endif
 }
 
 void OSLShader::register_closures(OSLShadingSystem *ss_)
