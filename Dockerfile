FROM debian:11.5

LABEL maintainer="ozeliurs@gmail.com"

# Base packages
RUN apt-get update && \
    apt-get -y install nginx tor torsocks ntpdate sudo \
    gcc libsodium-dev make autoconf

ADD ./mkp224o /mkp224o
ADD ./main.sh /main.sh
ADD ./torrc /etc/tor/torrc
ADD ./nginx.conf /etc/nginx/nginx.conf

# Security and permissions
RUN useradd --system --uid 666 -M --shell /usr/sbin/nologin hidden

# Configure nginx logs to go to Docker log collection (via stdout/stderr)
RUN ln --symbolic --force /dev/stdout /var/log/nginx/access.log
RUN ln --symbolic --force /dev/stderr /var/log/nginx/error.log

# Configuration files and data output folder
VOLUME /web
WORKDIR /web

EXPOSE 9050

ENTRYPOINT ["/main.sh"]
CMD ["serve"]

