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
    static const uint32_t LBA_COUNT = 100;
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
    SSD() {}

    void Init()
    {
        OpenSSDFile(std::ios::out);
        for (uint32_t i = 0; i < LBA_COUNT; ++i)
        {
            ssd_file << "0X00000000" << std::endl;
        }
        ssd_file.close();

        OpentxtFile(std::ios::out);
        result_file.write("", 0);
        result_file.close();
        std::cout << "SSD, nand.txt 초기화 완료\n";
    }

    void Read(uint32_t *buffer, uint32_t offset, uint32_t count = 1)
    {
        if (offset >= LBA_COUNT)
        {
            throw std::out_of_range("읽기 범위가 SSD 크기를 초과합니다.");
        }
        OpenSSDFile(std::ios::in);
        std::string line;
        ssd_file.seekg(0);
        for (uint32_t i = 0; i <= offset; ++i)
        {
            std::getline(ssd_file, line);
        }
        *buffer = std::stoul(line.substr(2), nullptr, 16);
        ssd_file.close();

        OpentxtFile(std::ios::out);
        result_file << line << std::endl;
        result_file.close();
    }

    void Write(const uint32_t *buffer, uint32_t offset, uint32_t count = 1)
    {
        if (offset >= LBA_COUNT)
        {
            throw std::out_of_range("쓰기 범위가 SSD 크기를 초과합니다.");
        }
        std::vector<std::string> lines;
        OpenSSDFile(std::ios::in);
        std::string line;
        while (std::getline(ssd_file, line))
        {
            lines.push_back(line);
        }
        ssd_file.close();

        std::stringstream ss;
        ss << "0X" << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << *buffer;
        lines[offset] = ss.str();

        OpenSSDFile(std::ios::out);
        for (const auto &l : lines)
        {
            ssd_file << l << std::endl;
        }
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
