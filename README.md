# Kurento Module to stream raw audio via http

DISCLAIMER: hack!

Kurent Recorder Endpoint can stream audio in mp4/wemb format over
http. This is neat feture but I needed access to the raw samples
without mp4 compression. Audio format being streamed is mono, 16 bits
singed integers at 16kHz using little endian. Or in gstreamer caps
terms: "audio/x-raw,channels=1,rate=16000,format=S16LE"

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
-v /path/to/curlendpoint:/curlendpoint

Then attach to the docker container and build a deb package
```
#cd /curlendpoint
#debuild -b
```
The deb package is to be found at /path/to/curlendpoint_0.0.1~rc1_amd64.deb.
It should be installed on the image based on Kurento Media Server(KMS) docker image.
Also kurento-media-server-6.0-dev may be required ( as it was not tested w/o it) 

Alternatively one can build the module using cmake:
```
#cd /curlendpoint/
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

#Misc
Curlhttpsink expects 100-trying as response to its POST. Unfortunately AWS's ELB swallows them up. Returning 202 from the server resolves this issue. The package also includes G.711 payloader with minimum p-time set to 20ms. By default KMS uses 10ms packets for G.711 ignoring for now SDP's p-time attributes.

