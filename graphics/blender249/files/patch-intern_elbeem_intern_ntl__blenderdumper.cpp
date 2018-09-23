--- intern/elbeem/intern/ntl_blenderdumper.cpp.orig	2018-09-11 18:21:49 UTC
+++ intern/elbeem/intern/ntl_blenderdumper.cpp
@@ -164,7 +164,7 @@ int ntlBlenderDumper::renderScene( void 
 				boutfilename << ".bobj.gz";
 				gzf = gzopen(boutfilename.str().c_str(), "wb1"); // wb9 is slow for large meshes!
 				if (!gzf) {
-					errMsg("ntlBlenderDumper::renderScene","Unable to open output '"<<boutfilename<<"' ");
+					errMsg("ntlBlenderDumper::renderScene","Unable to open output '" + boutfilename.str() + "' ");
 					return 1; }
 
 				// dont transform velocity output, this is handled in blender
