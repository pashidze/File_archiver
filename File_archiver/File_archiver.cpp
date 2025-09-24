// File_archiver.cpp : Defines the entry point for the application.
//

#include "File_archiver.h"

using namespace std;

void get_files(deque<filesystem::path>& patchs, const filesystem::path& current_patch)
{
	for (const auto& file : filesystem::directory_iterator(current_patch))
	{
		if (filesystem::is_directory(file))
		{
			get_files(patchs, file.path().string());
		}
		else if (filesystem::is_regular_file(file))
		{
			patchs.push_back(file.path());
		}
		else
		{
			return;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	
	deque<filesystem::path> patchs;
	string catPatch;
	
	cout << "Укажите путь к каталогу: ";
	getline(cin, catPatch);

	get_files(patchs, catPatch);

	cout << "Найдено " << patchs.size() << " файлов:\n";
	for (auto it = patchs.cbegin(); it != patchs.cend(); ++it)
	{
		cout << *it << "\n";
	}
	
	return 0;
}
