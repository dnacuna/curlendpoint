# Kurento Module to stream raw audio via http

DISCLAIMER: hack!

Kurent Recorder Endpoint can stream audio in mp4/wemb format over
http. This is neat feture but I needed access to the raw samples
without mp4 compression.

Little experiment with modification of kmsdummysink resulted in poor
audio quality with alot of drop outs and glitches. It has been put
on hold and this module based on Kurent Recorder endpoint instead.

# Building

You will need a kurento media server docker with following packages
installed:
* kurento-media-server-6.0-dev
* maven
* openjdk-7-jdk
* devscripts

Run the docker with this folder mapped as a volume
-v /path/to/curl-endpoint:/curl-endpoint

Then attach to the docker container and build a deb package
```
#cd /curl-endpoint
#debuild -b
```
The deb package is to be found at /path/to/curl-endpoint/curlendpoint_0.0.1~rc1_amd64.deb.
It shoudl be installed on the image based on Kurento Media Server docker image.

Alternatively one can build the module using cmake:
```
#cd /curl-endpoint/curlendpoint/
#make build
#cd build
#cmake ..
#make
#cmake .. -DGENERATE_JAVA_CLIENT_PROJECT=TRUE
#cd java
#mvn clean install
#mvn deploy
```
More details on how to generate java bindings can be found [here](http://doc-kurento.readthedocs.io/en/stable/mastering/develop_kurento_modules.html)


