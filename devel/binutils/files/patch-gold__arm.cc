--- gold/arm.cc.orig	2011-11-21 10:40:12.000000000 +0100
+++ gold/arm.cc	2012-03-05 20:12:40.000000000 +0100
@@ -2372,8 +2372,8 @@ class Target_arm : public Sized_target<3
 			       unsigned char* preloc_out);
  
   // Return whether SYM is defined by the ABI.
-  bool
-  do_is_defined_by_abi(Symbol* sym) const
+  virtual bool
+  do_is_defined_by_abi(const Symbol* sym) const
   { return strcmp(sym->name(), "__tls_get_addr") == 0; }
 
   // Return whether there is a GOT section.
@@ -7039,7 +7039,7 @@ Stub_addend_reader<elfcpp::SHT_REL, big_
     const unsigned char* view,
     const typename Reloc_types<elfcpp::SHT_REL, 32, big_endian>::Reloc&) const
 {
-  typedef struct Arm_relocate_functions<big_endian> RelocFuncs;
+  typedef class Arm_relocate_functions<big_endian> RelocFuncs;
   
   switch (r_type)
     {
@@ -11778,7 +11778,7 @@ Target_arm<big_endian>::scan_span_for_co
 	  // Check if we have an offending branch instruction.
 	  uint16_t upper_insn = (insn >> 16) & 0xffffU;
 	  uint16_t lower_insn = insn & 0xffffU;
-	  typedef struct Arm_relocate_functions<big_endian> RelocFuncs;
+	  typedef class Arm_relocate_functions<big_endian> RelocFuncs;
 
 	  if (cortex_a8_reloc != NULL
 	      && cortex_a8_reloc->reloc_stub() != NULL)
@@ -11881,7 +11881,7 @@ Target_arm<big_endian>::apply_cortex_a8_
   Valtype lower_insn = elfcpp::Swap<16, big_endian>::readval(wv + 1);
   off_t branch_offset = stub_address - (insn_address + 4);
 
-  typedef struct Arm_relocate_functions<big_endian> RelocFuncs;
+  typedef class Arm_relocate_functions<big_endian> RelocFuncs;
   switch (stub->stub_template()->type())
     {
     case arm_stub_a8_veneer_b_cond:
