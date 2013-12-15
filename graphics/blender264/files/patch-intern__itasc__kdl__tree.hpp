--- intern/itasc/kdl/tree.hpp.orig	2012-10-10 05:04:31.000000000 +1030
+++ intern/itasc/kdl/tree.hpp	2013-12-14 21:59:26.258307175 +1030
@@ -35,27 +35,28 @@
 {
     //Forward declaration
     class TreeElement;
-#if !defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_5)
+#if defined(__APPLE__) && MAC_OS_X_VERSION_MIN_REQUIRED <= 1050
+    typedef std::map<std::string,TreeElement> SegmentMap;
+#else
     // Eigen allocator is needed for alignment of Eigen data types
     typedef std::map<std::string,TreeElement, std::less<std::string>, Eigen::aligned_allocator<std::pair<std::string, TreeElement> > > SegmentMap;
-#else
-    typedef std::map<std::string,TreeElement> SegmentMap;
 #endif
+
     class TreeElement
     {
     public:
-        TreeElement():q_nr(0)
+        TreeElement():q_nr(0),parent(0)
         {};
     public:
         Segment segment;
         unsigned int q_nr;
-        SegmentMap::const_iterator  parent;
+        SegmentMap::value_type const *parent;
         std::vector<SegmentMap::const_iterator > children;
-        TreeElement(const Segment& segment_in,const SegmentMap::const_iterator& parent_in,unsigned int q_nr_in)
+        TreeElement(const Segment& segment_in,const SegmentMap::value_type& parent_in,unsigned int q_nr_in)
         {
 			q_nr=q_nr_in;
             segment=segment_in;
-            parent=parent_in;
+            parent=&parent_in;
         };
         static TreeElement Root()
         {
@@ -156,7 +157,15 @@
             return segments.find(segment_name);
         };
 
-
+        SegmentMap::value_type const* getSegmentPtr(const std::string& segment_name)const
+        {
+            SegmentMap::const_iterator it = segments.find(segment_name);
+            
+            if (it == segments.end())
+                return 0;
+ 
+            return &*it;
+        };
 
         const SegmentMap& getSegments()const
         {
