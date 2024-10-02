 #include <iostream>
#include "Obec.h"
#include <vector>
#include <Windows.h>
#include "DataCR.h"
#include "Algoritmus.h"
#include "Aplikacia.h"
#include <libds/heap_monitor.h>
#include "Gui.h"

int main()
{
	initHeapMonitor();
	SetConsoleOutputCP(1250);
	SetConsoleCP(1250);
	std::locale::global(std::locale("Czech_Czechia.1250"));

	Gui gui = Gui();
    gui.spustiAplikaciu();

	return 0;
}

