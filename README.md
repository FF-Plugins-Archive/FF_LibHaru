# NOTE
We frequently checking our issues. If you have a problem, open an issue. Not send us an email. If problem is about us and we can help you, we will help you. Sending an email won't change our response speed.

# USED LIBRARY
LibHaru (We didn't use ZLIB, LIBJPEG or LIBPNG) <br />
https://github.com/libharu/libharu

# DEPENDENCIES
https://github.com/FF-Projects-UE/ExtendedVars

# TARGET PLATFORM
* It currently only works on Windows platform.
* It supports only <b>latest released version of Unreal Engine</b>. We can't help you if you want to use older ones. Moving to latest version takes approximately one month.

# LIBHARU WRITE FUNCTIONS
* <b>LibHaru - Create Document</b>: It creates a LibHaru based PDF file. It's object is different than PDFium's. So, you can't merge them unless export it and then re-import it, first.

* <b>LibHaru - Add Pages</b>: It adds pages to target PDF file with defined size. (Array count is page count and each vector element of array is its size)

* <b>LibHaru - Load Standart Font</b>: There are 14 standart fonts embedded to PDF libraries according to PDF Spec 1.7 page 416. This function allows to select one them. These fonts don't support extended characters (Turkish, Cyrillic and Asian). If you want to use that kind of chars, you have to find and use external fonts.

* <b>LibHaru - Load External Font</b>:

* <b>LibHaru - Add Text</b>: It adds text objects to target page. Libharu doesn't support line break at default but we integrated a parse system. So it has auto wrap feature. Neverthless, we suggest you that be careful about your layout (for example when will you create a line break or not)
	* Text Color
	* Position X = Horizontal position.
	* Position Y = Vertical position but it starts from bottom. If your PDF page's height is 800 pixel, top will be 800 and bottom will be 0.
	* Shear X and Y = It strecth your text object. Scaling won't be vectoral. So we don't suggest it.
	* Rotation X and Y = We don't know how it works right now.
	* Border X and Y = It defines vertical and horizontal borders.
	
* <b>LibHaru - Add Image</b>: It adds an UTexture2D to target page. Extension and format is not important. Function converts its data to RGB Raw Data.

* <b>LibHaru - Add Line, Circle, Ellipse, Arc and Rectangle</b>: It draws line, circle, ellipse, arc or rectangle to target page with specified properties.

* <b>LibHaru - Add U3D 3D Model to PDF</b>: It adds a U3D 3D model to target page. You can define background color, viewer size and location. You can convert your models to U3D with Aspose OBJ/GLTF/FBX online converter to U3D or you can use local tools like CAD Exchanger. U3D extension is very primitive. So, don't expect realistic views. Google Chrome and other basic PDF viewers can't show 3D contents on PDF pages. You have to use Acrobat Pro like professional tools to view it.

* <b>LibHaru - Save PDF</b>: It saves PDF file to given absolute path. You don't need to spawn anything to use this function like PDFium.

* <b>LibHaru - Save as Bytes</b>: It saves PDF as bytes array (TArray<uint8>). So, you can render it with PDFium without writing and reading a PDF file.

* <b>LibHaru - Close Document</b> 

# IMPORTANT FOR IMAGE INSERT
In order to insert images to PDF files in runtime, you have to do these changes for your textures. Because currently DXT textures aren't supported in runtime. But you can use them for editor-only projects.<br />
Runtime imported textures are generally transient PF_B8G8R8A8 without compression. They can work without problem. <br />
* Texture Group as UI
* MipGen Settings as NoMipMaps
* CompressionSettings as UserInterface2D
