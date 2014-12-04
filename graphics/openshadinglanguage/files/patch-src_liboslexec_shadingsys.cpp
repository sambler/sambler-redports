--- src/liboslexec/shadingsys.cpp.orig	2014-12-04 12:15:18 UTC
+++ src/liboslexec/shadingsys.cpp
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
 
 
@@ -2474,7 +2476,8 @@ void
 ClosureRegistry::register_closure (string_view name, int id,
                                    const ClosureParam *params,
                                    PrepareClosureFunc prepare,
-                                   SetupClosureFunc setup)
+                                   SetupClosureFunc setup,
+                                   int alignment)
 {
     if (m_closure_table.size() <= (size_t)id)
         m_closure_table.resize(id + 1);
@@ -2498,6 +2501,7 @@ ClosureRegistry::register_closure (strin
     }
     entry.prepare = prepare;
     entry.setup = setup;
+    entry.alignment = alignment;
     m_closure_name_to_id[ustring(name)] = id;
 }
 
