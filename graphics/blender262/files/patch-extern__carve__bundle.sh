--- ./extern/carve/bundle.sh.orig	2013-10-23 01:55:16 UTC
+++ ./extern/carve/bundle.sh
@@ -1,7 +1,9 @@
 #!/bin/sh
 
-if [ -d ./.svn ]; then
-  echo "This script is supposed to work only when using git-svn"
+if [ "x$1" = "x--i-really-know-what-im-doing" ] ; then
+  echo Proceeding as requested by command line ...
+else
+  echo "*** Please run again with --i-really-know-what-im-doing ..."
   exit 1
 fi
 
@@ -14,8 +16,8 @@
   cat ./patches/$p | patch -d $tmp/carve -p1
 done
 
-rm -rf include
-rm -rf lib
+find include -type f -not -iwholename '*.svn*' -exec rm -rf {} \;
+find lib -type f -not -iwholename '*.svn*' -exec rm -rf {} \;
 
 cat "files.txt" | while read f; do
   mkdir -p `dirname $f`
@@ -24,9 +26,9 @@
 
 rm -rf $tmp
 
-sources=`find ./lib -type f -iname '*.cc' -or -iname '*.cpp' -or -iname '*.c' | sed -r 's/^\.\//\t/'`
-headers=`find ./lib -type f -iname '*.h' -or -iname '*.hpp' | sed -r 's/^\.\//\t/'`
-includes=`find ./include -type f -iname '*.h' -or -iname '*.hpp' | sed -r 's/^\.\//\t/'`
+sources=`find ./lib -type f -iname '*.cc' -or -iname '*.cpp' -or -iname '*.c' | sed -r 's/^\.\//\t/' | sort -d`
+headers=`find ./lib -type f -iname '*.h' -or -iname '*.hpp' | sed -r 's/^\.\//\t/' | sort -d`
+includes=`find ./include -type f -iname '*.h' -or -iname '*.hpp' | sed -r 's/^\.\//\t/' | sort -d`
 
 mkdir -p include/carve/external/boost
 cp patches/files/random.hpp include/carve/external/boost/random.hpp
@@ -47,7 +49,7 @@
 #
 # You should have received a copy of the GNU General Public License
 # along with this program; if not, write to the Free Software Foundation,
-# Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
+# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 #
 # The Original Code is Copyright (C) 2006, Blender Foundation
 # All rights reserved.
@@ -89,7 +91,7 @@
 		-DCARVE_SYSTEM_BOOST
 	)
 
-	list(APPEND INC
+	list(APPEND INC_SYS
 		\${BOOST_INCLUDE_DIR}
 	)
 endif()
@@ -114,7 +116,7 @@
 if env['WITH_BF_BOOST']:
     if env['OURPLATFORM'] not in ('win32-vc', 'win64-vc'):
         # Boost is setting as preferred collections library in the Carve code when using MSVC compiler
-        if env['OURPLATFORM'] != 'win32-mingw':
+        if env['OURPLATFORM'] not in ('win32-mingw', 'win64-mingw'):
             defs.append('HAVE_BOOST_UNORDERED_COLLECTIONS')
 
     defs.append('CARVE_SYSTEM_BOOST')
@@ -122,3 +124,4 @@
 
 env.BlenderLib ('extern_carve', Split(sources), incs, defs, libtype=['extern'], priority=[40] )
 EOF
+
