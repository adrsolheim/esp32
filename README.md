# WiFi

The wifi setup require that `include/secrets.h` exists with the following wifi credentials:
```
#pragma once

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
```

# Display image
```
curl -X POST http://<ip-addr>:80/image -F "file=@media/display.jpeg
```

Generate example image 
```
magick -size 128x160 xc:black \
  -font DejaVu-Sans-Bold \
  -pointsize 14 \
  -fill white \
  -gravity center \
  -annotate 0 "Juicy Pale Ale\n\nPåkoblet" \
  -alpha off \
  -colorspace sRGB \
  -interlace none \
  -sampling-factor 4:4:4 \
  -define jpeg:colorspace=2 \
  media/display.jpeg
```
