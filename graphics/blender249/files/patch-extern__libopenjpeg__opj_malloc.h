--- extern/libopenjpeg/opj_malloc.h.orig	2009-09-02 00:52:10 UTC
+++ extern/libopenjpeg/opj_malloc.h
@@ -78,7 +78,7 @@
 		#elif defined(__GNUC__)
                         #ifndef __APPLE__
 			    #define HAVE_MEMALIGN
-			    #include <malloc.h>
+			    #include <stdlib.h>
                         #endif
 		/* Linux x86_64 and OSX always align allocations to 16 bytes */
 		#elif !defined(__amd64__) && !defined(__APPLE__)	
