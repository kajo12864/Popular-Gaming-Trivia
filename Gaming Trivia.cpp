/*Developer: Kaylee A. Jones & Alexander Griego
 * Class: COP 2006-13969, Spring 2024
 * Date: 3/26/2024
 * Description: Uses random function to pick a random string out of a table.
 * LOGS:
 * 3/29/2024 - Switched the random system from randomly picking a position in a shrinking vector each question to
 * shuffling the entire vector before the quiz begins.
 * 4/2/2024 - Added support for multiple quizzes being taken, giving a score at the end of the quiz, & error handling.
 * 4/3/2024 - Added more quiz questions for the additional quizzes
 * 4/4/2024 - Completed adding quiz questions, fixed an issue with scores where they would not properly reset.
 * 4/18/2024 - Updated the error handler to be more flexible in use case (function can now specify lower & upper
 * bounds as parameters)
 * 4/19/2024 - Added input and support for allowing the player to choose how many questions they will be asked in a
 * quiz.
 * 4/21/2024 - Created a new quiz type that includes questions from all quizzes.
 * 4/22/2024 - Adjusted quiz questions to make it more apparent which game they are from (for the all-quizzes quiz)
 * SOURCES:
 * https://www.geeksforgeeks.org/convert-cpp-string-to-uppercase/ --Read to support user inputting lowercase letters
 * for answers.
 * https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector --Read for assistance in shuffling a
 * vector's contents.
 * https://stackoverflow.com/questions/33284483/how-to-use-cin-fail-in-c-properly --Read to learn how to use cin.fail()
*/

#include <iostream>
#include <string>
#include <vector> /*Used to create a vector that holds question objects, serving as a question bank.*/
#include <algorithm> /*Used to shuffle the vector containing quiz questions once a quiz begins.*/
#include <random> /*Used in conjunction with algorithm to shuffle the vector.*/
/*Clears the input if it is not the correct data type to prevent a crash. Must be used in conjunction with another
 * handler to input a new, correct value. */
void incorrect_type_error_handler(){
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    };
};
/*Unexpected input handler, activates when an invalid test or questions number is entered*/
int errored_input_handler(int entered_num, int lower_bound, int upper_bound){
    do {
        std::cout << "Please enter a number in the range of " << lower_bound << "-" << upper_bound << ": \n";
        std::cin >> entered_num;
        if (std::cin.fail()) {
            incorrect_type_error_handler();
        };
    }while(entered_num < lower_bound or entered_num > upper_bound);
    return entered_num;
}

/*Class type that can hold information pertaining to quiz questions*/
class question{
public:
    std::string prompt; /*Contains the trivia question being asked*/
    char answer = '0'; /*Contains A, B, C, or D which corrosponds to the correct answer*/
    std::string choices; /*Contains the four answer choices*/
};


/*MAIN BEGINS*/
int main() {
    /*Program title*/
    std::cout << "== GAMING TRIVIA ==" << std::endl;
    /*Program description*/
    std::cout << "There are four quizzes of different games and a quiz ''mash-up'' if you would like to be quizzed on"
                 " all four games. Try to get at least half of the quiz correct to pass!\n"
    << std::endl;
    /* INITIALIZATION --------------------------------------------------------------------------------------*/
    /*Setting up the random seed so questions are in a different order every run*/
    auto rd = std::random_device {}; /*Sets up the random seed*/
    auto srand = std::default_random_engine { rd() };
    /*A variable that the controls main while loop so users can choose to take another quiz after finishing a quiz*/
    bool continue_val = true;
    /*Variable that holds the response given by the user to a trivia question*/
    char given_answer = 'O';
    /*User response to whether the main loop should terminate or continue*/
    char continue_prompt;
    /*User input for which quiz they wish to take.*/
    int quiz_choice = 0;

    /* QUESTIONS LIST --------------------------------------------------------------------------------------*/
    /*Defines questions for the Terraria quiz*/
    question terraria_q1;
    terraria_q1.prompt = "What do you need to craft Terraria's Gold Crown?\n";
    terraria_q1.choices = " A. Gold ore and ruby \n B. Gold bars and sapphire \n C. Gold bars and jade \n D. Gold "
                          "bars and ruby";
    terraria_q1.answer = 'D';
    question terraria_q2;
    terraria_q2.prompt = "What can Terraria's Blue Berries be used for?\n";
    terraria_q2.choices = " A. Fruit Salad \n B. Blue Dye \n C. Mulch \n D. Sapphire";
    terraria_q2.answer = 'B';
    question terraria_q3;
    terraria_q3.prompt = "What item summons the Terraria's Eye of Cthulhu?\n";
    terraria_q3.choices = " A. Suspicious Looking Eye \n B. Cthulhu's Sigil \n C. Evil Eye \n D. Dubious Eyeball";
    terraria_q3.answer = 'A';
    question terraria_q4;
    terraria_q4.prompt = "What boss unlocks Terraria's Hard Mode?\n";
    terraria_q4.choices = " A. Wall of Flesh \n B. Duke Fishron \n C. Moon Lord \n D. King Slime";
    terraria_q4.answer = 'A';
    question terraria_q5;
    terraria_q5.prompt = "Which of these is NOT an ore in Terraria?\n";
    terraria_q5.choices = " A. Platinum \n B. Lead \n C. Aluminum \n D. Tungsten";
    terraria_q5.answer = 'C';
    question terraria_q6;
    terraria_q6.prompt = "What is the final boss of Terraria?\n";
    terraria_q6.choices = " A. Cthulhu \n B. Wall of Flesh \n C. Moon Lord \n D. Empress of Light";
    terraria_q6.answer = 'C';
    question terraria_q7;
    terraria_q7.prompt = "What is NOT a feature in Terraria?\n";
    terraria_q7.choices = " A. Golfing \n B. Basketball \n C. Fishing \n D. Capture the Flag";
    terraria_q7.answer = 'B';
    question terraria_q8;
    terraria_q8.prompt = "What enrages Terraria's Empress of Light?\n";
    terraria_q8.choices = " A. Fighting her at night \n B. Leaving the Hallow \n C. Attacking rabbits \n D. Going "
                          "underground";
    terraria_q8.answer = 'B';
    question terraria_q9;
    terraria_q9.prompt = "Which of these is NOT a possible town member from Terraria?\n";
    terraria_q9.choices = " A. Golfer \n B. Santa Claus \n C. Wizard \n D. Batter";
    terraria_q9.answer = 'D';
    question terraria_q10;
    terraria_q10.prompt = "Which of these are hostile in Terraria?\n";
    terraria_q10.choices = " A. Scorpion \n B. Penguin \n C. Unicorn \n D. Enchanted Nightcrawler";
    terraria_q10.answer = 'C';
    /*Defines questions for the Super Mario 64 quiz*/
    question sm64_q1;
    sm64_q1.prompt = "How many Stars does it take to 100% complete Super Mario 64?\n";
    sm64_q1.choices = " A. 125 \n B. 120 \n C. 130 \n D. 115 ";
    sm64_q1.answer = 'B';
    question sm64_q2;
    sm64_q2.prompt = "How many stars can you possibly collect Super Mario 64's Bob-omb Battlefield?\n";
    sm64_q2.choices = " A. 7 \n B. 6 \n C. 5 \n D. 4";
    sm64_q2.answer = 'A';
    question sm64_q3;
    sm64_q3.prompt = "How many sections is Super Mario 64's Peach's Castle split into?\n";
    sm64_q3.choices = " A. 5 \n B. 2 \n C. 6 \n D. 3";
    sm64_q3.answer = 'D';
    question sm64_q4;
    sm64_q4.prompt = "Which is a popular fan theory for the etchings in Peach's Garden's podium in Super Mario 64?\n";
    sm64_q4.choices = " A. L is real 2401 \n B. Welcome to the Courtyard \n C. Beware of the Ghosts \n D. The 120 "
                      "Stars are Shimmering";
    sm64_q4.answer = 'A';
    question sm64_q5;
    sm64_q5.prompt = "Which is used as a Super Mario 64 Speedrunning term?\n";
    sm64_q5.choices = " A. Alternate Universes / AUs \n B. Backwards Long Jump (BLJs) \n C. Triple Long Jumps (TLJs) "
                      "\n "
                      "D. Forward-Back Jumps (FBJs)";
    sm64_q5.answer = 'B';
    question sm64_q6;
    sm64_q6.prompt = "Which was a popular Super Mario 64 hoax?\n";
    sm64_q6.choices = " A. Playable Link \n B. Peach's Castle was haunted \n C. The game actively analyzes player skill "
                      "\n D. Playable Luigi";
    sm64_q6.answer = 'D';
    question sm64_q7;
    sm64_q7.prompt = "How may someone defeat Super Mario 64's King Bob-omb?\n";
    sm64_q7.choices = " A. Tossing him \n B. Attacking him from the front \n C. Throwing Bob-ombs at him \n D. Luring"
                      " him in front of a boulder";
    sm64_q7.answer = 'A';
    question sm64_q8;
    sm64_q8.prompt = "What is the name of King Whomp's level in Super Mario 64?\n";
    sm64_q8.choices = " A. Concrete Kingdom \n B. Whomp Fortress \n C. Whomp's Domain \n D. Bob-omb Battlefield";
    sm64_q8.answer = 'B';
    question sm64_q9;
    sm64_q9.prompt = "How does Super Mario 64's story begin?\n";
    sm64_q9.choices = " A. Mario jumping from a pipe \n B. Princess Peach getting kidnapped \n C. A letter from "
                      "Princess Peach \n D. Mario driving to Peach's Castle";
    sm64_q9.answer = 'C';
    question sm64_q10;
    sm64_q10.prompt = "Which of these does not appear in Super Mario 64's Big Boo's Haunt?\n";
    sm64_q10.choices = " A. Mad Piano \n B. Ghost Snifit \n C. Bookend \n D. Mr. I";
    sm64_q10.answer = 'B';
    /*Defines questions for the Minecraft quiz*/
    question minecraft_q1;
    minecraft_q1.prompt = "Which is the most iconic fan-made horror character from Minecraft?\n";
    minecraft_q1.choices = " A. Notch \n B. Herobrine \n C. Night Dweller \n D. Entity 404 ";
    minecraft_q1.answer = 'B';
    question minecraft_q2;
    minecraft_q2.prompt = "How do you make a Potion of Poison in Minecraft?\n";
    minecraft_q2.choices = " A. 1. Create an Awkward Potion using 1 Netherwart.\n  2. Combine the Awkward Potion with"
                           " a Spider Eye to create the Potion of Poison."
                           "\n B. 1. Create a Mundane Potion using 1 Dirt.\n  2. Combine the Mundane Potion "
                           "with a Fermented Spider Eye to create the Potion of Poison."
                           "\n C. 1. Create a Mundane Potion using 1 Netherwart.\n  2. Combine the Mundane Potion "
                           "with a Fermented Spider Eye to create the Potion of Poison. \n D. "
                           "1. Create a Mundane Potion using 1 Spider Eye.\n  2. Combine the Mundane Potion "
                           "with a Nether Wart to create the Potion of Poison.";
    minecraft_q2.answer = 'C';
    question minecraft_q3;
    minecraft_q3.prompt = "What items are needed to craft Minecraft's Enchanting Table?\n";
    minecraft_q3.choices = " A. 4 Books, 1 diamond, and 2 obsidian blocks \n B. A. 2 Books, 4 diamond, and 2 obsidian"
                           " blocks \n C. 2 Books, 1 diamond, and 4 obsidian blocs \n D. 1 Book, 2 diamonds, and 4 "
                           "obsidian blocks";
    minecraft_q3.answer = 'D';
    question minecraft_q4;
    minecraft_q4.prompt = "What item causes Cows to follow the player in Minecraft?\n";
    minecraft_q4.choices = "A. Seeds \n B. Wheat \n C. Carrots \n D. Beetroots \n";
    minecraft_q4.answer = 'B';
    question minecraft_q5;
    minecraft_q5.prompt = "What resource from Minecraft's Nether must be collected to complete the game?\n";
    minecraft_q5.choices = " A. Magma Cream \n B. Ghast Tears \n C. Blaze Rods \n D. Nether Quartz";
    minecraft_q5.answer = 'C';
    question minecraft_q6;
    minecraft_q6.prompt = "What item leads players to the End portal in Minecraft?\n";
    minecraft_q6.choices = " A. Compass \n B. Portal Key \n C. Ender Pearl \n D. Eye of Ender";
    minecraft_q6.answer = 'D';
    question minecraft_q7;
    minecraft_q7.prompt = "Which boss is guarding an unusable portal and Minecraft's Dark City?\n";
    minecraft_q7.choices = " A. The Warden \n B. The Night Watcher \n C. The Guardian \n D. The Knight";
    minecraft_q7.answer = 'A';
    question minecraft_q8;
    minecraft_q8.prompt = "What inspired Creepers to be implemented into Minecraft?\n";
    minecraft_q8.choices = " A. An employee's suggestion \n B. A coding error while making Pigs \n C. A suggestion "
                           "from the creator's brother \n D. A method of getting explosive ingredients";
    minecraft_q8.answer = 'B';
    question minecraft_q9;
    minecraft_q9.prompt = "Which is the strongest material in Minecraft?\n";
    minecraft_q9.choices = " A. Gold \n B. Diamond \n C. Chainmail \n D. Netherite";
    minecraft_q9.answer = 'D';
    question minecraft_q10;
    minecraft_q10.prompt = "What is the 'final boss' of Minecraft?\n";
    minecraft_q10.choices = " A. Wither \n B. The Elder Guardian \n C. Ender Dragon \n D. The Wither Storm";
    minecraft_q10.answer = 'C';
    /*Defines questions for the Pokemon Scarlet & Violet quiz*/
    question pkmsv_q1;
    pkmsv_q1.prompt = "What is the name of the Fighting-type Flamingo introduced in Pokemon's Paldea region?\n";
    pkmsv_q1.choices = " A. Flamencigo \n B. Flamigo \n C. Flamlenco \n D. Sprixie";
    pkmsv_q1.answer = 'B';
    question pkmsv_q2;
    pkmsv_q2.prompt = "How many new dog Pokemon are introduced in Pokemon Scarlet & Violet?\n";
    pkmsv_q2.choices = " A. 2 \n B. 3 \n C. 4 \n D. 6";
    pkmsv_q2.answer = 'D';
    question pkmsv_q3;
    pkmsv_q3.prompt = "Which Pokemon is not obtainable without trading in Pokemon Violet?\n";
    pkmsv_q3.choices = " A. Armarouge \n B. Ceruledge \n C. Bagon \n D. Dreepy";
    pkmsv_q3.answer = 'A';
    question pkmsv_q4;
    pkmsv_q4.prompt = "Which Pokemon does not have a paradox variant?\n";
    pkmsv_q4.choices = " A. Jigglypuff \n B. Hariyama \n C. Tyranitar \n D. Absol";
    pkmsv_q4.answer = 'D';
    question pkmsv_q5;
    pkmsv_q5.prompt = "What Pokemon is never on any of Larry's teams?\n";
    pkmsv_q5.choices = " A. Staraptor \n B. Vigoroth \n C. Komala \n D. Altaria";
    pkmsv_q5.answer = 'B';
    question pkmsv_q6;
    pkmsv_q6.prompt = "What are the names of the academies in Pokemon Scarlet and Violet respectively?\n";
    pkmsv_q6.choices = " A. Naranja Academy and Uva Academy \n B. Orange Academy and Grape Academy \n C. Apfelsine "
                       "Academy and Traube Academy \n D. Apel'sin Academy and Vinograd Academy";
    pkmsv_q6.answer = 'A';
    question pkmsv_q7;
    pkmsv_q7.prompt = "What Tera Type is Iono's last Pokemon?\n";
    pkmsv_q7.choices = " A. Steel \n B. Ghost \n C. Electric \n D. Fairy";
    pkmsv_q7.answer = 'C';
    question pkmsv_q8;
    pkmsv_q8.prompt = "What region is Pokemon's Blueberry Academy in?\n";
    pkmsv_q8.choices = " A. Paldea \n B. Unova \n C. Johto \n D. Kanto";
    pkmsv_q8.answer = 'B';
    question pkmsv_q9;
    pkmsv_q9.prompt = "What type combination does the Pokemon Arboliva have?\n";
    pkmsv_q9.choices = " A. Grass \n B. Grass/Psychic \n C. Grass/Normal \n D. Grass/Fairy";
    pkmsv_q9.answer = 'C';
    question pkmsv_q10;
    pkmsv_q10.prompt = "How does the Pokemon Varoom evolve into Revavroom?\n";
    pkmsv_q10.choices = " A. A Fire Stone \n B. Trading \n C. A Steel Coat \n D. Level-up";
    pkmsv_q10.answer = 'D';


    /* CHOOSE A QUIZ SCREEN --------------------------------------------------------------------------------------*/
    /*Loops for  as long as user wants to continue taking quizzes*/
    while(continue_val) {
        /*Prompts the user on which quiz they would like to select, with instructions on what input they need to
         * enter.*/
    std::cout << "Which quiz would you like to take?: \n 1. MINECRAFT QUIZ \n 2. TERRARIA QUIZ \n 3. SUPER MARIO 64 "
                 "QUIZ \n 4. POKEMON SCARLET & VIOLET QUIZ \n 5. QUIZ MASH-UP (Questions from any combination of "
                 "quiz)\n"
                 "(Enter 1, 2, 3, 4, or 5)\n";
    /*Collects user input*/
    std::cin >> quiz_choice;
    /*Checks if the quiz choice is valid*/
    /*PART 1: Checks if the input is non-numeric*/
        if (std::cin.fail()) {
            incorrect_type_error_handler(); /*Clears the entered errored input*/
            quiz_choice = 0;
            quiz_choice = errored_input_handler(quiz_choice,1,5);
        };
    /*PART 2: Checks if the input is out of the asked range*/
    if(quiz_choice < 1 or quiz_choice > 5){
        /*The error handler will ask the user for a valid quiz choice until one is entered*/
        quiz_choice = errored_input_handler(quiz_choice,1,5);
    }
        /* Initializes a question bank. This bank will be filled with different questions based off of what quiz the
         * user selects*/
        std::vector <question> question_bank;
        /*Switch case that populates the question bank based off of the selected quiz*/
        switch(quiz_choice){
            case 1: /* Minecraft Quiz*/
                question_bank = {minecraft_q1,minecraft_q2,minecraft_q3,minecraft_q4,minecraft_q5,minecraft_q6,
                                 minecraft_q7,minecraft_q8,minecraft_q9,minecraft_q10};
                std::cout << "*X*X* MINECRAFT QUIZ *X*X*";
                break;
            case 2: /* Terraria Quiz*/
                question_bank = {terraria_q1,terraria_q2,terraria_q3,terraria_q4,terraria_q5,terraria_q6,
                                 terraria_q7,terraria_q8,terraria_q9,terraria_q10};
                std::cout << "*X*X* TERRARIA QUIZ *X*X*";
                break;
            case 3: /* Super Mario 64 Quiz*/
                question_bank = {sm64_q1,sm64_q2,sm64_q3,sm64_q4,sm64_q5,sm64_q6,sm64_q7,sm64_q8,sm64_q9,sm64_q10};
                std::cout << "*X*X* SUPER MARIO 64 QUIZ *X*X*";
                break;
            case 4: /* Pokemon Scarlet & Violet Quiz*/
                question_bank = {pkmsv_q1, pkmsv_q2,pkmsv_q3,pkmsv_q4,pkmsv_q5,pkmsv_q6,pkmsv_q7,pkmsv_q8,pkmsv_q9,
                                 pkmsv_q10};
                std::cout << "*X*X* POKEMON SCARLET & VIOLET QUIZ *X*X*";
                break;
            case 5: /* Quiz Mash-up */
                question_bank = {minecraft_q1,minecraft_q2,minecraft_q3,minecraft_q4,minecraft_q5,minecraft_q6,minecraft_q7,minecraft_q8,minecraft_q9,minecraft_q10,
                                 terraria_q1,terraria_q2,terraria_q3,terraria_q4,terraria_q5,terraria_q6,terraria_q7,terraria_q8,terraria_q9,terraria_q10,
                                 sm64_q1,sm64_q2,sm64_q3,sm64_q4,sm64_q5,sm64_q6,sm64_q7,sm64_q8,sm64_q9,sm64_q10,
                                 pkmsv_q1, pkmsv_q2,pkmsv_q3,pkmsv_q4,pkmsv_q5,pkmsv_q6,pkmsv_q7,pkmsv_q8,pkmsv_q9,pkmsv_q10};
                std::cout << "*X*X* QUIZ MASH-UP *X*X*";
                break;
        }
        /*Shuffles the question bank so question order is randomized*/
        std::shuffle(std::begin(question_bank), std::end(question_bank),srand);
        int num_questions = 0; /*Player-input number of questions they would like in their quiz*/
        std::cout << "\nHow many questions would you like for the quiz? \n(Input 1 to " << question_bank.size() << ")\n";
        std::cin >> num_questions;
        /*This handler checks if a character or other non-number is entered*/
        if (std::cin.fail()) {
            incorrect_type_error_handler(); /*Clears the entered errored input*/
            num_questions = 0;
            num_questions = errored_input_handler(num_questions,1,question_bank.size());
        };
        if(num_questions < 1 or num_questions > question_bank.size()){
            /*The error handler will ask the user for a valid number of questions until one is entered*/
            num_questions = errored_input_handler(num_questions,1,question_bank.size());
        }
        std::cout /*Divider*/
                <<"\n=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n";


        /*MAIN QUIZ LOOP --------------------------------------------------------------------------------------------*/
        /*Stores the amount of questions correctly answered on the quiz * 10 (functions as a score).*/
        int number_correct = 0;
        for (int quiz_iterator = 0; quiz_iterator < num_questions; quiz_iterator++) { /*10 Questions per Quiz*/
            /* Prints "#(Quiz Number). Quiz Question at position of the quiz_iterator"*/
            std::cout << "\n\n" << "#" << quiz_iterator+1 << ". " << question_bank[quiz_iterator].prompt;
            /* Prints the corresponding answer choices*/
            std::cout << question_bank[quiz_iterator].choices;
            /* Guides the user's input to only be A, B, C, or D*/
            std::cout << "\nPlease input A, B, C, or D: \n";
            std::cin >> given_answer;
            /* Automatically capitalizes the answer choice so lowercase A, B, C, and D are correctly recognized*/
            if (toupper(given_answer) == question_bank[quiz_iterator].answer) {
                std::cout << "Correct!\n";
                /*Adds to score*/
                number_correct += 10;
            } else {
                /*Displays to the user what the correct answer choice was*/
                std::cout << "Incorrect! The correct answer was " << question_bank[quiz_iterator].answer
                          << "\n ";
            }
            std::cout /*Divider between questions*/
            <<"=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n";
        }


        /*SCORE SCREEN --------------------------------------------------------------------------------------------*/
            std::cout << "\nYour score is " << number_correct << " out of " << num_questions * 10 << "!";
            if(number_correct >= num_questions * 5){ /*If the score is 50% correct or higher*/
                std::cout << "\n You passed!\n";
            }
            else{ /*If the # of answers correct is below 50%*/
                std::cout << "\n You didn't pass..\n";
            }
            /*Asks the user whether they would like to take the quiz again, which will bring them back to the quiz
             * selection dialog if true or terminates the program if false.*/
            std::cout << "\nWould you like to take another quiz? Enter Y (yes) or N (no)\n";
            std::cin >> continue_prompt;
            if (toupper(continue_prompt) == 'Y') {
                continue_val = true;
            } else {
                continue_val = false;
        }
    }
    return 0;
}
