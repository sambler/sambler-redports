--- platform/x11/detect.py.orig	2017-12-28 05:14:45 UTC
+++ platform/x11/detect.py
@@ -52,7 +57,9 @@ def get_opts():
         BoolVariable('use_static_cpp', 'Link stdc++ statically', False),
         BoolVariable('use_sanitizer', 'Use LLVM compiler address sanitizer', False),
         BoolVariable('use_leak_sanitizer', 'Use LLVM compiler memory leaks sanitizer (implies use_sanitizer)', False),
-        BoolVariable('pulseaudio', 'Detect & use pulseaudio', True),
+        BoolVariable('alsa','Detect & Use alsa audio',False),
+        BoolVariable('oss','Detect & Use OSS audio',False),
+        BoolVariable('pulseaudio', 'Detect & Use pulseaudio', False),
         BoolVariable('udev', 'Use udev for gamepad connection callbacks', False),
         EnumVariable('debug_symbols', 'Add debug symbols to release version', 'yes', ('yes', 'no', 'full')),
         BoolVariable('touch', 'Enable touch events', True),
@@ -215,12 +222,18 @@ def configure(env):
 
     ## Flags
 
-    if (os.system("pkg-config --exists alsa") == 0): # 0 means found
-        print("Enabling ALSA")
-        env.Append(CPPFLAGS=["-DALSA_ENABLED"])
-        env.ParseConfig('pkg-config alsa --cflags --libs')
-    else:
-        print("ALSA libraries not found, disabling driver")
+    if env['alsa']:
+        if os.system("pkg-config --exists alsa")==0:
+            print("Enabling ALSA")
+            env.Append(CPPFLAGS=["-DALSA_ENABLED"])
+            env.Append(LIBS=['asound'])
+        else:
+            print("ALSA libraries not found, disabling driver")
+
+    if env['oss']:
+        print("Enabling OSS Audio")
+        env.Append(CPPFLAGS=["-DOSS_ENABLED"])
+        env.Append(CCFLAGS=['-Ithirdparty/rtaudio'])
 
     if env['pulseaudio']:
         if (os.system("pkg-config --exists libpulse-simple") == 0): # 0 means found
