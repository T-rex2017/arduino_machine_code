// home btn vars
int home_btn = 2; // 2
bool home_btn_pressing = false;
int home_btn_pressed = false;
unsigned long home_btn_millis = 0;
unsigned long home_btn_delay = 500;

// feedback btn vars
int feedback_btn = 4; // 2
bool feedback_btn_pressing = false;
bool stage_one_feedback_btn_pressed = false;
bool stage_two_feedback_btn_pressed = false;
unsigned long feedback_btn_millis = 0;
unsigned long feedback_btn_delay = 500;

// homing vars
bool mech_homing = false;
bool mech_homed = false;
unsigned long homing_millis = 0;
unsigned long homing_delay = 5000;

// start btn vars
int start_btn = 3; // 3
bool start_btn_pressing = false;
int start_btn_pressed = false;
unsigned long start_btn_millis = 0;
unsigned long start_btn_delay = 500;

// stage one vars
bool move_one_send = false;
bool move_one_over = false;
bool trigger_one_send = false;
bool trigger_one_over = false;
bool stage_one_over = false;
unsigned long move_one_millis = 0;
unsigned long move_one_delay = 3000;
unsigned long trigger_one_millis = 0;
unsigned long trigger_one_delay = 700;


// stage two vars
bool move_two_send = false;
bool move_two_over = false;
bool trigger_two_send = false;
bool trigger_two_over = false;
bool stage_two_over = false;
unsigned long move_two_millis = 0;
unsigned long move_two_delay = 3000;
unsigned long trigger_two_millis = 0;
unsigned long trigger_two_delay = 700;

// common vars
unsigned long currentMillis = 0;
bool debug = true;
bool debug_delay = false;
int trigger = 10; // 10

void setup() {
  Serial.begin(115200);
  pinMode(home_btn, INPUT_PULLUP);
  pinMode(start_btn, INPUT_PULLUP);
  pinMode(feedback_btn, INPUT_PULLUP);

  //pinMode(the_led, OUTPUT);
  pinMode(trigger, OUTPUT);

  //digitalWrite(the_led, LOW);
  digitalWrite(trigger, LOW);
}

void loop() {
  currentMillis = millis();

  // home button rutine

  if (digitalRead(home_btn) == 0 && home_btn_pressing == false && home_btn_pressed == false) {
    home_btn_pressing = true;
    if (debug == true) {
      Serial.println("home btn pressing ...");
    }
    home_btn_millis = currentMillis;
  }
  if (currentMillis - home_btn_millis >= home_btn_delay && home_btn_pressing == true) {
    if (home_btn_pressed == false) {
      home_btn_pressed = true;
      home_btn_pressing = false;
      if (debug == true) {
        Serial.println("home btn press final...");
      }
    }
  }
  if (home_btn_pressing == true) {
    if (debug == true && debug_delay == true) {
      Serial.println(currentMillis - home_btn_millis);
    }
  }
  if (digitalRead(home_btn) == 1 && home_btn_pressing == true && home_btn_pressed == false) {
    home_btn_pressing = false;
    if (debug == true) {
      Serial.println("home btn not pressing ...");
    }
  }

  // homing rutine

  if (home_btn_pressed == true && mech_homing == false && mech_homed == false) {
    homing_millis = currentMillis;
    mech_homing = true;
    if (debug == true) {
      Serial.println("machine homing ....");
    }
    // homing cmd
    Serial.println("$H");
  }
  if (mech_homing == true && mech_homed == false) {
    if (debug == true && debug_delay == true) {
      Serial.println(currentMillis - homing_millis);
    }
  }
  if (mech_homing == true && currentMillis - homing_millis >= homing_delay) {
    if (mech_homed == false) {
      mech_homed = true;
      mech_homing = false;
      if (debug == true) {
        Serial.println("machine homed ....");
      }
    }
  }

  // start button rutine

  if (digitalRead(start_btn) == 0 && start_btn_pressing == false && start_btn_pressed == false && mech_homed == true) {
    start_btn_pressing = true;
    if (debug == true) {
      Serial.println("start btn pressing ...");
    }
    start_btn_millis = currentMillis;
  }
  if (currentMillis - start_btn_millis >= start_btn_delay && start_btn_pressing == true) {
    if (start_btn_pressed == false) {
      start_btn_pressed = true;
      start_btn_pressing = false;
      if (debug == true) {
        Serial.println("start btn press final...");
      }
    }
  }
  if (start_btn_pressing == true) {
    if (debug == true && debug_delay == true) {
      Serial.println(currentMillis - start_btn_millis);
    }
  }
  if (digitalRead(start_btn) == 1 && start_btn_pressing == true && start_btn_pressed == false) {
    start_btn_pressing = false;
    if (debug == true) {
      Serial.println("start btn not pressing ...");
    }
  }
  // stage one rutine

  if (start_btn_pressed == true && move_one_send == false) {
    move_one_send = true;
    move_one_millis = currentMillis;
    if (debug == true) {
      Serial.println("move one send....");
    }
    //send move one cmd
    Serial.println("G91 X-6.5");
  }
  if (move_one_send == true && move_one_over == false) {
    if (debug == true && debug_delay == true) {
      Serial.println(currentMillis - move_one_millis);
    }
  }
  if (move_one_send == true && currentMillis - move_one_millis >= move_one_delay) {
    if (move_one_over == false) {
      move_one_over = true;
      if (debug == true) {
        Serial.println("move one over....");
      }
    }
  }
  if (move_one_over == true && trigger_one_send == false) {
    trigger_one_send =  true;
    trigger_one_millis = currentMillis;
    digitalWrite(trigger, HIGH);
    if (debug == true) {
      Serial.println("trigger one send....");
    }
  }
  if (trigger_one_send == true && trigger_one_over == false) {
    if (debug == true && debug_delay == true) {
      Serial.println(currentMillis - trigger_one_millis);
    }
  }
  if (trigger_one_send == true && currentMillis - trigger_one_millis >= trigger_one_delay) {
    if (trigger_one_over == false) {
      trigger_one_over = true;
      digitalWrite(trigger, LOW);
      if (debug == true) {
        Serial.println("trigger one over....");
      }
    }
  }

  if (digitalRead(feedback_btn) == 0 && trigger_one_over == true && feedback_btn_pressing == false && stage_one_feedback_btn_pressed == false) {
    feedback_btn_pressing = true;
    feedback_btn_millis = currentMillis;
    //Serial.println("feedback....");
  }
  if (feedback_btn_pressing == true && stage_one_feedback_btn_pressed == false && currentMillis - feedback_btn_millis >= feedback_btn_delay) {
    stage_one_feedback_btn_pressed = true;
    feedback_btn_pressing = false;
    Serial.println("stage one feedback....");
  }
  if (digitalRead(feedback_btn) == 1 && feedback_btn_pressing == true && stage_one_feedback_btn_pressed == false) {
    feedback_btn_pressing = false;
  }

  if (stage_one_feedback_btn_pressed == true && trigger_one_over == true && stage_one_over == false) {
    stage_one_over = true;
    if (debug == true) {
      Serial.println("stage one over ....");
    }
  }

  // stage two rutine

  if (stage_one_over == true && move_two_send == false) {
    move_two_send = true;
    move_two_millis = currentMillis;
    if (debug == true) {
      Serial.println("move two send....");
    }
    //send move two cmd
    Serial.println("G91 X6.5");
  }
  if (move_two_send == true && move_two_over == false) {
    if (debug == true && debug_delay == true) {
      Serial.println(currentMillis - move_two_millis);
    }
  }
  if (move_two_send == true && currentMillis - move_two_millis >= move_two_delay) {
    if (move_two_over == false) {
      move_two_over = true;
      if (debug == true) {
        Serial.println("move two over....");
      }
    }
  }
  if (move_two_over == true && trigger_two_send == false) {
    trigger_two_send =  true;
    trigger_two_millis = currentMillis;
    digitalWrite(trigger, HIGH);
    if (debug == true) {
      Serial.println("trigger two send....");
    }
  }
  if (trigger_two_send == true && trigger_two_over == false) {
    if (debug == true && debug_delay == true) {
      Serial.println(currentMillis - trigger_two_millis);
    }
  }
  if (trigger_two_send == true && currentMillis - trigger_two_millis >= trigger_two_delay) {
    if (trigger_two_over == false) {
      trigger_two_over = true;
      digitalWrite(trigger, LOW);
      if (debug == true) {
        Serial.println("trigger two over....");
      }
    }
  }

  if (digitalRead(feedback_btn) == 0 && trigger_two_over == true && feedback_btn_pressing == false && stage_two_feedback_btn_pressed == false) {
    feedback_btn_pressing = true;
    feedback_btn_millis = currentMillis;
    //Serial.println("feedback....");
  }
  if (feedback_btn_pressing == true && stage_two_feedback_btn_pressed == false && currentMillis - feedback_btn_millis >= feedback_btn_delay) {
    stage_two_feedback_btn_pressed = true;
    feedback_btn_pressing = false;
    Serial.println("stage two feedback....");
  }
  if (digitalRead(feedback_btn) == 1 && feedback_btn_pressing == true && stage_two_feedback_btn_pressed == false) {
    feedback_btn_pressing = false;
  }

  if (stage_two_feedback_btn_pressed == true && trigger_two_over == true && stage_two_over == false) {
    stage_two_over = true;
    if (debug == true) {
      Serial.println("stage two over ....");
    }
  }

  // reset everything
  if (stage_two_over == true) {
    // start button rutine
    start_btn_pressed = false;
    stage_one_feedback_btn_pressed = false;
    stage_two_feedback_btn_pressed = false;

    // stage one runtine
    move_one_send = false;
    move_one_over = false;
    trigger_one_send = false;
    trigger_one_over = false;
    stage_one_over = false;

    // stage one runtine
    move_two_send = false;
    move_two_over = false;
    trigger_two_send = false;
    trigger_two_over = false;
    stage_two_over = false;
  }
} // loop
