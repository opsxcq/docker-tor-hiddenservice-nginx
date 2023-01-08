# Easily create and run hidden services 
[![Docker Pulls](https://img.shields.io/docker/pulls/ozeliurs/tor-hiddenservice-nginx.svg?style=plastic)](https://hub.docker.com/r/ozeliurs/tor-hiddenservice-nginx/)
![License](https://img.shields.io/badge/License-GPL-blue.svg?style=plastic)

<p align="center">
  <a href="https://sonarqube.ozeliurs.com/dashboard?id=docker-tor-hiddenservice-nginx">
    <img src="https://sonarqube.ozeliurs.com/api/project_badges/quality_gate?project=docker-tor-hiddenservice-nginx&token=fafab838944b408774e000f0c2e7f6176916a3a8"> 
  </a>
</p>

This is a fork of opsxcq's project. This docker image now supports tor v3
adresses and shallot has been replaced by mkp224o (v3 compatible).
Feel free to open issues on this project if you see something wrong.

Easily run a hidden service inside the Tor network with this container

Generate the skeleton configuration for you hidden service, replace <pattern>
for your hidden service pattern name. Example, if you want to your hidden
service contain the word 'boss', just use this word as argument. Be aware that 
bigger the pattern, more time it will take to generate it.

```sh
docker run -it --rm -v $(pwd)/web:/web ozeliurs/tor-hiddenservice-nginx generate <pattern>
```

Create an container named 'hiddensite' to serve your generated hidden service

```sh
docker run -d --restart=always --name hiddensite -v $(pwd)/web:/web ozeliurs/tor-hiddenservice-nginx 
```

## Example

Let's create a hidden service with the name beginning with strm.

```sh
docker pull ozeliurs/tor-hiddenservice-nginx
```

Wait to the container image be downloaded. And them we can generate our site
skeleton:

```sh
$docker run -it --rm -v $(pwd)/web:/web ozeliurs/tor-hiddenservice-nginx generate strm
[+] Generating the address with mask: ^strm
[+] Found matching domain after 137072 tries: strmfyygjp5st54g.onion
[+] Generating nginx configuration for site  strmfyygjp5st54g.onion
[+] Creating www folder
[+] Generating index.html template
```

Now we have our skeleton generated, we can run the container with:

```sh
docker run -d --restart=always --name hiddensite -v $(pwd)/web:/web ozeliurs/tor-hiddenservice-nginx
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

## Build Docker image

```
docker build -t ozeliurs/tor-hiddenservice-nginx .
```

## Run Docker container

```
docker run -d --restart=always --name hiddensite -v $(pwd)/web:/web ozeliurs/tor-hiddenservice-nginx 

```
## Shell

```
docker run -it --rm -v $(pwd)/web:/web --entrypoint /bin/bash ozeliurs/tor-hiddenservice-nginx
```
