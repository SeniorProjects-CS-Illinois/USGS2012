@ECHO OFF
TITLE Building Rivermodel
SETLOCAL DISABLEDELAYEDEXPANSION

SET batchpath=%~dp0
cd %batchpath%

ECHO Compiling Python code...
ECHO ################ COMPILE PYTHON ################# >> build_log.txt
ECHO RUNNING: python buildPython.py py2exe -p encodings -pPIL > build_log.txt
python buildPython.py py2exe -p encodings -pPIL >> build_log.txt 2>&1
if %errorlevel% neq 0 ( 
	GOTO error
)

ECHO . >> build_log.txt
ECHO ################ COMPILE C ################# >> build_log.txt
ECHO Compiling C code...
ECHO RUNNING: python setup.py build -cmingw32 >> build_log.txt
python setup.py build -cmingw32 >> build_log.txt 2>&1
if %errorlevel% neq 0 ( 
	GOTO error
)

ECHO . >> build_log.txt
ECHO ################ COPY CONTROLLER ################# >> build_log.txt
IF NOT EXIST "%batchpath%dist\controller" MKDIR "%batchpath%dist\controller"
ECHO Copying the controller directory to dist...
ECHO RUNNING: robocopy "%batchpath%controller" "%batchpath%dist\controller" /e /mir >> build_log.txt
robocopy "%batchpath%controller" "%batchpath%dist\controller" /e /mir >> build_log.txt 2>&1
if %errorlevel% neq 0 if %errorlevel% neq 1 if %errorlevel% neq 2  (  
	GOTO error
)

ECHO . >> build_log.txt
ECHO ################ COPY VIEW ################# >> build_log.txt
IF NOT EXIST "%batchpath%dist\view" MKDIR "%batchpath%dist\view"
ECHO Copying the view directory to dist...
ECHO RUNNING: robocopy "%batchpath%view" "%batchpath%dist\view" /e /mir >> build_log.txt
robocopy "%batchpath%view" "%batchpath%dist\view" /e /mir >> build_log.txt 2>&1
if %errorlevel% GEQ 8 ( 
	GOTO error
)

ECHO . >> build_log.txt
ECHO ################ COPY COMPILED PYTHON ################# >> build_log.txt
ECHO Copying the compiled python to dist\view...
ECHO RUNNING: robocopy "%batchpath%build\lib.win32-2.7" "%batchpath%dist\view" MainModule.pyd >> build_log.txt
robocopy "%batchpath%build\lib.win32-2.7" "%batchpath%dist\view" MainModule.pyd >> build_log.txt 2>&1
if %errorlevel% GEQ 8 ( 
	GOTO error
)

ECHO . >> build_log.txt
ECHO ################ COPY TKINTER FILES ################# >> build_log.txt
ECHO Copying tkinter files to dist\view...
ECHO RUNNING: robocopy C:\Python27\Lib\lib-tk "%batchpath%dist\view" tkFileDialog.py >> build_log.txt
robocopy C:\Python27\Lib\lib-tk "%batchpath%dist\view" tkFileDialog.py >> build_log.txt 2>&1
if %errorlevel% GEQ 8 ( 
	GOTO error
)
ECHO RUNNING: robocopy C:\Python27\Lib\lib-tk "%batchpath%dist\view" tkMessageBox.py >> build_log.txt
robocopy C:\Python27\Lib\lib-tk "%batchpath%dist\view" tkMessageBox.py >> build_log.txt 2>&1
if %errorlevel% GEQ 8 ( 
	GOTO error
)
ECHO RUNNING: robocopy C:\Python27\Lib\lib-tk "%batchpath%dist\view" tkCommonDialog.py >> build_log.txt
robocopy C:\Python27\Lib\lib-tk "%batchpath%dist\view" tkCommonDialog.py >> build_log.txt 2>&1
if %errorlevel% GEQ 8 ( 
	GOTO error
)


ECHO .
ECHO Build Complete
PAUSE
CLS
EXIT

:error
type build_log.txt
ECHO .
ECHO ################ ERROR #################
ECHO An error was encountered during the build.
ECHO The above output was appended to build_log.txt
PAUSE
CLS
EXIT
