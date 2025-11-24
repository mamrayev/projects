/*
    Author: Mikhail Amrayev
    ECE 114 – Final Game Project

    Over the past two weeks, I dedicated a very large amount of time and effort
    to building this project. I often stayed up late working on the game logic,
    combat system, story flow, and dungeon movement. This was by far the most
    involved C++ project I have ever written, and I’m proud of how much I was
    able to accomplish.

    The project is approximately 750–800 lines of code. I tried my best to keep
    the structure organized and readable, and I hope the slight excess over the
    guideline range will not cause issues. Every mechanic, story piece,
    encounter, and system was created and implemented by me.

    I used documentation, online references, and Visual Studio’s built-in tools
    (such as IntelliSense explanations and debugging assistance) to better
    understand C++ behavior — particularly how input buffers work and how to
    structure functions cleanly. These tools helped me understand the language
    better, but the design and implementation of the code itself are my own.

    I hope Professor Lee enjoys playing through the game and sees the effort
    and dedication I put into creating this project.
*/
#include <iostream> // For std::cout, std::cin
#include <string> // For std::string
#include <cstdlib> // For std::system, std::rand, std::srand
#include <ctime> // For std::time
#include <limits> // For std::numeric_limits
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::seconds
#include <random> // For random number generation
void printMenu(); // Function prototypes
int  getMenuChoice(); // Function prototypes
void startGame();   // Function prototypes
void clearInputBuffer(); // Function prototypes
void handleOrderChoice(); // Function prototypes
void showMap(); // Function prototypes
void clearScreen(); // Function prototypes
void runDungeon(); // Function prototypes
void enterRootPassage(); // Function prototypes
void enterForgottenTunnels(); // Function prototypes
void enterChamberOfWhispers(); // Function prototypes
void enterSanctum(); // Function prototypes
void printRootPassageMenu(); // Function prototypes
void printForgottenTunnelsMenu(); // Function prototypes
void printChamberOfWhispersMenu(); // Function prototypes
void printSanctumMenu(); // Function prototypes
void mageEncounter(); // Function prototypes
void printMageArt(); // Function prototypes
void goblinBattle(); // Function prototypes
void printGoblinArt(); // Function prototypes
int  rollD20(); // Function prototypes
void dragonBattle(); // Function prototypes
void printDragonArt(); // Function prototypes
int playerHP    = 50; // Player stats
int maxPlayerHP = 50; // Player stats
int potions     = 2; // Player stats
int armor       = 1; // Player stats
int gold        = 0; // Player stats
const int ROWS = 10; // Map dimensions
const int COLS = 20; // Map dimensions
void sleepSeconds(int seconds) { // Helper function for sleep
    std::this_thread::sleep_for(std::chrono::seconds(seconds)); // Sleep for specified seconds
} // Helper function for sleep
int rollD20() { // Helper function to roll a 20-sided die
    static std::mt19937 rng{ std::random_device{}() }; // Mersenne Twister RNG
    static std::uniform_int_distribution<int> dist(1, 20); // Uniform distribution from 1 to 20
    return dist(rng); // Return the rolled value
} // Helper function to roll a 20-sided die
void dragonBattle() { // Dragon battle function
    int dragonHP = 50; // Dragon HP
    int choice; // Player choice
    while (true) { // Battle loop
        clearScreen(); // Clear the screen
        std::cout << "========================================\n"; // Separator line
        std::cout << "           FINAL BATTLE: DRAGON\n"; // Battle title
        std::cout << "========================================\n\n"; // Separator line
        printDragonArt(); // Print dragon ASCII art
        std::cout << "The dragon towers before you, flames burning in its chest.\n\n"; // Battle intro
        std::cout << " Player HP : " << playerHP    << " / " << maxPlayerHP << '\n'; // Display player HP
        std::cout << " Dragon HP : " << dragonHP    << '\n'; // Display dragon HP
        std::cout << " Potions   : " << potions     << "\n\n"; // Display potions
        std::cout << " What will you do?\n"; // Prompt for action
        std::cout << "  1. Attack\n"; // Option 1
        std::cout << "  2. Use healing potion\n"; // Option 2
        std::cout << "  3. Try to flee\n"; // Option 3
        std::cout << "> "; // Input prompt
        if (!(std::cin >> choice)) { // Get player choice
            clearInputBuffer(); // Clear input buffer on invalid input
            std::cout << "Invalid input.\n"; // Notify invalid input
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Pause for a moment
            continue; // Restart loop
        } 
        clearInputBuffer(); // Clear input buffer after valid input
        if (choice == 1) { // Attack choice
            int roll = rollD20(); // Roll d20 for attack
            std::cout << "\nYou roll the d20... (" << roll << ")\n"; // Display roll result
            sleepSeconds(1); // Pause for a moment
            if (roll == 1) { // Critical failure
                std::cout << "Critical failure! Your strike glances harmlessly off the scales.\n"; // Notify critical failure
                sleepSeconds(2); // Pause for a moment
            } else if (roll >= 2 && roll <= 9) { // Miss
                std::cout << "You swing with all your might, but the dragon shrugs it off.\n"; // Notify miss
                sleepSeconds(2); // Pause for a moment
            } else if (roll >= 10 && roll <= 19) { // Hit
                int dmgToDragon = 8; // Damage to dragon
                dragonHP -= dmgToDragon; // Subtract damage from dragon HP
                if (dragonHP < 0) dragonHP = 0;    // Prevent negative HP
                std::cout << "Your blade finds a weak spot! You deal " // Notify damage dealt
                          << dmgToDragon << " damage.\n"; // Notify damage dealt
                std::cout << "Dragon HP is now " << dragonHP << ".\n"; // Display dragon HP
                sleepSeconds(2); // Pause for a moment
            } else { // 20 (Critical hit)
                int dmgToDragon = 15; // Damage to dragon
                dragonHP -= dmgToDragon; // Subtract damage from dragon HP
                if (dragonHP < 0) dragonHP = 0;    // Prevent negative HP
                std::cout << "NAT 20! You drive your sword deep between the dragon's scales!\n"; // Notify critical hit
                std::cout << "You deal " << dmgToDragon << " massive damage!\n"; // Notify damage dealt
                std::cout << "Dragon HP is now " << dragonHP << ".\n"; // Display dragon HP
                sleepSeconds(2); // Pause for a moment
            } // End of attack resolution
            if (dragonHP <= 0) { // Check if dragon is defeated
                clearScreen(); // Clear the screen
                std::cout << "With a final roar, the dragon crashes to the ground.\n"; // Notify dragon defeat
                sleepSeconds(2); // Pause for a moment
                std::cout << "Flames flicker and die around you.\n"; // Describe aftermath
                sleepSeconds(2); // Pause for a moment
                std::cout << "\n>>> YOU HAVE SLAIN THE DRAGON. <<<\n"; // Victory message
                sleepSeconds(3); // Pause for a moment
                std::cout << "The artifact pulses quietly in your hand...\n"; // Artifact mention
                sleepSeconds(2); // Pause for a moment
                std::cout << "\n[ENDING SEQUENCE COMES HERE]\n"; // Placeholder for ending sequence
                sleepSeconds(2); // Pause for a moment
                return; // Exit battle
            } // End of dragon defeat check
            int dRoll = rollD20(); // Dragon's attack roll
            std::cout << "\nThe dragon inhales deeply and rolls the d20... (" // Display dragon's roll
                      << dRoll << ")\n"; // Display dragon's roll
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (dRoll <= 4) { // Dragon misses
                std::cout << "The dragon's claws scrape the stone, but you dodge aside.\n"; // Notify miss
                sleepSeconds(2); // Pause for a moment
            } else if (dRoll <= 18) { // Dragon hits
                int dmgToPlayer = 8; // Damage to player
                playerHP -= dmgToPlayer;  // Subtract damage from player HP
                if (playerHP < 0) playerHP = 0; // Prevent negative HP
                std::cout << "The dragon's tail smashes into you! You take " // Notify damage dealt
                          << dmgToPlayer << " damage.\n"; // Notify damage dealt
                std::cout << "Your HP is now " << playerHP << ".\n"; // Display player HP
                sleepSeconds(2); // Pause for a moment
            } else {
                int dmgToPlayer = 16; // Damage to player
                playerHP -= dmgToPlayer; // Subtract damage from player HP
                if (playerHP < 0) playerHP = 0; // Prevent negative HP
                std::cout << "Critical hit! A cone of fire engulfs you!\n"; // Notify critical hit
                std::cout << "You take " << dmgToPlayer // Notify damage dealt
                          << " damage. Your HP is now " << playerHP << ".\n"; // Display player HP
                sleepSeconds(2); // Pause for a moment
            }
            if (playerHP <= 0) { // Check if player is defeated
                clearScreen(); // Clear the screen
                std::cout << "The flames consume you completely.\n"; // Notify defeat
                sleepSeconds(2); // Pause for a moment
                std::cout << "*** YOU DIED TO THE DRAGON ***\n"; // Notify defeat
                sleepSeconds(3); // Pause for a moment
                std::cout << "\nYour journey ends here...\n"; // Notify end of journey
                sleepSeconds(2); // Pause for a moment
                enterRootPassage(); // Return to root passage
                return; // Exit battle
            } // End of player defeat check
        } // End of attack choice
        else if (choice == 2) { // Use healing potion
            if (potions <= 0) { // No potions left
                std::cout << "\nYou reach for a potion, but your belt is empty...\n"; // Notify no potions
                sleepSeconds(2); // Pause for a moment
            } else { // Use potion
                std::cout << "\nYou quickly drink a healing potion.\n"; // Notify potion use
                sleepSeconds(1); // Pause for a moment
                playerHP += 12; // Heal player
                if (playerHP > maxPlayerHP) playerHP = maxPlayerHP; // Cap at max HP
                potions--; // Decrease potion count
                std::cout << "Your HP is now " << playerHP << ". Potions left: " << potions << '\n'; // Display player HP and potions left
                sleepSeconds(2); // Pause for a moment
            }
        }
        else if (choice == 3) { // Try to flee
            std::cout << "\nYou try to flee...\n"; // Notify flee attempt
            std::this_thread::sleep_for(std::chrono::seconds(2)); // Pause for a moment
            int fleeRoll = rollD20(); // Roll d20 for flee
            std::cout << "You roll the d20... (" << fleeRoll << ")\n"; // Display roll result
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Pause for a moment
            if (fleeRoll <= 15) { // Failed flee
                std::cout << "The dragon blocks your path with a wall of fire. "  // Notify failed flee
                             "There is no escape.\n"; // Notify failed flee
                std::this_thread::sleep_for(std::chrono::seconds(2)); // Pause for a moment
            } else { // Successful flee
                clearScreen(); // Clear the screen 
                std::cout << "Against all odds, you slip past the dragon's wings into the tunnels!\n"; // Notify successful flee
                sleepSeconds(3); // Pause for a moment
                std::cout << "Your heart pounds as flames erupt behind you.\n"; // Describe escape
                sleepSeconds(2); // Pause for a moment
                std::cout << "You sprint through the Chamber of Whispers...\n"; // Describe escape
                sleepSeconds(2); // Pause for a moment
                std::cout << "The Forgotten Tunnels shake as the dragon roars.\n"; // Describe escape
                sleepSeconds(3); // Pause for a moment
                std::cout << "Roots crack and fall as you burst into the Root Passage.\n"; // Describe escape
                sleepSeconds(3); // Pause for a moment
                std::cout << "\nYou see daylight—faint, but unmistakable.\n"; // Describe escape
                sleepSeconds(2); // Pause for a moment
                std::cout << "You run. Faster than you ever have.\n"; // Describe escape
                sleepSeconds(2); // Pause for a moment
                clearScreen(); // Clear the screen
                std::cout << "Your black horse waits trembling at the entrance.\n"; // Describe escape
                sleepSeconds(2); // Pause for a moment
                std::cout << "Without hesitation, you leap into the saddle.\n"; // Describe escape
                sleepSeconds(2); // Pause for a moment
                std::cout << "Behind you, the ground trembles as the dragon claws its way upward.\n"; // Describe escape
                sleepSeconds(3); // Pause for a moment
                std::cout << "\nYou spur the horse forward, racing across the scorched plains of Kirkland.\n"; // Describe escape
                sleepSeconds(3); // Pause for a moment
                std::cout << "The wind tears at your cloak as smoke billows behind you.\n"; // Describe escape
                sleepSeconds(3); // Pause for a moment
                std::cout << "\nBut you do not look back.\n"; // Describe escape
                sleepSeconds(2); // Pause for a moment
                std::cout << "Not once.\n"; // Describe escape
                sleepSeconds(2); // Pause for a moment
                clearScreen(); // Clear the screen
                std::cout << "========================================\n"; // Separator line
                std::cout << "        ** YOU HAVE ESCAPED **\n"; // Victory message
                std::cout << "========================================\n\n"; // Separator line
                sleepSeconds(2); // Pause for a moment 
                std::cout << "You survived...\n"; // Survival message
                sleepSeconds(2); // Pause for a moment
                std::cout << "But the artifact... and the dragon... remain.\n"; // Describe aftermath
                sleepSeconds(3); // Pause for a moment
                std::cout << "\nThis is not a victory.\n"; // Describe aftermath
                sleepSeconds(2); // Pause for a moment
                std::cout << "Only postponement.\n"; // Describe aftermath
                sleepSeconds(2); // Pause for a moment
                std::cout << "\n[ COWARD'S ENDING – You fled Kirkland ]\n"; // Describe aftermath
                sleepSeconds(3); // Pause for a moment
                std::cout << "\nReturning to main menu...\n"; // Notify return to menu
                sleepSeconds(3); // Pause for a moment
                startGame();
                return;
            }
        }
        else { // Invalid choice
            std::cout << "\nChoose 1, 2, or 3.\n"; // Notify invalid choice
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Pause for a moment
        } // End of choice handling
    } // End of battle loop
} // Dragon battle function
void goblinBattle() { // Goblin battle function
    int goblinHP = 20; // Goblin HP
    int choice; // Player choice
    while (true) { // Battle loop
        clearScreen(); // Clear the screen
        std::cout << "========================================\n"; // Separator line
        std::cout << "          BATTLE: GOBLIN SCOUT\n"; // Battle title
        std::cout << "========================================\n\n"; // Separator line
        printGoblinArt(); // Print goblin ASCII art
        std::cout << " Player HP : " << playerHP << "\n";  // Display player HP
        std::cout << " Goblin HP : " << goblinHP << "\n";  // Display goblin HP
        std::cout << " Potions   : " << potions << "\n\n"; // Display potions
        std::cout << " What will you do?\n"; // Prompt for action
        std::cout << "  1. Attack\n"; // Option 1
        std::cout << "  2. Use healing potion\n"; // Option 2
        std::cout << "  3. Flee back into the tunnels\n"; // Option 3
        std::cout << "> "; // Input prompt
        if (!(std::cin >> choice)) { // Get player choice
            clearInputBuffer(); // Clear input buffer on invalid input
            std::cout << "Invalid input.\n"; // Notify invalid input
            sleepSeconds(1); // Pause for a moment
            continue; // Restart loop
        } // End of input validation
        clearInputBuffer(); // Clear input buffer after valid input
        if (choice == 1) { // Attack choice
            int roll = rollD20(); // Roll d20 for attack
            std::cout << "\nYou roll the d20... (" << roll << ")\n"; // Display roll result
            sleepSeconds(1); // Pause for a moment
            if (roll == 1) { // Critical failure
                std::cout << "Critical failure! You slip on loose stones and miss completely!\n"; // Notify critical failure
                sleepSeconds(2); // Pause for a moment
            } // End of critical failure
            else if (roll >= 2 && roll <= 9) {
                std::cout << "You swing, but the goblin dodges out of the way.\n"; // Notify miss
                sleepSeconds(2); // Pause for a moment
            } // End of miss
            else if (roll >= 10 && roll <= 19) { // Hit
                int dmgToGoblin = 6; // Damage to goblin
                goblinHP -= dmgToGoblin; // Subtract damage from goblin HP
                if (goblinHP < 0) goblinHP = 0;   // Prevent negative HP
                std::cout << "Solid hit! You deal " << dmgToGoblin << " damage. Goblin HP is now " << goblinHP << ".\n"; // Notify damage dealt
                sleepSeconds(2); // Pause for a moment
                sleepSeconds(2); // Pause for a moment
            }
            else { // 20 (Critical hit)
                int dmgToGoblin = 10; // Damage to goblin
                goblinHP -= dmgToGoblin; // Subtract damage from goblin HP
                if (goblinHP < 0) goblinHP = 0; // Prevent negative HP
                std::cout << "NAT 20! A devastating strike deals " // Notify critical hit
                          << dmgToGoblin << " damage!\n"; // Notify critical hit
                std::cout << "Goblin HP is now " << goblinHP << ".\n"; // Display goblin HP
                sleepSeconds(2); // Pause for a moment
            } // End of attack resolution
            if (goblinHP <= 0) { // Check if goblin is defeated
                std::cout << "\nThe goblin collapses with a shriek.\n"; // Notify goblin defeat
                sleepSeconds(2); // Pause for a moment
                std::cout << "You survived the encounter.\n"; // Notify survival
                sleepSeconds(2); // Pause for a moment 
                std::cout << "\n[You can now continue deeper into the Forgotten Tunnels.]\n"; // Notify progression
                sleepSeconds(2); // Pause for a moment
                showMap(); // Show updated map
                return; // Exit battle
            } // End of goblin defeat check
            int gRoll = rollD20(); // Goblin's attack roll
            std::cout << "\nThe goblin snarls and rolls the d20... (" << gRoll << ")\n"; // Display goblin's roll
            sleepSeconds(1); // Pause for a moment
            if (gRoll <= 5) { // Goblin misses
                std::cout << "The goblin swings wildly and misses you.\n"; // Notify miss
                sleepSeconds(2); // Pause for a moment
            } // End of goblin miss
            else if (gRoll <= 19) { // Goblin hits
                int dmgToPlayer = 4; // Damage to player
                playerHP -= dmgToPlayer; // Subtract damage from player HP
                if (playerHP < 0) playerHP = 0; // Prevent negative HP
                std::cout << "The goblin's blade cuts your arm. You take " << dmgToPlayer << " damage.\n"; // Notify damage dealt
                std::cout << "Your HP is now " << playerHP << ".\n"; // Display player HP
                sleepSeconds(2); // Pause for a moment
            } // End of goblin hit
            else { // Goblin critical hit
                int dmgToPlayer = 8; // Damage to player
                playerHP -= dmgToPlayer; // Subtract damage from player HP
                if (playerHP < 0) playerHP = 0; // Prevent negative HP
                std::cout << "Critical hit! The goblin drives the blade into your side!\n"; // Notify critical hit
                std::cout << "You take " << dmgToPlayer << " damage. Your HP is now " << playerHP << ".\n"; // Display player HP
                sleepSeconds(2); // Pause for a moment
            } // End of goblin attack resolution
            if (playerHP <= 0) { // Check if player is defeated
                std::cout << "\nYou fall to the cold stone floor...\n"; // Notify defeat
                sleepSeconds(2); // Pause for a moment
                std::cout << "*** YOU DIED TO THE GOBLIN ***\n"; // Notify defeat
                sleepSeconds(2); // Pause for a moment
                std::cout << "\nYou awaken back at the ROOT PASSAGE.\n"; // Notify respawn location
                sleepSeconds(2); // Pause for a moment
                enterRootPassage(); // Return to root passage
                return; // Exit battle
            } // End of player defeat check
        } // End of attack choice
        else if (choice == 2) { // Use healing potion
            if (potions <= 0) { // No potions left
                std::cout << "\nYou reach for a potion, but your belt is empty...\n"; // Notify no potions
                sleepSeconds(2); // Pause for a moment
            } else { // Use potion
                std::cout << "\nYou quickly drink a healing potion.\n"; // Notify potion use
                sleepSeconds(1); // Pause for a moment
                playerHP += 10; // Heal player
                if (playerHP > 35) // Cap HP at maximum
                    playerHP = 35; // Cap HP at maximum
                potions--; // Decrease potion count
                std::cout << "Your HP is now " << playerHP << ". Potions left: " << potions << "\n"; // Display player HP and potions left
                sleepSeconds(2); // Pause for a moment
            } // End of potion use
        } // End of healing potion choice
        else if (choice == 3) { // Flee choice
            std::cout << "\nYou turn and flee into the darkness!\n"; // Notify flee
            sleepSeconds(2); // Pause for a moment
            std::cout << "The goblin's laughter echoes behind you...\n"; // Describe escape
            sleepSeconds(2); // Pause for a moment
            enterForgottenTunnels(); // Return to Forgotten Tunnels
            return; // Exit battle
        } // End of flee choice
        else {
            std::cout << "\nChoose 1, 2, or 3.\n"; // Notify invalid choice
            sleepSeconds(1); // Pause for a moment
        } // End of choice handling
    } // End of battle loop
} // Goblin battle function
void printMageArt(void) { // Function to print mage ASCII art
    std::cout << "                .----.\n";
    std::cout << "               / .-\"-.\\\n";
    std::cout << "               | | ' \\ \\\n";
    std::cout << "               | |  / /|\n";
    std::cout << "            _   \\ \\_/ /_\n";
    std::cout << "           / \\__/'.-'.__\\\\\n";
    std::cout << "           \\____/ / \\____/\n";
    std::cout << "             _/ /| | \\_\n";
    std::cout << "            / _/ | |  \\ \\\n";
    std::cout << "           /_/   |_|   \\_\\\n";
    std::cout << "             ( )  |      |\n";
    std::cout << "              ||  |  /\\  |\n";
    std::cout << "              ||  |  ||  |\n";
    std::cout << "              ||  |  ||  |\n";
    std::cout << "              ||  |  ||  |\n";
    std::cout << "              ||  |  ||  |\n";
    std::cout << "              ||  |  ||  |\n";
    std::cout << "              ||  |  ||  |\n";
    std::cout << "             /__\\ |__||__|\n";
    std::cout << "              /_/  \\_||_/\n";
    std::cout << "\n";
} // Function to print mage ASCII art
void printGoblinArt() { // Function to print goblin ASCII art
std::cout <<  "    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
std::cout << ":::::===-:::::::::::::::=+***=--------=****=:::::::::::::::-===:::::\n";
std::cout << ":::=+***++-:::::::::::++*+=================*++:::::::::::-++***+=:::\n";
std::cout << ":::*%%====+++::::::::=*++====================++*+::::::::+*++===%%#:::\n";
std::cout << "---*%%+=++===#*------*%%--====================--%%*------*#===++=+%%#---\n";
std::cout << "---*%%++%%#*+=-=%+--=%+-========================-+%=--+%=-=+*#%%++%%#---\n";
std::cout << "-----#%%*#%%**==-*%-=%+--------==========--------+%=-%*-==**%%#*%%#-----\n";
std::cout << "------=%%#*#%%*+=--%%#---%%%%%%%-========-%%%%%%%---#%%--=+*%%#*#%=------\n";
std::cout << "------=%%#*#%%%%#*+=--=#%%..=*%%==%%*======*%%==%%#=..%%#=--=+*#%%%%#*#%=------\n";
std::cout << "--------*%%**%%%#*===*%%..=*%%==%%*======*%%==%%#=..%%#===*#%%%**%%*--------\n";
std::cout << "--------*%%**%%%#*=====%%%--=..%%#*=--=*#%%..=-.#%%=====*#%%%**%%*--------\n";
std::cout << "========*%%****%%%**===**%%%%%***=--=***%%%%%**===**%%%****%%*========\n";
std::cout << "==========*#***##%%=====+++++#*=----=*#+++++=====#%%#***#*==========\n";
std::cout << "============**#**##*++=======+*#*+++#*+=======++*##**#**============\n";
std::cout << "=============+*####*##++=+*====+*##*++===*+=++##*####*+=============\n";
std::cout << "===============+***=*%%*+=*#*****####*****#*=+*%%#=***+===============\n";
std::cout << "====================++##++****************++##++====================\n";
std::cout << "======================++%%%**==========+*%%%++======================\n";
std::cout << "++++++++++++++++++++++%%%%%%%**********%%%%%%%++++++++++++++++++++++\n";
std::cout << "++++++++++++++++++++#%%++###%%%%%%%%%%%%%%###++%%#++++++++++++++++++++\n";
std::cout << "+++++++++++++++++++%%+-**+*###%%%%%%%%%%###*+**-+%%++++++++++++++++++++\n";
std::cout << "+++++++++++++++++++%%+-==*++##############++*==-+%%++++++++++++++++++++\n";
std::cout << "+++++++++++++++++%%#-=====+*++##########++*+=====-#%%++++++++++++++++++++\n";
std::cout << "+++++++++++++++++%%#-=======**+*######*+**=======-#%%++++++++++++++++++++\n";
std::cout << "+++++++++++++++#%%--==========+++*##*+++==========--%%#+++++++++++++++++++\n";
std::cout << "+++++++++++++****-=++*========+#*++*#+========*++==****+++++++++++++\n";
std::cout << "**************%%+-==*#%%**+******#++++#******+**%%#*==-+%%**************\n";
std::cout << "************##+==++###%%%%**####*+====+*####**%%%%###++==+*#************\n";
std::cout << "************%%#-==**%%#*%%*+++++========+++++*%%*#%%**==-#%%************\n";
std::cout << "**********##===+*%%%%***%%%%*+================+*%%%%***%%%%*+===##**********\n";
std::cout << "**********%%--=+*%%%%*#%%**====================+*%%#*%%%%*+=--#%%**********\n";
std::cout << "********#%%=-=+*#%%***#%%*+====================+*%%#***%%#*+=-=%#********\n";
std::cout << "********#%%=-=+*#%%***#%%*+====================+*%%#***%%#*+=-=%#********\n";
} // Function to print goblin ASCII art
void printDragonArt() { // Function to print dragon ASCII art
    std::cout << "                   / \\\\  //\\\\\n";
    std::cout << "          |\\\\___/|      /   \\\\//  \\\\\\\\\n";
    std::cout << "          /0  0  \\\\__  /    //  | \\\\ \\\\\n";
    std::cout << "         /     /  \\\\_/\\\\    //   |  \\\\  \\\\\n";
    std::cout << "         \\\\_^_\\\\'/   \\\\_/   //    |   \\\\   \\\\ \n";
    std::cout << "         //_^_/     \\\\_/ //     |    \\\\    \\\\ \n";
    std::cout << "      ( //) |        \\\\\\\\\\      |     \\\\     \\\\ \n";
    std::cout << "    ( / /) _|_ /   )  //       |      \\\\     _\\\\\n";
    std::cout << "  ( // /) '/,_ _ _/  ( ; -.    |    _ _\\\\.-~        .-~~~^-.\n";
    std::cout << "(( / / )) ,-{        _      `-.|.-~-.           .~         `.\n";
    std::cout << "(( // / ))  '/\\\\      /                 ~-. _ .-~      .-~^-.  \\\\\n";
    std::cout << "(( /// ))      `.   {            }                   /      \\\\  \\\\\n";
    std::cout << " (( / ))     .----~-.\`-._       }            }      {        }  }\n";
    std::cout << "            ///.----..> _.-~-.                    .-~-.\\\\     /\n";
    std::cout << "              ///-._ _ _ _ _ _}^ - - - - -. _ _ _ _ _ _}^ - - - - ~-.\n";
    std::cout << "\n";
} // Function to print dragon ASCII art
void clearScreen() { // Function to clear the console screen
    std::cout << "\x1b[2J\x1b[H"; // ANSI escape codes to clear screen and move cursor to home position
    std::cout.flush(); // Flush the output buffer
} // Function to clear the console screen
void showMap(void) { // Function to display the map and handle location selection
    int choice; // Player's location choice
    while (1) {
        clearScreen(); // Clear the screen
        std::cout << "    +----------------------------+\n"; // Map header
        std::cout << "    |       ROOT PASSAGE    (1)  |\n";
        std::cout << "    +----------------------------+\n\n";
        std::cout << "    +----------------------------+\n";
        std::cout << "    |   FORGOTTEN TUNNELS   (2)  |\n";
        std::cout << "    +----------------------------+\n\n";
        std::cout << "    +----------------------------+\n";
        std::cout << "    | CHAMBER OF WHISPERS   (3)  |\n";
        std::cout << "    +----------------------------+\n\n";
        std::cout << "    +----------------------------+\n";
        std::cout << "    | SANCTUM OF THE ARTIFACT(4) |\n";
        std::cout << "    +----------------------------+\n\n"; // Map footer
        std::cout << "    Gold: " << gold << " | HP: " << playerHP << " / " << maxPlayerHP << " | Potions: " << potions << "\n\n"; // Player stats
        std::cout << "Select location (0 to stay on map): "; // Prompt for location choice
        if (!(std::cin >> choice)) { // Get player choice using std::cin
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            std::cout << "Invalid input.\n"; // Notify invalid input
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Pause for a moment
            continue; // Restart loop
        } // End of input validation
        if (choice == 0) { // Stay on map
            continue; // stay on the map
        } // End of stay on map choice
        else if (choice == 1) { // Enter Root Passage
            enterRootPassage(); // Call function to enter Root Passage
            break; // Exit loop
        } // End of Root Passage choice
        else if (choice == 2) { // Enter Forgotten Tunnels
            enterForgottenTunnels(); // Call function to enter Forgotten Tunnels
            break; // Exit loop
        } // End of Forgotten Tunnels choice
        else if (choice == 3) { // Enter Chamber of Whispers
            enterChamberOfWhispers(); // Call function to enter Chamber of Whispers
            break; // Exit loop
        } // End of Chamber of Whispers choice
        else if (choice == 4) { // Enter Sanctum of the Artifact
            enterSanctum(); // Call function to enter Sanctum of the Artifact
            break; // Exit loop
        } // End of Sanctum of the Artifact choice
        else { // Invalid choice
            std::cout << "Choose 0–4 only.\n"; // Notify invalid choice
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Pause for a moment
        } // End of choice handling
    } // End of location selection loop
} // Function to display the map and handle location selection
void runDungeon() { // Function to run the dungeon maze
    char map[ROWS][COLS + 1] = { // +1 for null terminator
        "####################", 
        "#P.......#.........#",
        "#.#####..#..####...#",
        "#.....#..#.....#...#",
        "###.#.####.###.#.###",
        "#...#......#...#...#",
        "#.####.########..###",
        "#.....#......#.....#",
        "#.###.######.#.##X##",
        "####################" 
    };
    int playerRow = 0, playerCol = 0; // Player's current position
    int foundArtifact = 0; // Flag to track if artifact is found
    for (int r = 0; r < ROWS; r++) { // Find initial player position
        for (int c = 0; c < COLS; c++) { // Iterate through columns
            if (map[r][c] == 'P') { // Player found
                playerRow = r; // Set player's initial row
                playerCol = c; // Set player's initial column
            } // End of player found check
        } // End of row iteration
    } // End of column iteration
    while (!foundArtifact) { // Main game loop
        clearScreen(); // Clear the screen
        std::cout << "DUNGEON OF KIRKWOOD\n"; // Title
        std::cout << "--------------------\n\n"; // Separator
        for (int r = 0; r < ROWS; r++) { // Display the map
            for (int c = 0; c < COLS; c++) { // Iterate through columns
                std::cout << map[r][c]; // Print map character
            } // End of column iteration
            std::cout << '\n'; // New line after each row
        } // End of row iteration
        std::cout << "\nLegend: P = you, X = artifact, # = wall\n"; // Legend
        std::cout << "Move with W/A/S/D, Q to quit.\n"; // Instructions
        std::cout << "> "; // Input prompt
        char cmd; // Player command
        if (!(std::cin >> cmd)) { // Get player command
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore rest of the line
            continue; // Restart loop
        } // End of input validation
        int dr = 0, dc = 0; // Movement deltas
        if (cmd == 'w' || cmd == 'W') dr = -1; // Move up
        else if (cmd == 's' || cmd == 'S') dr = 1; // Move down
        else if (cmd == 'a' || cmd == 'A') dc = -1; // Move left
        else if (cmd == 'd' || cmd == 'D') dc = 1; // Move right
        else if (cmd == 'q' || cmd == 'Q') { // Quit command
            std::cout << "\nYou decide to turn back from the darkness...\n"; // Notify quitting
            sleepSeconds(1); // Pause for a moment
            return; // Exit function
        } else { // Invalid command
            std::cout << "\nYou hesitate, doing nothing...\n";
            sleepSeconds(1); // Pause for a moment
            continue; // Restart loop
        } // End of command handling
        int newRow = playerRow + dr; // Calculate new row
        int newCol = playerCol + dc; // Calculate new column
        if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS) { // Out of bounds check
            std::cout << "\nYou bump into the unseen edge of the world.\n"; // Notify out of bounds
            sleepSeconds(1); // Pause for a moment
            continue; // Restart loop
        }
        char target = map[newRow][newCol]; // Target cell character
        if (target == '#') { // Wall check
            std::cout << "\nYou slam into a cold stone wall.\n"; // Notify wall collision
            sleepSeconds(1); // Pause for a moment
            continue; // Restart loop
        }
        if (target == 'X') { // Artifact found
            map[playerRow][playerCol] = '.'; // Clear previous position
            map[newRow][newCol] = 'P'; // Move player to artifact position
            playerRow = newRow; // Update player row
            playerCol = newCol; // Update player column
            clearScreen(); // Clear the screen
            for (int r = 0; r < ROWS; r++) { // Display the map
                for (int c = 0; c < COLS; c++) { // Iterate through columns
                    std::cout << map[r][c]; // Print map character
                } // End of column iteration
                std::cout << '\n'; // New line after each row
            } // End of row iteration
            std::cout << "\nYou step into the final chamber...\n"; // Notify artifact discovery
            sleepSeconds(2); // Pause for a moment 
            std::cout << "The artifact pulses with a sickly light beneath your hands.\n"; // Describe artifact
            sleepSeconds(3); // Pause for a moment  
            std::cout << "\n>> You have found the artifact. <<\n"; // Notify artifact found
            sleepSeconds(2); // Pause for a moment
            foundArtifact = 1; // Set artifact found flag
            break; // Exit loop
        } // End of artifact found check
        map[playerRow][playerCol] = '.'; // Clear previous position
        map[newRow][newCol] = 'P'; // Move player to new position
        playerRow = newRow; // Update player row
        playerCol = newCol; // Update player column
    } // End of main game loop
    if (foundArtifact == 1) { // If artifact was found
        if (playerHP < maxPlayerHP) playerHP = maxPlayerHP; // Restore player HP
        if (potions < 1) potions = 1; // Ensure at least one potion
        std::cout << "As soon as you put your sword away and take the artifact,\n"; // Describe artifact pickup
        sleepSeconds(2); // Pause for a moment
        std::cout << "out of nowhere, a dragon appears from the burning depths!\n"; // Describe dragon appearance
        sleepSeconds(2); // Pause for a moment
        std::cout << "The same one you saw in your dreams...\n"; // Describe dragon
        sleepSeconds(3); // Pause for a moment
        std::cout << "\n\"FIGHT, MORTAL,\" said the dragon.\n"; // Dragon's challenge
        sleepSeconds(2); // Pause for a moment
        dragonBattle(); // Start dragon battle
        return; // Exit function
    } // End of artifact found handling
} // Function to run the dungeon maze
void printRootPassageMenu() { // Function to print Root Passage menu
    std::cout << "(Root Passage Menu Placeholder)\n"; // Placeholder text
} // Function to print Root Passage menu
void skeletonBattle() { // Skeleton battle function
    int skeletonHP = 30; // Skeleton HP
    int choice; // Player choice
    int round = 0; // Round counter
    while (true) { // Battle loop
        clearScreen(); // Clear the screen
        round++; // Increment round counter
        std::cout << "========================================\n"; // Battle header
        std::cout << "        BATTLE: UNDEAD SKELETON\n"; // Battle title
        std::cout << "========================================\n"; // Battle header
        std::cout << "\n[Round " << round << "] You face an ancient skeleton warrior!\n\n"; // Round info
        std::cout << " Player HP : " << playerHP << " / " << maxPlayerHP << "\n"; // Display player HP
        std::cout << " Skeleton HP : " << skeletonHP << "\n"; // Display skeleton HP
        std::cout << " Armor : " << armor << "\n"; // Display player armor
        std::cout << " Potions : " << potions << "\n\n"; // Display potions
        std::cout << " What will you do?\n"; // Prompt for action
        std::cout << "  1. Attack with sword\n"; // Option 1
        std::cout << "  2. Use healing potion\n"; // Option 2
        std::cout << "  3. Try to intimidate\n"; // Option 3
        std::cout << "> "; // Input prompt
        if (!(std::cin >> choice)) { // Get player choice
            clearInputBuffer(); // Clear input buffer on invalid input
            std::cout << "Invalid input.\n"; // Notify invalid input
            sleepSeconds(1); // Pause for a moment
            continue; // Restart loop
        } // End of input validation
        clearInputBuffer(); // Clear input buffer after valid input
        if (choice == 1) { // Attack choice
            int roll = rollD20(); // Roll d20 for attack
            std::cout << "\nYou swing your sword at the skeleton... (" << roll << ")\n"; // Display roll result
            sleepSeconds(1); // Pause for a moment
            if (roll <= 5) { // Attack misses
                std::cout << "Your sword passes through the air harmlessly!\n"; // Notify miss
                sleepSeconds(1); // Pause for a moment
            } else if (roll <= 14) { // Normal hit
                int dmg = 5; // Damage to skeleton
                skeletonHP -= dmg; // Subtract damage from skeleton HP
                if (skeletonHP < 0) skeletonHP = 0;  // Prevent negative HP
                std::cout << "You strike the skeleton for " << dmg << " damage!\n"; // Notify damage dealt
                std::cout << "Skeleton HP: " << skeletonHP << "\n"; // Notify damage dealt
                sleepSeconds(1); // Pause for a moment
            } else { // Critical hit
                int dmg = 12; // Damage to skeleton
                skeletonHP -= dmg;  // Subtract damage from skeleton HP
                if (skeletonHP < 0) skeletonHP = 0;  // Prevent negative HP
                std::cout << "A powerful strike! " << dmg << " damage dealt!\n"; // Notify damage dealt
                std::cout << "Skeleton HP: " << skeletonHP << "\n"; // Notify damage dealt
                sleepSeconds(1); // Pause for a moment
            } // End of attack resolution
            if (skeletonHP <= 0) { // Check if skeleton is defeated
                clearScreen(); // Clear the screen
                std::cout << "\nThe skeleton crumbles to dust...\n"; // Notify skeleton defeat
                sleepSeconds(2); // Pause for a moment
                std::cout << "You find 50 gold coins among the remains!\n"; // Notify gold found
                gold += 50; // Add gold to player
                sleepSeconds(2); // Pause for a moment
                return; // Exit battle
            } // End of skeleton defeat check
            int skRoll = rollD20(); // Skeleton's attack roll
            std::cout << "\nThe skeleton retaliates... (" << skRoll << ")\n"; // Display skeleton's roll
            sleepSeconds(1); // Pause for a moment
            if (skRoll <= 3) { // Skeleton misses
                std::cout << "The skeleton's bony fist misses you entirely!\n"; // Notify miss
                sleepSeconds(1); // Pause for a moment
            } else if (skRoll <= 15) { // Skeleton hits
                int dmg = 3 + (armor > 0 ? 0 : 2); // Damage to player
                playerHP -= dmg; // Subtract damage from player HP
                if (playerHP < 0) playerHP = 0; // Prevent negative HP
                std::cout << "The skeleton hits you for " << dmg << " damage!\n"; // Notify damage dealt
                std::cout << "Your HP: " << playerHP << "\n"; // Display player HP
                sleepSeconds(1); // Pause for a moment
            } else { // Skeleton critical hit
                int dmg = 7 + (armor > 0 ? 1 : 3); // Damage to player
                playerHP -= dmg; // Subtract damage from player HP
                if (playerHP < 0) playerHP = 0; // Prevent negative HP
                std::cout << "A critical hit! " << dmg << " damage!\n"; // Notify damage dealt
                std::cout << "Your HP: " << playerHP << "\n"; // Display player HP
                sleepSeconds(1); // Pause for a moment
            } // End of skeleton attack resolution
            if (playerHP <= 0) { // Check if player is defeated
                clearScreen(); // Clear the screen
                std::cout << "The skeleton's relentless assault overwhelms you...\n"; // Notify player defeat
                sleepSeconds(2); // Pause for a moment
                std::cout << "*** YOU WERE DEFEATED BY THE SKELETON ***\n"; // Display defeat message
                sleepSeconds(2); // Pause for a moment
                playerHP = 25; // Reset player HP
                return; // Exit battle
            } // End of player defeat check
        } // End of player defeat check
        else if (choice == 2) { // Use healing potion
            if (potions <= 0) { // No potions left
                std::cout << "\nYou have no potions left!\n"; // Notify no potions left
                sleepSeconds(1); // Pause for a moment
            } else { // Use potion
                std::cout << "\nYou drink a healing potion...\n"; // Notify potion use
                sleepSeconds(1); // Pause for a moment
                int healed = 15; // Healing amount
                playerHP += healed; // Heal player
                if (playerHP > maxPlayerHP) playerHP = maxPlayerHP; // Cap HP at maximum
                potions--; // Decrease potion count
                std::cout << "You recover " << healed << " HP!\n"; // Notify healing amount
                std::cout << "HP: " << playerHP << " | Potions left: " << potions << "\n"; // Display current HP and potions
                sleepSeconds(2); // Pause for a moment
            } // End of potion use
        } // End of healing potion choice
        else if (choice == 3) { // Intimidate choice
            std::cout << "\nYou attempt to intimidate the skeleton...\n"; // Notify intimidate attempt
            sleepSeconds(1); // Pause for a moment
            int intimRoll = rollD20(); // Roll d20 for intimidation
            if (intimRoll >= 12) { // Successful intimidation
                std::cout << "The skeleton, confused by your bravery, hesitates!\n"; // Notify success
                sleepSeconds(2); // Pause for a moment
                std::cout << "You slip past and escape to safety!\n"; // Notify escape
                sleepSeconds(1); // Pause for a moment
                return; // Exit battle
            } else { // Failed intimidation
                std::cout << "The skeleton is unmoved. It knows no fear.\n"; // Notify failure
                sleepSeconds(2); // Pause for a moment
            } // End of intimidation resolution
        } // End of intimidate choice
        else { // Invalid choice
            std::cout << "\nChoose 1, 2, or 3.\n"; // Notify invalid choice
            sleepSeconds(1); // Pause for a moment
        } // End of choice handling
    } // End of battle loop
} // Skeleton battle function
void mageEncounter() { // Mage encounter function
    int choice; // Player choice
    clearScreen(); // Clear the screen
    sleepSeconds(2); // Pause for a moment
    printMageArt(); // Print mage ASCII art
    sleepSeconds(2); // Pause for a moment
    std::cout << "Magician: Good evening, traveler... Have you come for the artifact?\n"; // Mage dialogue
    sleepSeconds(2); // Pause for a moment
    std::cout << "\nYou:\n"; // Player dialogue prompt
    std::cout << "  (1) How... How did you know?\n"; // Option 1
    std::cout << "  (2) No, I live here.\n"; // Option 2
    std::cout << "> ";  // Input prompt
    if (!(std::cin >> choice)) { // Get player choice
        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        enterRootPassage(); // Return to root passage
        return; // Exit function
    } // End of input validation
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
    if (choice == 2) { // Player denies seeking artifact
        clearScreen();  // Clear the screen 
        std::cout << "Magician: A pity... A LIE.\n"; // Mage dialogue
        sleepSeconds(2); // Pause for a moment
        std::cout << "The mage raises his staff.\n"; // Describe mage action
        sleepSeconds(1); // Pause for a moment
        std::cout << "A flash of burning light devours your body.\n"; // Describe attack
        sleepSeconds(2); // Pause for a moment
        std::cout << "\n*** YOU ARE DEAD ***\n"; // Notify player death
        sleepSeconds(3); // Pause for a moment
        std::cout << "\nYou awaken back in the ROOT PASSAGE...\n"; // Notify player awakening
        sleepSeconds(2); // Pause for a moment            
        enterRootPassage(); // Return to root passage
        return; // Exit function
    } // End of denial choice
    if (choice == 1) { // Player admits seeking artifact
        clearScreen(); // Clear the screen
        std::cout << "Mage: Everyone here is searching for an artifact: the philosopher's stone.\n"; // Mage dialogue
        sleepSeconds(3); // Pause for a moment
        std::cout << "But they don't understand how terrifying this world is...\n"; // Mage dialogue
        sleepSeconds(2); // Pause for a moment
        std::cout << "\nMage: I am Ming-Lun Lee, lord of programming and audio,\n"; // Mage dialogue
        std::cout << "grandmaster of C++, and master of black magic.\n"; // Mage dialogue
        sleepSeconds(3); // Pause for a moment
        std::cout << "\nMage: I guard these tunnels, and I saw the creation of the artifact myself.\n"; // Mage dialogue
        sleepSeconds(3); // Pause for a moment
        std::cout << "\nMage: I will let you pass **if** you solve my riddle.\n"; // Mage dialogue
        sleepSeconds(2); // Pause for a moment
        std::cout << "Otherwise, you will die on the spot.\n"; // Mage dialogue
        sleepSeconds(2); // Pause for a moment
        std::cout << "Your corpse will wander these halls as an eternally hungry zombie.\n"; // Mage dialogue
        sleepSeconds(3); // Pause for a moment
        std::cout << "\nMage: Are you ready?\n"; // Mage dialogue
        sleepSeconds(1); // Pause for a moment
        std::cout << "\nYou: Yes, I am ready...\n"; // Player dialogue
        sleepSeconds(2); // Pause for a moment
        std::cout << "\nMage: Then listen carefully.\n"; // Mage dialogue
        sleepSeconds(2); // Pause for a moment
        std::cout << "\n\"I have a chest of fire,\n"; // Mage riddle
        std::cout << " and dead nations are born beneath my gaze.\n"; // Mage riddle
        std::cout << " I am of wisdom and death,\n"; // Mage riddle
        std::cout << " myth and ruin.\n"; // Mage riddle
        std::cout << " What am I?\"\n\n"; // Mage riddle
        sleepSeconds(3); // Pause for a moment
        std::cout << "Your answer:\n"; // Player prompt
        std::cout << "  (1) A dragon?\n"; // Option 1
        std::cout << "  (2) ...Something else?\n"; // Option 2
        std::cout << "> "; // Input prompt
        if (!(std::cin >> choice)) { // Get player choice
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            clearScreen(); // Clear the screen
            std::cout << "Mage: Wrong.\n"; // Mage dialogue
            sleepSeconds(1); // Pause for a moment
            std::cout << "You have failed.\n"; // Player notification
            sleepSeconds(1); // Pause for a moment
            std::cout << "Your soul is forfeit.\n"; // Player notification
            sleepSeconds(1); // Pause for a moment
            std::cout << "\n*** YOU ARE DEAD ***\n"; // Player notification
            sleepSeconds(3); // Pause for a moment
            std::cout << "\nYou awaken back in the ROOT PASSAGE...\n"; // Player notification
            sleepSeconds(2); // Pause for a moment
            enterRootPassage(); // Return to root passage
            return;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear input buffer
        if (choice == 1) {
            clearScreen();
            std::cout << "Mage: That is correct.\n"; // Mage dialogue
            sleepSeconds(2); // Pause for a moment
            std::cout << "You have proven yourself worthy.\n"; // Player notification
            sleepSeconds(2); // Pause for a moment
            std::cout << "Take this healing potion.\n"; // Player notification
            sleepSeconds(1); // Pause for a moment
            std::cout << "\n[Healing Potion added to inventory]\n"; // Player notification
            sleepSeconds(2); // Pause for a moment
            std::cout << "\nMage: Now go. The next level awaits.\n"; // Mage dialogue
            sleepSeconds(3); // Pause for a moment
            enterForgottenTunnels(); // Proceed to Forgotten Tunnels
            return; // Exit function
        } else { // Wrong answer
            clearScreen(); // Clear the screen
            std::cout << "Mage: Wrong.\n"; // Mage dialogue
            sleepSeconds(1); // Pause for a moment
            std::cout << "You have failed.\n"; // Player notification
            sleepSeconds(1); // Pause for a moment
            std::cout << "Your soul is forfeit.\n"; // Player notification
            sleepSeconds(1); // Pause for a moment
            std::cout << "\n*** YOU ARE DEAD ***\n"; // Player notification
            sleepSeconds(3); // Pause for a moment
            std::cout << "\nYou awaken back in the ROOT PASSAGE...\n"; // Player notification
            sleepSeconds(2); // Pause for a moment
            enterRootPassage(); // Return to root passage
            return; // Exit function
        } // End of else block
    } // End of mage encounter function
} // End of mageEncounter function
void enterRootPassage() { // Function to enter Root Passage
    clearScreen(); // Clear the screen
    sleepSeconds(2); // Pause for a moment
    std::cout << "You squeeze past the blackened roots and step into the first tunnel.\n"; // Player notification
    sleepSeconds(2); // Pause for a moment 
    std::cout << "In the distance, you see a mage silently staring at you.\n"; // Player notification
    sleepSeconds(2); // Pause for a moment
    std::cout << "You approach him...\n"; // Player notification
    sleepSeconds(3); // Pause for a moment
    mageEncounter(); // Start mage encounter
} // End of enterRootPassage function
void enterForgottenTunnels() { // Function to enter Forgotten Tunnels
    clearScreen(); // Clear the screen
    std::cout << "You descend into the Forgotten Tunnels. The air is stale.\n"; // Player notification
    sleepSeconds(2); // Pause for a moment
    std::cout << "A faint scuttling echoes ahead... A goblin scout emerges!\n"; // Player notification
    sleepSeconds(2); // Pause for a moment
    goblinBattle(); // Start goblin battle
    sleepSeconds(2); // Pause for a moment
    std::cout << "\n)"; // Player notification
    sleepSeconds(1); // Pause for a moment
    std::cout <<"You've made it through and are moving on...\n"; // Player notification
    sleepSeconds(2); // Pause for a moment
    showMap(); // Show map
} // End of enterForgottenTunnels function
void enterChamberOfWhispers() { // Function to enter Chamber of Whispers
    clearScreen(); // Clear the screen
    sleepSeconds(2); // Pause for a moment
    std::cout << "You enter the Chamber of Whispers.\n"; // Player notification
    sleepSeconds(2); // Pause for a moment
    std::cout << "Echoing voices surround you from all directions...\n"; // Player notification
    sleepSeconds(2); // Pause for a moment
    std::cout << "\"Who dares enter our sacred chamber?\" the voices cry.\n"; // Player notification
    sleepSeconds(2); // Pause for a moment
    std::cout << "\nYou see a spectral skeleton rise from the ground!\n"; // Player notification
    sleepSeconds(2); // Pause for a moment
    skeletonBattle(); // Start skeleton battle
    sleepSeconds(2); // Pause for a moment
    std::cout << "The whispers fade... You may proceed.\n"; // Player notification
    sleepSeconds(2); // Pause for a moment
    showMap(); // Show map
} // End of enterChamberOfWhispers function
void enterSanctum() { // Function to enter Sanctum of the Artifact
    clearScreen(); // Clear the screen
    sleepSeconds(2); // Pause for a moment
    std::cout << "A vast cavern opens before you, lit by a sickly, pulsating light.\n"; // Player notification
    sleepSeconds(3); // Pause for a moment
    std::cout << "At the center, upon a jagged altar, rests the Artifact of Kirkwood.\n"; // Player notification
    sleepSeconds(3); // Pause for a moment
    std::cout << "\nYou tighten your grip on your sword and step forward...\n"; // Player notification
    sleepSeconds(2); // Pause for a moment
    runDungeon(); // Start dungeon maze
} // End of enterSanctum function
void printMenu() { // Function to print the main menu
    std::cout << "                    +----------------------------------------+\n";
    sleepSeconds(1);
    std::cout << "                    |     Part 1. The Beginning of the End   |\n";
    sleepSeconds(1);
    std::cout << "                    +----------------------------------------+\n";
    sleepSeconds(1);
    std::cout << "                    |              1. Continue               |\n";
    sleepSeconds(1);
    std::cout << "                    |              0. Exit                   |\n";
    sleepSeconds(1);
    std::cout << "                    +----------------------------------------+\n";
    sleepSeconds(1);
    std::cout << "> "; // Input prompt
} // Function to print the main menu
int getMenuChoice() { // Function to get menu choice
    int choice; // Player choice
    printMenu(); // Print the menu
    while (!(std::cin >> choice) || (choice != 0 && choice != 1)) { // Get player choice
        std::cout << "Invalid choice. Press 1 to continue or 0 to exit.\n"; // Notify invalid choice
        std::cout << "> "; // Input prompt
        while (std::cin.get() != '\n'); // Clear input buffer
    } // End of input validation
    return choice; // Return player choice
} // Function to get menu choice
void handleOrderChoice(void) {
    int choice;  // Player choice
    std::cout << "\n\n[1] \"Not for me... I need to study for my C++ exam.\"\n"; // Option 1
    std::cout << "[2] \"Understood... what should I do next?\"\n"; // Option 2
    std::cout << "> "; // Input prompt
    while (!(std::cin >> choice) || (choice != 1 && choice != 2)) { // Get player choice
        std::cout << "Please type 1 or 2.\n> "; // Notify invalid choice
        clearInputBuffer(); // Clear input buffer
    } // End of input validation
    clearInputBuffer(); // Clear input buffer after valid input
    if (choice == 1) { // Player chooses to study
        std::cout << "\nYou: \"Not for me... I need to study for my C++ exam.\"\n"; // Player response
        sleepSeconds(2); // Pause for a moment
        std::cout << "The capitan sighs deeply.\n";// Capitan response
        sleepSeconds(2); // Pause for a moment
        std::cout << "\"Very well, Mike. Your future and the artifact will have to wait.\"\n"; // Capitan response
        sleepSeconds(2); // Pause for a moment
        std::cout << "\nGAME OVER: You chose to study.\n"; // Game over message
    } else {
        std::cout << "\nYou: \"Understood... what should I do next?\"\n"; // Player response
        sleepSeconds(2); // Pause for a moment
        std::cout << "The capitan nods.\n"; // Capitan response
        sleepSeconds(2); // Pause for a moment
        std::cout << "\"Prepare yourself. The journey starts at noon.\"\n"; // Capitan response
        sleepSeconds(2); // Pause for a moment
        std::cout << "You gather all your gear:\n"; // Player action
        sleepSeconds(2); // Pause for a moment
        std::cout << "\n"; // Newline for spacing
        std::cout << "A sword that has been through many battles. A loyal friend and companion.\n"; // Player action
        sleepSeconds(2); // Pause for a moment
        std::cout << "\n"; // Newline for spacing
        std::cout << "A shield that has protected you from giants, ogres, and trolls.\n"; // Player action
        std::cout << "\n"; // Newline for spacing
        sleepSeconds(2); // Pause for a moment
        std::cout << "And a couple of health potions...\n"; // Player action
        sleepSeconds(2); // Pause for a moment
std::cout << "            ......   ......    .....    ......    .....    ......   ......    .....    ......   ......    ..\n"; // ASCII art line 1
std::cout << "    ......   ......    .....    ......    .....    ......   ......    .....    ......   ......    ..\n";
std::cout << ".................................................-..................................................\n";
std::cout << ".....    ......   ......    .....    ......    -+##=.   ......   ......    .....    ......   ...... \n";
 std::cout << ".....    ......   ......    .....    ......  .*%##%%#.  ......   ......    .....    ......   ...::. \n";
std::cout << "    ......   ......    .....    ......    .::::*%##%-....   ......    .....    ......   ......... ..\n";
std::cout << "    ......   ......    .....    ......   ...:...%#%-.....   ......    .....    ......   ....:...  ..\n";
std::cout << "................................................%%%:.......................................:........\n";
std::cout << ".....    ......   ......    .....    ...::.    :%%%-    ......   ......    .....    ........ ...... \n";
std::cout << ".....    ......   ......    .....    ......    :%%%=    ......   ......    .....    ......   ...... \n";
std::cout << "    ......   ......    .....    ......    ......%@%+.....   ......    .....    ......   ......    ..\n";
std::cout << "    ......   ......    .....    ......    ......%@@+.....   ......    .....    ......   ......    ..\n";
std::cout << "    .......  ......    .....    ......    ......%@@*..... ........    .....    ......   ......    ..\n";
std::cout << ".....   .......   ......    .....    ......    :@@@+    ..::..   ......    .....    ......   ...... \n";
std::cout << ".....    ......   ......    .....    ......    :%@@-    ......   ......    .....    ......   ...... \n";
std::cout << "...............................................:@%%=................................................\n";
std::cout << "    ......   ......    .....    ...::.    ..:--+%#%#=--:.   ..:::.    .....    ......   ......    ..\n";
std::cout << "    ......   ......  ...:...    ..+%%*=+*#*#%%%%%*#%%%%#**#*++##%.    ..:::    ......   ......    ..\n";
std::cout << ".....    ......   ..:::.    ..... .##=......:=*%@#%%%=-.......*%=......... .....    ......   ...... \n";
std::cout << ".....    ......  ..::...    .....    ...... .#*%%%%%##+ ......   ....:..   .....    ......   ...... \n";
std::cout << "...............................................@@%%%+..............::...............................\n";
std::cout << "    ......   ....:.    .....    ......    .....%@%%%+....   ...... .  .....    ......   ......    ..\n";
std::cout << "    ......   ......    .....    ......    .....%@%%%+....   ......    .....    ......   ......    ..\n";
std::cout << "...............................................%@%%%+...............................................\n";
std::cout << ".....    ......   ......    .....    ......   .%@%%%+   ......   ......    .....    ......   ...... \n";
std::cout << ".....    ......   ......    ...:..   ......   .%@%%%=   ......   ......    ...............   ...... \n";
std::cout << "    ......   ......    .....   .......    .....#@%%%=....   ......    .....    ......   ......    ..\n";
std::cout << "    ......   ......    .....    ......    .....#@%#%=....   ......    .....    ......   ......    ..\n";
std::cout << "...............................................#@##%-...............................................\n";
std::cout << ".....    ......   ......    .....    ......    #@###-   ......   ......    .....    ......   ...... \n";
std::cout << ".....    ......   ......    .....    ......    #@###-   ......   ......    .....    ......   ...... \n";
std::cout << "    ......   ......    .....    ......    .....#@###=....   ......    .....    ......   ......  ....\n";
std::cout << "    ......   ......    .....    ......    ...::#@*##=....   ......    .....    ......   ...... .....\n";
std::cout << "...............................................#@###=...............................................\n";
std::cout << ".....    ......   ......    .....    ....:...  #@%%#-   ......   ......    .....    ..........:.... \n";
std::cout << ".....    ......   ......    .....    ...::.    #@%%#-   ......   ......    .....    ............... \n";
std::cout << "    ......   ......    .....    ......  .......#@%%#=....   ......    .....    ......   ......    ..\n";
std::cout << "    ......   ......    .....    ......    .....#@%%#=....   ......    .....    ......   ......    ..\n";
std::cout << "...............................................#@%%#=...............................................\n";
std::cout << ".....    ......   ......    .....    ......    #@%%#-   ......   ......    .....    ......   ...... \n";
std::cout << ".....   ..:....   ......    .....    ......    #@%%#=   ..::..   ......    .....    ......   ...... \n";
std::cout << "    ......   ......    .....    ......    .....#@%%#=....   ......    .....    ......   ......    ..\n";
std::cout << "    ......   ......    .....    ......    .....#@%%#=....   ......    .....    ......   ......    ..\n";
std::cout << "    ......   ......    .....    ......    .....#@%%#=....   ......    .....    ......   ......    ..\n";
std::cout << ".....    ......   .......   .....    ......   .#@%%#=   ......   ...... ........    ......   ...... \n";
std::cout << ".....    ......   ...::..   .....    ......   .%@%%#=   ......   ...............    ......   ...... \n";
std::cout << "...............................................%@%%#=...............................................\n";
std::cout << "    ......   ......... .....    ......    .....%@%%*=....   ...... ........    ......   ......    ..\n";
std::cout << "    ......   ...::..   .....    ......    .....#@%#*-....   ...............    ......   ......    ..\n";
std::cout << ".....    ......  .......    .....    ......    +@#+*.   ......   ......    .....    ......   ...... \n";
std::cout << ".....    ......   ......    .....    ......    :%#+:.   ......   ......    .....    ......   ...... \n";
std::cout << "................................................:*-.................................................\n";
std::cout << "    ......   ......    .....   .......    .....  ........   ......    .....    ......   ......    ..\n";
std::cout << "    ......   ......    .....  ...:....    .....    ......   ......    .....    ..:::.   ......    ..\n";
std::cout << ".....    ......   ......    .....    ......    .....    ......   ......    .....    ......   ...... \n";
std::cout << "You climb onto your black horse and set off as soon as the bell strikes 12.\n"; // Player action
sleepSeconds(2); // Pause for a moment
std::cout << "\nTwelve days passed...\n"; // Time passage
sleepSeconds(3); // Pause for a moment                                                                                                                                                                                   
std::cout << "           @    *##*    =+:          #     =+##@@@+**%     #                                         \n"; // ASCII art line 1
std::cout << "                @%%@%*+++*           %@*+*#%%##* %+**+   *#                                          \n";
std::cout << "               % ##    ***+:     ## =*##%@   %@@@%*@  @%%%%                                          \n";
std::cout << "           # #*#*****# +**#%#+ *##%*+#**       @ *%    @@ @@                                         \n";
std::cout << "         %##++*%%% *#@%####@#*##*% =*@***   #%%#*+*#####   @@                                        \n";
std::cout << "           +*##%#-++  ##    ##%%#+++@#*%%++**###%+#     #           =                                \n";
std::cout << "             @**#.*#*  *    **#  %%@%%%%@@       %%     %@      #**#+   +*                           \n";
std::cout << "              %+**=++*++=    **#  @@@%# %#      ####    ++   =++**+%%  *#                            \n";
std::cout << "             *%% @%#**@@@%##****#  %%@@%# #    @%  **   +**++***##%#### #%@      #       *#          \n";
std::cout << "               @%##@##*     *#****##+*@@%  ##+     **+=+=**++*****+%%#%         #       *#           \n";
std::cout << "              %% *@  ##*%   +#+++#**#@@@ #***#      @+*%%++**#    *@%%         * %%    +#            \n";
std::cout << "             @   #%  ###+*##**+**#%@@@   +=+       *##****#%   ###%@ %%    #####%    =+             \n";
std::cout << "           ##    ***#%%@+=* **++** %@%*===+==*       ###%%@  %@@  @@@  %   +###**    +*%##%   +*#    \n";
std::cout << "             *++*%*%    +++**+===++*@%%#***##%#*     %%###               *#   ##+*+==+     =+#%@     \n";
std::cout << "              %%%**++   %@@@*#%%%##**#@@@@@@%%%       %##**            ***+#@@@%*#@@@%#*#%%    @     \n";
std::cout << "             @      ****%@%*#%## @%@%#****#@@@%      =*##** =+=++===    *%     ##%                   \n";
std::cout << "                        %%@@ %%  @    %#**#%@@%%     +###*++***#####*++*@#*    +#%                   \n";
std::cout << "                      #@   @@%%%        ##*%%@%#  ==#%  %+=+#%@@@@@@@@%#*+#*+**%@                    \n";
std::cout << "                   @##    %@  % @         @@@@%%##%@   ++**#%%         @@@%#%#%++-:-  +# *#          \n";
std::cout << "                          #  @             *%%@@%##  +++**#%%@%#%          @@@%%#*##*+ **            \n";
std::cout << "                          %@                 %%%%%%######%@     *=+#           *#    *+*+            \n";
std::cout << "                                             *###%%%%##%%@   +*#*===-          +* ##=+*%*+=          \n";
std::cout << "                                             ++#*#%%##%  ##*++#%@##*+++++=     **+#%  +== #+=        \n";
std::cout << "                                             +***####%% +**#%%@@   @%%##*+===+++#** =+*.#**%#+       \n";
std::cout << "                                            =+**#####%**#%@@             %%#*%@ -+*#%+%@##  =+       \n";
std::cout << "                                           +*****####%@@@@                 %##*+=* +#%@ #  #=+       \n";
std::cout << "                                           +*****##%@@                      #@%######     ===#       \n";
std::cout << "                                           **+*#%#%%%                    %@#  %%%  @@#*++* ++        \n";
std::cout << "                                            **#**#*##                     =  +*  @@    %%   +        \n";
std::cout << "                                             *#*#####                        ..             =*       \n";
std::cout << "                                            ++#*##%%%                                       *        \n";
std::cout << "                                            +***##%%#                                                \n";
std::cout << "                                            +#**##%%                                                 \n";
std::cout << "                                           =**+#*#%%                                                 \n";
std::cout << "                                          +**##*#%%                                                  \n";
std::cout << "                                          #*****#%%                                                  \n";                                                                          
std::cout << "You find yourself in the lands of Kirkwood, while your homeland is riddled with decay...\n"; // Narrative
sleepSeconds(2); // Pause for a moment
std::cout << "\nYou sigh heavily and look at the tree, whose bark has turned black with death,\n"; // Narrative
std::cout << "and beneath the tree is a door that leads to the underground.\n"; // Narrative 
sleepSeconds(3); // Pause for a moment
std::cout << "\n\"You need to go there,\" said a strange, quiet, almost whispering voice.\n"; // Narrative
sleepSeconds(2); // Pause for a moment
std::cout << "When you lit the torch, you saw endless tunnels...\n"; // Narrative
sleepSeconds(3);    // Pause for a moment
std::cout << "You open the map...\n"; // Narrative
sleepSeconds(2); // Pause for a moment
showMap(); // Show map
sleepSeconds(2); // Pause for a moment
std::cout << "\nYou decide to start with the ROOT PASSAGE.\n"; // Narrative
sleepSeconds(2); // Pause for a moment
enterRootPassage(); // Enter Root Passage
    } // End of else block
} // End of handleOrderChoice function
void clearInputBuffer() { // Function to clear input buffer
    std::cin.clear(); // Clear error flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
} // End of clearInputBuffer function
void startGame() { // Function to start the game
    int choice = getMenuChoice(); // Get player menu choice
    if (choice == 0) { // Player chooses to exit
        std::cout << "\nExiting the game...\n"; // Notify exiting
        return; // Exit function
    } // End of exit choice
    if (choice == 1) { // Player chooses to continue
        std::cout << "\nYou chose to continue...\n"; // Notify continuation
sleepSeconds(3); // Pause for a moment
std::cout << "The Castle of the Snowy Lands of King Ostfall.\n"; // Narrative
sleepSeconds(3); // Pause for a moment
std::cout << "\n"; // Newline for spacing
sleepSeconds(1); // Pause for a moment
std::cout << "You approach a large knight's courtyard at the court and meet the captain of your squad.\n"; // Narrative
sleepSeconds(3); // Pause for a moment
std::cout << "\n"; // Newline for spacing
sleepSeconds(2); // Pause for a moment
std::cout << "Mike, you're going on a mission to the scorched lands of Kirkland.\n"; // Narrative
sleepSeconds(1); // Pause for a moment
std::cout << "Since you're the only one who was born and raised there,\n"; // Narrative
sleepSeconds(2); // Pause for a moment
std::cout << "You know the land better than any scout we have.\n"; // Narrative
sleepSeconds(2); // Pause for a moment
std::cout << "I know how this sounds... but you must retrieve the artifact for the king.\n"; // Narrative
sleepSeconds(2); // Pause for a moment
std::cout << "In return, you will receive a substantial reward.\n"; // Narrative
sleepSeconds(2); // Pause for a moment
std::cout << "\nDid you understand the order?\n"; // Captain's question
handleOrderChoice(); // Handle player order choice
    } // End of continue choice
} // End of startGame function
int main(int argc, char *argv[]) { // Main function
srand((unsigned)time(NULL)); // Seed random number generator
std::cout << "- Strange Voice: Wake up...\n"; // Strange voice narrative
sleepSeconds(3); // Pause for a moment
std::cout << "- Strange Voice: New day new life...\n"; // Strange voice narrative
sleepSeconds(3); // Pause for a moment
sleepSeconds(2); // Pause for a moment
std::cout << "."; // Ellipsis for dramatic effect
sleepSeconds(2);  // Pause for a moment
std::cout << "."; // Ellipsis for dramatic effect
sleepSeconds(2); // Pause for a moment
std::cout << "."; // Ellipsis for dramatic effect
sleepSeconds(2); // Pause for a moment
std::cout << ".\n"; // Ellipsis for dramatic effect
sleepSeconds(2); // Pause for a moment
std::cout << "**You wake up in a sweat from the voice that has tormented you for years...**\n"; // Narrative
sleepSeconds(4); // Pause for a moment
std::cout << "**The sun's rays penetrate the fogged windows like a sword cutting through flesh.**\n"; // Narrative
sleepSeconds(4); // Pause for a moment
std::cout << "**You remember the battles at Westwald...**\n"; // Narrative
sleepSeconds(3); // Pause for a moment
std::cout << "**The screams of your fallen comrades echo in your mind...**\n"; // Narrative
std::cout << "\n"; // Newline for spacing
sleepSeconds(3); // Pause for a moment
std::cout << "."; // Ellipsis for dramatic effect
sleepSeconds(3); // Pause for a moment
std::cout << "."; // Ellipsis for dramatic effect
sleepSeconds(3); // Pause for a moment
std::cout << "."; // Ellipsis for dramatic effect
std::cout << "                                                       WELCOME TO                                              \n";
std::cout << "\n"; // Newline for spacing
sleepSeconds(1); // Pause for a moment
std::cout << " ,ggggggggggg,              ,ggg,   ,ggg,         ,gg   ,ggggggg,  ,ggg, ,ggggggg,     d8'   ,gg,  \n";
std::cout << " dP   88      Y8,           dP  8I dP  Y8a       ,8P  ,dP      Y8bdP  Y8,8P     Y8b   d8'   i8  8i \n";
std::cout << "Yb,  88      `8b          dP   88 Yb,  88       d8   d8     a  Y8Yb, `8dP'     `88  \"\"     `8,,8'  \n";
std::cout << " `   88      ,8P         dP    88      88       88   88      Y8P  `   88       88          `88   \n";
std::cout << "     88aaaad8P         ,8     88      88       88    8baaaa          88        88          dP 8,  \n";
std::cout << "     88\"\"\"\"Yb,          d88888888      I8       8I  ,d8P\"\"\"\"          88        88         dP' `8a \n";
std::cout << "     88      8b   __   ,8     88      `8,     ,8   d8                88        88        dP    `Yb \n";
std::cout << "     88       8i dP  ,8P      Y8       Y8,   ,8P   Y8,               88        88    _ ,dP'     I8\n";
std::cout << "     88       Yb,Yb,_,dP       `8b,      Yb,_,dP    `Yba,,_____,      88        Y8,    888,,____,dP\n";
std::cout << "    88        Y8  Y8P          `Y8        Y8P       `Y8888888      88        `Y8   a8P Y88888P  \n";
std::cout << "\n";
std::cout << "   _,gggggg,_               ,ggg,  ,ggggggggggggggg ,ggg,        gg                                 \n";
std::cout << " ,d8P  d8P Y8b,            dP  8I dP      88       dP  Y8b       88                                 \n";
std::cout << ",d8'   Y8    8b,dP        dP   88 Yb,_    88       Yb, `88       88                                 \n";
std::cout << "d8'    `Ybaaad88P'       dP    88  `      88        `  88       88                                 \n";
std::cout << "8P       `    Y8        ,8'    88         88            88aaaaaaa88                                 \n";
std::cout << "8b            d8        d88888888         88            88       88                                 \n";
std::cout << "Y8,          ,8P  __   ,8      88         88            88       88                                 \n";
std::cout << "`Y8,        ,8P' dP   ,8P      Y8   gg,   88            88       88                                 \n";
std::cout << " `Y8b,,__,,d8P   Yb,_,dP       `8b,   Yb,,8P            88       Y8,                                \n";
std::cout << "  ` Y8888P '      Y8P          `Y8     Y8P'            88       `Y8                                \n";
std::cout << "\n"; // Newline for spacing
sleepSeconds(2); // Pause for a moment
startGame(); // Start the game
    return 0; // End of main function
} // End of main function