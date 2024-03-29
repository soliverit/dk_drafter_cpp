/*===
    Includes
===*/
// Native
#include <iostream>
#include <Windows.h>
// Project
#include "map.h"
#include "building.h"
#include "print_helper.h"
// Some useful constants
const int MAP_SIZE = 40;
const std::string CSV_PATH = "C:/workspaces/dungeon_keeper/dungeon_drafter/drafts/example.csv";
int main()
{  
    // Get handle to the console window
    HWND consoleWindow = GetConsoleWindow();

    // Set the console window position and size
    SetWindowPos(consoleWindow, HWND_TOP, 0, 0, 800, 600, SWP_SHOWWINDOW);

    // Set the console screen buffer size
    COORD bufferSize = { 10, 10 };  // Adjust the values as needed
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);


    /*===
        Do stuff here.
    ===*/
    Map* map = new Map(MAP_SIZE, 40, {Player("Player 1", 1), Player("Player 2", 2)});
    if (!map->parseCSV(CSV_PATH)) {
        std::cout << "\nProbably couldn't find the CSV";
        return 0;
    }
    PrintHelper::PrintHeader("Draw map");
    map->drawToConsole();
    map->drawPlayersToConsole();
    
    PrintHelper::PrintHeader("Extract Player Map");
    Map* playerMap = map->extractPlayerMap(1);
    playerMap->drawToConsole();

  
    Building building   = Building(map);
    PrintHelper::PrintHeader("Do the survey");

    SbemSurvey survey   = building.toSbemSurvey();
    std::cout << survey.toInp();
    return 0;
  
    Map* playerMap2 = playerMap->clone();
    playerMap2->drawPlayersToConsole();
    return 0;
    /* Print stuff*/

    PrintHelper::PrintHeader("Extract Player map");
    playerMap->drawToConsole();

    PrintHelper::PrintHeader("Replace REINFORCED Tiles with LAVA");
    playerMap->replaceBlocks(Tile::REINFORCED, Tile::TILE_DEFINITIONS_LABELED["LAVA"], 1);
    playerMap->drawToConsole();

    PrintHelper::PrintHeader("Remove all ownable blocks that aren't LAIR");
    playerMap->removeOwnableBlocksExcept(Tile::LAIR, Tile::TILE_DEFINITIONS_LABELED["DIRT"], 1);
    playerMap->drawToConsole();

    PrintHelper::PrintHeader("Rescale LAIR-only map by extracting the Player Map");
    Map* playerMap3 = playerMap->extractPlayerMap(1);
    playerMap3->drawToConsole();
    return 0;
    std::cout << "\n\n--- Merge map 2\n\n";
    playerMap2->merge(playerMap);
    playerMap2->drawToConsole();
    PrintHelper::SpamLine("", "\n", 5);
    std::cout << "\n--- Resize merged map";
   
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
