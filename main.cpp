#include <string>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>


using namespace std;
namespace fs = experimental::filesystem;

string EXPLORER_LOG_PATH = "log.txt";


void displayFile(string fileAddress) {
    //Проверка на существование файла
    if(!fs::exists(fileAddress)) {
      throw runtime_error("ERROR: We don't have such file");
    }
    //Имя файла
    fs::path filePath = fileAddress;
    fs::path textfile = filePath.filename();
    //Дата модификации
    auto ftime = fs::last_write_time(filePath);
    time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
    //Размер файла
    double size;
    size = fs::file_size(filePath);
    //Запись данных о файле в файл.txt
    ofstream fout(EXPLORER_LOG_PATH);
    fout << "File name: " << textfile << endl;
    fout << "Latest modification: " << asctime(localtime(&cftime)) << endl;
    fout << "File size: " << size/1000 << " Kb" << endl;
    fout.close();

}


int main()
{

  string ad;
  cin >> ad;
  //ad = "example";

  try {
    displayFile(ad);
  }
  catch(const exception& e) {
    cout << e.what() << endl;
  }
}