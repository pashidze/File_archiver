// File_archiver.cpp : Defines the entry point for the application.
//

#include "File_archiver.h"

using namespace std;
namespace fs = filesystem;

class QueueFiles
{
private:
	vector<fs::path> files;
	fs::path current_patch = {};
public:

	void set_path(const string& string_patch)
	{
		this->current_patch = fs::u8path(string_patch);
	}

	fs::path& get_patch()
	{
		return this->current_patch;
	}

	const vector<fs::path>& get_files()
	{
		return this->files;
	}

	size_t get_size()
	{
		return this->files.size();
	}

	void collect_files()
	{
		error_code ec;
		this->files.clear();

		if (this->current_patch.empty() || !fs::exists(this->current_patch, ec))
		{
			if (!ec) ec = make_error_code(errc::no_such_file_or_directory);
		}

		try
		{
			for (const auto& file : fs::recursive_directory_iterator(this->current_patch))
			{
				fs::file_status fStatus = fs::symlink_status(file.path());
				if (fs::is_regular_file(fStatus))
				{
					this->files.push_back(file.path());
				}
			}
		}
		catch (const fs::filesystem_error& er)
		{
			ec = er.code();
			cerr << "Ошибка при обходе: " << ec.message() << "\n";
		}
	}

	void write_list_to_text_file(const fs::path& output_file)
	{
		error_code ec;
		ofstream ofs(output_file);
		if (ofs)
		{
			for (const auto& it : this->files)
			{
				ofs << it << "\n";
			}
		}
		else
		{
			ec = make_error_code(errc::io_error);
			cerr << "Не удалось записать файл: " << ec.message() << "\n";
		}
		ofs.close();
	}
};

int main()
{
	setlocale(LC_ALL, "rus");

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	
	string string_patch;
	QueueFiles qf;
	
	cout << "Укажите путь к каталогу: ";
	getline(cin, string_patch);

	qf.set_path(string_patch);

	qf.collect_files();
	cout << "Найдено " << qf.get_size() << " файлов.\n\n";

	qf.write_list_to_text_file("Files_list.txt");
	cout << "Список файлов записан в Files_list.txt\n\n";

	system("pause");
	return 0;
}
