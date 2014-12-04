--- src/include/OSL/oslexec.h.orig	2014-12-04 11:59:48 UTC
+++ src/include/OSL/oslexec.h
@@ -418,7 +418,8 @@ public:
     std::string getstats (int level=1) const;
 
     void register_closure (string_view name, int id, const ClosureParam *params,
-                           PrepareClosureFunc prepare, SetupClosureFunc setup);
+                           PrepareClosureFunc prepare, SetupClosureFunc setup,
+                           int alignment = 1);
     /// Query either by name or id an existing closure. If name is non
     /// NULL it will use it for the search, otherwise id would be used
     /// and the name will be placed in name if successful. Also return
