--- docs/configurations/spi_vfx.rst.orig	2012-04-18 09:38:16.000000000 +0930
+++ docs/configurations/spi_vfx.rst	2012-09-23 09:32:29.056500081 +0930
@@ -71,7 +71,7 @@
 
 lg8, lg10, and lg16 are similar. They are all the same log to linear transformation but are explicitly defined to be lossless at the specified bit depths. The luts use nearest neighbor interpolation to search for an exact match. Significant performance gains were found when using the proper bitdepth lut. While using the lg16 conversion on an 8 bit image will yield the same result, it is measurably slower than using the 8-bit conversion (assuming 8-bits is all that is needed). This performance gap remains even on current graphics hardware.
 
-.. figure::  images/spi-vfx/lg10_to_linear_light.jpeg
+.. figure::  images/spi-vfx/lg10_to_linear_light.jpg
     :align:   center
 
     lg10 to linear light. The green curve represents the lg to ln conversion. The red curve show the green channel of a Kodak 5218 exposure test. The x-axis is in 10bit input lg the output is in lg base2 linear light units. 0.0 Represents diffuse white.
@@ -81,7 +81,7 @@
 lgf is identical on the range from 0-1 to the standard lg luts. It specifies an additional range below 0.0 and above 1.0. In 10 bit the spaces is defined from -512 to 2048. Lg color timing number from either on set color correction devices or from a DI house to be applied in a way that can be fully inverted out without loss. Lgf specifies 18 stops above the lg10 max and 36 stops below the log10 min with a total dynamic range of 85 stops. The space is designed to be bigger than needed.
 
 
-.. figure::  images/spi-vfx/lgf_to_linear_light.jpeg
+.. figure::  images/spi-vfx/lgf_to_linear_light.jpg
     :align:   center
 
     lgf to linear light. The green curve represents the lg to ln conversion. The red curve show the green channel of a Kodak 5218 exposure test. The x axis is in 10bit input lg the output is in log(base2) linear light units. 0 Represents diffuse white
@@ -94,7 +94,7 @@
 
 GN is the Imageworks Panalog space. It follows the Panalog specification and additionally extrapolates so all of the values from 0 to 1023 are defined. This was necessary due to compression artifacts that could create values below the Panalog specifications. gn8,10,16 are defined with diffuse white at 681, Max white is approximately 2.6 stops above diffuse white and black is approximately 12.6 stops below diffuse white. The dynamic range is less than that of lg.
 
-.. figure::  images/spi-vfx/gn10_to_linear_light.jpeg
+.. figure::  images/spi-vfx/gn10_to_linear_light.jpg
     :align:   center
 
     gn10 to linear light. the x axis is in 10bit Panalog values. The Y axis is in linear light. The green curve is the gn curve. the red curve is the Panalog data.
@@ -103,7 +103,7 @@
 
 gnf specifies 14.5 stops above the gn10 max and 18 of stops below the gn10 min. The entire range of gnf is 47 stops.
 
-.. figure::  images/spi-vfx/gnf_to_linear_light.jpeg
+.. figure::  images/spi-vfx/gnf_to_linear_light.jpg
    :align:   center
 
    gnf to linear light. the x axis is in 10bit Panalog values. The Y axis is in linear light. The green curve is the gn curve. the red curve is the Panalog data. Only a subset of the function is used to define the gnf solorspace
@@ -116,7 +116,7 @@
 
 The vd spaces are mappings of linear image data into display space. The main part of the transformation is defined as a single curve that is conceptually two parts. The first is a ln to lg conversion. The second is lg to sRGB conversion. This is based off the neutral channel response of the sRGB film emulation lut used in the profile. The dynamic range of the vd colorspace is limited. It is undesirable to map the vd max to the linear max. Such a conversion results in linear values are almost never what an artist intended. The rule of thumb is that, at the high end, single value deltas in an 8 bit image should never create over a half stop of additional linear light. The vd conversion curve is limited to prevent this case.
 
-.. figure :: images/spi-vfx/lg8_to_vd8.jpeg
+.. figure :: images/spi-vfx/lg8_to_vd8.jpg
    :align: center
 
    The curve used to map from Lg8 to vd 8. The x-axis is in lg8 units, the y-axis is in vd8 units.
