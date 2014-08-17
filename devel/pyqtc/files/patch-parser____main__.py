--- ./parser/__main__.py.orig	2013-04-11 21:25:34.000000000 +0930
+++ ./parser/__main__.py	2014-08-18 03:25:11.807456747 +0930
@@ -72,7 +72,7 @@
     project = rope.base.project.Project(root)
 
     self.projects[root] = Project(project)
-  
+
   def DestroyProjectRequest(self, request, _response):
     """
     Cleans up a rope project when it is closed by the user in Qt Creator.
@@ -89,9 +89,9 @@
     Returns a (project, resource, source, offset) tuple for the context.
     """
 
-    project       = self._ProjectForFile(context.file_path).rope_project
+    project = self._ProjectForFile(context.file_path).rope_project
     relative_path = os.path.relpath(context.file_path, project.address)
-    resource      = project.get_resource(relative_path)
+    resource = project.get_resource(relative_path)
 
     return (
       project,
@@ -99,7 +99,7 @@
       context.source_text + "\n",
       context.cursor_position,
     )
-  
+
   def _ProjectForFile(self, file_path):
     """
     Tries to find the project that contains the given file.
@@ -113,7 +113,7 @@
         pass
 
       project_root = os.path.dirname(project_root)
-    
+
     raise ProjectNotFoundError(file_path)
 
   def CompletionRequest(self, request, response):
@@ -137,12 +137,12 @@
                                        maxfixes=self.MAXFIXES,
                                        resource=resource,
                                        remove_self=True)
-      
+
       if calltip is not None:
         response.insertion_position = paren_start + 1
         response.calltip = calltip
         return
-    
+
     # Do normal completion if a calltip couldn't be found
     proposals = codeassist.code_assist(project, source, offset,
                                        maxfixes=self.MAXFIXES,
@@ -152,7 +152,7 @@
     # Get the position that this completion will start from.
     starting_offset = codeassist.starting_offset(source, offset)
     response.insertion_position = starting_offset
-    
+
     # Construct the response protobuf
     for proposal in proposals:
       proposal_pb = response.proposal.add()
@@ -168,7 +168,7 @@
 
       if docstring is not None:
         proposal_pb.docstring = docstring
-  
+
   def TooltipRequest(self, request, response):
     """
     Finds and returns a tooltip for the given location in the given source file.
@@ -180,7 +180,7 @@
 
     if docstring is not None:
       response.rich_text = docstring
-  
+
   def DefinitionLocationRequest(self, request, response):
     """
     Finds the definition location of the current symbol.
@@ -193,10 +193,10 @@
 
     if resource is not None:
       response.file_path = resource.real_path
-    
+
     if offset is not None:
       response.line = offset
-  
+
   def RebuildSymbolIndexRequest(self, request, _response):
     """
     Parses all the files in the project and rebuilds the symbol index.
@@ -204,7 +204,7 @@
 
     project = self.projects[request.project_root]
     project.symbol_index.Rebuild()
-  
+
   def UpdateSymbolIndexRequest(self, request, _response):
     """
     Parses just one file in the project and updates the symbol index.
@@ -215,9 +215,9 @@
     # Make the file_path relative to the project
     relative_path = os.path.relpath(
         request.file_path, project.rope_project.address)
-    
+
     project.symbol_index.UpdateFile(relative_path)
-  
+
   def SearchRequest(self, request, response):
     """
     Searches the symbol index.
@@ -229,7 +229,7 @@
       projects = [self._ProjectForFile(request.file_path)]
     else:
       projects = self.projects.values()
-    
+
     for project in projects:
       project_dir = project.rope_project.address
 
@@ -240,20 +240,20 @@
         # Make the file_path relative to the project
         file_path = os.path.relpath(
             request.file_path, project_dir)
-      
+
       if request.HasField("symbol_type") and request.symbol_type != rpc_pb2.ALL:
         symbol_type = request.symbol_type
-      
+
       # Do the query
       results = project.symbol_index.Search(request.query,
           file_path=file_path, symbol_type=symbol_type)
-      
+
       # Create the response
       for module_name, file_path, line_number, symbol_name, symbol_type in results:
         result_pb = response.result.add()
 
         result_pb.module_name = module_name
-        result_pb.file_path   = os.path.join(project_dir, file_path)
+        result_pb.file_path = os.path.join(project_dir, file_path)
         result_pb.line_number = line_number
         result_pb.symbol_name = symbol_name
         result_pb.symbol_type = symbol_type
