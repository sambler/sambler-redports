--- gold/gc.h.orig	2011-05-24 23:41:10.000000000 +0200
+++ gold/gc.h	2012-03-05 19:00:49.000000000 +0100
@@ -40,7 +40,7 @@ template<int size, bool big_endian>
 class Sized_relobj_file;
 
 template<int sh_type, int size, bool big_endian>
-class Reloc_types;
+struct Reloc_types;
 
 class Output_section;
 class General_options;
