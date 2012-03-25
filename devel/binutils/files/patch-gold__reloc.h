--- gold/reloc.h.orig	2011-11-21 10:37:51.000000000 +0100
+++ gold/reloc.h	2012-03-05 18:58:15.000000000 +0100
@@ -37,7 +37,7 @@ namespace gold
 class General_options;
 class Object;
 class Relobj;
-class Read_relocs_data;
+struct Read_relocs_data;
 class Symbol;
 class Layout;
 class Output_data;
