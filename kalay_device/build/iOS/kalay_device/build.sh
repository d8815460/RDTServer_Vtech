
rm -rf build

xcodebuild -showsdks

xcodebuild -configuration Release -target kalay_device

xcodebuild -configuration Release -target kalay_device_mac
