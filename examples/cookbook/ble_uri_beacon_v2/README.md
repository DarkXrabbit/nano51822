# LilyPad-nano51822 for UriBeacon

![Smaller icon](http://www.embeda.com.tw/tw/wp-content/uploads/2014/10/LilyPad-4-NANO51822-01s.jpg "LilyPad-nano51822")

**This document provides instructions for over-the-air device firmware update (DFU) of the LilyPad-nano51822 to UriBeacon firmware and how to change the UriBeacon mode.**


## Getting Started
1. Purchase the [LilyPad-nano51822 on AMAZON](http://www.amazon.com/uCXpresso-LilyPad-nano51822-Arduino-iBeacon/dp/B00RE6CL4G/ref=sr_1_1?s=pc&ie=UTF8&qid=1423904848&sr=1-1) (P/N: LilyPad-nano51822-AA 16KB)
2. Install one of the Nordic Android apps that support DFU: [nRF Master Control Panel (BLE)](https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp) or [nRF Toolbox for BLE](https://play.google.com/store/apps/details?id=no.nordicsemi.android.nrftoolbox)
3. Copy the [ble_uri_beacon_v2](https://www.dropbox.com/s/cfwc8g5m12wrj7u/ble_uri_beacon_v2.hex?dl=0) to your phone using  [Google Drive](https://play.google.com/store/apps/details?id=com.google.android.apps.docs) for Android or another method.

## Flashing UriBeacon
1. Put the hardware in DFU (Device Firmware Update) mode by pressing DFU-Button over 5 seconds. Hint: use a tool for pressing the small buttons, like a pen tip.
2. Use nRF Master (or nRF Toolbox) to upload the firmware file.
![LilyPad-nano51822 DFU-Button](http://www.embeda.com.tw/ucxpresso/wp-content/uploads/2015/02/LilyPad-4-NANO51822-01ss.png "LilyPad-nano51822 Button")

Steps for nRF Master:

1. Connect to tag with the name nanoDFU
2. Click on DFU tab in upper right hand corner
3. Select Application
4. Click on DFU
6. Click on select file and select Application
7. Select hex file from downloads on phone or from Google Drive
8. Click on Select Device
9. Select tag with the name nanoDFU
10. Click on Upload

## UriBeacon Configuration

After loading the firmware file, the tag will be in a normal mode and will not transmit advertisement packets until it is configured.

1. Press DFU-button about 1 seconds on the tag to enter `CONFIG MODE.`, the LED1 will fast blink when in 'CONFIG MODE.'.
2. Using the [Blesh Physical Web](https://play.google.com/store/apps/details?id=com.blesh.physicalweb) or [UriBeacon Developer Tools](https://github.com/google/uribeacon/releases) Android App, input the desired Uri.

##LilyPad-nano51822 UriBeacon Source code

Source code and project setup instructions can be found in the folder ble_uri_beacon_v2.

##About the uCXpresso.NRF RTOS C/C++ Framework:
The nano51822 are working on the uCXpresso.NRF framework, you may need to study the [Getting Started](http://www.embeda.com.tw/ucxpresso/?article=getting-started-2) first.
