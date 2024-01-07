#include "country.h"
#include "service.h"
#include "tree.h"
#include "file_database.h"
#include "user_interface.h"
#include "admin_interface.h"
#include "main_menu.h"

int main()
{
	system("chcp 1251");
	MENU ui;
	try
	{
		ui.main_menu();
	}
	catch (const std::exception& ex)
	{
		std::cerr << endl << ex.what() << endl;
		return -1;
	}
	return 0;
}
