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
}

void loop() {
    // Manually advance the arpeggiator to the next note.
    uint8_t newNote = arp.advance();

    // Print the new note value.
    Serial.println(newNote);

    // Delay some random amount of time.
    int randomMs = random(500, 2000);
    delay(randomMs);
}