--- src/include/OSL/llvm_util.h.orig	2018-09-14 18:46:29 UTC
+++ src/include/OSL/llvm_util.h
@@ -43,7 +43,7 @@ namespace llvm {
   class ExecutionEngine;
   class Function;
   class FunctionType;
-  class JITMemoryManager;
+  class SectionMemoryManager;
   class Linker;
   class LLVMContext;
   class Module;
@@ -500,7 +500,7 @@ private:
     llvm::LLVMContext *m_llvm_context;
     llvm::Module *m_llvm_module;
     IRBuilder *m_builder;
-    MemoryManager *m_llvm_jitmm;
+    llvm::SectionMemoryManager *m_llvm_jitmm;
     llvm::Function *m_current_function;
     llvm::legacy::PassManager *m_llvm_module_passes;
     llvm::legacy::FunctionPassManager *m_llvm_func_passes;
