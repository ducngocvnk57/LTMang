# LTMang
china chess via socket on ubuntu


#Install 
1. install gtk+2
```
sudo apt-get install build-essential libgtk2.0-dev
```
2. Build client:
```
gcc `pkg-config --cflags gtk+-2.0` -o bin/client client.c `pkg-config --libs gtk+-2.0`
```
