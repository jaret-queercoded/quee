if not exist external (
	mkdir external
)
if not exist external\SDL2-devel-2.0.20-VC (
	cd external
	if not exist SDL2-devel-2.0.20-VC.zip (
		curl -LO https://www.libsdl.org/release/SDL2-devel-2.0.20-VC.zip
	)
	powershell Expand-Archive SDL2-devel-2.0.20-VC.zip
	cd ..
)
if not exist external\SDL2_image-devel-2.0.5-VC (
	cd external
	if not exist SDL2_image-devel-2.0.5-VC.zip (
		curl -LO https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip
	)
	powershell Expand-Archive SDL2_image-devel-2.0.5-VC.zip
	cd ..
)
if not exist external\json-c-0.15 (
	cd external
	if not exist json-c-0.15.tar.gz (
		curl -LO https://s3.amazonaws.com/json-c_releases/releases/json-c-0.15.tar.gz
	)
	tar -xzf json-c-0.15.tar.gz json-c-0.15
	if not exist json-c-build (
		call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
		mkdir json-c-build
		cd json-c-build
		cmake ../json-c-0.15
		msbuild "json-c.vcxproj" /m /verbosity:normal /p:OutDir=lib\
		cd ..
	)
	cd ..
)
echo %CD%
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

copy external\SDL2-devel-2.0.20-VC\SDL2-2.0.20\lib\x64\*.dll .
copy external\SDL2_image-devel-2.0.5-VC\SDL2_image-2.0.5\lib\x64\*.dll .
copy external\json-c-build\lib\json-c.dll .
cl /Fequee.exe main.c quee_helpers.c quee_sprite.c quee_scene.c quee_renderer.c^
	external\SDL2-devel-2.0.20-VC\SDL2-2.0.20\lib\x64\SDL2.lib external\SDL2_image-devel-2.0.5-VC\SDL2_image-2.0.5\lib\x64\SDL2_image.lib external\json-c-build/Debug/json-c.lib^
	/I external\SDL2-devel-2.0.20-VC\SDL2-2.0.20\include /I external\SDL2_image-devel-2.0.5-VC\SDL2_image-2.0.5\include /I external\json-c-0.15/ /I external\json-c-build/