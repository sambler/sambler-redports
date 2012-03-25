--- gold/object.h.orig	2011-08-01 20:25:21.000000000 +0200
+++ gold/object.h	2012-03-05 18:59:19.000000000 +0100
@@ -47,7 +47,7 @@ class Pluginobj;
 class Dynobj;
 class Object_merge_map;
 class Relocatable_relocs;
-class Symbols_data;
+struct Symbols_data;
 
 template<typename Stringpool_char>
 class Stringpool_template;
