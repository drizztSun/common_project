import datetime

def main():

    for i in range(10):
        print(i)
    # print("Current time %s " % (datetime.datetime.now()))


if __name__ == '__main__':

    main()


# convert py file into exe by 'pyinstaller'

# pyinstaller --onefile -w main.py

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