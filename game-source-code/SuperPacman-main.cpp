/**
∗ @class <SuperPacman-main>
∗ @brief Front-End UI
*/
#include <iostream>



#include "GameEngine.h"

auto main(void)->int
{
    /**
    ∗ @brief  function executes the game engine
    ∗
    */

    try
    {
      GameEngine m_GameEngine;
      m_GameEngine.run();

    }
    catch (std::exception& excep) //Provides information if exception is thrown
    {
      std::cout << "\nEXCEPTION: " << excep.what() << std::endl;
    }


}
