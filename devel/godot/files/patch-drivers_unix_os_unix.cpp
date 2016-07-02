--- drivers/unix/os_unix.cpp.orig	2016-05-13 06:06:31 UTC
+++ drivers/unix/os_unix.cpp
@@ -46,6 +46,7 @@
 
 #ifdef __FreeBSD__
 #include <sys/param.h>
+#include <sys/sysctl.h>
 #endif
 #include <stdarg.h>
 #include <sys/time.h>
@@ -364,17 +365,7 @@ Error OS_Unix::execute(const String& p_p
 			args.push_back((char*)cs[i].get_data());// shitty C cast
 		args.push_back(0);
 
-#ifdef __FreeBSD__
-		if(p_path.find("/")) {
-			// exec name contains path so use it
-			execv(p_path.utf8().get_data(),&args[0]);
-		}else{
-			// use program name and search through PATH to find it
-			execvp(getprogname(),&args[0]);
-		}
-#else
 		execv(p_path.utf8().get_data(),&args[0]);
-#endif
 		// still alive? something failed..
 		fprintf(stderr,"**ERROR** OS_Unix::execute - Could not create child process while executing: %s\n",p_path.utf8().get_data());
 		abort();
@@ -499,11 +490,14 @@ String OS_Unix::get_executable_path() co
 	}
 	return b;
 #elif defined(__FreeBSD__)
-	char resolved_path[MAXPATHLEN];
-
-	realpath(OS::get_executable_path().utf8().get_data(), resolved_path);
-
-	return String(resolved_path);
+	int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PATHNAME, -1 };
+	char buf[MAXPATHLEN];
+	size_t cb = sizeof(buf);
+	if (sysctl(mib, 4, buf, &cb, NULL, 0) != 0)
+		buf[0] = '\0';
+	String b;
+	b.parse_utf8(buf);
+	return b;
 #else
 	ERR_PRINT("Warning, don't know how to obtain executable path on this OS! Please override this function properly.");
 	return OS::get_executable_path();
