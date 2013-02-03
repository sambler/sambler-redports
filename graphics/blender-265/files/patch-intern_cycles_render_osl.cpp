--- intern/cycles/render/osl.cpp.orig	2013-02-01 17:52:34.805857995 +1030
+++ intern/cycles/render/osl.cpp	2013-02-01 17:55:13.941857822 +1030
@@ -275,9 +275,45 @@
 	return shader_load_bytecode(bytecode_hash, bytecode);
 }
 
+/* patch from r52885 to allow 2.65 release to build with newer osl libs */
+
+/* don't try this at home .. this is a template trick to use either
+ * LoadMemoryShader or LoadMemoryCompiledShader which are the function
+ * names in our custom branch and the official repository. */
+
+template<bool C, typename T = void> struct enable_if { typedef T type; };
+template<typename T> struct enable_if<false, T> { };
+
+template<typename T, typename Sign>
+struct has_LoadMemoryCompiledShader {
+	typedef int yes;
+	typedef char no;
+	
+	template<typename U, U> struct type_check;
+	template<typename _1> static yes &chk(type_check<Sign, &_1::LoadMemoryCompiledShader>*);
+	template<typename   > static no  &chk(...);
+	static bool const value = sizeof(chk<T>(0)) == sizeof(yes);
+};
+
+template<typename T>
+typename enable_if<has_LoadMemoryCompiledShader<T, 
+	bool(T::*)(const char*, const char*)>::value, bool>::type
+load_memory_shader(T *ss, const char *name, const char *buffer)
+{
+	return ss->LoadMemoryCompiledShader(name, buffer);
+}
+
+template<typename T>
+typename enable_if<!has_LoadMemoryCompiledShader<T, 
+	bool(T::*)(const char*, const char*)>::value, bool>::type
+load_memory_shader(T *ss, const char *name, const char *buffer)
+{
+	return ss->LoadMemoryShader(name, buffer);
+}
+
 const char *OSLShaderManager::shader_load_bytecode(const string& hash, const string& bytecode)
 {
-	ss->LoadMemoryShader(hash.c_str(), bytecode.c_str());
+	load_memory_shader(ss, hash.c_str(), bytecode.c_str());
 
 	/* this is a bit weak, but works */
 	OSLShaderInfo info;
