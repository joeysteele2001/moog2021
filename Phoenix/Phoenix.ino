#include <arpeggiator.h>
#include <smoothers.h>
#include <smoother.h>
#include <circularsmoother.h>

#include "pindefs.h"
#include "accelmag.h"
#include "inputs.h"

using namespace PinDefs;

enum PhoenixState {
  PS_DISABLED,
  PS_LO_ONLY,
  PS_HI_ONLY,
  PS_LO_HI,
  PS_STRUM_UP,
  PS_STRUM_DOWN,
  PS_CHORD1,
  PS_CHORD2,
};

constexpr uint8_t SEMITONE = ScaleDegree::min2;
constexpr uint8_t SLIDER_LO_BASE_PITCH = NoteName::C;
constexpr uint8_t SLIDER_HI_BASE_PITCH = NoteName::G;

static AccelMag accmag;
static Smoother<8> accSmoother;
static Arpeggiator arpeg(PIN_VCO);

uint8_t lohiNotes[] = {NoteName::C, NoteName::G};
constexpr int LOHI_NOTES_LEN = sizeof(lohiNotes) / sizeof(uint8_t);
static uint8_t chordNotes[] = {NoteName::C, NoteName::F, NoteName::A, NoteName::C + ScaleDegree::octave};
constexpr int CHORD_NOTES_LEN = sizeof(chordNotes) / sizeof(uint8_t);
static uint8_t chord1Notes[] = {
  NoteName::D + ScaleDegree::octave, 
  NoteName::E + ScaleDegree::octave, 
  NoteName::F + ScaleDegree::octave, 
  NoteName::G + ScaleDegree::octave, 
  NoteName::E + ScaleDegree::octave,
  NoteName::E + ScaleDegree::octave, 
  NoteName::C + ScaleDegree::octave, 
  NoteName::D + ScaleDegree::octave
};
constexpr int CHORD1_NOTES_LEN = sizeof(chord1Notes) / sizeof(uint8_t);
static uint8_t chord2Notes[] = {NoteName::C, NoteName::E, NoteName::G, NoteName::B};
constexpr int CHORD2_NOTES_LEN = sizeof(chord2Notes) / sizeof(uint8_t);

static PhoenixState currentState = PS_DISABLED;

void setup() {
  Serial.begin(9600);
  accmag.begin();
}

void loop() {
  // READ ALL INPUTS
  int8_t magRawReading = accmag.getMagX();
  int8_t accRawReading = accmag.getAccX();

  bool slideTopPressed = slideTopIsPressed();
  bool slideBottomPressed = slideBottomIsPressed();
  float slideTopReading = readSlideTop();
  float slideBottomReading = readSlideBottom();

  SlideVals slideSimultaneous = readSlides();

  float dialReading = readDial();

  bool fsr1Pressed = fsrBodyIsPressed();
  bool fsr2Pressed = fsrNeckIsPressed();

  bool switchOn = readSwitch();

  // PROCESS ACCELEROMETER DATA
  float magNorm = (float) magRawReading / 128;
  float accNorm = (float) accRawReading / 64;
  accSmoother.addData(accNorm);
  float accSmoothed = (accSmoother.average() + 1) * 128;

  // PROCESS SLIDER DATA
  uint8_t slideTopPitch = quantizeTop(slideTopReading);
  uint8_t slideBottomPitch = quantizeBot(slideBottomReading);

  uint8_t slideTopSimultPitch = quantizeTop(slideSimultaneous.top);
  uint8_t slideBottomSimultPitch = quantizeBot(slideSimultaneous.bottom);

  // ACT ON SLIDER PRESSED DATA
  if (slideTopPressed && slideBottomPressed) {
    if (currentState != PS_LO_HI) {
      currentState = PS_LO_HI;
      arpeg.setForward();
      arpeg.setNotes(lohiNotes, LOHI_NOTES_LEN);
      arpeg.start();
    }
  } else {
    // STOP THE ARPEGGIATOR!
    if (currentState == PS_LO_HI) {
      arpeg.stop();
    }
    
    if (slideTopPressed) {
      currentState = PS_HI_ONLY;
      // TODO
    } else if (slideBottomPressed) {
      currentState = PS_LO_ONLY;
      // TODO
    } else {
      // TODO
    }
  }

  // ACT ON MAGNETOMETER DATA
  if (magNorm > 0.95) {
    delay(120);
    currentState = PS_STRUM_DOWN;
    arpeg.setForward();
    arpeg.setNotes(chordNotes, CHORD_NOTES_LEN);
    arpeg.start();
  } else if (magNorm < -0.95) {
    delay(120);
    currentState = PS_STRUM_UP;
    arpeg.setReverse();
    arpeg.setNotes(chordNotes, CHORD_NOTES_LEN);
    arpeg.start();
  }

  // ACT ON FSR DATA
  if (fsr2Pressed) {
    if (currentState != PS_CHORD2) {
      currentState = PS_CHORD2;
      arpeg.setForward();
      arpeg.setNotes(chord2Notes, CHORD2_NOTES_LEN);
      arpeg.start(); 
    }
  } else if (fsr1Pressed) {
    if (currentState != PS_CHORD1) {
      currentState = PS_CHORD1;
      arpeg.setForward();
      arpeg.setNotes(chord1Notes, CHORD1_NOTES_LEN);
      arpeg.start(); 
    }
  }

  // PROCESS DIAL DATA
  float bpm = dialReading * 800 + 60;
  arpeg.setTempo(bpm);

  // DEFINE OUTPUTS
  int vcfOut = accSmoothed;
  int vcoOut = 0;

  switch (currentState) {
    case PS_LO_ONLY:
      vcoOut = slideBottomPitch;
      analogWrite(PIN_VCO, vcoOut);
      break;
    case PS_HI_ONLY:
      vcoOut = slideTopPitch;
      analogWrite(PIN_VCO, vcoOut);
      break;
    case PS_LO_HI:
      // DON'T write to PIN_VCO!
      lohiNotes[0] = slideBottomSimultPitch;
      lohiNotes[1] = slideTopSimultPitch;
      arpeg.setNotes(lohiNotes, LOHI_NOTES_LEN);
      break;
    default:
      break;
    // TODO other cases
  }

  // WRITE OUTPUTS
  analogWrite(PIN_VCF, vcfOut);
  digitalWrite(PIN_VCA, switchOn);

  // UPDATE ARPEGGIATOR
  // does nothing if the arpeggiator is inactive
  arpeg.update();

  //// DEBUG ONLY ////
  delay(20);
  //// END DEBUG  ////
}

// Quantize data between 0 and 1 to an Am7 chord
uint8_t quantizeTop(float data) {
  using namespace NoteName;
  using namespace ScaleDegree;
  constexpr uint8_t notes[] = {A, C + octave, E + octave, G + octave};
  constexpr int notesLen = sizeof(notes) / sizeof(uint8_t);
  
  int pitchInd = floor(data * notesLen);

  if (pitchInd >= notesLen) {
    pitchInd = notesLen;
  }
  return notes[pitchInd];
}

uint8_t quantizeBot(float data) {
  using namespace NoteName;
  using namespace ScaleDegree;
  constexpr uint8_t notes[] = {E, G, A, C + octave};
  constexpr int notesLen = sizeof(notes) / sizeof(uint8_t);
  
  int pitchInd = floor(data * notesLen);

  if (pitchInd >= notesLen) {
    pitchInd = notesLen;
  }
  return notes[pitchInd] + octave; 
}
