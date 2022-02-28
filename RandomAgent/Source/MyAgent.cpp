
#include "MyAgent.h"
#include "WordleAgent/Random.h"
#include <iostream>
#include <set>


// constructor.
MyAgent::MyAgent(Game& game)
    : Agent(game)
{
    // do any preprocessing here

    // start with our own copy of the full word set
    m_word_set = GetGame().GetWordSet();
}


// return the agent's next guess at the solution
std::string MyAgent::GetNextGuess()
{
    // if (there has been a previous guess) then
    auto gr = GetGame().GetLastGuessResult();
    if (gr)
    {
        // update our knowledge based on the result of the last guess

        // first, remove the guess from the list as it obviously wasn't correct
        m_word_set.erase(gr->guess);

        // for the result code associated with each letter of the guess
        for (size_t i = 0; i < gr->result.size(); i++)
        {
            // if (this letter was in the correct position) then
            if (gr->result[i] == Colour::GREEN)
            {
                // for our word set, filter out any words which don't have this letter in that position
                for (WordSet::iterator iter = m_word_set.begin(); iter != m_word_set.end(); )
                {
                    // if (this letter of this word doesn't match this letter of the guess word) then
                    if ((*iter)[i] != gr->guess[i])
                    {
                        iter = m_word_set.erase(iter);
                    }
                    else
                    {
                        ++iter;
                    }
                }
            }
        }
    }

    // debugging
    //std::cout << "m_word_set size = " << m_word_set.size() << std::endl;

    // return a random item from our remaining word set
    int index = Random::GetRandomInt(0, static_cast<int>(m_word_set.size() - 1));
    return *std::next(m_word_set.begin(), index);
}

