//--------------------------------------------------
// Startup code module
//
// @author: Wild Boar
//
// @date: 2022-09-26
//--------------------------------------------------

#include "Engine.h"

//--------------------------------------------------
// Execution entry point
//--------------------------------------------------

/**
 * Main Method
 * @param argc The count of the incoming arguments
 * @param argv The number of incoming arguments
 */
int main(int argc, char ** argv) 
{
    auto logger = NVL_App::Logger();

    try
    {
        auto parameters = NVL_App::ArgUtils::Load("SimpleGP", argc, argv);
        NVL_App::Engine(&logger, parameters).Run();
    }
    catch (runtime_error exception)
    {
        logger << "Error: " << exception.what() << NVL_App::Logger::End();
        exit(EXIT_FAILURE);
    }
    catch (string exception)
    {
        logger << "Error: " << exception << NVL_App::Logger::End();
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
