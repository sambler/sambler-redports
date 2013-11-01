--- ./include/pugiconfig.hpp.orig	2013-10-03 00:57:17.000000000 +0930
+++ ./include/pugiconfig.hpp	2013-10-03 01:01:24.000000000 +0930
@@ -1,7 +1,7 @@
 /**
- * pugixml parser - version 1.0
+ * pugixml parser - version 1.2
  * --------------------------------------------------------
- * Copyright (C) 2006-2010, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
+ * Copyright (C) 2006-2012, by Arseny Kapoulkine (arseny.kapoulkine@gmail.com)
  * Report bugs and download new versions at http://pugixml.org/
  *
  * This library is distributed under the MIT License. See notice at the end
@@ -21,11 +21,9 @@
 // #define PUGIXML_NO_XPATH
 
 // Uncomment this to disable STL
-// Note: you can't use XPath with PUGIXML_NO_STL
 // #define PUGIXML_NO_STL
 
 // Uncomment this to disable exceptions
-// Note: you can't use XPath with PUGIXML_NO_EXCEPTIONS
 // #define PUGIXML_NO_EXCEPTIONS
 
 // Set this to control attributes for public classes/functions, i.e.:
@@ -34,6 +32,15 @@
 // #define PUGIXML_FUNCTION __fastcall // to set calling conventions to all public functions to fastcall
 // In absence of PUGIXML_CLASS/PUGIXML_FUNCTION definitions PUGIXML_API is used instead
 
+// Uncomment this to switch to header-only version
+// #define PUGIXML_HEADER_ONLY
+// #include "pugixml.cpp"
+
+// Tune these constants to adjust memory-related behavior
+// #define PUGIXML_MEMORY_PAGE_SIZE 32768
+// #define PUGIXML_MEMORY_OUTPUT_STACK 10240
+// #define PUGIXML_MEMORY_XPATH_PAGE_SIZE 4096
+
 // OIIO: use already defined OIIO_API
 #include "export.h"
 #define PUGIXML_API OIIO_API
@@ -41,7 +48,7 @@
 #endif
 
 /**
- * Copyright (c) 2006-2010 Arseny Kapoulkine
+ * Copyright (c) 2006-2012 Arseny Kapoulkine
  *
  * Permission is hereby granted, free of charge, to any person
  * obtaining a copy of this software and associated documentation
