



void lightsComplete();


// NeoPattern Class - derived from the Adafruit_NeoPixel class
class NeoPatterns : public Adafruit_NeoPixel
{                                
  uint32_t bottle1MissingColor = Color(20,20,20);
  uint32_t bottle1ClosedColor = Color(27,48,51);
  uint32_t bottle1OpenColor1 = Color(57,48,51);
  uint32_t bottle1OpenColor2 = Color(0,0,0);
  
  uint32_t bottle2MissingColor = Color(20,20,20);
  uint32_t bottle2ClosedColor = Color(56,48,51);
  uint32_t bottle2OpenColor1 = Color(56,78,51);
  uint32_t bottle2OpenColor2 = Color(0,0,0);
  
  uint32_t bottle3MissingColor = Color(20,20,20);
  uint32_t bottle3ClosedColor = Color(56,56,31);
  uint32_t bottle3OpenColor1 = Color(56,56,61);
  uint32_t bottle3OpenColor2 = Color(0,0,0);

  uint32_t bottleColors[3][4] = { {bottle1MissingColor, bottle1ClosedColor, bottle1OpenColor1, bottle1OpenColor2},
                                {bottle2MissingColor, bottle2ClosedColor, bottle2OpenColor1, bottle2OpenColor2},
                                {bottle3MissingColor, bottle3ClosedColor, bottle3OpenColor1, bottle3OpenColor2}};

  const int FLICKER_STEPS_MIN = 75;
  const int FLICKER_STEPS_MAX = 400;
  
  const int BOTTLE_OFF = 0;
  const int BOTTLE_ON_CLOSED = 1;
  const int BOTTLE_ON_OPEN = 2;
  
  int bottleState[3];

  bool areAllBottlesOff() {
    return (bottleState[0] == BOTTLE_OFF 
        && bottleState[1] == BOTTLE_OFF
        && bottleState[2] == BOTTLE_OFF);
  }

  public:

    // Member Variables:
    unsigned long Interval;   // milliseconds between updates
    unsigned long lastUpdate; // last update of position

    uint32_t Color1[3], Color2[3], ColorCurrent[3];  // What colors are in use

    uint16_t stepsDefault;
    uint16_t TotalSteps[3];  // total number of steps in the patterns
    uint16_t Index[3] = { 0, 0, 0};  // current step within each pattern
    int splitPos[4]; //index for splitting strip to 3

    // Constructor - calls base-class constructor to initialize strip
    NeoPatterns(uint16_t pixels, uint8_t pin, uint8_t type, uint16_t steps, uint8_t interval)
      : Adafruit_NeoPixel(pixels, pin, type)
    {
      splitPos[0] = 0;
      splitPos[1] = floor(numPixels()*0.33);
      splitPos[2] = numPixels()-splitPos[1];
      splitPos[3] = numPixels();

      for (int i=0; i<3; i++) {
        Color1[i] = Color(0,0,0);
        Color2[i] = bottleColors[i][0];
      }

      Interval = interval;
      
      stepsDefault = steps;
      for (int i=0; i<3; i++) {
        TotalSteps[i] = steps;
        Index[i] = 0;
      }
    }

    void setBottleStates(bool isBottleOn[], bool isCapOn[]) {
        for (int i=0; i<3; i++) {
          int oldState = bottleState[i];
          int newState = ((isBottleOn[i])?((isCapOn[i])?BOTTLE_ON_CLOSED:BOTTLE_ON_OPEN):BOTTLE_OFF);

          if (newState != oldState) {
            bottleState[i] = newState; 
            Color1[i] = ColorCurrent[i];
            Color2[i] = bottleColors[i][newState];
            Index[i] = 0;
          }
          
        }        
    }
    
    // Update the pattern
    void Update()
    {
      if ((millis() - lastUpdate) > Interval) // time to update
      {
        lastUpdate = millis();

        // Calculate linear interpolation between Color1 and Color2
        // Optimise order of operations to minimize truncation error

        for (int i = 0; i<3; i++) {
          uint8_t red = ((Red(Color1[i]) * (TotalSteps[i] - Index[i])) + (Red(Color2[i]) * Index[i])) / TotalSteps[i];
          uint8_t green = ((Green(Color1[i]) * (TotalSteps[i] - Index[i])) + (Green(Color2[i]) * Index[i])) / TotalSteps[i];
          uint8_t blue = ((Blue(Color1[i]) * (TotalSteps[i] - Index[i])) + (Blue(Color2[i]) * Index[i])) / TotalSteps[i];

          ColorCurrent[i] =  Color(green, red, blue);
          
          ColorSet(splitPos[i], splitPos[i+1],ColorCurrent[i]);        
        }
        show();
        Increment();
      }
    }

    // Increment the Index and reset at the end
    void Increment()
    {
      for (int i = 0; i<3; i++) {
        Index[i]++;
        if (Index[i] >= TotalSteps[i])
        {
          Index[i] = 0;
          OnComplete(i); // call the comlpetion callback
        }      
      }
    }

    // Set all pixels to a color (synchronously)
    void ColorSet(int fromPixel, int toPixel, uint32_t color)
    {
      for (int i = fromPixel; i < toPixel; i++)
      {
        setPixelColor(i,color);
      }
      //show(); //<-- disabled, no need to show here, we do it after running all 3
    }

    // Returns the Red component of a 32-bit color
    uint8_t Green(uint32_t color)
    {
      return (color >> 16) & 0xFF;
    }

    // Returns the Green component of a 32-bit color
    uint8_t Red(uint32_t color)
    {
      return (color >> 8) & 0xFF;
    }

    // Returns the Blue component of a 32-bit color
    uint8_t Blue(uint32_t color)
    {
      return color & 0xFF;
    }
    
    // Completion Callback
    void OnComplete(int i)
    {
      if (bottleState[i]==BOTTLE_ON_OPEN) {
        TotalSteps[i] = random(FLICKER_STEPS_MIN, FLICKER_STEPS_MAX+1);

        if (Color2[i] == bottleColors[i][BOTTLE_ON_OPEN]) {
          Color2[i] = bottleColors[i][BOTTLE_ON_OPEN+1];
          Color1[i] = bottleColors[i][BOTTLE_ON_OPEN];
          Index[i] = 0;
        } else {
          Color1[i] = bottleColors[i][BOTTLE_ON_OPEN+1];
          Color2[i] = bottleColors[i][BOTTLE_ON_OPEN];
          Index[i] = 0;          
        }
      } else {
        TotalSteps[i] = stepsDefault; //just int case -- revert back from flickering
        //keep color constant
        Color1[i]=Color2[i];
      }
    }
};

NeoPatterns lights(36/*108*/, NeoPixelPin, NEO_RGBW + NEO_KHZ800, 75, 2);


