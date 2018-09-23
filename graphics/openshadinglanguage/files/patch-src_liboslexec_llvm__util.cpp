--- src/liboslexec/llvm_util.cpp.orig	2018-09-14 18:47:34 UTC
+++ src/liboslexec/llvm_util.cpp
@@ -106,6 +106,32 @@ namespace pvt {
 
 
 namespace {
+
+#if OSL_LLVM_VERSION >= 60
+// NOTE: This is a COPY of something internal to LLVM, but since we destroy our LLVMMemoryManager
+//       via global variables we can't rely on the LLVM copy sticking around.
+//       Because of this, the variable must be declared _before_ jitmm_hold so that the object stays
+//       valid until after we have destroyed all our memory managers.
+struct DefaultMMapper final : public llvm::SectionMemoryManager::MemoryMapper {
+    llvm::sys::MemoryBlock
+    allocateMappedMemory(llvm::SectionMemoryManager::AllocationPurpose Purpose,
+                         size_t NumBytes, const llvm::sys::MemoryBlock *const NearBlock,
+                         unsigned Flags, std::error_code &EC) override {
+        return llvm::sys::Memory::allocateMappedMemory(NumBytes, NearBlock, Flags, EC);
+    }
+
+    std::error_code protectMappedMemory(const llvm::sys::MemoryBlock &Block,
+                                        unsigned Flags) override {
+        return llvm::sys::Memory::protectMappedMemory(Block, Flags);
+    }
+
+    std::error_code releaseMappedMemory(llvm::sys::MemoryBlock &M) override {
+        return llvm::sys::Memory::releaseMappedMemory(M);
+    }
+};
+static DefaultMMapper llvm_default_mapper;
+#endif
+
 static OIIO::spin_mutex llvm_global_mutex;
 static bool setup_done = false;
 static boost::thread_specific_ptr<LLVM_Util::PerThreadInfo> perthread_infos;
@@ -271,14 +297,16 @@ public:
     virtual void registerEHFrames(uint8_t *Addr, uint64_t LoadAddr, size_t Size) {
         mm->registerEHFrames (Addr, LoadAddr, Size);
     }
-    virtual void deregisterEHFrames(uint8_t *Addr, uint64_t LoadAddr, size_t Size) {
 #if OSL_LLVM_VERSION < 50
+    virtual void deregisterEHFrames(uint8_t *Addr, uint64_t LoadAddr, size_t Size) {
         mm->deregisterEHFrames(Addr, LoadAddr, Size);
+    }
 #else
-        // TODO: verify this is correct
+    virtual void deregisterEHFrames() {
         mm->deregisterEHFrames();
-#endif
     }
+#endif
+
     virtual uint64_t getSymbolAddress(const std::string &Name) {
         return mm->getSymbolAddress (Name);
     }
@@ -329,17 +357,20 @@ LLVM_Util::LLVM_Util (int debuglevel)
         if (! m_thread->llvm_jitmm) {
 #if USE_OLD_JIT
             m_thread->llvm_jitmm = llvm::JITMemoryManager::CreateDefaultMemManager();
+#elif OSL_LLVM_VERSION >= 60
+            m_thread->llvm_jitmm = new LLVMMemoryManager(&llvm_default_mapper);
 #else
-            m_thread->llvm_jitmm = new LLVMMemoryManager;
+            m_thread->llvm_jitmm = new LLVMMemoryManager();
 #endif
             ASSERT (m_thread->llvm_jitmm);
-            jitmm_hold.push_back (std::shared_ptr<LLVMMemoryManager>(m_thread->llvm_jitmm));
+            jitmm_hold.emplace_back (m_thread->llvm_jitmm);
         }
 #if USE_OLD_JIT
-        m_llvm_jitmm = new MemoryManager(m_thread->llvm_jitmm);
+        m_llvm_jitmm = (llvm::SectionMemoryManager*) new MemoryManager(m_thread->llvm_jitmm);
 #else
         // Hold the REAL manager and use it as an argument later
-        m_llvm_jitmm = reinterpret_cast<MemoryManager*>(m_thread->llvm_jitmm);
+//        m_llvm_jitmm = reinterpret_cast<MemoryManager*>(m_thread->llvm_jitmm);
+        m_llvm_jitmm = m_thread->llvm_jitmm;
 #endif
     }
 
@@ -584,13 +615,14 @@ LLVM_Util::make_jit_execengine (std::str
     engine_builder.setErrorStr (err);
 
 #if USE_OLD_JIT
-    engine_builder.setJITMemoryManager (m_llvm_jitmm);
+    engine_builder.setJITMemoryManager ((llvm::JITMemoryManager*)m_llvm_jitmm);
     // N.B. createJIT will take ownership of the the JITMemoryManager!
     engine_builder.setUseMCJIT (0);
 #else
     // We are actually holding a LLVMMemoryManager
     engine_builder.setMCJITMemoryManager (std::unique_ptr<llvm::RTDyldMemoryManager>
-        (new MemoryManager(reinterpret_cast<LLVMMemoryManager*>(m_llvm_jitmm))));
+//        (new MemoryManager(reinterpret_cast<LLVMMemoryManager*>(m_llvm_jitmm))));
+        (new MemoryManager(m_llvm_jitmm)));
 #endif /* USE_OLD_JIT */
 
     engine_builder.setOptLevel (llvm::CodeGenOpt::Default);
