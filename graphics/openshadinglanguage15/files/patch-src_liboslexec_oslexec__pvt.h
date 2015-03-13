--- src/liboslexec/oslexec_pvt.h.orig	2014-12-26 20:22:53 UTC
+++ src/liboslexec/oslexec_pvt.h
@@ -39,11 +39,12 @@ OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 #include <boost/unordered_map.hpp>
 #include <boost/intrusive_ptr.hpp>
 
-#include <OpenImageIO/ustring.h>
-#include <OpenImageIO/thread.h>
-#include <OpenImageIO/paramlist.h>
-#include <OpenImageIO/refcnt.h>
+#include <OpenImageIO14/ustring.h>
+#include <OpenImageIO14/thread.h>
+#include <OpenImageIO14/paramlist.h>
+#include <OpenImageIO14/refcnt.h>
 
+#include "OSL/genclosure.h"
 #include "OSL/oslexec.h"
 #include "OSL/oslclosure.h"
 #include "osl_pvt.h"
@@ -634,13 +635,16 @@ public:
         std::vector<ClosureParam> params;
         // the needed size for the structure
         int                       struct_size;
+        // the needed alignment of the structure
+        int                       alignment;
         // Creation callbacks
         PrepareClosureFunc        prepare;
         SetupClosureFunc          setup;
     };
 
     void register_closure (string_view name, int id, const ClosureParam *params,
-                           PrepareClosureFunc prepare, SetupClosureFunc setup);
+                           PrepareClosureFunc prepare, SetupClosureFunc setup,
+                           int alignment = 1);
 
     const ClosureEntry *get_entry (ustring name) const;
     const ClosureEntry *get_entry (int id) const {
@@ -796,7 +800,8 @@ public:
     ustring *alloc_string_constants (size_t n) { return m_string_pool.alloc (n); }
 
     void register_closure (string_view name, int id, const ClosureParam *params,
-                           PrepareClosureFunc prepare, SetupClosureFunc setup);
+                           PrepareClosureFunc prepare, SetupClosureFunc setup,
+                           int alignment = 1);
     bool query_closure (const char **name, int *id,
                         const ClosureParam **params);
     const ClosureRegistry::ClosureEntry *find_closure(ustring name) const {
@@ -1056,19 +1061,24 @@ public:
     char * alloc(size_t size, size_t alignment=1) {
         // Alignment must be power of two
         DASSERT ((alignment & (alignment - 1)) == 0);
-        // Fail if beyond allocation limits or senseless alignment
-        if (size > BlockSize || (size & (alignment - 1)) != 0)
+        // Fail if beyond allocation limits (we make sure there's enough space
+        // for alignment padding here as well).
+        if (size + alignment - 1 > BlockSize)
             return NULL;
-        m_block_offset -= (m_block_offset & (alignment - 1)); // Fix up alignment
-        if (size <= m_block_offset) {
+        // Fix up alignment
+        size_t alignment_offset = alignment_offset_calc(alignment);
+        if (size + alignment_offset <= m_block_offset) {
             // Enough space in current block
-            m_block_offset -= size;
+            m_block_offset -= size + alignment_offset;
         } else {
             // Need to allocate a new block
             m_current_block++;
             m_block_offset = BlockSize - size;
             if (m_blocks.size() == m_current_block)
                 m_blocks.push_back(new char[BlockSize]);
+            alignment_offset = alignment_offset_calc(alignment);
+            DASSERT (m_block_offset >= alignment_offset);
+            m_block_offset -= alignment_offset;
         }
         return m_blocks[m_current_block] + m_block_offset;
     }
@@ -1076,6 +1086,10 @@ public:
     void clear () { m_current_block = 0; m_block_offset = BlockSize; }
 
 private:
+    inline size_t alignment_offset_calc(size_t alignment) {
+        return (((uintptr_t)m_blocks[m_current_block] + m_block_offset) & (alignment - 1));
+    }
+    
     std::vector<char *> m_blocks;
     size_t              m_current_block;
     size_t              m_block_offset;
@@ -1250,7 +1264,9 @@ public:
     ClosureComponent * closure_component_allot(int id, size_t prim_size, int nattrs) {
         size_t needed = sizeof(ClosureComponent) + (prim_size >= 4 ? prim_size - 4 : 0)
                                                  + sizeof(ClosureComponent::Attr) * nattrs;
-        ClosureComponent *comp = (ClosureComponent *) m_closure_pool.alloc(needed);
+        int alignment = m_shadingsys.find_closure(id)->alignment;
+        size_t alignment_offset = closure_alignment_offset_calc(alignment);
+        ClosureComponent *comp = (ClosureComponent *) (m_closure_pool.alloc(needed + alignment_offset, alignment) + alignment_offset);
         comp->type = ClosureColor::COMPONENT;
         comp->id = id;
         comp->size = prim_size;
@@ -1265,7 +1281,9 @@ public:
         // Allocate the component and the mul back to back
         size_t needed = sizeof(ClosureComponent) + (prim_size >= 4 ? prim_size - 4 : 0)
                                                  + sizeof(ClosureComponent::Attr) * nattrs;
-        ClosureComponent *comp = (ClosureComponent *) m_closure_pool.alloc(needed);
+        int alignment = m_shadingsys.find_closure(id)->alignment;
+        size_t alignment_offset = closure_alignment_offset_calc(alignment);
+        ClosureComponent *comp = (ClosureComponent *) (m_closure_pool.alloc(needed + alignment_offset, alignment) + alignment_offset);
         comp->type = ClosureColor::COMPONENT;
         comp->id = id;
         comp->size = prim_size;
@@ -1416,6 +1434,13 @@ private:
     // Buffering of error messages and printfs
     typedef std::pair<ErrorHandler::ErrCode, std::string> ErrorItem;
     mutable std::vector<ErrorItem> m_buffered_errors;
+    
+    // Calculate offset needed to align ClosureComponent's mem to a given alignment.
+    inline size_t closure_alignment_offset_calc(size_t alignment) {
+        return alignment == 1 ? 0 : 
+        alignment - (reckless_offsetof(ClosureComponent, mem) & (alignment - 1));
+    }
+    
 };
 
 
