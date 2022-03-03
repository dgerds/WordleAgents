# WordleAgents

Develop an intelligent agent that plays Wordle and challenge your friends for a bit of fun.

## PickWords
Executable which selects 'N' words from the list randomly. Useful for setting up a tournament where multiple player agents attempt to solve the same Wordle games.

## PlayWordle
Executable which runs the Wordle game. Pass as parameters the name of the Agent plugin DLL (that provides the guesses), the number of games, and any specific solution words (optional).

## RandomAgent
Example player agent that picks words at random. Great starting-point for developing your own agent, just change the "GetNextGuess" implementation and show us your AI skills.

## WordleAgent
Static library that provides a lot of the common base and helper classes.

## Tournaments
When challenging your friends, the following guidelines are suggested:
- Set up a tournament as a group of challenge days, a few weeks apart.
- For each challenge day, select 5 words at random using 'PickWords'.
- Run the game for each agent passing those same sets of 5 words.
- Keep the console output for all of the games and view side-by-side to compare strategies.
- The winner of each challenge day is the player who solved the most games overall.
- In case of a tied result, the winner is the player who used the least moves overall.
- In case of a tied result, the winner is the player who used the least overall time.
- Hopefully players learn from each other and adapt their strategies over the tournament period.
- The winner on the final challenge day is the tournament winner and gets cake.
- Keep it fair and clean, no stackoverflows or reinterpret cast hackery please.
