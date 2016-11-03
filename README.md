# Easy container for running hidden services

Easily run a hidden service inside the Tor network with this container


Generate the skeleton configuration for you hidden service, replace <pattern> for your hidden service pattern name.
Example, if you want to your hidden service contain the word 'boss', just use this word as argument. You can use regular expressions, like ```^boss```, will generate an address wich will start with 'boss'. Be aware that bigger the pattern, more time it will take to generate it.

```sh
docker run -it --rm -v $(pwd)/web:/web strm/tor-hidden-service-nginx generate <pattern>
```


Create an container named 'hiddensite' to serve your generated hidden service

```sh
docker run -d --restart=always --name hiddensite -v $(pwd)/web:/web strm/tor-hidden-service-nginx 
```

## Build

docker build -t strm/tor-hidden-service-nginx .

## Run

docker run -d --restart=always --name hiddensite -v $(pwd)/web:/web strm/tor-hidden-service-nginx 

## Shell

docker run -it --rm -v $(pwd)/web:/web --entrypoint /bin/bash strm/tor-hidden-service-nginx
