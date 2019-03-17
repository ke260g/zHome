cmake -D CMAKE_TOOLCHAIN_FILE=platforms/linux/arm-gnueabi.toolchain.cmake -D CMAKE_BUILD_TYPE=Release -D SOFTFP=ON -D ENABLE_NEON=ON -Wno-dev .
