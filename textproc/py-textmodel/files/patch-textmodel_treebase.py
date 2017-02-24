--- textmodel/treebase.py.orig	2016-02-05 20:31:58 UTC
+++ textmodel/treebase.py
@@ -146,7 +146,7 @@ def is_elementlist(l):
     """Returns True if $l$ is a list of Elements.
     """
     if not type(l) in (tuple, list):
-        print "not a list or tuple", type(l), l.__class__ # XXX remove this
+        print("not a list or tuple", type(l), l.__class__) # XXX remove this
         return False
     return not False in [isinstance(x, Element) for x in l]
 
@@ -180,20 +180,20 @@ def strip(element):
 
 
 def out(*args): # XXX remove this
-    print repr(args)
+    print(repr(args))
     return True
 
 
 def dump(element, name=''): # XXX remove this
-    print "Dump %s:" % name
+    print("Dump %s:" % name)
     element.dump()
     return True
 
 def dump_list(l):
-    print "Dumping list (efficient: %s)" % is_list_efficient(l)
+    print("Dumping list (efficient: %s)" % is_list_efficient(l))
     for i, element in enumerate(l):
-        print "Dumping element no. %i" % i,
-        print "(efficient: %s)" % is_element_efficient(element)
+        print("Dumping element no. %i" % i)
+        print("(efficient: %s)" % is_element_efficient(element))
         element.dump()
     return True
 
@@ -280,7 +280,7 @@ If element is a container, it must provi
             is_list_efficient(__return__[0])
             is_list_efficient(__return__[1])
         """
-        print self, len(self), i1, i2 # XXX
+        print(self, len(self), i1, i2) # XXX
         raise NotImplementedError()
 
     def can_merge(self, other):
@@ -297,7 +297,7 @@ If element is a container, it must provi
 
     def dump(self, i=0):
         """Print out a graphical representation of the tree."""
-        print (" "*i)+str(self.__class__.__name__), self.weights
+        print((" "*i)+str(self.__class__.__name__), self.weights)
         for i1, i2, child in self.iter_childs():
             child.dump(i+2)
 
@@ -360,9 +360,9 @@ class GroupBase(Element):
             assert calc_length(tmp) == len(self)+calc_length(stuff)-(i2-i1)
         except:
             dump(self, "self")
-            print "len(tmp):", len(tmp)
-            print "len(self):", len(self)
-            print "i1, i2:", i1, i2
+            print("len(tmp):", len(tmp))
+            print("len(self):", len(self))
+            print("i1, i2:", i1, i2)
             dump_list(stuff)
             dump_list(tmp)
             raise
@@ -374,7 +374,7 @@ class GroupBase(Element):
         if debug > 1: # XXX remove this
             if not is_root_efficient(self):
                 dump(self)
-                print "nmax=", nmax
+                print("nmax=", nmax)
             assert is_root_efficient(self)
 
         if not (0 <= i1 <= i2 <= len(self)):
@@ -793,7 +793,7 @@ class Text(Element):
         return "T(%s)" % repr(self.text)
 
     def dump(self, n=0):
-        print (" "*n)+str(self), self.weights
+        print((" "*n)+str(self), self.weights)
 T = Text
 
 
@@ -819,7 +819,7 @@ if debug:
      #enable contract checking
      import contract
      contract.checkmod(__name__)
-     print "enabled contracts"
+     print("enabled contracts")
 
 def test_00():
     "homogenize"
@@ -833,7 +833,7 @@ def test_01():
     "is_homogeneous"
     assert not is_homogeneous([G([T('X')]), T('0'), T('1')])
     for x in G([T('X')]), G([T('0'), T('1')]):
-        print depth(x), x
+        print(depth(x), x)
     assert is_homogeneous([G([T('X')]), G([T('0'), T('1')])])
 
 
@@ -841,7 +841,7 @@ def test_02():
     "strip"
     element = G([G([G([T('1'), T('2')]), G([T('3')])])])
     element.dump()
-    print depth(element)
+    print(depth(element))
     assert depth(element) == 3
     assert depth(strip(element)) == 2
     #strip(element).dump()
