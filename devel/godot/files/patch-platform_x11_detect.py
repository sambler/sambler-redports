--- platform/x11/detect.py.orig	2014-12-15 18:49:18 UTC
+++ platform/x11/detect.py
@@ -1,13 +1,13 @@
 
 import os
-import sys	
+import sys
 
 
 def is_active():
 	return True
-        
+
 def get_name():
-        return "X11"
+	return "X11"
 
 
 def can_build():
@@ -29,10 +29,10 @@ def can_build():
 		print("X11 not found.. x11 disabled.")
 		return False
 
-        ssl_error=os.system("pkg-config openssl --modversion > /dev/null ")
-        if (ssl_error):
-                print("OpenSSL not found.. x11 disabled.")
-                return False
+		ssl_error=os.system("pkg-config openssl --modversion > /dev/null ")
+		if (ssl_error):
+			print("OpenSSL not found.. x11 disabled.")
+			return False
 
 	x11_error=os.system("pkg-config xcursor --modversion > /dev/null ")
 	if (x11_error):
@@ -55,7 +55,7 @@ def get_flags():
 	('builtin_zlib', 'no'),
 	("openssl", "yes"),
 	("theora","no"),
-        ]
+		]
 			
 
 
@@ -72,9 +72,10 @@ def configure(env):
 
 	env.Append(CPPPATH=['#platform/x11'])
 	if (env["use_llvm"]=="yes"):
-		env["CC"]="clang"
-		env["CXX"]="clang++"
-		env["LD"]="clang++"
+		if 'clang++' not in env['CXX']:
+			env["CC"]="clang"
+			env["CXX"]="clang++"
+			env["LD"]="clang++"
 		if (env["use_sanitizer"]=="yes"):
 			env.Append(CXXFLAGS=['-fsanitize=address','-fno-omit-frame-pointer'])
 			env.Append(LINKFLAGS=['-fsanitize=address'])
@@ -82,6 +83,8 @@ def configure(env):
 		else:
 			env.extra_suffix=".llvm"
 
+	if ("clang++" in env["CXX"]):
+		env.Append(CPPFLAGS=['-DTYPED_METHOD_BIND'])
 
 
 
@@ -128,11 +131,6 @@ def configure(env):
 		env.Append(LINKFLAGS=['-m64','-L/usr/lib/i686-linux-gnu'])
 
 
-	if (env["CXX"]=="clang++"):
-		env.Append(CPPFLAGS=['-DTYPED_METHOD_BIND'])
-		env["CC"]="clang"
-		env["LD"]="clang++"
-
 	import methods
 
 	env.Append( BUILDERS = { 'GLSL120' : env.Builder(action = methods.build_legacygl_headers, suffix = 'glsl.h',src_suffix = '.glsl') } )