cd ..

qmake RoomKit.pro "CONFIG+=release"
make

cd ../bin

macdeployqt RoomKit.app

cp -r ../SDK/RoomEngineSDK/mac/TUIRoomEngine_Mac.framework ./RoomKit.app/Contents/Frameworks/TUIRoomEngine_Mac.framework
cp -r ../SDK/RoomEngineSDK/mac/ImSDKForMac_Plus.framework ./RoomKit.app/Contents/Frameworks/ImSDKForMac_Plus.framework
cp -r ../SDK/RoomEngineSDK/mac/TXLiteAVSDK_TRTC_Mac.framework ./RoomKit.app/Contents/Frameworks/TXLiteAVSDK_TRTC_Mac.framework
cp -r ../SDK/RoomEngineSDK/mac/TXSoundTouch.xcframework/macos-arm64_x86_64/TXSoundTouch.framework ./RoomKit.app/Contents/Frameworks/TXSoundTouch.framework
cp -r ../SDK/RoomEngineSDK/mac/TXFFmpeg.xcframework/macos-arm64_x86_64/TXFFmpeg.framework ./RoomKit.app/Contents/Frameworks/TXFFmpeg.framework

cp -r ../RoomKit/Resource/trtcres ./RoomKit.app/Contents/MacOS/trtcres
cp -r ../RoomKit/Resource/MacOSX/RoomKit.icns ./RoomKit.app/Contents/Resources/
cp -r ../RoomKit/Resource/MacOSX/Info.plist ./RoomKit.app/Contents/


# mv RoomKit.dmg TRTCRoomSetup64_Mac_V$LiteavVersion.$BuildNo.dmg

# tar -czvf TRTCApp.tar ./*
# tar -cjf TRTCAppSetup64_Mac_V$LiteavVersion.$BuildNo.tar.bz2 TRTCAppSetup64_Mac_V$LiteavVersion.$BuildNo.dmg
