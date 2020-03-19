
# wsjcpp@v0.0.1
FROM debian:10
# install build requiremenets
RUN apt update && apt install -y --no-install-recommends \
  make \
  cmake \
  g++ \
  pkg-config \
  git-core \
  libcurl4-openssl-dev

COPY . /root/wsjcpp-src
RUN cd /root/wsjcpp-src \
    && mkdir -p tmp.docker \
    && cd tmp.docker \
    && cmake .. \
    && make \
    && cp ../wsjcpp /usr/bin/wsjcpp

WORKDIR /root/project

