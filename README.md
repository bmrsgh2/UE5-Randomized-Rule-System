
# 🎮 # UE5-Randomized-Rule-System

This project showcases a **procedural rule generation system** built in C++ for Unreal Engine 5. It dynamically assigns rule attributes (Aggression and Occurrence) to actor-based game rules while maintaining a target difficulty range. The system is designed for use in custom game modes, particularly those that require randomized challenge configurations at runtime.

---

## ✨ Features

- ✅ Randomized rule attribute assignment (`Aggression`, `Occurrence`)
- ✅ Difficulty clamping and balancing using a threshold formula
- ✅ Reusable and efficient lambdas for shuffling and processing rules
- ✅ Constraint loop ensures rule sets meet difficulty expectations before spawning
- ✅ Configurable difficulty scaling via `GMDifficulty` and `RulesSlots`

---

## 🔧 How It Works

1. **Rules are stored in `RulesData`**, a structure holding multiple `FRulesStruct` items.
2. **Each rule is randomly assigned values** within a calculated range based on game difficulty.
3. The system ensures the **total difficulty rating falls within a target threshold** before proceeding.
4. Once the conditions are met, **selected rules are spawned into the game world** using `SpawnActor`.

---

## 🧠 Technical Notes

- Implemented in **C++** using **Unreal Engine 5**'s gameplay framework.
- Makes use of **lambda functions** for logic reuse (`ProcessRules` and `ShuffleRules`).
- Designed to be easily extendable with additional constraints or curve-based scaling.

---

## 🛠️ Setup Instructions

1. Place the code in your custom `GameMode` class (e.g. `ARulesGameMode`).
2. Ensure `RulesData` is a valid pointer to a structure containing rules (e.g., objects with a mesh or actor).
3. Adjust values like `GMDifficulty` and `RulesSlots` to match your design needs.
4. Call `GetRules()` during game start or when you want to procedurally generate new rules.

---

## 🖼️ Example Use Case

This system can be used in:
- Wave-based enemy spawning
- Puzzle configurations with changing difficulty
- Dynamic scenario generation in narrative games

---

## 📄 License

This project is intended for portfolio and educational use. You may use or adapt it freely — attribution is appreciated but not required.

---

## 🙋 About the Author

Built by a developer passionate about gameplay systems, procedural generation, and scalable game architecture. Looking for internship opportunities in gameplay or systems programming.
