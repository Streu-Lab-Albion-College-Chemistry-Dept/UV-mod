# UV-mod
Code for embedded radiator device.
# Bioactivity Relay Control System

**Albion College Department of Chemistry – Streu Lab**

---

## Overview

This Arduino‑based relay control system automates timed light or stimulus cycles for bioactivity experiments. It drives up to eight independent relay channels, each with configurable on/off durations and cycle counts. This work supports ongoing research in the Streu Lab on Beta‑1 adrenergic receptor inhibition.

---

## Features

- Up to 8 parallel experiments  
- Individually configurable on‑duration, off‑duration, and cycle count  
- Automatic shutdown when allotted cycles are complete  
- Simple start/stop interface via serial console  

---

## Installation

1. Clone this repository.  
2. Open the `.ino` file in the Arduino IDE.  
3. Ensure each relay module input pin matches the defined `relay_pin` in the code.  
4. Compile and upload to your Arduino Uno (or compatible board).

---

## Usage

1. Power the Arduino and relay modules.  
2. Configure `on_duration`, `off_duration`, and `remaining_cycles` for each `Exp` struct.  
3. Open the Serial Monitor at 9600 baud to observe status messages.  
4. The system will automatically start and cycle each relay in turn.

---

## Directory Structure

