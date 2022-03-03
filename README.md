# WordleAgents

Develop an intelligent agent that plays Wordle and challenge your friends for a bit of fun.

PickWords - Executable which selects 'N' words from the list randomly. Useful for setting up a tournament where multiple player agents attempt to solve the same Wordle games.

PlayWodle - Executable which runs the Wordle game. Pass as parameters the name of the Agent plugin DLL (that provides the guesses), the number of games, and any specific solution words (optional).

RandomAgent - Example player agent that picks words at random. Great starting-point for developing your own agent, just change the "GetName" and "GetNextGuess" implementations and show us your AI skills.

WordleAgent - Static library that provides a lot of the common base and helper classes.
