--- src/include/osl_pvt.h.orig	2017-09-01 22:48:03 UTC
+++ src/include/osl_pvt.h
@@ -29,14 +29,12 @@ OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 #ifndef OSL_PVT_H
 #define OSL_PVT_H
 
+#include <memory>
+
 #include "oslconfig.h"
 
 #include "OpenImageIO/dassert.h"
 
-#include <boost/tr1/memory.hpp>
-using std::tr1::shared_ptr;
-
-
 OSL_NAMESPACE_ENTER
 namespace pvt {
 
