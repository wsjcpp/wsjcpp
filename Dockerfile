
# wsjcpp@v0.2.2
FROM debian:10
# install build requiremenets
RUN apt update && apt install -y --no-install-recommends \
  build-essential \
  make \
  cmake \
  gcc \
  g++ \
  pkg-config \
  git-core \
  ssh \
  ca-certificates \
  libcurl4-openssl-dev && rm -rf /var/lib/apt/lists/*

COPY . /root/wsjcpp-src
RUN cd /root/wsjcpp-src \
    && mkdir -p tmp.docker \
    && cd tmp.docker \
    && cmake .. \
    && make \
    && cp ../wsjcpp /usr/bin/wsjcpp \
    && cd .. \
    && rm -rf tmp.docker

WORKDIR /root/project

