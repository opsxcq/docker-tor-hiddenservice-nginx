FROM debian:jessie

MAINTAINER opsxcq <opsxcq@thestorm.com.br>

# Setup user
RUN useradd --system --uid 666 -M --shell /usr/sbin/nologin hidden

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

# Configure permissions
RUN chmod -R 777 /var/log/nginx /var/lib/tor/ /var/log/tor && \
    chmod 644 -R /etc/nginx/ && \
    chmod 644 -R /etc/tor/

# Add nginx default configuration 
ADD ./nginx.conf /etc/nginx/nginx.conf

# Security meansure
USER hidden-service

# Configuration files and data output folder
VOLUME /web
WORKDIR /web

USER hidden

ENTRYPOINT ["/main.sh"]
CMD ["serve"]

