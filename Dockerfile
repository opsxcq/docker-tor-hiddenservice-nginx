FROM debian:jessie

MAINTAINER Rafael <rafael@thestorm.com.br>

# Base packages
RUN apt-get update && \
    apt-get -y install \
    nginx \  
    tor torsocks ntpdate

# Compile shallot
ADD ./shallot /shallot
RUN apt-get -y install \
    build-essential \ 
    libssl-dev && \
    cd /shallot && \
    ./configure && \
    make && \
    mv ./shallot /bin && \
    cd / && \
    rm -Rf /shallot && \
    apt-get -y purge build-essential libssl-dev && \
    rm -Rf /var/lib/apt/lists/*

# Main script
ADD ./main.sh /main.sh

# Tor Config
ADD ./torrc /etc/tor/torrc

# Link nginx conf to /web/conf
ADD ./nginx.conf /etc/nginx/nginx.conf

# Configuration files and data output folder
VOLUME /web
WORKDIR /web

# Network configuration for browser exploidation
EXPOSE 80

ENTRYPOINT ["/main.sh"]
CMD ["serve"]

