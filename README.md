# WordleAgents

Develop an intelligent agent that plays Wordle and challenge your friends for a bit of fun.

Built using the free edition of Microsoft Visual Studio Community 2022.

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
- Keep it fair and clean, no stack overflows or const cast hackery please.

## Wordle Rules
All the standard rules of Wordle apply, and the results of your guess are provided in terms of the standard Wordle colours.

There is however one rule that is applied slightly differently, and that's in regards to returning a guess that's not contained in the word list.

If your agent guesses a word that's not in the list, this is treated as an invalid guess but still counts towards the guess limit. This approach is taken to avoid providing useful feedback to agents who try and use invalid guesses for advantage, for example, the word "aeiou" is not valid but if processed would return useful information.
To avoid this, ensure your agent only returns words that are contained in the word list (just like the user interface for the real Wordle does).

