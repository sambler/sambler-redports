--- ./liboslcomp/oslcomp.cpp.orig	2012-08-31 06:58:32.000000000 +0930
+++ ./liboslcomp/oslcomp.cpp	2012-10-27 15:54:13.708663748 +1030
@@ -316,8 +316,10 @@
     std::string program = OIIO::Sysutil::this_program_path ();
     if (program.size()) {
         boost::filesystem::path path (program);  // our program
+        boost::filesystem::path path2;
         path = path.parent_path ();  // now the bin dir of our program
         path = path.parent_path ();  // now the parent dir
+        path2 = path; // copy path from this point (live will be /usr/local)
         path = path / "shaders";
         bool found = false;
         if (OIIO::Filesystem::exists (path.string())) {
@@ -335,6 +337,26 @@
                 found = true;
             }
         }
+        if (! found) {
+            // FreeBSD fix - shaders are installed into /usr/local/share/openshadinglanguage/shaders
+            // add this path to the search list to prevent manually adding it with -I every time
+            path2 = path2 / "share/openshadinglanguage/shaders";
+            if (OIIO::Filesystem::exists (path2.string())) {
+#ifdef USE_BOOST_WAVE
+                includepaths.push_back(path2.string());
+#else
+                // pass along to cpp
+                cppoptions += "\"-I";
+                cppoptions += path2.string();
+                cppoptions += "\" ";
+#endif
+                path2 = path2 / "stdosl.h";
+                if (OIIO::Filesystem::exists (path2.string())) {
+                    stdinclude = path2.string();
+                    found = true;
+                }
+            }
+        }
         if (! found)
             warning (ustring(filename), 0, "Unable to find \"%s\"",
                      path.string().c_str());
