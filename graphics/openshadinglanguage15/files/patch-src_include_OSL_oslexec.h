--- src/include/OSL/oslexec.h.orig	2014-12-26 20:22:53 UTC
+++ src/include/OSL/oslexec.h
@@ -33,8 +33,8 @@ OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 #include "OSL/shaderglobals.h"
 #include "OSL/rendererservices.h"
 
-#include <OpenImageIO/refcnt.h>
-#include <OpenImageIO/ustring.h>
+#include <OpenImageIO14/refcnt.h>
+#include <OpenImageIO14/ustring.h>
 
 
 OSL_NAMESPACE_ENTER
@@ -418,7 +418,8 @@ public:
     std::string getstats (int level=1) const;
 
     void register_closure (string_view name, int id, const ClosureParam *params,
-                           PrepareClosureFunc prepare, SetupClosureFunc setup);
+                           PrepareClosureFunc prepare, SetupClosureFunc setup,
+                           int alignment = 1);
     /// Query either by name or id an existing closure. If name is non
     /// NULL it will use it for the search, otherwise id would be used
     /// and the name will be placed in name if successful. Also return
