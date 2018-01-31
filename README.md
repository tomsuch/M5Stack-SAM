# M5Stack-SAM

Fast and dirty minimalist application menu for M5Stack.


Integrated applications:

	DHT12 - Temperature / Humidity, Stopwatch, I2C scanner
	Bluetooth BLE Beacon Simulator (iBeacon, Eddystone TLM + URL, ALTBeacon)
	QRCODE generator


Settings:
  
	Display backlight


Other:
  
	Sleep mode
	Serial control at 115200 8N1 and NL&CR termination


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

Serial commands:

	Serial control at 115200 8N1 and NL&CR termination

	bright [0-255] - display bright
        	EXAMPLE: bright 128
	clr - clear display
	sleep - power sleep, wakeup on BTN_B
	qrc [text] - show QRCODE with text
		EXAMPLE: qrc www.google.com
	
	Send iBeacone message
	ibeacon [major code 0-65535] [minor code 0-65535] [power 0-255]
		EXAMPLE: ibeacon 1024 2048 50
	
	Send Eddystone TLM message
	eddystonetlm [voltage 0-65535] [temperature 0-65535] [pocket cound 0-4294967295] [second from up 0-4294967295]
		EXAMPLE: eddystonetlm 100 200 300 400

	Send Eddystone URL message
	eddystoneurl [prefix 0-3] [power 0-255] [url]
		EXAMPLE: eddystoneurl 1 1 google.com
		PREFIXES:
			0	http://www.
			1	https://www.
			2	http://
			3	https://		
		

Based on:

	https://github.com/Kongduino/M5_QR_Code
	https://github.com/ricmoo/qrcode
	https://github.com/kroimon/Arduino-SerialCommand
	
	
