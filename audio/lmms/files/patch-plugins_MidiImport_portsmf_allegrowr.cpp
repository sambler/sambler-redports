--- plugins/MidiImport/portsmf/allegrowr.cpp.orig	2015-06-11 08:37:46 UTC
+++ plugins/MidiImport/portsmf/allegrowr.cpp
@@ -41,7 +41,7 @@ void parameter_print(ostream &file, Alg_
         break;
     case 's': {
         string str;
-        string_escape(str, p->s, "\"");
+        string_escape(str, p->s, (char *)"\"");
         file << str;
         break;
     }
