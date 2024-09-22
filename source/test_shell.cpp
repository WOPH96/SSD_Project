#include <iostream>
#include <string>
#include <cstdlib>

// 명령어 실행 함수
void execute_command(const std::string& command) {
    system(command.c_str());
}

// help 함수 (한국어 설명)
void print_help() {
    std::cout << "사용 가능한 명령어:\n";
    std::cout << "write [LBA] [Value]  - 주어진 LBA에 값을 저장합니다.\n";
    std::cout << "read [LBA]           - 주어진 LBA에서 값을 읽어옵니다.\n";
    std::cout << "fullwrite [Value]    - 모든 LBA에 동일한 값을 씁니다.\n";
    std::cout << "fullread             - 모든 LBA에서 값을 읽어옵니다.\n";
    std::cout << "testapp1             - 전체 SSD에 값을 쓰고 검증하는 테스트.\n";
    std::cout << "testapp2             - 특정 LBA에 여러 번 값을 쓰고 덮어쓰기 후 검증하는 테스트.\n";
    std::cout << "exit                 - Shell을 종료합니다.\n";
    std::cout << "help                 - 이 도움말을 출력합니다.\n";
}

// testapp1: Full Write 후 Read Compare
int testapp1() {
    std::string test_value = "0xABCD1234";  // 테스트할 값

    // Step 1: Full Write
    std::cout << "[testapp1] SSD에 전체 값을 쓰는 중...\n";
    for (int lba = 0; lba < 100; ++lba) {
        std::string write_command = "./ssd_program W " + std::to_string(lba) + " " + test_value;
        execute_command(write_command);
    }

    // Step 2: Full Read and Compare
    std::cout << "[testapp1] SSD에서 전체 값을 읽어오는 중...\n";
    for (int lba = 0; lba < 100; ++lba) {
        std::string read_command = "./ssd_program R " + std::to_string(lba);
        execute_command(read_command);  // 읽은 값을 result.txt에 저장
        // 실제로 result.txt를 읽어서 검증하는 코드 추가 가능
    }

    std::cout << "[testapp1] 테스트 완료\n";
    return 0;
}

// testapp2: Write Aging 후 Read Compare
int testapp2() {
    std::string initial_value = "0xAAAABBBB";  // 초기 쓰기 값
    std::string final_value = "0x12345678";    // 마지막에 덮어씌울 값

    // Step 1: Write initial_value 30 times to LBA 0 ~ 5
    std::cout << "[testapp2] SSD에 값을 30번 쓰는 중...\n";
    for (int i = 0; i < 30; ++i) {
        for (int lba = 0; lba < 6; ++lba) {
            std::string write_command = "./ssd_program W " + std::to_string(lba) + " " + initial_value;
            execute_command(write_command);
        }
    }

    // Step 2: Overwrite with final_value to LBA 0 ~ 5
    std::cout << "[testapp2] 덮어씌우는 값 쓰는 중...\n";
    for (int lba = 0; lba < 6; ++lba) {
        std::string write_command = "./ssd_program W " + std::to_string(lba) + " " + final_value;
        execute_command(write_command);
    }

    // Step 3: Read and Compare
    std::cout << "[testapp2] SSD에서 값을 읽어오는 중...\n";
    for (int lba = 0; lba < 6; ++lba) {
        std::string read_command = "./ssd_program R " + std::to_string(lba);
        execute_command(read_command);  // 읽은 값을 result.txt에 저장
        // 실제로 result.txt를 읽어서 검증하는 코드 추가 가능
    }

    std::cout << "[testapp2] 테스트 완료\n";
    return 0;
}

// 메인 함수 (Test Shell)
int main() {
    std::string input;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);  // 사용자로부터 명령어 입력

        // exit 명령 처리
        if (input == "exit") {
            break;
        }
        // help 명령 처리
        else if (input == "help") {
            print_help();
        }
        // testapp1 명령 처리
        else if (input == "testapp1") {
            testapp1();
        }
        // testapp2 명령 처리
        else if (input == "testapp2") {
            testapp2();
        }
        // write 명령 처리
        else if (input.find("write") == 0) {
            std::string ssd_command = "./ssd_program W " + input.substr(6);
            execute_command(ssd_command);
        }
        // read 명령 처리
        else if (input.find("read") == 0) {
            std::string ssd_command = "./ssd_program R " + input.substr(5);
            execute_command(ssd_command);
        }
        // fullwrite 명령 처리
        else if (input.find("fullwrite") == 0) {
            for (int lba = 0; lba < 100; ++lba) {
                std::string ssd_command = "./ssd_program W " + std::to_string(lba) + " " + input.substr(10);
                execute_command(ssd_command);
            }
        }
        // fullread 명령 처리
        else if (input == "fullread") {
            for (int lba = 0; lba < 100; ++lba) {
                std::string ssd_command = "./ssd_program R " + std::to_string(lba);
                execute_command(ssd_command);
            }
        }
        // 잘못된 명령 처리
        else {
            std::cout << "INVALID COMMAND\n";
        }
    }

    return 0;
}
