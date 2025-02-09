#include <SoftwareSerial.h>

/* Initialize constants */

// Standard RFID Format
const int BUFFER_SZ = 14;
// Store extracted data (version + tag)
const int DATA_SZ = 10;
// Store data from tag
const int DATA_TAG_SZ = 8;
// Store version from tag
const int DATA_VERSION_SZ = 2;
// store checksum
const int CHECKSUM_SZ = 2;

// Forward declarations
void processBuffer();

/* Declare pin mapping */
SoftwareSerial ssrfid = SoftwareSerial(6,9);
int pinToParticlePhoton = 2;

// Buffer to store incoming messages
uint8_t buffer[BUFFER_SZ];
int buffer_index = 0;

/* Establish standard serial connection */
void setup() {
 Serial.begin(9600);
 pinMode(pinToParticlePhoton,OUTPUT);
 ssrfid.begin(9600);
 ssrfid.listen();
}

/* Enter read loop */
void loop() {

    if (ssrfid.available() > 0){
      bool call_extract_tag = false;

      // Read data
      int ssvalue = ssrfid.read(); 
      // If no data read by function then return
      if (ssvalue == -1) { 
        return;
      }
      // Tag is found
      if (ssvalue == 2) {
        buffer_index = 0;
        // Tag is transmitted
      } else if (ssvalue == 3) {
        // Extract tag
        call_extract_tag = true;
      }
      buffer[buffer_index++] = ssvalue; 
      if (call_extract_tag == true) {
        if (buffer_index == BUFFER_SZ) {
          unsigned tag = extract_tag();
        } else {
          buffer_index = 0;
          return;
        }
      }
    }

}
unsigned extract_tag() {

    // Declare byte constants
    uint8_t msg_head = buffer[0];
    uint8_t *msg_data = buffer + 1;
    uint8_t *msg_data_version = msg_data;
    uint8_t *msg_data_tag = msg_data + 2;
    uint8_t *msg_checksum = buffer + 11; // 2 byte
    uint8_t msg_tail = buffer[13];

    // Convert tag from hex to long
    long tag = hexstr_to_long(msg_data_tag, DATA_TAG_SZ);

    // Calculate checksum
    long checksum = 0;
    for (int i = 0; i < DATA_SZ; i+= CHECKSUM_SZ) {
      long val = hexstr_to_long(msg_data + i, CHECKSUM_SZ);
      checksum = checksum ^ val;
    }

    // Compare calculated checksum to transmitted checksum
    // Transmit tag with status of checksum match
    if (checksum == hexstr_to_long(msg_checksum, CHECKSUM_SZ)) {
        Serial.print("Extracted Tag (Checksum Match): ");
        Serial.println(tag);
        digitalWrite(pinToParticlePhoton, HIGH);
    } else {
        Serial.print("Extracted Tag (Error Checksum Mis-match): ");
        Serial.println(tag);
        digitalWrite(pinToParticlePhoton, HIGH);
    }
    return tag;
}

// Helper function
// Converts a hexadecimal value to a numeric value
long hexstr_to_long(char *str, unsigned int length) {
  char* copy = malloc((sizeof(char) * length) + 1);
  memcpy(copy, str, sizeof(char) * length);
  //copy null terminated
  copy[length] = '\0';
  // convert to long
  long value = strtol(copy, NULL, 16);
  free(copy); 
  return value;
}