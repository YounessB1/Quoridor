# Quoridor Game for NXP LPC17xx LandTiger  

## 📌 Project Overview  
This project implements the **Quoridor board game** on the **NXP LPC17xx LandTiger development board** using **Keil μVision**. The game logic, board representation, and player interactions are managed through embedded C programming, optimized for the LandTiger board’s hardware.  

## 🛠️ Technologies & Tools  
- **Platform:** NXP LPC17xx (LandTiger Board)  
- **IDE:** Keil μVision  
- **Programming Language:** C  
- **Peripherals Used:** LCD Display, GPIO Buttons, Timers  

## 🎮 Game Features  
- **Two-player mode** (human vs. human)  
- **Board representation** with player movement and wall placement  
- **Game logic enforcement** (valid moves, win conditions)  
- **LCD-based UI** for real-time game state visualization  
- **Button-based input system** for player controls  

## 🚀 Setup & Installation  
1. **Install Keil μVision** and configure it for **NXP LPC17xx**.  
2. **Clone this repository:**  
   ```bash
   git clone <repo-url>
3. Open the project in Keil μVision.
4. Compile and flash the program onto the LandTiger board.
5. Connect the board to a power source and start playing!

## 🏆 How to Play
Players take turns moving their pawn or placing walls.
The goal is to reach the opposite side of the board before the opponent.
Walls can be placed strategically to block the opponent’s path.
The game follows official Quoridor rules.
