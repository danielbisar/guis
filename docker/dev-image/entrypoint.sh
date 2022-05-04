#!/bin/bash

xauth add $XAUTH_COOKIE
cd
cd src

if [ ! -d ./guis ]; then
    git clone https://github.com/danielbisar/guis.git
fi

cd guis
/bin/bash
