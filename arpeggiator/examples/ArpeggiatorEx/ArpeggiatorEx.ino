#include <arpeggiator.h>

// Set this to the pin you want to output from.
#define ARP_PIN 6

// Create an arpeggiator outputting from ARP_PIN.
Arpeggiator arp(ARP_PIN);

// Import note names and define the arpeggiated chord.
using namespace NoteName;
uint8_t notes[] = {D, E, F, G, E, E, C, D};

// Macro for length of notes array.
#define NOTES_LEN (sizeof(notes) / sizeof(uint8_t))

void setup() {
    // Arpeggiator automatically sets the ARP_PIN to output, so we don't need to do that.
    
    Serial.begin(9600);

    // Setup the arpeggiator with tempo and notes.
    arp.setTempo(120);
    arp.setNotes(notes, NOTES_LEN);
    arp.start();
}

void loop() {
    // Update the arpeggiator.
    // The arpeggiator will check if it's time to change the note.
    // If so, it returns the note it changed to.
    // Otherwise, it returns -1.
    int res = arp.update();

    // Print the new note if there is one.
    if (res != -1) {
        Serial.print("New note: ");
        Serial.println(res);
    }
}