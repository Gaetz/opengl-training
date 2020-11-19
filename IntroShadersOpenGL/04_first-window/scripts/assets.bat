set buildDir=%~dp0..\build
set assetsDir=%~dp0..\assets
set extDir=%~dp0..\external

:: Copy dependencies
if not exist %buildDir%\SDL2.dll xcopy /y %extDir%\SDL2-2.0.12\lib\x64\SDL2.dll %buildDir%
if not exist %buildDir%\SDL2_image.dll xcopy /y %extDir%\SDL2_image-2.0.5\lib\x64\SDL2_image.dll %buildDir%
if not exist %buildDir%\libjpeg-9.dll xcopy /y %extDir%\SDL2_image-2.0.5\lib\x64\libjpeg-9.dll %buildDir%
if not exist %buildDir%\libpng16-16.dll xcopy /y %extDir%\SDL2_image-2.0.5\lib\x64\libpng16-16.dll %buildDir%
if not exist %buildDir%\zlib1.dll xcopy /y %extDir%\SDL2_image-2.0.5\lib\x64\zlib1.dll %buildDir%
if not exist %buildDir%\glew32.dll xcopy /y %extDir%\glew-2.1.0\bin\Release\x64\glew32.dll %buildDir%

:: Copy assets
if not exist %buildDir%\assets mkdir %buildDir%\assets
xcopy /y /s %assetsDir% %buildDir%\assets