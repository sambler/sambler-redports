--- numpy/distutils/fcompiler/gnu.py.orig	2015-10-04 12:57:36 UTC
+++ numpy/distutils/fcompiler/gnu.py	2015-10-04 12:59:13
@@ -83,7 +83,7 @@ class GnuFCompiler(FCompiler):
             return None
         return v[1]
 
-    possible_executables = ['g77', 'f77']
+    possible_executables = ['%%FC%%', 'g77', 'f77']
     executables = {
         'version_cmd'  : [None, "-dumpversion"],
         'compiler_f77' : [None, "-g", "-Wall", "-fno-second-underscore"],
@@ -107,11 +107,13 @@ class GnuFCompiler(FCompiler):
         for key in ['version_cmd', 'compiler_f77', 'linker_so', 'linker_exe']:
             executables[key].append('-mno-cygwin')
 
-    g2c = 'g2c'
+    g2c = '%%FC%%'
     suggested_f90_compiler = 'gnu95'
 
     def get_flags_linker_so(self):
         opt = self.linker_so[1:]
+        if 'FFLAGS' in os.environ:
+                opt.append(os.environ['FFLAGS'])
         if sys.platform == 'darwin':
             target = os.environ.get('MACOSX_DEPLOYMENT_TARGET', None)
             # If MACOSX_DEPLOYMENT_TARGET is set, we simply trust the value
@@ -265,7 +265,7 @@ class Gnu95FCompiler(GnuFCompiler):
                     self.executables[key].append('-mno-cygwin')
         return v
 
-    possible_executables = ['gfortran', 'f95']
+    possible_executables = ['%%FC%%', 'gfortran', 'f95']
     executables = {
         'version_cmd'  : ["<F90>", "-dumpversion"],
         'compiler_f77' : [None, "-Wall", "-g", "-ffixed-form",
