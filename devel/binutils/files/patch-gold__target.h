--- gold/target.h.orig	2011-07-09 00:48:08.000000000 +0200
+++ gold/target.h	2012-03-05 18:52:40.000000000 +0100
@@ -49,7 +49,7 @@ template<int size, bool big_endian>
 class Sized_relobj_file;
 class Relocatable_relocs;
 template<int size, bool big_endian>
-class Relocate_info;
+struct Relocate_info;
 class Reloc_symbol_changes;
 class Symbol;
 template<int size>
