--- ./parser/messagehandler.py.orig	2013-04-11 21:25:34.000000000 +0930
+++ ./parser/messagehandler.py	2014-08-18 03:25:11.956455819 +0930
@@ -21,7 +21,7 @@
   """
   The request protobuf did not contain any recognised request types.
   """
-  
+
   pass
 
 
@@ -36,8 +36,8 @@
 
   handlers = None
 
-  UNDER_LETTER    = re.compile(r'_([a-z])')
-  REQUEST_SUFFIX  = "_request"
+  UNDER_LETTER = re.compile(r'_([a-z])')
+  REQUEST_SUFFIX = "_request"
   RESPONSE_SUFFIX = "_response"
 
   def __init__(self, message_class):
@@ -47,7 +47,7 @@
     """
     Reads a uint32 length-encoded protobuf from the file handle and returns it.
     """
-    
+
     # Read the length
     encoded_length = handle.read(4)
     if len(encoded_length) != 4:
@@ -88,11 +88,11 @@
       name = descriptor.name
       if not name.endswith(self.REQUEST_SUFFIX):
         continue
-      
+
       # Convert some_thing_request to SomeThingRequest
       func_name = name[0].upper() + name[1:]
       func_name = self.UNDER_LETTER.sub(lambda m: m.group(1).upper(), func_name)
-      
+
       try:
         function = getattr(self, func_name)
       except AttributeError:
@@ -101,17 +101,17 @@
       response_name = name[:-len(self.REQUEST_SUFFIX)] + self.RESPONSE_SUFFIX
 
       # Get the nested messages
-      request_pb  = getattr(request, name)
+      request_pb = getattr(request, name)
       response_pb = getattr(response, response_name)
 
       return (function, request_pb, response_pb)
-    
+
     raise UnknownRequestType
 
   def ServeForever(self, socket_filename):
     """
     Connects to the given local socket and listens for incoming request
-    protobufs.  Handles the requests and writes the responses back to the 
+    protobufs.  Handles the requests and writes the responses back to the
     socket.
     """
 
