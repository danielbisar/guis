#!/bin/bash

XAUTH_COOKIE="$(xauth list | head -1 | sed "s/unix:/unix$DISPLAY/")"
export XAUTH_COOKIE

docker run --env="DISPLAY" --env="XAUTH_COOKIE" \
    --volume=/tmp/.X11-unix:/tmp/.X11-unix \
    --network=host \
    -it dbisar/guis-dev-image \
    /bin/bash -c /tmp/entrypoint.sh
