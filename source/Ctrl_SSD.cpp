#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <iomanip>

class SSD
{
private:
    static const uint32_t SSD_SIZE = 400;
    static const uint32_t LBA_SIZE = 4;
    static const std::string SSD_FILE_NAME;
    static const std::string RESULT_FILE_NAME;

    std::fstream ssd_file;
    std::fstream result_file;

    void OpenSSDFile(std::ios_base::openmode mode)
    {
        ssd_file.open(SSD_FILE_NAME, mode);
        if (!ssd_file.is_open())
        {
            throw std::runtime_error("SSD 파일을 열 수 없습니다.");
        }
    }
    void OpentxtFile(std::ios_base::openmode mode)
    {
        result_file.open(RESULT_FILE_NAME, mode);
        if (!result_file.is_open())
        {
            throw std::runtime_error("txt 파일을 열 수 없습니다.");
        }
    }

public:
    SSD()
    {
        // init();
    }

    void Init()
    {
        OpenSSDFile(std::ios::out);
        OpentxtFile(std::ios::out);
        std::vector<char> buffer(SSD_SIZE, 0);
        ssd_file.write(buffer.data(), SSD_SIZE);
        ssd_file.close();
        result_file.write("", 1);
        result_file.close();
        std::cout << "SSD, nand.txt 초기화 완료\n";
    }

    void Read(uint32_t *buffer, uint32_t offset, uint32_t count = 1)
    {
        if (LBA_SIZE * (offset + count) > SSD_SIZE)
        {
            throw std::out_of_range("읽기 범위가 SSD 크기를 초과합니다.");
        }
        OpenSSDFile(std::ios::in);
        ssd_file.seekg(offset * LBA_SIZE);
        ssd_file.read(reinterpret_cast<char *>(buffer), count * LBA_SIZE);
        ssd_file.close();
        OpentxtFile(std::ios::out);
        result_file << "0x" << std::hex << std::setw(8)
                    << std::setfill('0') << *buffer << std::endl;
        result_file.close();
    }

    void Write(const uint32_t *buffer, uint32_t offset, uint32_t count = 1)
    {
        if (LBA_SIZE * (offset + count) > SSD_SIZE)
        {
            throw std::out_of_range("쓰기 범위가 SSD 크기를 초과합니다.");
        }
        OpenSSDFile(std::ios::in | std::ios::out);
        ssd_file.seekp(offset * LBA_SIZE);
        ssd_file.write(reinterpret_cast<const char *>(buffer), count * LBA_SIZE);
        ssd_file.close();
    }
};

const std::string SSD::SSD_FILE_NAME = "../memory/nand.txt";
const std::string SSD::RESULT_FILE_NAME = "../result/result.txt";

uint32_t StrtoHex(const char *hexstr)
{
    std::string str{hexstr};
    if (str.substr(0, 2) == "0x" || str.substr(0, 2) == "0X")
    {
        str = str.substr(2);
    }
    uint32_t result;
    std::stringstream ss;
    ss << std::hex << str;
    ss >> result;
    return result;
}
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
            uint32_t data = StrtoHex(argv[3]);
            ssd.Write(&data, atoi(argv[2]));
            // std::cout << "쓰기 완료: " << data << std::endl;
        }
        else if (!strcmp(argv[1], "R") && argc == 3)
        {
            std::cout << "읽기 작업 실행" << std::endl;
            uint32_t read_buffer = 0;
            ssd.Read(&read_buffer, atoi(argv[2]));
            std::cout << "읽기 완료: 0x" << std::hex << read_buffer << std::endl;
        }
        else if (!strcmp(argv[1], "I") && argc == 2)
        {
            ssd.Init();
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