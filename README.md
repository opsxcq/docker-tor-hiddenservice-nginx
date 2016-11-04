# Docker container for creating and running your hidden services 
[![Docker Pulls](https://img.shields.io/docker/pulls/strm/docker-tor-hiddenservice-nginx.svg?style=plastic)](https://hub.docker.com/r/strm/docker-tor-hiddenservice-nginx/)
[![Open Source Love](https://badges.frapsoft.com/os/gpl/gpl.svg?v=102)](https://github.com/ellerbrock/open-source-badge/)

Easily run a hidden service inside the Tor network with this container


Generate the skeleton configuration for you hidden service, replace <pattern> for your hidden service pattern name.
Example, if you want to your hidden service contain the word 'boss', just use this word as argument. You can use regular expressions, like ```^boss```, will generate an address wich will start with 'boss'. Be aware that bigger the pattern, more time it will take to generate it.

```sh
docker run -it --rm -v $(pwd)/web:/web \
       strm/docker-tor-hiddenservice-nginx generate <pattern>
```


Create an container named 'hiddensite' to serve your generated hidden service

```sh
docker run -d --restart=always --name hiddensite -v $(pwd)/web:/web \
       strm/docker-tor-hiddenservice-nginx 
```

## Example

Let's create a hidden service with the name beginning with strm.

```sh
docker pull strm/docker-tor-hiddenservice-nginx
```

Wait to the container image be downloaded. And them we can generate our site skeleton:

```sh
#docker run -it --rm -v $(pwd)/web:/web strm/docker-tor-hiddenservice-nginx generate ^strm
[+] Generating the address with mask: ^strm
[+] Found matching domain after 137072 tries: strmfyygjp5st54g.onion
[+] Generating nginx configuration for site  strmfyygjp5st54g.onion
[+] Creating www folder
[+] Generating index.html template
```

Now we have our skeleton generated, we can run the container with:

```sh
docker run -d --restart=always --name hiddensite \
       -v $(pwd)/web:/web strm/docker-tor-hiddenservice-nginx
```

And you have the service running ! :)

<p align="center">
  <img src="https://github.com/opsxcq/docker-tor-hiddenservice-nginx/raw/master/print.png" alt="print"/>
  </p>

## Build

docker build -t strm/docker-tor-hiddenservice-nginx .

## Run

docker run -d --restart=always --name hiddensite \
       -v $(pwd)/web:/web strm/docker-tor-hiddenservice-nginx 

## Shell

docker run -it --rm -v $(pwd)/web:/web \
       --entrypoint /bin/bash strm/docker-tor-hiddenservice-nginx

