#!/bin/bash
if [ ! -d releases ]; then
  mkdir releases
fi

#echo "Do you want to sign the build(Y/N)?"

#read signbuild

signbuild='N'

if [[ $signbuild = 'Y' ]] || [[ $signbuild == 'y' ]]
then
export CSC_IDENTITY_AUTO_DISCOVERY=true
else
export CSC_IDENTITY_AUTO_DISCOVERY=false
fi

echo "CSC_IDENTITY_AUTO_DISCOVERY=$CSC_IDENTITY_AUTO_DISCOVERY"

export VERSION_MAJOR=1.3.2
export VERSION=$VERSION_MAJOR.`git rev-parse --short HEAD`

RED='\033[0;31m'
NC='\033[0m' # No Color
echo ""
echo "${RED}-----------------------------------${NC}"
echo "${RED}BUILDING VERSION : $VERSION ${NC}"
echo "${RED}-----------------------------------${NC}"

rm -rf releases/*

echo "Changing working directory to wapptunnel and running make"
cd wapptunnel
make

echo "Changing working directory to ui"
cd ../ui
rm -rf dist

if [ ! -d bin ]; then
  mkdir bin
fi

npm install
npm run build

export DEBUG=electron-builder


for i in `ls ../wapptunnel/bin`
do
  IFS="-" read -ra names <<< "$i"
  os=${names[1]}
  arch=${names[2]}

  rm -rf bin/*
  cp ../wapptunnel/bin/$i ./bin
  cp bin/$i build/pkg-scripts/wapptunneld
  echo $VERSION > build/pkg-scripts/version
  chmod 777 build/pkg-scripts/version
  cp bin/$i build/wapptunneld.exe
  echo $VERSION > build/version
  mv bin/$i bin/wapptunnel

  if [ "$os" == "darwin" ]
  then
    if [ "$arch" == "amd64" ]
    then
      echo "Building installer for $os $arch"
      cp ./build/osquery-3.4.0/darwin/osqueryd build/pkg-scripts/
      npm run buildmac64
      rm dist/EAAClient-$VERSION_MAJOR.pkg
      cp -rf build/pkg-scripts dist/mac/EAAClient.app/Contents/
      if [[ $signbuild = 'Y' ]] || [[ $signbuild == 'y' ]]
      then
        mv ../releases/EAAClient-$VERSION_MAJOR.pkg ../releases/EAAClient-tmp.pkg
        productsign --sign 'Developer ID Installer: Seetharama Ayyadevara' "../releases/EAAClient-tmp.pkg" "../releases/EAAClient.pkg"
        rm ../releases/EAAClient-tmp.pkg
      else
        rm ../releases/EAAClient-$VERSION_MAJOR.pkg
      fi
      /Applications/BitRock\ InstallBuilder\ Professional\ 18.8.0/bin/builder build ../EAAClient-$VERSION_MAJOR-MACOSX.xml osx --setvars project.version=$VERSION project.outputDirectory=$PWD/../releases
      tar -C ../releases/EAAClient-$VERSION-osx-installer.app/ -cvf ../releases/EAAClient-$VERSION-osx-installer.app.zip ./
      rm -rf ../releases/EAAClient-$VERSION-osx-installer.app/
    fi
  elif [ "$os" == "windows" ]
  then
    if [ "$arch" == "386" ]
    then
      echo "Building installer for $os $arch"
      cp ../wapptunnel/windowsrun/bin/windowsrun-windows-386 build/wapprun.exe
      npm run buildwin32
      rm  dist/EAAClient\ Setup\ $VERSION_MAJOR.exe
      cp build/pkg-scripts/wapptunneld dist/win-ia32-unpacked/wapptunneld.exe
      cp build/prod_cacert.pem  dist/win-ia32-unpacked/
      cp build/stage_cacert.pem dist/win-ia32-unpacked/
      cp build/eaacloop.png dist/win-ia32-unpacked/
      cp ../wapptunnel/windowsrun/bin/windowsrun-windows-386 dist/win-ia32-unpacked/wapprun.exe
      /Applications/BitRock\ InstallBuilder\ Professional\ 18.8.0/bin/builder build ../EAAClient-$VERSION_MAJOR-Win-x86.xml windows --setvars project.version=$VERSION-x86 project.outputDirectory=$PWD/../releases
      #mv ../releases/EAAClient\ Setup\ $VERSION_MAJOR.exe ../releases/EAAClient-i386.exe
    else
      echo "Building installer for $os $arch"
      cp ../wapptunnel/windowsrun/bin/windowsrun-windows-amd64 build/wapprun.exe
      npm run buildwin64
      cp ./build/osquery-3.4.0/windows/osqueryd.exe dist/win-unpacked/osqueryd.exe
      rm dist/EAAClient\ Setup\ $VERSION_MAJOR.exe
      cp build/pkg-scripts/wapptunneld dist/win-unpacked/wapptunneld.exe
      cp build/prod_cacert.pem  dist/win-unpacked/
      cp build/stage_cacert.pem dist/win-unpacked/
      cp build/eaacloop.png dist/win-unpacked/
      cp ../wapptunnel/windowsrun/bin/windowsrun-windows-amd64 dist/win-unpacked/wapprun.exe
      /Applications/BitRock\ InstallBuilder\ Professional\ 18.8.0/bin/builder build ../EAAClient-$VERSION_MAJOR-Win-x64.xml windows --setvars project.version=$VERSION-x64 project.outputDirectory=$PWD/../releases
      #mv ../releases/EAAClient\ Setup\ $VERSION_MAJOR.exe ../releases/EAAClient-x64.exe
    fi
  elif [ "$os" == "linux" ]
  then
    if [ "$arch" == "amd64" ]
    then
      echo "Building installer for $os $arch"
      npm run buildlinux64
      if [ ! -d dist/linux-unpacked-stage ]; then
          mkdir -p dist/linux-unpacked-stage
      fi
      cp ../wapptunnel/linuxrun/uninstaller dist/linux-unpacked-stage/
      cp ../wapptunnel/linuxrun/eaaclient.desktop dist/linux-unpacked-stage/
      cp ../wapptunnel/linuxrun/wapptunnel.service dist/linux-unpacked-stage/
      cp ../wapptunnel/bin/wapptunnel-linux-amd64 dist/linux-unpacked-stage/wapptunneld
      cp build/eaacloop.png dist/linux-unpacked-stage/
      cp build/iconlin.png dist/linux-unpacked-stage/
      cp build/prod_cacert.pem dist/linux-unpacked-stage/
      cp build/stage_cacert.pem dist/linux-unpacked-stage/
      cp dist/EAAClient*.AppImage dist/linux-unpacked-stage/EAAClient
      /Applications/BitRock\ InstallBuilder\ Professional\ 18.8.0/bin/builder build ../EAAClient-$VERSION_MAJOR-Linux.xml linux-x64 --setvars project.version=$VERSION project.outputDirectory=$PWD/../releases
    fi
  fi

  rm build/pkg-scripts/wapptunneld
  rm build/wapptunneld.exe
  #rm build/pkg-scripts/version
  #rm build/version
done
