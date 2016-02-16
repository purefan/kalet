# All purpose variables
compiler=g++
debugger=/usr/local/bin/gdb
project_root = ./
#   Where to store the binaries
target_folder=bin
target_bin=kalet
# Variables for production
# prod_lib := $(shell find lib/internal -name "*.cpp" ! -name "*test.cpp") main.cpp

# Variables for testing
#   Google test
# googletest_path = lib/external/googletest/googletest
# googletest_libs = $(googletest_path)/libgtest.a $(googletest_path)/libgtest_main.a

#   CppCheck
checker=/usr/local/Cellar/cppcheck/1.71/bin/cppcheck

test_lib := main_test.cpp
# sql_cipher = -Ilib/external/sqlcipher/src -Llib/external/sqlcipher -lsqlcipher

# Compiler flags
flags=-std=c++11 -Wall -Werror -g
# Compilation instructions
all:
	cd $(project_root)
	if [ -a $(target_folder)/${target_bin} ] ;  then  rm $(target_folder)/${target_bin} ;  fi;

	$(compiler) -Wall -std=c++0x main.cpp -o $(target_folder)/${target_bin}
test:
	$(compiler) \
		$(test_lib) \
		$(flags) \
		-o $(target_folder)/test
		# $(googletest_libs) \
		# $(sql_cipher)
	$(debugger) $(target_folder)/test
	# $(checker) -q main_test.cpp $(all_lib)
	# ./bin/test
clean:
	rm -f $(target_folder)/* *.o
	rm -f $(target_folder)/test
	rm -f $(target_folder)/${target_bin}
