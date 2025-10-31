# VEX Robotics 38535A — *"Over Under"* State Championship Code

This repository contains the complete **C/C++ source code** for **VEX Robotics Team 38535A’s** robot for the **2023–2024 VRC game, “Over Under.”**  
This code was developed for and used at the **Illinois State Championship**.

---

## 🏆 About the Game: *“Over Under”*

The **2023–2024 VEX Robotics Competition**, *“Over Under,”* was a **2v2 game** where robots scored **acorn-shaped objects (“Triballs”)** into goals and could **elevate themselves** at the end of the match.  

This program includes all the logic for both:
- **Autonomous Period** — 15 seconds  
- **Driver-Control Period** — 1 minute and 45 seconds

---

## ⚙️ Key Features

### 🔁 Multi-Routine Autonomous
- Multiple selectable autonomous programs  
- Supports different starting positions and alliance strategies

### 📍 Odometry-Based Navigation
- Integrates sensor data using the **EZ-Template** library  
- Enables precise and reliable odometry for complex, multi-step autonomous paths

### 🎮 Driver Control Enhancements
- Fine-tuned driver controls with custom button mappings  
- Helper functions for a more intuitive and responsive driving experience

### 🧩 Subsystem Management
- Clean, modular code managing all major robot subsystems:
  - Drivetrain  
  - Intake  
  - Scoring mechanisms

---

## 🛠️ Tech Stack

| Component | Details |
|------------|----------|
| **Language** | C / C++ |
| **Framework** | [PROS](https://pros.cs.purdue.edu/) (Purdue Robotics Operating System) |
| **Key Library** | [EZ-Template](https://ez-robotics.github.io/EZ-Template/) — odometry and autonomous movement |
| **Hardware** | VEX V5 Electronics |
