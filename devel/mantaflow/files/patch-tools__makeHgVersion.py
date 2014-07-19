--- ./tools/makeHgVersion.py.orig	2014-07-12 23:30:29.021399758 +0930
+++ ./tools/makeHgVersion.py	2014-07-12 23:30:29.025399924 +0930
@@ -21,8 +21,8 @@
 # params
 
 if(len(sys.argv)<2):
-	print "Usage makeHgVersion.py <out-file> <optional: path-to-hg> "
-	print "Warning, the target file <out-file> will be overwritten! "
+	print("Usage makeHgVersion.py <out-file> <optional: path-to-hg> ")
+	print("Warning, the target file <out-file> will be overwritten! ")
 	exit(1)
 
 # target file
@@ -57,10 +57,10 @@
 	oldContent = infile.read()
 	infile.close()
 	if(doDebug):
-		print "\n Old file content '"+oldContent+"' end \n"
+		print("\n Old file content '"+oldContent+"' end \n")
 except IOError:
 	if(doDebug):
-		print "Old file not found..."
+		print("Old file not found...")
 
 
 # get hg version
@@ -75,11 +75,11 @@
 
 if(newContent == oldContent):
 	if(doDebug):
-		print "MATCHES! No write"
+		print("MATCHES! No write")
 	doWrite = False
 else:
 	if(doDebug):
-		print "Old info different, writing"
+		print("Old info different, writing")
 
 # write temp file
 if(doWrite):
