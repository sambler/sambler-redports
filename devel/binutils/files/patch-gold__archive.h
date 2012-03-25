--- gold/archive.h.orig	2011-06-02 22:13:23.000000000 +0200
+++ gold/archive.h	2012-03-05 18:57:24.000000000 +0100
@@ -40,7 +40,7 @@ class Input_group;
 class Layout;
 class Symbol_table;
 class Object;
-class Read_symbols_data;
+struct Read_symbols_data;
 class Input_file_lib;
 class Incremental_archive_entry;
 
