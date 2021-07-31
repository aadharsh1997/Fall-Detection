# Fall-Detection
An algorithm capable of detecting a fall based on accelerometric values and giving out alerts on the detection of a fall. 

Working Principal

•	The values of all three axes of the accelerometer are read.

•	The root mean square of these values is calculated to obtain the reading which is used for fall detection. The reading value at rest is found to be 1.73 units.

•	During the time of fall it is found that the reading value goes down to 1.0 units due to free fall condition. This is followed by a sharp increase in the reading value during the time of impact. Thus, a fall is detected as a successive occurrence of these factors.

•	Threshold values are set at 0.8 for the duration of free fall and 2.2 for the time of impact. This eliminates “false-fall” triggers such as wrist movements as well as heavyset movements. The reading values of wrist movements are found to be in the range of 1.43-2.1 units.

•	Once the fall is detected, immediately an SMS is sent to the caretaker indicating that fall has occurred.

•	SMS contains the location (GPS coordinates) would be sent by the GSM and GPS module collectively.

