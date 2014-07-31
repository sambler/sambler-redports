--- ./src/Main/MainPy.cpp.orig	2014-07-14 01:03:02.000000000 +0930
+++ ./src/Main/MainPy.cpp	2014-07-29 14:42:03.565400281 +0930
@@ -142,6 +142,20 @@
         strncpy(argv[0], buf, PATH_MAX);
         argv[0][PATH_MAX-1] = '\0'; // ensure null termination
         free(buf);
+#elif defined(__FreeBSD__)
+        putenv("LANG=C");
+        putenv("LC_ALL=C");
+        // get whole path of the library
+        Dl_info info;
+        int ret = dladdr((void*)initFreeCAD, &info);
+        if ((ret == 0) || (!info.dli_fname)) {
+            PyErr_SetString(PyExc_ImportError, "Cannot get path of the FreeCAD module!");
+            return;
+        }
+
+        argv[0] = (char*)malloc(PATH_MAX);
+        strncpy(argv[0], info.dli_fname,PATH_MAX);
+        argv[0][PATH_MAX-1] = '\0'; // ensure null termination
 #else
 # error "Implement: Retrieve the path of the module for your platform."
 #endif
