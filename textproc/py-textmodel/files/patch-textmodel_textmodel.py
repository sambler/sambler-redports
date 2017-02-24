--- textmodel/textmodel.py.orig	2016-02-05 20:31:58 UTC
+++ textmodel/textmodel.py
@@ -86,7 +86,7 @@ def dump_range(texel, i1, i2, i0=0, inde
     s = texel.__class__.__name__
     if isinstance(texel, Characters):
         s += " "+repr(texel.text)
-    print " "*indent+"%i:%i %s" % (i0, i0+len(texel), s)
+    print(" "*indent+"%i:%i %s" % (i0, i0+len(texel), s))
     if texel.has_childs:
         skip = False
         for j1, j2, child in iter_extended(texel):
@@ -94,7 +94,7 @@ def dump_range(texel, i1, i2, i0=0, inde
                 dump_range(child, i1-j1, i2-j1, i0+j1, indent+4)
                 skip = False
             elif not skip:
-                print " "*indent+'...'
+                print(" "*indent+'...')
                 skip = True # skip output of more '...'
 
 
@@ -165,9 +165,9 @@ class TextModel(Model):
         if i2 is None:
             i2 = len(self.texel)
         if i1<0:
-            raise IndexError, i1
+            raise IndexError(i1)
         if i2>len(self):
-            raise IndexError, i2
+            raise IndexError(i2)
         return _get_text(self.texel, i1, i2)
 
     def get_style(self, i):
@@ -346,23 +346,23 @@ def pycolorize(rawtext, coding='latin-1'
         _KEYWORD:           '#C00000',
         #_TEXT:              '#000000',
     }
-    def tokeneater(toktype, toktext, (srow,scol), (erow,ecol), line):
-        i1 = model.position2index(srow-1, scol)
-        i2 = model.position2index(erow-1, ecol)
-        if token.LPAR <= toktype and toktype <= token.OP:
-            toktype = token.OP
-        elif toktype == token.NAME and keyword.iskeyword(toktext):
-            toktype = _KEYWORD
-        try:
-            color = _colors[toktype]
-        except:
-            return
-        model.set_properties(i1, i2, textcolor=color)
+    #def tokeneater(toktype, toktext, (srow,scol), (erow,ecol), line):
+        #i1 = model.position2index(srow-1, scol)
+        #i2 = model.position2index(erow-1, ecol)
+        #if token.LPAR <= toktype and toktype <= token.OP:
+            #toktype = token.OP
+        #elif toktype == token.NAME and keyword.iskeyword(toktext):
+            #toktype = _KEYWORD
+        #try:
+            #color = _colors[toktype]
+        #except:
+            #return
+        #model.set_properties(i1, i2, textcolor=color)
 
     text = rawtext.decode(coding)
     model = TextModel(text)
 
-    tokenize.tokenize(instream, tokeneater)
+    tokenize.tokenize(instream)
     return model.copy(0, len(model)-1)
 
 
@@ -603,7 +603,7 @@ def test_11():
     t = TextModel(text1+'\n'+text2)
     t.set_properties(5, 15, selected=True)
     t.set_properties(5, 15, selected=False)
-    #print t.texel
+    #print(t.texel)
     t.get_style(5) == {
         'bgcolor': 'white', 'textcolor': 'black', 'fontsize': 10,
         'selected': False}
