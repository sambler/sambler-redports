--- textmodel/texeltree.py.orig	2015-11-05 20:29:16 UTC
+++ textmodel/texeltree.py
@@ -43,8 +43,10 @@ def updated_style(style, properties):
     return create_style(**new)
 
 
-def _style_add((n1, style1), (n2, style2)):
+def _style_add(a1, a2):
     # used as argument for listjoin: listjoin(a, b, _style_add)
+    n1, style1 = a1
+    n2, style2 = a2
     if style1 is style2:
         return [(n1+n2, style1)]
     return [(n1, style1), (n2, style2)]
@@ -173,11 +175,11 @@ class Group(Texel, treebase.Group):
         try:
             assert is_homogeneous(r)
         except:
-            print "before:"
+            print("before:")
             self.dump()
-            print "after:"
+            print("after:")
             for i, x in enumerate(r):
-                print "item", i
+                print("item", i)
                 x.dump()
         return groups(r)
 G = Group
@@ -228,7 +230,7 @@ class Glyph(Texel, treebase.Element):
             return join(stuff, [self])
         elif i1 == i2 == 1:
             return join([self], stuff)
-        raise IndexError, (i1, i2)
+        raise IndexError((i1, i2))
 
     def takeout(self, i1, i2):
         if i1 == i2:
@@ -360,7 +362,7 @@ class Characters(Texel, treebase.Element
         return self.__class__(self.text+other.text, self.style)
 
     def dump(self, i=0):
-        print (" "*i)+str(self), id(self.style)
+        print((" "*i)+str(self), id(self.style))
 
 C = Characters
 NULL_TEXEL = Characters('')
@@ -481,7 +483,7 @@ def check(texel):
         try:
             assert tmp.get_style(i) == s1
         except:
-            print i, tmp.get_text()[i:i+1]
+            print(i, tmp.get_text()[i:i+1])
             tmp.dump()
             raise
         tmp = texel.set_properties(i, i+1, {'fontsize':-2})
@@ -635,7 +637,7 @@ def test_08():
     t = Characters(text1)
     assert t.get_styles(0, len(t)) == [(len(t), s0)]
     t = t.set_styles(6, [(1, s2)])
-    #print styles2str(t.get_styles(0, len(t)))
+    #print(styles2str(t.get_styles(0, len(t))))
     assert styles2str(t.get_styles(0, len(t))) == '0000002000'
 
     t = Characters(text1)
@@ -726,7 +728,7 @@ def test_10():
     "optimized growth"
 
     for n in (3, 4, 5, 6):
-        #print "nmax = ", n
+        #print("nmax = ", n)
         treebase.set_nmax(n)
         t =  Characters("X")
         for i in range(30):
@@ -737,7 +739,7 @@ def test_10():
             try:
                 assert is_root_efficient(t)
             except:
-                print "t is not efficient:"
+                print("t is not efficient:")
                 t.dump()
                 raise
 
