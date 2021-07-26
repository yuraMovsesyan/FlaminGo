#include "header.h"

int main(int argc, char* argv[]) {

    

    if (argc != 4)
        return 2;

    setlocale(LC_ALL, "rus");
    //режим разработчика
    switchDeveloperMode(true);


    string FULL_FILE_NAME = argv[1];
    FULL_FILE_NAME += "\\";
    FULL_FILE_NAME += argv[2];
    FULL_FILE_NAME += argv[3];
    
    ifstream file(FULL_FILE_NAME);
    string line;

    cout << FULL_FILE_NAME << endl;

    int i = 0, j = 0;

    saveFile("main.asm", ".\\code\\", "");
    saveFile("header.asm", ".\\code\\", "");

    while (file.peek() != EOF) {
        getline(file, line);
        j++;
    }

    file.close();
    file.open(FULL_FILE_NAME);

    while (file.peek() != EOF) {
        i++;
        
        getline(file, line);

        
        print(to_string(i) + ")" + line + "\n", "header");

        handling(line);

        loading(i, j);
    }
    
    print("Строк: " + i, "inform");

    file.close();

    string map = argv[1];
    map += "\\";
    string name = argv[2];
    build(map, name);

	return 0;
}