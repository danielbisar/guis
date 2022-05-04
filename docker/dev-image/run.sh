#!/bin/bash

XAUTH_COOKIE="$(xauth list | head -1 | sed "s/unix:/unix$DISPLAY/")"
docker run --env="DISPLAY" \
    --volume=/tmp/.X11-unix:/tmp/.X11-unix \
    --network=host \
    -it dbisar/guis-dev-image \
    /bin/bash -c "xauth add $XAUTH_COOKIE && cd && cd src && git clone https://github.com/danielbisar/guis.git && /bin/bash"
