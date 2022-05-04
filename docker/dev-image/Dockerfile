FROM ubuntu:22.04

ENV DISPLAY=${DISPLAY}

# requirements for building skia
RUN apt-get update -y && apt-get upgrade -y && apt-get install git -y

# requirements for building guis
RUN apt-get install -y libglfw3-dev libyaml-cpp-dev

COPY ./clone-and-build-skia.sh /tmp
RUN cd /tmp && ./clone-and-build-skia.sh

CMD [ "/bin/bash" ]
