/*
 * Functions and commands to use digital outputs
 */

//
// Output01
//
#ifdef OUTPUT01_PIN
  HomieNode output01Node("output01", "switch");

  // output01_on
  void publichOutput01on() {
    if ( !HOMIE_STANDALONE ) {
      output01Node.setProperty("on").send(output01_on ? "true" : "false");
    };
  }

  void updateOutput01on(String value, bool write = true) {
    output01_on = (value == "true" || value == String(true));
    if ( DEBUGLEVEL >= 1 ) {
      Homie.getLogger() << "[DEBUG1] UPDATE: value: " << value << endl;
      Homie.getLogger() << "[DEBUG1] UPDATE: output01_on: " << output01_on << endl;
    }
    // set output; consider output01_invert
    digitalWrite(OUTPUT01_PIN, (output01_on == !output01_invert) ? HIGH : LOW);
    publichOutput01on();
    if (write) writeEeepromOutput01on();
  }

  bool output01OnHandler(const HomieRange& range, const String& value) {
    if (value != "true" && value != "false") return false;
    updateOutput01on(value);
    return true;
  }

  // output01_invert
  void publichOutput01invert() {
    if ( !HOMIE_STANDALONE ) {
      output01Node.setProperty("invert").send(output01_invert ? "true" : "false");
    };
  }

  void updateOutput01invert(String value, bool write = true) {
    output01_invert = (value == "true" || value == String(true));
    if ( DEBUGLEVEL >= 1 ) {
      Homie.getLogger() << "[DEBUG1] UPDATE: value: " << value << endl;
      Homie.getLogger() << "[DEBUG1] UPDATE: output01_invert: " << output01_invert << endl;
    }
    publichOutput01invert();
    if (write) writeEeepromOutput01invert();
  }

  bool output01invertHandler(const HomieRange& range, const String& value) {
    if (value != "true" && value != "false") return false;
    updateOutput01invert(value);
    return true;
  }

  // Setup
  void HomieSetupOutput01() {
    pinMode(OUTPUT01_PIN, OUTPUT);
    digitalWrite(OUTPUT01_PIN, HIGH);
    output01Node.advertise("on").settable(output01OnHandler);
    output01Node.advertise("invert").settable(output01invertHandler);

    readEepromOutput01on();
    readEepromOutput01invert();
  }
#endif