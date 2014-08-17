--- ./parser/symbolindex.py.orig	2013-04-11 21:25:34.000000000 +0930
+++ ./parser/symbolindex.py	2014-08-18 03:25:11.973455174 +0930
@@ -61,7 +61,7 @@
       for version in xrange(current_version + 1, len(self.SCHEMA)):
         # Apply this schema update
         self.conn.executescript(self.SCHEMA[version])
-  
+
   def Rebuild(self):
     """
     Completely rebuilds the index by removing everything from the database and
@@ -74,7 +74,7 @@
       self.conn.execute("DELETE FROM symbol_index")
 
       map(self._AddFile, self.project.pycore.get_python_files())
-  
+
   def UpdateFile(self, file_path):
     """
     Updates a single file in the index.
@@ -88,11 +88,11 @@
       row = self.conn.execute(
         "SELECT rowid FROM files WHERE file_path = ?",
         (file_path, )).fetchone()
-      
+
       if row is not None:
         # Remove the existing data for this file
         self._RemoveFile(row[0])
-      
+
       # Re-parse the file
       self._AddFile(resource)
 
@@ -124,7 +124,7 @@
     if file_path is not None:
       where_clauses.append("f.file_path = ?")
       where_parameters.append(file_path)
-    
+
     if symbol_type is not None:
       where_clauses.append("s.symbol_type = ?")
       where_parameters.append(symbol_type)
@@ -133,7 +133,7 @@
     sql = """
       SELECT f.module_name,
              f.file_path,
-             s.line_number, 
+             s.line_number,
              s.symbol_name,
              s.symbol_type
       FROM files AS f,
@@ -154,13 +154,13 @@
 
     # Open this file
     try:
-      pyobject  = self.project.pycore.resource_to_pyobject(resource)
+      pyobject = self.project.pycore.resource_to_pyobject(resource)
     except rope.base.exceptions.RopeError:
       # If the file couldn't be loaded, ignore it
       return
 
     module_name = self.project.pycore.modname(resource)
-    file_path   = resource.path
+    file_path = resource.path
 
     # Get the list of symbols in the module
     symbols = []
@@ -174,7 +174,7 @@
     # Add each symbol to the database
     for symbol_name, line_number, symbol_type in symbols:
       self._AddSymbol(fileid, line_number, symbol_name, symbol_type)
-  
+
   def _AddSymbol(self, fileid, line_number, symbol_name, symbol_type):
     """
     Adds the Python symbol to the database.
@@ -208,7 +208,7 @@
         symbol_type = rpc_pb2.CLASS
       elif isinstance(pyobject, rope.base.pyobjects.AbstractModule):
         symbol_type = rpc_pb2.MODULE
-      
+
       # Add this object to the result list
       ret.append((dotted_name, line_number, symbol_type))
 
@@ -218,14 +218,14 @@
     except Exception:
       # Ignore any errors from rope
       return
-    
+
     for name, pyname in children:
       if isinstance(pyname, rope.base.pynames.DefinedName):
         if dotted_name is not None:
           name = "%s.%s" % (dotted_name, name)
 
         self._WalkPyObject(pyname.get_object(), name, ret)
-  
+
   def _RemoveFile(self, fileid):
     """
     Removes the file with the give rowid from the database.
@@ -238,7 +238,7 @@
     for row in self.conn.execute("SELECT rowid FROM symbols WHERE fileid = ?",
                                  (fileid,)):
       self._RemoveSymbol(row[0])
-  
+
   def _RemoveSymbol(self, rowid):
     """
     Removes the symbol with the given rowid from the database.
