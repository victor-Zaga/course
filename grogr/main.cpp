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
	ui.main_menu();
	return 0;
}
