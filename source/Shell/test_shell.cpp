#include "../../header/shell_func.h"
// 메인 함수 (Test Shell)
#include <iostream>
#include <cstdlib>
#include <fstream>
int main()
{
    std::string input;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, input); // 사용자로부터 명령어 입력

        // exit 명령 처리
        if (input == "exit")
        {
            break;
        }
        // help 명령 처리
        else if (input == "help")
        {
            PrintHelp();
        }
        // TestApp1 명령 처리
        else if (input == "TestApp1")
        {
            TestApp1();
        }
        // TestApp2 명령 처리
        else if (input == "TestApp2")
        {
            TestApp2();
        }
        // init 명령 처리
        else if (input == "init")
        {
            std::cout << "[Shell] SSD 초기화 중...\n";
            ExecuteCommand("./SSD I");
            std::cout << "[Shell] SSD 초기화 완료\n";
        }
        // write 명령 처리
        else if (input.find("write") == 0)
        {
            std::string ssd_command = "./SSD W " + input.substr(6);
            ExecuteCommand(ssd_command);
            std::cout << "write완료" << std::endl;
        }
        // read 명령 처리
        else if (input.find("read") == 0)
        {
            std::string ssd_command = "./SSD R " + input.substr(5);
            ExecuteCommand(ssd_command);

            std::ifstream result_file("../result/result.txt");
            if (result_file.is_open())
            {
                std::string line;
                std::getline(result_file, line);                                     // result.txt에서 첫 번째 줄 읽기
                std::cout << "LBA " << input.substr(5) << ": " << line << std::endl; // LBA와 함께 출력
                result_file.close();
                std::cout << "read완료" << std::endl;
            }
            else
            {
                std::cerr << "result.txt 파일을 열 수 없습니다." << std::endl;
            }
        }
        // fullwrite 명령 처리
        else if (input.find("fullwrite") == 0)
        {
            for (int lba = 0; lba < 100; ++lba)
            {
                std::string ssd_command = "./SSD W " + std::to_string(lba) + " " + input.substr(10);
                ExecuteCommand(ssd_command);
            }
            std::cout << "fullwrite완료" << std::endl;
        }
        // fullread 명령 처리
        else if (input == "fullread")
        {
            for (int lba = 0; lba < 100; ++lba)
            {
                std::string ssd_command = "./SSD R " + std::to_string(lba);
                ExecuteCommand(ssd_command);

                std::ifstream result_file("../result/result.txt");
                if (result_file.is_open())
                {
                    std::string line;
                    std::getline(result_file, line);                         // result.txt에서 첫 번째 줄 읽기
                    std::cout << "LBA " << lba << ": " << line << std::endl; // LBA와 함께 출력
                    result_file.close();
                }
                else
                {
                    std::cerr << "result.txt 파일을 열 수 없습니다." << std::endl;
                }
            }
            std::cout << "fullread완료" << std::endl;
        }
        // 잘못된 명령 처리
        else
        {
            std::cout << "INVALID COMMAND\n";
        }
    }

    return 0;
}