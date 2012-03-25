--- gold/script.cc.orig	2011-06-29 23:57:14.000000000 +0200
+++ gold/script.cc	2012-03-05 20:05:49.000000000 +0100
@@ -2871,7 +2871,7 @@ script_add_search_dir(void* closurev, co
   else if (!closure->command_line()->options().nostdlib())
     {
       std::string s = "-L" + std::string(option, length);
-      script_parse_option(closurev, s.c_str(), s.size());
+      ::script_parse_option(closurev, s.c_str(), s.size());
     }
 }
 
@@ -3011,7 +3011,7 @@ version_script_push_lang(void* closurev,
       snprintf(buf, langlen + 100,
 	       _("unrecognized version script language '%s'"),
 	       language.c_str());
-      yyerror(closurev, buf);
+      ::yyerror(closurev, buf);
       delete[] buf;
       code = Version_script_info::LANGUAGE_C;
     }
@@ -3165,7 +3165,7 @@ script_string_sort_list_add(String_sort_
 			    const struct Wildcard_section* string_sort)
 {
   if (pv == NULL)
-    return script_new_string_sort_list(string_sort);
+    return ::script_new_string_sort_list(string_sort);
   else
     {
       pv->push_back(*string_sort);
@@ -3189,7 +3189,7 @@ extern "C" String_list_ptr
 script_string_list_push_back(String_list_ptr pv, const char* str, size_t len)
 {
   if (pv == NULL)
-    return script_new_string_list(str, len);
+    return ::script_new_string_list(str, len);
   else
     {
       pv->push_back(std::string(str, len));
@@ -3261,7 +3261,7 @@ script_phdr_string_to_type(void* closure
     if (namelen == phdr_type_names[i].namelen
 	&& strncmp(name, phdr_type_names[i].name, namelen) == 0)
       return phdr_type_names[i].val;
-  yyerror(closurev, _("unknown PHDR type (try integer)"));
+  ::yyerror(closurev, _("unknown PHDR type (try integer)"));
   return elfcpp::PT_NULL;
 }
 
@@ -3336,7 +3336,7 @@ script_parse_memory_attr(void* closurev,
       case 'l':
 	attributes |= MEM_INITIALIZED; break;
       default:
-	yyerror(closurev, _("unknown MEMORY attribute"));
+	::yyerror(closurev, _("unknown MEMORY attribute"));
       }
 
   if (invert)
@@ -3349,7 +3349,7 @@ extern "C" void
 script_include_directive(void* closurev, const char*, size_t)
 {
   // FIXME: Implement ?
-  yyerror (closurev, _("GOLD does not currently support INCLUDE directives"));
+  ::yyerror (closurev, _("GOLD does not currently support INCLUDE directives"));
 }
 
 // Functions for memory regions.
