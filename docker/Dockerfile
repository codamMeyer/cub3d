FROM debian:buster

RUN apt-get -y update && apt-get -y upgrade && apt-get -y install apt-utils && apt-get -y install make gcc vim clang libx11-dev libxext-dev zlib1g-dev libbsd-dev

COPY ./compile.sh /opt/

CMD bash /opt/compile.sh