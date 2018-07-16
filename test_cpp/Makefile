all:
	g++ -std=c++11 -Wl,--whole-archive -ldpdk -Wl,--no-whole-archive -libverbs -I$(RTE_SDK)/x86_64-native-linuxapp-gcc/include -L../test_dpdklib/build/lib -L$(RTE_SDK)/x86_64-native-linuxapp-gcc/lib main.cpp -lpthread -ldl -lnuma -lrte_eal -ldpdktest -ldpdk -o test_cpp

clean:
	rm *.o
	rm *.a
