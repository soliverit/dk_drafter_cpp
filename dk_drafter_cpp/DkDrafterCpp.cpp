/*===
    Includes
===*/
// Native
#include <iostream>
// Project
#include "map.h"
#include "print_helper.h"
// Some useful constants
const int MAP_SIZE = 26;
const std::string CSV_PATH = "C:/workspaces/dungeon_keeper/dungeon_drafter/drafts/example.csv";
int main()
{  
    Map* map = new Map(MAP_SIZE, MAP_SIZE, {Player("Player 1", 1), Player("Player 2", 2)});
    if (!map->parseCSV(CSV_PATH)) {
        std::cout << "\nProbably couldn't find the CSV";
        return 0;
    }
    PrintHelper::PrintHeader("Draw map");
    map->drawToConsole();
    
    Map* playerMap  = map->extractPlayerMap(1);
    Map* playerMap2 = playerMap->clone();
    /* Print stuff*/

    PrintHelper::PrintHeader("Extract Player map");
    playerMap->drawToConsole();

    PrintHelper::PrintHeader("Replace REINFORCED Tiles with LAVA");
    playerMap->replaceBlocks(Tile::REINFORCED, Tile::TILE_DEFINITIONS_KEYWORDED["LAVA"], 1);
    playerMap->drawToConsole();

    PrintHelper::PrintHeader("Remove all ownable blocks that aren't LAIR");
    playerMap->removeOwnableBlocksExcept(Tile::LAIR, Tile::TILE_DEFINITIONS_KEYWORDED["DIRT"], 1);
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
