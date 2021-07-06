# Easily create and run hidden services 
[![Docker Pulls](https://img.shields.io/docker/pulls/strm/tor-hiddenservice-nginx.svg?style=plastic)](https://hub.docker.com/r/strm/tor-hiddenservice-nginx/)
![License](https://img.shields.io/badge/License-GPL-blue.svg?style=plastic)


##This fork is under developpement and thus not recommanded.

## TODO
- [ ] [warn] You are running Tor as root. You don't need to, and you probably shouldn't.
- [ ] Fix permissions on web server

Easily run a hidden service inside the Tor network with this container


Generate the skeleton configuration for you hidden service, replace <pattern>
for your hidden service pattern name. Example, if you want to your hidden
service contain the word 'boss', just use this word as argument. You can use
regular expressions, like ```^boss```, will generate an address wich will start
with 'boss'. Be aware that bigger the pattern, more time it will take to
generate it.

```sh
docker run -it --rm -v $(pwd)/web:/web \
       strm/tor-hiddenservice-nginx generate <pattern>
```


Create an container named 'hiddensite' to serve your generated hidden service

```sh
docker run -d --restart=always --name hiddensite -v $(pwd)/web:/web \
       strm/tor-hiddenservice-nginx 
```

## Example

Let's create a hidden service with the name beginning with strm.

```sh
docker pull strm/tor-hiddenservice-nginx
```

Wait to the container image be downloaded. And them we can generate our site
skeleton:

```sh
$docker run -it --rm -v $(pwd)/web:/web strm/tor-hiddenservice-nginx generate ^strm
[+] Generating the address with mask: ^strm
[+] Found matching domain after 137072 tries: strmfyygjp5st54g.onion
[+] Generating nginx configuration for site  strmfyygjp5st54g.onion
[+] Creating www folder
[+] Generating index.html template
```

Now we have our skeleton generated, we can run the container with:

```sh
docker run -d --restart=always --name hiddensite \
       -v $(pwd)/web:/web strm/tor-hiddenservice-nginx
```

And you have the service running ! :)

<p align="center">
  <img src="https://github.com/opsxcq/docker-tor-hiddenservice-nginx/raw/master/print.png" alt="print"/>
  </p>

## Troubleshoot 

 - 403 error on nginx, check your directory permissions and folder permissions.
   Nginx run as "hidden" user, his UID is 666, just check if you give this user
   access to the /web/www folder (in the case the folder mapped to it).
   
# FAQ

## Anti-Pattern

While is not a good thing to run everything in one container, this is a easy way
to get started if you don't have that much experience with docker and hidden
services. If you want to use something more elaborated, check this
[repository](https://github.com/opsxcq/docker-tor).

Here is an example of how a deploy using this other image looks like.

```yml
version: '3'

services:
  tor:
    image: strm/tor
    restart: always
    depends_on:
      - backend
    environment:
        LISTEN_PORT: "80"
        REDIRECT: "backend:80"
        PRIVATE_KEY: |
          -----BEGIN RSA PRIVATE KEY-----
          MIICXQIBAAKBgQDSqBzjGxL+UFdrFJSdc+LJn3RrXiaZ7k6kgSw8KqOCSRgIr2qO
          XZrCa3YHE+PqsfbDVF0GO0Xy3A9fsIxRFMUo3K++3BaVJslUbqK2TH9fJt5Ji1b6
          N5UzXsEzf73atXwMF63hgVFZFLhfSWH8jGE1svwDXn0YQWP88PVX34SrWQIDASsd
          AoGAUWdd+/m9TrTQyqK0IbzIr0fYQ5gDq4mv1GLEYjR4SWF8pSCxL1yOBsmQ02sj
          BSS2Vw4dpFfloCrRw2ipM8ac4kdLGCoYefQHwW2Kfdf9raVfPDP7vcxrs37sOgOh
          2rSXCOOrmcoMrEka2/OTGW15jaNUEEoWacS3YL1Fj0Bi6g0CQQD4ZmBiF6qu2XnT
          8lMr1Asdz3K8fYiyfl6CzHItUubAbQ8ipv12q8CerJqk3dO98V+w8llAsQ7BT5wq
          8AZOPQR3AkEA2RobnACDvb2Jw+dYSFsqrHyIDojKsrNiDEFedkiFijRFqme+nrif
          kJ4yTnSiphC+rSSBbvYMawsqiWBA7UPSrwJBAKXSVQClxNUpJ2PZt91HZAtuipRt
          t8suGIY4mot1iDRN0XdiNN8TNZ3qLag7wUU4or+Yn/3Xae1euHpyftTxmYsCQQCd
          oJxsGotYx62ULxPqz0um7yEWOU6hUAy8MB3X3FcTCjGO0PPKpfJ2ntXo0Ajcp5ci
          msi81/e9DTnF9mPjtsY9AkAUG6heBlETMFzyka9FHPgu9aN2kRwvJ3QZDHuPxYG4
          VZwljLxstlx57+N74D0aj6wrJw+iBH2BI+b+ZpnLXyy7
          -----END RSA PRIVATE KEY-----
```

To make it work you should also add a webserver with the name `backend`, and add
your content there. There are more moving pieces using a deploy like this, so
this is the justification for this repository, for people who never put anything
on the deep web being able to enjoy it without busting their asses debugging
some infrastructure.


## Build

```
docker build -t strm/tor-hiddenservice-nginx .
```

## Run

```
docker run -d --restart=always --name hiddensite \
       -v $(pwd)/web:/web strm/tor-hiddenservice-nginx 

```
## Shell

```
docker run -it --rm -v $(pwd)/web:/web \
       --entrypoint /bin/bash strm/tor-hiddenservice-nginx

```
