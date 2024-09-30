#include <iostream>
#include <cstring>
#include "../../header/SSD_class.h"
#include "../../header/utils.h"

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
            uint32_t data = StrtoHex(argv[3]);
            ssd.Write(&data, atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "R") && argc == 3)
        {
            uint32_t read_buffer = 0;
            ssd.Read(&read_buffer, atoi(argv[2]));
        }
        else if (!strcmp(argv[1], "I") && argc == 2)
        {
            ssd.Init();
        }
        else
        {
            std::cout << "잘못된 입력" << std::endl;
            return -1;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "에러 발생: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
