--- ./src/include/OpenImageIO/array_view.h.orig	2014-05-21 14:38:28.010229787 +0930
+++ ./src/include/OpenImageIO/array_view.h	2014-05-21 14:44:01.611229841 +0930
@@ -223,7 +223,7 @@
     array_view_strided (T *data, size_t len) { init(data,len); }
 
     /// Construct from T*, length, and stride (in bytes).
-    array_view_strided (T *data, size_t len, ptrdiff_t stride) {
+    array_view_strided (T *data, size_t len, stride_t stride) {
         init(data,len,stride);
     }
 
@@ -263,7 +263,7 @@
     size_type size() const { return m_len; }
     size_type max_size() const { return m_len; }
     bool empty() const { return m_len == 0; }
-    ptrdiff_t stride() const { return m_stride; }
+    stride_t stride() const { return m_stride; }
 
     const T& operator[] (size_type pos) const { return get(pos); }
     const T& at (size_t pos) const {
@@ -310,17 +310,17 @@
 private:
     T * m_data;
     size_t m_len;
-    ptrdiff_t m_stride;
+    stride_t m_stride;
 
-    void init (T *data, size_t len, ptrdiff_t stride=AutoStride) {
+    void init (T *data, size_t len, stride_t stride=AutoStride) {
         m_data = data;
         m_len = len;
         m_stride = stride == AutoStride ? sizeof(T) : stride;
     }
-    inline T* getptr (ptrdiff_t pos=0) const {
+    inline T* getptr (stride_t pos=0) const {
         return (T*)((char *)m_data + pos*m_stride);
     }
-    inline T& get (ptrdiff_t pos=0) const {
+    inline T& get (stride_t pos=0) const {
         return *getptr(pos);
     }
 
