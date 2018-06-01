--- src/shaders/MaterialX/build_materialX_osl.py.orig	2018-06-01 07:01:31 UTC
+++ src/shaders/MaterialX/build_materialX_osl.py
@@ -370,11 +370,11 @@ def main():
     args = parser.parse_args()
 
     # create a dictionary of options
-    oslc_exec = 'oslc'
+    oslc_exec = 'oslc_dev'
     types = None
 
     if args.oslc_path != '':
-        oslc_exec = str(os.path.abspath(os.path.join(args.oslc_path, 'oslc')))
+        oslc_exec = str(os.path.abspath(os.path.join(args.oslc_path, 'oslc_dev')))
 
     if args.types != '':
         types = args.types.split(',')
