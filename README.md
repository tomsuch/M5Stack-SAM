# M5Stack-SAM

Fast and dirty minimalist application menu for M5Stack.


Integrated applications:

	DHT12 - Temperature / Humidity, Stopwatch, I2C scanner
	Bluetooth BLE Beacon Simulator (iBeacon, Eddystone TLM + URL, ALTBeacon)


Settings:
  
	Display backlight


Other:
  
	Sleep mode


I be glad when you share the further development, I will continuously add other applications and options.

QRCode showing:

	QRPrint("www.google.com");

SimpleBeacon:

	ble.iBeacon(10,20,50); // ble.iBeacon(MajorCode,MinorCode,Power);
	ble.EddystoneTLM(2048,512,100,1024); // ble.EddystoneTLM(Voltage,Temperature,packetCount,timeSECfromPowerUp);
	ble.EddystoneURIPlain(1,"brmlab.cz",1); // ble.EddystoneURIPlain(prefix,"url.url",Power);
		prefix:
			0	http://www.
			1	https://www.
			2	http://
			3	https://
	ble.AltBeacon();


Based on:

	https://github.com/Kongduino/M5_QR_Code
	https://github.com/ricmoo/qrcode
	
