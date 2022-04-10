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
if not exist external\SDL2_mixer-devel-2.0.4-VC (
	cd external
	if not exist SDL2_mixer-devel-2.0.4-VC.zip (
		curl -LO https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.4-VC.zip
	)
	powershell Expand-Archive SDL2_mixer-devel-2.0.4-VC.zip
	cd ..
)

if not exist external\json-c-0.15 (
	cd external
	if not exist json-c-0.15.tar.gz (
		curl -LO https://s3.amazonaws.com/json-c_releases/releases/json-c-0.15.tar.gz
	)
	tar -xzf json-c-0.15.tar.gz json-c-0.15
	if not exist json-c-build (
		if not defined DevEnvDir (
			call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
		)
		mkdir json-c-build
		cd json-c-build
		cmake ../json-c-0.15
		msbuild "json-c.vcxproj" /m /verbosity:normal /p:OutDir=lib\
		cd ..
	)
	cd ..
)
if not exist external\lua-5.4.4 (
	if not defined DevEnvDir (
		call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
	)
	cd external
	if not exist lua-5.4.4.tar.gz (
		curl -LO https://www.lua.org/ftp/lua-5.4.4.tar.gz
	)
	tar -xzf lua-5.4.4.tar.gz lua-5.4.4
	cd lua-5.4.4\src

	cl /MD /O2 /c /DLUA_BUILD_AS_DLL *.c
	ren lua.obj lua.o
	ren luac.obj luac.o
	link /DLL /IMPLIB:lua5.4.4.lib /OUT:lua5.4.4.dll *.obj
	link /OUT:lua.exe lua.o lua5.4.4.lib
	lib /OUT:lua5.4.4-static.lib *.obj
	link /OUT:luac.exe luac.o lua5.4.4-static.lib
	cd ..\..\..
)
echo %CD%
if not defined DevEnvDir (
	call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

copy external\SDL2-devel-2.0.20-VC\SDL2-2.0.20\lib\x64\*.dll .
copy external\SDL2_image-devel-2.0.5-VC\SDL2_image-2.0.5\lib\x64\*.dll .
copy external\json-c-build\lib\json-c.dll .
copy external\lua-5.4.4\src\*.dll .
copy external\SDL2_mixer-devel-2.0.4-VC\SDL2_mixer-2.0.4\lib\x64\*.dll .
cl /Fequee.exe *.c^
	external\SDL2-devel-2.0.20-VC\SDL2-2.0.20\lib\x64\SDL2.lib external\SDL2_image-devel-2.0.5-VC\SDL2_image-2.0.5\lib\x64\SDL2_image.lib external\SDL2_mixer-devel-2.0.4-VC\SDL2_mixer-2.0.4\lib\x64\SDL2_mixer.lib external\json-c-build/Debug/json-c.lib external\lua-5.4.4\src\lua5.4.4.lib^
	/I external\SDL2-devel-2.0.20-VC\SDL2-2.0.20\include /I external\SDL2_image-devel-2.0.5-VC\SDL2_image-2.0.5\include /I external\SDL2_mixer-devel-2.0.4-VC\SDL2_mixer-2.0.4\include /I external\json-c-0.15/ /I external\json-c-build/ /I external\lua-5.4.4\src