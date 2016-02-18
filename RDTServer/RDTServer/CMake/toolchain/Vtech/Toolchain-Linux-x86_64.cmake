# toolchain file I use to cross compile on Linux
# targetting OSX/Darwin (x86_64). running:
# cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/Toolchain-OSX-x86_64.cmake ....

SET(CMAKE_SYSTEM_NAME Linux)

SET(CMAKE_C_COMPILER   /opt/dspg/v1.2.7-rc2/sysroots/i686-dspg-linux/usr/bin/armv5te-dspg-linux-gnueabi/arm-dspg-linux-gnueabi-gcc)
SET(CMAKE_CXX_COMPILER /opt/dspg/v1.2.7-rc2/sysroots/i686-dspg-linux/usr/bin/armv5te-dspg-linux-gnueabi/arm-dspg-linux-gnueabi-g++)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH /opt/dspg/v1.2.7-rc2/sysroots/i686-dspg-linux)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
