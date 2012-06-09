--- libdirac_encoder/quant_chooser.cpp.orig
+++ libdirac_encoder/quant_chooser.cpp
@@ -340,7 +340,7 @@
     {
         for (int i=cblock.Xstart(); i<cblock.Xend(); ++i )
         {
-            if ( (std::abs(m_coeff_data[j][i])<<2) >= u_threshold )
+            if ( (int(std::abs(m_coeff_data[j][i]))<<2) >= u_threshold )
                 can_skip = false;
         }   
     }
@@ -355,7 +355,7 @@
     {
         for (int i=node.Xp() ; i<node.Xp()+node.Xl(); ++i)
         {    
-            val = std::max( val , std::abs(m_coeff_data[j][i]) );
+            val = std::max( val , int(std::abs(m_coeff_data[j][i])) );
         }// i
     }// j
 
