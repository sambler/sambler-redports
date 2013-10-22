--- ./extern/libmv/third_party/glog/src/logging.cc.orig	2013-10-23 02:07:07.453021376 +1030
+++ ./extern/libmv/third_party/glog/src/logging.cc	2013-10-23 02:15:03.107018625 +1030
@@ -1243,12 +1243,10 @@
 #endif
 }
 
-#ifdef HAVE___ATTRIBUTE__
+typedef void (*logging_fail_func_t)();
+
 GOOGLE_GLOG_DLL_DECL
-void (*g_logging_fail_func)() __attribute__((noreturn)) = &logging_fail;
-#else
-GOOGLE_GLOG_DLL_DECL void (*g_logging_fail_func)() = &logging_fail;
-#endif
+logging_fail_func_t g_logging_fail_func = &logging_fail;
 
 void InstallFailureFunction(void (*fail_func)()) {
   g_logging_fail_func = fail_func;
