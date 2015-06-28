// PWM pins for red, green, blue leds respectively
int pins[] = {9, 10, 11};

// calibrate RGB leds by multiplying each channel by a value
// modify these so that the RGB leds start out white
double calibration[] = {1.00, 0.52, 0.33};

// minimum values for each channel to prevent extreme flicker from dithering
double minvals[] = {6.0, 3.0, 2.0};

// initial rgb values
double rgb[] = {255, 255, 255};

// temporary variables
double val;
char inChar;
String input = "";

void setup()  {
  Serial.begin(115200);

  // more than enough (tm)
  input.reserve(256);
}

void loop()  {
  for (int i = 0; i < 3; i++) {
    // calibrate and scale 0..255 to minvals[i]..255
    val = (rgb[i] * calibration[i] + minvals[i]) / (255 + minvals[i]) * 255;

    // perform dither
    val += (double) random() / 0x7FFFFFFF;
    analogWrite(pins[i], max(minvals[i], min(floor(val), 255)));
  }
}

void serialEvent() {
  while (Serial.available()) {
    inChar = (char) Serial.read();
    input += inChar;

    // read entire line?
    if (inChar == '\n') {
      // input looks like "R255.00G255.00B255.00\n"
      rgb[0] = input.substring(input.indexOf("R") + 1, input.indexOf("G")).toFloat();
      rgb[1] = input.substring(input.indexOf("G") + 1, input.indexOf("B")).toFloat();
      rgb[2] = input.substring(input.indexOf("B") + 1, input.indexOf("\n")).toFloat();

      input.remove(0);
    }
  }
}
