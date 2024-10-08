#include "../../header/shell_func.h"
#include <iostream>
#include <fstream>


// 명령어 실행 함수 (결과값 반환)
std::string ExecuteCommand(const std::string &command)
{
    char buffer[128];
    std::string result = "";
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "popen() failed!" << std::endl;
        return "";
    }
    try
    {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            result += buffer;
        }
    }
    catch (...)
    {
        pclose(pipe);
        std::cerr << "Error reading command output!" << std::endl;
        return "";
    }
    pclose(pipe);
    return result;
}

// help 함수 (한국어 설명)
void PrintHelp()
{
    std::cout << "사용 가능한 명령어:\n";
    std::cout << "init                 - SSD를 초기화합니다.\n";
    std::cout << "write [LBA] [Value]  - 주어진 LBA에 값을 저장합니다.\n";
    std::cout << "read [LBA]           - 주어진 LBA에서 값을 읽어옵니다.\n";
    std::cout << "fullwrite [Value]    - 모든 LBA에 동일한 값을 씁니다.\n";
    std::cout << "fullread             - 모든 LBA에서 값을 읽어옵니다.\n";
    std::cout << "TestApp1             - 전체 SSD에 값을 쓰고 검증하는 테스트.\n";
    std::cout << "TestApp2             - 특정 LBA에 여러 번 값을 쓰고 덮어쓰기 후 검증하는 테스트.\n";
    std::cout << "exit                 - Shell을 종료합니다.\n";
    std::cout << "help                 - 이 도움말을 출력합니다.\n";
}

// TestApp1: Full Write 후 Read Compare
int TestApp1() {
    std::string test_value = "0XABCD1234";  // 테스트할 값
    std::ifstream result_file;              // 파일 스트림 객체

    // Step 0: SSD 초기화
    std::cout << "[TestApp1] SSD 초기화 중...\n";
    ExecuteCommand("./SSD I");

    // Step 1: Full Write
    std::cout << "[TestApp1] SSD에 전체 값을 쓰는 중...\n";
    for (int lba = 0; lba < 100; ++lba) {
        std::string write_command = "./SSD W " + std::to_string(lba) + " " + test_value;
        ExecuteCommand(write_command);
    }

    // Step 2: Full Read and Compare
    std::cout << "[TestApp1] SSD에서 전체 값을 읽어오는 중...\n";
    for (int lba = 0; lba < 100; ++lba) {
        std::string read_command = "./SSD R " + std::to_string(lba);
        ExecuteCommand(read_command);  // 읽은 값을 result.txt에 저장

        // result.txt 파일을 열어서 읽고 값 검증
        result_file.open("../result/result.txt");
        if (result_file.is_open()) {
            std::string line;
            std::getline(result_file, line);  // 첫 번째 줄 읽기
            if (line == test_value) {
                std::cout << "LBA " << lba << ": 값 일치 (" << line << ")\n";
            } else {
                std::cerr << "LBA " << lba << ": 값 불일치! (" << line << "!=" << test_value << ")\n";
            }
            result_file.close();
        } else {
            std::cerr << "result.txt 파일을 열 수 없습니다." << std::endl;
        }
    }

    std::cout << "[TestApp1] 테스트 완료\n";
    return 0;
}

// TestApp2: Write Aging 후 Read Compare
int TestApp2() {
    std::string initial_value = "0xAAAABBBB";  // 초기 쓰기 값
    std::string final_value = "0X12345678";    // 마지막에 덮어씌울 값
    std::ifstream result_file;                 // 파일 스트림 객체

    // Step 0: SSD 초기화
    std::cout << "[TestApp2] SSD 초기화 중...\n";
    ExecuteCommand("./SSD I");

    // Step 1: 0 ~ 5번 LBA에 initial_value를 30번 쓰기
    std::cout << "[TestApp2] SSD에 값을 30번 쓰는 중...\n";
    for (int i = 0; i < 30; ++i) {
        for (int lba = 0; lba < 6; ++lba) {
            std::string write_command = "./SSD W " + std::to_string(lba) + " " + initial_value;
            ExecuteCommand(write_command);
        }
    }

    // Step 2: 0 ~ 5번 LBA에 final_value로 덮어쓰기
    std::cout << "[TestApp2] 덮어씌우는 값 쓰는 중...\n";
    for (int lba = 0; lba < 6; ++lba) {
        std::string write_command = "./SSD W " + std::to_string(lba) + " " + final_value;
        ExecuteCommand(write_command);
    }

    // Step 3: 0 ~ 5번 LBA 값 읽어서 검증
    std::cout << "[TestApp2] SSD에서 값을 읽어오는 중...\n";
    for (int lba = 0; lba < 6; ++lba) {
        std::string read_command = "./SSD R " + std::to_string(lba);
        ExecuteCommand(read_command);  // 읽은 값을 result.txt에 저장

        // result.txt 파일을 열어서 읽고 값 검증
        result_file.open("../result/result.txt");
        if (result_file.is_open()) {
            std::string line;
            std::getline(result_file, line);  // 첫 번째 줄 읽기
            if (line == final_value) {
                std::cout << "LBA " << lba << ": 값 일치 (" << line << ")\n";
            } else {
                std::cerr << "LBA " << lba << ": 값 불일치! (" << line << " != " << final_value << ")\n";
            }
            result_file.close();
        } else {
            std::cerr << "result.txt 파일을 열 수 없습니다." << std::endl;
        }
    }

    std::cout << "[TestApp2] 테스트 완료\n";
    return 0;
}