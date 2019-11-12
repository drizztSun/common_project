import datetime


def main():

    for i in range(10):
        print(i)
    # print("Current time %s " % (datetime.datetime.now()))


print("loading the pyc")

if __name__ == '__main__':

    main()


# convert py file into exe by 'pyinstaller'

# pyinstaller --onefile -w main.py

# pyinstaller --onefile main.py # on windows

#  install 'pyinstaller'
# pip install pyinstaller

# pyinstaller command
# usage: pyinstaller [-h] [-v] [-D] [-F] [--specpath DIR] [-n NAME]
#                   [--add-data <SRC;DEST or SRC:DEST>]
#                   [--add-binary <SRC;DEST or SRC:DEST>] [-p DIR]
#                   [--hidden-import MODULENAME]
#                   [--additional-hooks-dir HOOKSPATH]
#                   [--runtime-hook RUNTIME_HOOKS] [--exclude-module EXCLUDES]
#                   [--key KEY] [-d {all,imports,bootloader,noarchive}] [-s]
#                   [--noupx] [--upx-exclude FILE] [-c] [-w]
#                   [-i <FILE.ico or FILE.exe,ID or FILE.icns>]
#                   [--version-file FILE] [-m <FILE or XML>] [-r RESOURCE]
#                   [--uac-admin] [--uac-uiaccess] [--win-private-assemblies]
#                   [--win-no-prefer-redirects]
#                   [--osx-bundle-identifier BUNDLE_IDENTIFIER]
#                   [--runtime-tmpdir PATH] [--bootloader-ignore-signals]
#                   [--distpath DIR] [--workpath WORKPATH] [-y]
#                   [--upx-dir UPX_DIR] [-a] [--clean] [--log-level LEVEL]
#                   scriptname [scriptname ...]


import compileall

compileall.compile_dir('Lib/', force=True)

# Perform same compilation, excluding files in .svn directories.
import re
compileall.compile_dir('Lib/', rx=re.compile(r'[/\\][.]svn'), force=True)

# pathlib.Path objects can also be used.
import pathlib
compileall.compile_dir(pathlib.Path('Lib/'), force=True)



# The py_compile module provides a function to generate a byte-code file from a source file, 
# and another function used when the module source file is invoked as a script.

# Though not often needed, this function can be useful when installing modules for shared use, 
# especially if some of the users may not have permission to write the byte-code cache files in the directory containing the source code.

# Lib/py_compile.py
import py_compile

py_compile.compile('dir/main.py')