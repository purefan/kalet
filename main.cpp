#include <cstring>
#include <iostream>
#include "permuter.cpp"
#include "param.cpp"
#include "options.cpp"


#define ENDL "\n"

using namespace std;


void showIntro() {
    cout << "Dictionary Generator v1.0 - by Miguel Espinoza - http://purefan.me" << ENDL;
    cout << ENDL;
    cout << "| This program takes words from a file and permutes them into a  |" << ENDL;
    cout << "| dictionary that can be used in brute force attacks.            |" << ENDL;
    cout << "| Intended only for educational purposes, do not use it for evil |" << ENDL;
    cout << "| By using this software you agree to release the author(s) from |" << ENDL;
    cout << "| any liability and responsibility.                              |" << ENDL;
    cout << ENDL;
}

/**
 * KISS Require 2 params
 */
int main(int argc, char *argv[]) {
    showIntro();

    Param num_range_from = Param();
    num_range_from.set_description("Tells from which number to start");
    num_range_from.set_short_form('s');
    num_range_from.set_long_form("num-range-from");
    num_range_from.set_type("numeric");

    Param num_range_to = Param();
    num_range_to.set_description("Tells the maximum number to be used in the range");
    num_range_to.set_short_form('w');
    num_range_to.set_long_form("mix-words");

    Param lower_case = Param();
    lower_case.set_description("Converts every character to lower case: BALL -> [bALL, BaLL, BAlL, BALl, baLL, BalL, BAll, balL, Ball, ball]");
    lower_case.set_short_form('l');
    lower_case.set_long_form("lower-case");

    Param upper_case = Param();
    upper_case.set_description("Converts every character to upper case: ball -> [Ball, bAll, baLl, balL, BAll, bALl, baLL, BALl, bALL, BALL]");
    upper_case.set_short_form('u');
    upper_case.set_long_form("upper-case");

    Param mix_case = Param();
    mix_case.set_description("Combines upper and lower cases in every possible way");
    mix_case.set_short_form('m');
    mix_case.set_long_form("mixed-case");

    Param add_numbers_beginning = Param();
    add_numbers_beginning.set_description("Adds leading numbers to the beginning of the word. Requires the params \"num-range-from\" and \"num-range-to\": BALL -> [0BALL, 1BALL, 2BALL, 3BALL, 4BALL, ...]");
    add_numbers_beginning.set_short_form('n');
    add_numbers_beginning.set_long_form("leading-numbers");
    add_numbers_beginning.requires(num_range_from);
    add_numbers_beginning.requires(num_range_to);

    Param add_numbers_end = Param();
    add_numbers_end.set_description("Adds trailing numbers of the word. Requires the params \"num-range-from\" and \"num-range-to\": BALL -> [BALL0, BALL1, BALL2, BALL3, BALL4, ...]");
    add_numbers_end.set_short_form('N');
    add_numbers_end.set_long_form("trailing-numbers");
    add_numbers_end.requires(num_range_from);
    add_numbers_end.requires(num_range_to);

    Param add_numbers_in_between = Param();
    add_numbers_in_between.set_description("Adds numbers between each letter. Requires the params \"num-range-from\" and \"num-range-to\": BALL -> [B0ALL, BA0LL, BAL0L, B1ALL, BA1LL, ...]");
    add_numbers_in_between.set_short_form('n');
    add_numbers_in_between.set_long_form("numbers-beginning");
    add_numbers_in_between.requires(num_range_from);
    add_numbers_in_between.requires(num_range_to);

    Param mix_words = Param();
    mix_words.set_description("Mixes words from the source file: [hello, bye, red] -> [hellobye, byehello, hellored, redhello, byered, redbye]");
    mix_words.set_short_form('w');
    mix_words.set_long_form("mix-words");

    Param source_file = Param();
    source_file.set_description("Tells which file has the words that will be permuted.");
    source_file.set_short_form('f');
    source_file.set_long_form("source");

    Param target_file = Param();
    target_file.set_description("Tells which file will store the permuted words.");
    target_file.set_short_form('t');
    target_file.set_long_form("target");

    std::vector<std::string> arguments(argv + 1, argv + argc);
    Options main_options = Options();
    main_options.registerParams(arguments);
    main_options.add_param(lower_case);
    main_options.add_param(upper_case);
    main_options.add_param(mix_case);
    main_options.add_param(add_numbers_beginning);
    main_options.add_param(add_numbers_end);
    main_options.add_param(add_numbers_in_between);
    main_options.add_param(mix_words);

    // SUPER important
    std::locale::global(std::locale("sv_SE"));

    if (main_options.ok) {
        Permuter myPermuter = Permuter();
        myPermuter.set_options(main_options);

        if (myPermuter.allGood() == true) {
            myPermuter.run();
        }

    }
    std::string sourcePath;
    std::string targetPath;

    if (argc > 1) {
        sourcePath = argv[1];
    } else {
        cout << "1. Path to a file with common words to permute: ";
        getline(cin, sourcePath);
    }

    if (argc > 2) {
        targetPath = argv[2];
    } else {
        cout << "2. Path to the target file: ";
        getline(cin, targetPath);
    }


    return 0;
}