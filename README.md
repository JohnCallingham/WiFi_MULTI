# WiFi_MULTI

The file WiFi_Multi.h contains two classes WiFi_Multi and WiFi_Multi_Error.

The function WiFi_Multi::findMatchingSSID() searches for an SSID which matches one of the SSIDs in a configuration file. It returns a WiFi_Multi_Error object which will indicate success or failure.

This allows programs to work with differing WiFi Access Points without having to recompile.

This library has been developed using PlatformIO.
