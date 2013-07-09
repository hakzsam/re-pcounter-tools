#!/bin/sh

export WLD=$HOME/install
export LD_LIBRARY_PATH=$WLD/lib
export PKG_CONFIG_PATH=$WLD/lib/pkgconfig/:$WLD/share/pkgconfig/
#export ACLOCAL="aclocal -I $WLD/share/aclocal"

./autogen.sh                            \
    --prefix=$WLD                       \
    --enable-gles2                      \
    --disable-gallium-egl               \
    --with-egl-platforms=x11,drm        \
    --enable-gbm                        \
    --enable-shared-glapi               \
    --with-gallium-drivers=nouveau      \
    --enable-debug
make
make install
