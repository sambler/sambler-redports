--- src/liboslexec/shadingsys.cpp.orig	2014-12-26 20:22:53 UTC
+++ src/liboslexec/shadingsys.cpp
@@ -40,13 +40,13 @@ OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 #include "backendllvm.h"
 #include "OSL/oslquery.h"
 
-#include <OpenImageIO/strutil.h>
-#include <OpenImageIO/dassert.h>
-#include <OpenImageIO/thread.h>
-#include <OpenImageIO/timer.h>
-#include <OpenImageIO/filesystem.h>
-#include <OpenImageIO/optparser.h>
-#include <OpenImageIO/fmath.h>
+#include <OpenImageIO14/strutil.h>
+#include <OpenImageIO14/dassert.h>
+#include <OpenImageIO14/thread.h>
+#include <OpenImageIO14/timer.h>
+#include <OpenImageIO14/filesystem.h>
+#include <OpenImageIO14/optparser.h>
+#include <OpenImageIO14/fmath.h>
 
 using namespace OSL;
 using namespace OSL::pvt;
@@ -284,9 +284,10 @@ void
 ShadingSystem::register_closure (string_view name, int id,
                                  const ClosureParam *params,
                                  PrepareClosureFunc prepare,
-                                 SetupClosureFunc setup)
+                                 SetupClosureFunc setup,
+                                 int alignment)
 {
-    return m_impl->register_closure (name, id, params, prepare, setup);
+    return m_impl->register_closure (name, id, params, prepare, setup, alignment);
 }
 
 
@@ -795,7 +796,8 @@ void
 ShadingSystemImpl::register_closure (string_view name, int id,
                                      const ClosureParam *params,
                                      PrepareClosureFunc prepare,
-                                     SetupClosureFunc setup)
+                                     SetupClosureFunc setup,
+                                     int alignment)
 {
     for (int i = 0; params && params[i].type != TypeDesc(); ++i) {
         if (params[i].key == NULL && params[i].type.size() != (size_t)params[i].field_size) {
@@ -803,7 +805,7 @@ ShadingSystemImpl::register_closure (str
             return;
         }
     }
-    m_closure_registry.register_closure(name, id, params, prepare, setup);
+    m_closure_registry.register_closure(name, id, params, prepare, setup, alignment);
 }
 
 
@@ -2484,7 +2486,8 @@ void
 ClosureRegistry::register_closure (string_view name, int id,
                                    const ClosureParam *params,
                                    PrepareClosureFunc prepare,
-                                   SetupClosureFunc setup)
+                                   SetupClosureFunc setup,
+                                   int alignment)
 {
     if (m_closure_table.size() <= (size_t)id)
         m_closure_table.resize(id + 1);
@@ -2508,6 +2511,7 @@ ClosureRegistry::register_closure (strin
     }
     entry.prepare = prepare;
     entry.setup = setup;
+    entry.alignment = alignment;
     m_closure_name_to_id[ustring(name)] = id;
 }
 
