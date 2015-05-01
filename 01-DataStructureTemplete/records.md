# Project 01

* Ribbon Bar

* PowerPoint 2013 for UI Elements Designing 
  Picture for toolbar should be in 32px in height

* Initialize GDI+
  // Initialize GDI+
  Insert the following code before any drawing action. 

    ```
    GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
    INITCOMMONCONTROLSEX InitCtrls;
    ```

  And add the following code to common headers

    ```
    #include <gdiplus.h>
    using namespace Gdiplus;
    #pragma comment (lib,"Gdiplus.lib")
    ```

* Load PNG image from resource
  Using the following library
  http://www.codeproject.com/Articles/3537/Loading-JPG-PNG-resources-using-GDI

* Class heriechy relationships


