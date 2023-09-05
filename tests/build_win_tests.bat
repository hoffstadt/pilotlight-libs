@rem keep environment variables modifications local
@setlocal

@rem make script directory CWD
@pushd %~dp0
@set dir=%~dp0

@rem modify PATH to find vcvarsall.bat
@set PATH=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build;%PATH%
@set PATH=C:\Program Files\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build;%PATH%
@set PATH=C:\Program Files (x86)\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build;%PATH%
@set PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build;%PATH%
@set PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise/VC\Auxiliary\Build;%PATH%

@rem setup environment for MSVC dev tools
@call vcvarsall.bat amd64 > nul

@rem default compilation result
@set PL_RESULT=[1m[92mSuccessful.[0m

@rem create main target output directoy
@if not exist "../out" @mkdir "../out"

@echo.
@if exist "../out/pilot_light_test.exe" del "../out/pilot_light_test.exe"
@if exist "../out/pilot_light_test_*.pdb" del "../out/pilot_light_test_*.pdb"

@rem create output directory
@if not exist "../out" @mkdir "../out"

@rem preprocessor defines
@set PL_DEFINES=-D_USE_MATH_DEFINES -D_DEBUG 

@rem include directories
@set PL_INCLUDE_DIRECTORIES=-I".." -I"%WindowsSdkDir%Include\um" -I"%WindowsSdkDir%Include\shared" 

@rem compiler flags
@set PL_COMPILER_FLAGS=-Zc:preprocessor -nologo -std:c11 -W4 -WX -wd4201 -wd4100 -wd4996 -wd4505 -wd4189 -wd5105 -wd4115 -permissive- -Od -MDd -Zi 

@rem run compiler (and linker)
@echo.
@echo [1m[93mStep: pilot_light_test[0m
@echo [1m[93m~~~~~~~~~~~~~~~~~~~~~~[0m
@echo [1m[36mCompiling and Linking...[0m

@rem call compiler
cl %PL_INCLUDE_DIRECTORIES% %PL_DEFINES% %PL_COMPILER_FLAGS% "main_tests.c" -Fe"../out/pilot_light_test.exe" -Fo"../out/" -link -incremental:no -PDB:"../out/pilot_light_test_%random%.pdb"

@rem check build status
@set PL_BUILD_STATUS=%ERRORLEVEL%

@rem failed
@if %PL_BUILD_STATUS% NEQ 0 (
    @echo [1m[91mCompilation Failed with error code[0m: %PL_BUILD_STATUS%
    @set PL_RESULT=[1m[91mFailed.[0m
    goto Cleanuppilot_light_test
)

@rem cleanup obj files
:Cleanuppilot_light_test
    @echo [1m[36mCleaning...[0m
    @del "../out/*.obj"  > nul 2> nul

@rem print results
@echo.
@echo [36mResult: [0m %PL_RESULT%
@echo [36m~~~~~~~~~~~~~~~~~~~~~~[0m

@rem return CWD to previous CWD
@popd