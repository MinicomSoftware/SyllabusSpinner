/*
 Name:		Syllabus Spinner (MSJC 2017)
 Created:	8/1/2017 4:56:11 PM
 Author:	Minicom Software || Programmed by Steven Wilson (@SCMowns)
 Description: Source file for the 'Syllabus Spinner' game. The code below can be used for educational purposes and has been documented for your
 pleasure. Contact Steven if there are any concerns, and please fork this project if changes should be made. Please do not expect perfect code as I am a
 student who's learning more. Thank you.

 ############### Useful References that I used: ################
 https://www.arduino.cc/en/Reference/HomePage
 https://www.arduino.cc/en/tutorial/potentiometer

 Plugin used: https://marketplace.visualstudio.com/items?itemName=VisualMicro.ArduinoIDEforVisualStudio

*/

/*
Global variables for accessing throughout Arduino program (Not ideal for usage outside Arduino projects**)
*/

//array of PINS used for LED lights (Winning light = PIN 30, or defined below as variable winnerLight) 

int ledLights[16] = { 52, 53, 10, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 3, 35, 44 };


int potentiometerPin = 6;		//Pin that contains potentiometer for analog reading which adjuests the speed of the game
int currentLEDvalue;			//integer that contains a value that reflects the array of pins above (ledLights).
int winnerLight = 30;			//Winning LED on board
int delaySpeed; 				//stores the speed the potentiometer reads using analogRead


void setup() {

	/*
	Assignment of the ledLights
	*/

	pinMode(ledLights[0], OUTPUT);
	pinMode(ledLights[1], OUTPUT);
	pinMode(ledLights[2], OUTPUT);
	pinMode(ledLights[3], OUTPUT);
	pinMode(ledLights[4], OUTPUT);
	pinMode(ledLights[5], OUTPUT);
	pinMode(ledLights[6], OUTPUT);
	pinMode(ledLights[7], OUTPUT);
	pinMode(ledLights[8], OUTPUT);
	pinMode(ledLights[9], OUTPUT);
	pinMode(ledLights[10], OUTPUT);
	pinMode(ledLights[11], OUTPUT);
	pinMode(ledLights[12], OUTPUT);
	pinMode(ledLights[13], OUTPUT);
	pinMode(ledLights[14], OUTPUT);
	pinMode(ledLights[15], OUTPUT);

	/*
	Begin loading game beyond this point after data above is registered.
	*/

	Serial.begin(9600);		//begin Arduino connection and usage after data is loaded above
	TurnOnAllLights();		//Extra call that makes the board appear beautifully before game starts.
	//LEDdebugger();		//Ideal location for debugging the LED lights
	
	PrepareGameSettings();	//Real game begins here with the call of the settings
}


/*#######				#######
  #######	METHODS		#######
  #######				#######
  */


/*
Method: LEDdebugger
Description: Checks all lights and blinks each as it cycles through the 'totalLED' count (fixed number). Since there is 16
LED's I used 16 as a constant number. The debugger will cycle through each LED pin and display it's activation by printing
'ledLights[i]' (i = which count it is on) and turning on the LED on the board. After ten seconds the LED will light off and 
the debugger has successfully shown that the LED works or not.

*/
void LEDdebugger() {
	int totalLED = 16;
	int count = 0;
	for (int i = 0; i < totalLED; i++) {
		Serial.print("ledLights[");
		Serial.print(count);
		Serial.println("]");
		count++;
		digitalWrite(ledLights[i], HIGH);
		delay(10000);
		digitalWrite(ledLights[i], LOW);
	}
	Serial.println("Finish");

}



/*
Method: PrepareGameSettings
Description: This method prepares the game by indicating with an LED that the power is on (the LED is green on the board), 
and when it lights up the game can begin. While the player gets situated, the progam will shuffle through a random procedure
and start the player on a random light. Every game begins on a random LED. The operator can use the potentiometer to also adjust
the speed of the game. The green LED that indicates the power will also fade or brighten up based on the game's speed. Lower light
equals faster speed while higher light means slower. The speed is adjust based on the potentiometer's value which gives this 
program a new delay speed. So if the potentiometer reads 1000 that means the delay speed is one second.

*/
void PrepareGameSettings() {
	Serial.println("Launching game settings...");
	/*
	#####							#####
	#####	Gather Game Settings	#####
	#####	& POWER ON INDICATOR	#####
	*/

	int currentlyOnStatus = 8;			//currentlyOnStatus = status of the power whether on or off

	while (analogRead(A0) <= 975 || analogRead(A0) <= 975.0) {

		delaySpeed = analogRead(potentiometerPin);			//gather value for updating LED

		/*
		Blue light adjustment on the back of the unit to show speed based on the brightness of the BLUE LED
		*/

		if (delaySpeed > 240) {
			analogWrite(currentlyOnStatus, 250);
		}
		else {
			analogWrite(currentlyOnStatus, delaySpeed);
		}

		currentLEDvalue = random(0, 13);					//creating random number between 0 and 13 (13 total variables) for random start

	}

	delaySpeed = analogRead(potentiometerPin);				//record final value from the potentiometer

}




/*
	.:	LIGHT MODIFICATION METHODS	:.
	Descriptions: 

	LightLED: Method for recieving the current LED that is being cycled and turnng it on. Recieves the current led and sets it
	as 'ledToLight'. Returns NOTHING.

	TurnOffLED: Method that does the opposite of 'LightLED', it simply turns off the given LED paseed through the argument. Returns: NOTHING

	TurnOnAllLights: Method for turning every light on the board on.

	TurnOffAllLights; Method for turning every light on the board off.

	BlinkLight: Method for blinking the LED sent through the argument. Returns: NOTHING

	WinningSegmentOne: method that plays the ending light finale. It calls on TurnOnAllLights and flashes the board. It then calls on TurnOffAllLights
	to turn off all the light. 

	WinningSegmentTwo: Last segment that plays the ending light finale. It cycles through each light and turns them on until it reaches the end. It then 
	turns off all the lights and repeats itself but in a different direction.
	
*/
void LightLED(int ledToLight) {
	digitalWrite(ledLights[ledToLight], HIGH);
}

void TurnOffLED(int ledToOff) {
	digitalWrite(ledLights[ledToOff], LOW);
}

void TurnOnAllLights() {
	for (int i = 0; i <= sizeof(ledLights) / 2; i++) {
		digitalWrite(ledLights[i], HIGH);
	}
}

void TurnOffAllLights() {
	for (int i = 0; i <= sizeof(ledLights) / 2; i++) {
		digitalWrite(ledLights[i], LOW);
	}
}

void BlinkLight() {
	digitalWrite(ledLights[currentLEDvalue], HIGH);
	delay(500);
	digitalWrite(ledLights[currentLEDvalue], LOW);
	delay(500);
}

void WinningSegmentOne() {
	for (int i = 1; i != 2; i++) {
	TurnOnAllLights();
	delay(500);
	TurnOffAllLights();
	delay(500);
	}
}

void WinningSegmentTwo() {
	for (int i = 0; i < sizeof(ledLights) / 2; i++) {
		digitalWrite(ledLights[i], HIGH);
		delay(250);
	}
	for (int i = sizeof(ledLights) / 2; i != -1; i--) {
		digitalWrite(ledLights[i], LOW);
		delay(250);
	}
	for (int i = sizeof(ledLights) / 2; i != -1; i--) {
		digitalWrite(ledLights[i], HIGH);
		delay(250);
	}
	for (int i = 0; i < sizeof(ledLights) / 2; i++) {
		digitalWrite(ledLights[i], LOW);
		delay(250);
	}
}






/*
	 Method: LoadGameResults
	 Description: Gather game results from the user who activated a button and checks the light that was landed on. If the winnerLight is true
	 the user has won. If not the game blinks the losing light and then returns to PrepareGameSettings. This method always returns to PrepareGameSettings
	 to call on a random start for the next user. 
*/

void LoadGameResults() {
	Serial.println("Load game results...");

	if (ledLights[currentLEDvalue] == winnerLight) {
		digitalWrite(ledLights[currentLEDvalue], HIGH);		
		delay(500);
		WinningSegmentOne();
		WinningSegmentTwo();
		for (int i = 0; i <= 3; i++) {
			BlinkLight();				//Blink the light twice before ending winner results.
		}

		}
	else {
		for (int i = 0; i <= 3; i++) {
			BlinkLight();				//Blink the lost to indicate result.
		}
	}
}





/*
Method: loop (default arduino infinite loop method)
Description: The game begins here once sent from method 'PrepareGameSettings'. The game cycles through each LED with the value 'currentLEDvalue'.
currentLEDvalue is a random number created in method 'PrepareGameSettings'. currentLEDvalue enters a switch that turns on each light and then exits 
to enter a delay that is read from our potentiometerPin. The potentiometer can still adjust the speed during the game for LIVE edits. Once the delay ends
the currentLEDvalue is turned off, and then checked to ensure that all values are within the array's lengh. If the user pressed the button, the game enters
the 'LoadGameResults' method to check which LED was landed on.
*/
void loop() {
	/*
	#####				#####
	#####	Begin Game	#####
	#####				#####
	*/
	Serial.println("Starting game...");
	delay(200);					//delay for button to enter next function as 'OFF' because it can still record as being pressed
	while (analogRead(A0) <= 975 || analogRead(A0) <= 975.0) {
		
		/*
		SWITCH STATEMENT to shuffle through LEDs based off the speed of the potentiometer's delaySpeed reading.
		Variables shuffled through at random is provided by: currentLEDvalue
		*/

		switch (currentLEDvalue) {
		case 0:
			LightLED(currentLEDvalue);
			break;
		case 1:
			LightLED(currentLEDvalue);
			break;
		case 2:
			LightLED(currentLEDvalue);
			break;
		case 3:
			LightLED(currentLEDvalue);
			break;
		case 4:
			LightLED(currentLEDvalue);
			break;
		case 5:
			LightLED(currentLEDvalue);
			break;
		case 6:
			LightLED(currentLEDvalue);
			break;
		case 7:
			LightLED(currentLEDvalue);
			break;
		case 8:
			LightLED(currentLEDvalue);
			break;
		case 9:
			LightLED(currentLEDvalue);
			break;
		case 10:
			LightLED(currentLEDvalue);
			break;
		case 11:
			LightLED(currentLEDvalue);
			break;
		default:
			LightLED(currentLEDvalue);
			break;

		}

		delay(delaySpeed);
		TurnOffLED(currentLEDvalue);						//Turn off current LED before looping 
		currentLEDvalue++;									//Move forward to the next LED

		if (currentLEDvalue == sizeof(ledLights)/2) {						//Boundary to check if currentLEDvalue is going beyond the array's range
			currentLEDvalue = 0;
		}

		delaySpeed = analogRead(potentiometerPin);			//enabled for LIVE-ADJUSTMENTS during the game.					 
	}

	/*	
		#### End of game & results ####

	*/
	Serial.println("Ending game...");
	delay(200);					//delay for button to enter next function as 'OFF'
	LoadGameResults();			//gather results once button is pressed
	PrepareGameSettings();		//restart game
}