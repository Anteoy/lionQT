# lionQT
lionQT supported for liongo

# deploy
export LD_LIBRARY_PATH=/home/zhoudazhuang/db10/qt-soft/5.10.0/gcc_64/lib:$LD_LIBRARY_PATH    
export QT_PLUGIN_PATH=/home/zhoudazhuang/db10/qt-soft/5.10.0/gcc_64/plugins:$QT_PLUGIN_PATH    
export QML2_IMPORT_PATH=/home/zhoudazhuang/db10/qt-soft/5.10.0/gcc_64/qml:$QML2_IMPORT_PATH    
export PATH=/home/zhoudazhuang/db10/qt-soft/5.10.0/gcc_64/bin:$PATH    
openssl version    
sudo ../linuxdeployqt-6-x86_64.AppImage lionQT -appimage -qmake=/home/zhoudazhuang/db10/qt-soft/5.10.0/gcc_64/bin/qmake    
