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
    num_range_from.setDescription("Tells from which number to start");
    num_range_from.setShortForm('s');
    num_range_from.setLongForm("num-range-from");
    num_range_from.setType("numeric");

    Param num_range_to = Param();
    num_range_to.setDescription("Tells the maximum number to be used in the range");
    num_range_to.setShortForm('w');
    num_range_to.setLongForm("mix-words");

    Param lower_case = Param();
    lower_case.setDescription("Converts every character to lower case: BALL -> [bALL, BaLL, BAlL, BALl, baLL, BalL, BAll, balL, Ball, ball]");
    lower_case.setShortForm('l');
    lower_case.setLongForm("lower-case");

    Param upper_case = Param();
    upper_case.setDescription("Converts every character to upper case: ball -> [Ball, bAll, baLl, balL, BAll, bALl, baLL, BALl, bALL, BALL]");
    upper_case.setShortForm('u');
    upper_case.setLongForm("upper-case");

    Param mix_case = Param();
    mix_case.setDescription("Combines upper and lower cases in every possible way");
    mix_case.setShortForm('m');
    mix_case.setLongForm("mixed-case");

    Param add_numbers_beginning = Param();
    add_numbers_beginning.setDescription("Adds leading numbers to the beginning of the word. Requires the params \"num-range-from\" and \"num-range-to\": BALL -> [0BALL, 1BALL, 2BALL, 3BALL, 4BALL, ...]");
    add_numbers_beginning.setShortForm('n');
    add_numbers_beginning.setLongForm("leading-numbers");
    add_numbers_beginning.requires(num_range_from);
    add_numbers_beginning.requires(num_range_to);

    Param add_numbers_end = Param();
    add_numbers_end.setDescription("Adds trailing numbers to the end of the word. Requires the params \"num-range-from\" and \"num-range-to\": BALL -> [BALL0, BALL1, BALL2, BALL3, BALL4, ...]");
    add_numbers_end.setShortForm('N');
    add_numbers_end.setLongForm("trailing-numbers");
    add_numbers_end.requires(num_range_from);
    add_numbers_end.requires(num_range_to);

    Param add_numbers_in_between = Param();
    add_numbers_in_between.setDescription("Adds numbers between each letter. Requires the params \"num-range-from\" and \"num-range-to\": BALL -> [B0ALL, BA0LL, BAL0L, B1ALL, BA1LL, ...]");
    add_numbers_in_between.setShortForm('n');
    add_numbers_in_between.setLongForm("numbers-beginning");
    add_numbers_in_between.requires(num_range_from);
    add_numbers_in_between.requires(num_range_to);

    Param mix_words = Param();
    mix_words.setDescription("Mixes words from the source file: [hello, bye, red] -> [hellobye, byehello, hellored, redhello, byered, redbye]");
    mix_words.setShortForm('w');
    mix_words.setLongForm("mix-words");

    Param source_file = Param();
    source_file.setDescription("Tells which file has the words that will be permuted.");
    source_file.setShortForm('f');
    source_file.setLongForm("source");

    Param target_file = Param();
    target_file.setDescription("Tells which file will store the permuted words.");
    target_file.setShortForm('t');
    target_file.setLongForm("target");

    std::vector<std::string> arguments(argv + 1, argv + argc);
    Options main_options = Options();
    main_options.addParam(lower_case);
    main_options.addParam(upper_case);
    main_options.addParam(mix_case);
    main_options.addParam(add_numbers_beginning);
    main_options.addParam(add_numbers_end);
    main_options.addParam(add_numbers_in_between);
    main_options.addParam(mix_words);
    main_options.addParam(source_file);
    main_options.addParam(target_file);
    main_options.registerArgs(arguments);

    // SUPER important
    std::locale::global(std::locale("sv_SE"));

    if (main_options.areParamsOk()) {
        Permuter myPermuter = Permuter();
        myPermuter.set_options(main_options);

        if (myPermuter.allGood() == true) {
            myPermuter.run();
        }

    }

    return 0;
}