#include <iostream>
#include <cstring>
#include "../header/SSD_class.h"
#include "../header/utils.h"

int main(int argc, char *argv[])
{
    try
    {
        SSD ssd;
        if (argc < 2)
        {
            std::cout << "명령, 주소, 값을 입력해주세요!" << std::endl;
            std::cout << "ex) ssd W 3 0x1298CDEF\n : 3 번 LBA 영역에 값 0x1298CDEF 를 저장한다 " << std::endl;
            return -1;
        }

        if (!strcmp(argv[1], "W") && argc == 4)
        {
            // std::cout << "쓰기 작업 실행" << std::endl;
            uint32_t data = strtohex(argv[3]);
            ssd.write(&data, atoi(argv[2]));
            // std::cout << "쓰기 완료: " << data << std::endl;
        }
        else if (!strcmp(argv[1], "R") && argc == 3)
        {
            std::cout << "읽기 작업 실행" << std::endl;
            uint32_t read_buffer = 0;
            ssd.read(&read_buffer, atoi(argv[2]));
            std::cout << "읽기 완료: 0x" << std::hex << read_buffer << std::endl;
        }
        else if (!strcmp(argv[1], "I") && argc == 2)
        {
            ssd.init();
            // std::cout << "SSD 초기화" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "에러 발생: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}