#include <Arduino.h>
#define MAX_EXP 8

struct Exp {
  bool     active;
  uint8_t  remaining_cycles;
  uint8_t  relay_pin;
  uint32_t last_state_change;
  uint32_t off_duration;
  uint32_t on_duration;
  bool     is_running; 
};

/*
* takes in time in hours, minutes, and seconds as arguments
*/
uint32_t time(uint8_t hours, uint8_t minutes, uint8_t seconds) {
  return (60000 * minutes) + (60 * 60000 * hours) + (1000 * seconds);
}

Exp exp0 = { 
  .active            = false, 
  .remaining_cycles  = 2, 
  .relay_pin         = 2, 
  .last_state_change = 0, 
  .off_duration      = 500, 
  .on_duration       = 500, 
  .is_running        = false 
};

Exp* experiments[MAX_EXP] = { nullptr };

void startExperiment(Exp* e) {
  if (!e) return;
  e->active            = true;
  e->is_running        = true;
  e->last_state_change = millis();
  pinMode(e->relay_pin, OUTPUT);
  digitalWrite(e->relay_pin, HIGH);
}

void stopExperiment(Exp* e) {
  if (!e) return;
  Serial.println("stopping");
  digitalWrite(e->relay_pin, LOW);
  e->is_running = false;
  e->active = false;
  return;
}

void updateExperiment(Exp* e) {
  if (!e || !e->active) return;
  uint32_t now = millis();
  // stopExperiment(e);

  if (e->is_running) {
    if (now - e->last_state_change >= e->on_duration) {
      digitalWrite(e->relay_pin, LOW);
      e->is_running = false;
      e->last_state_change = now;
      Serial.println(e->remaining_cycles);
      e->remaining_cycles--;
      if (e->remaining_cycles == 0) {

        Serial.println("stop inside");
        digitalWrite(e->relay_pin, LOW);
        e->is_running = false;
        e->active = false;
        // stopExperiment(e);
      }
    }
  } else {
    if (now - e->last_state_change >= e->off_duration) {
      digitalWrite(e->relay_pin, HIGH);
      e->is_running = true;
      e->last_state_change = now;
    }
  }
}

void setup() {
  Serial.begin(9600);
  experiments[0] = &exp0;
  startExperiment(&exp0);
}

void loop() {
  for (int i = 0; i < 1; ++i) {
    updateExperiment(experiments[i]);
    if (experiments[i] && !experiments[i]->active) {
      digitalWrite(experiments[i]->relay_pin, LOW);
    }
  }
}
