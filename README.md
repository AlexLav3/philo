
<img width="150" height="150" alt="philosophersn" src="https://github.com/user-attachments/assets/1e894f78-d3c5-467b-a759-28377e309d23" />

## ⏳ Philosophers

This project is a simulation of the classic Dining Philosophers problem, a concurrency challenge. Each philosopher is a thread and must follow rules around eating, thinking, and not dying.

## 🔧 Project Details

- Each philosopher alternates between eating, sleeping, and thinking.
- They need two forks (mutexes) to eat.
- If a philosopher doesn't eat within a time threshold, they die.
- There must be no data races
