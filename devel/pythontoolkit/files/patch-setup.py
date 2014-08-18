--- ./setup.py.orig	2014-04-04 21:02:12.000000000 +1030
+++ ./setup.py	2014-08-18 16:55:52.109455004 +0930
@@ -69,6 +69,10 @@
     #installing on mac
     MODE = 'mac'
 
+elif sys.platform.startswith('freebsd'):
+    #installing on mac
+    MODE = 'freebsd'
+
 else:
     #installing on linux
     MODE = 'linux'
@@ -130,6 +134,21 @@
     DATA_FILES = [ ]
     #TODO add mac launch script??? where does this go on a mac?
 
+elif MODE == 'freebsd':
+    #installing on FreeBSD
+
+    #On freebsd we want to be able to type PTK to start the app using PTK
+    #so make a copy and use that as the script
+    shutil.copyfile('PTK.pyw', 'PTK')
+    shutil.copyfile('PTKengine.pyw', 'PTKengine')
+    SCRIPTS = ['PTK','PTKengine']
+
+    PACKAGE_DATA = {'ptk_lib': ['resources/tips.txt',   
+                                'resources/ptk.ico',
+                                'resources/ptkicon.svg']}
+    DATA_FILES = [  ( '%%LOCALBASE%%/share/applications', ['linux/PTK%%SUFFIX%%.desktop'] ),
+                    ( '%%LOCALBASE%%/share/pixmaps', ['ptk_lib/resources/ptkicon%%SUFFIX%%.svg']) ]
+
 elif MODE == 'linux':
     #installing on linux
 
