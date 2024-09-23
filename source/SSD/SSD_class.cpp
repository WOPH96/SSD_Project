#include "../..//header/SSD_class.h"
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>

const std::string SSD::SSD_FILE_NAME = "../memory/nand.txt";
const std::string SSD::RESULT_FILE_NAME = "../result/result.txt";

void SSD::OpenSSDFile(std::ios_base::openmode mode)
{
    ssd_file.open(SSD_FILE_NAME, mode);
    if (!ssd_file.is_open())
    {
        throw std::runtime_error("SSD 파일을 열 수 없습니다.");
    }
}

void SSD::OpentxtFile(std::ios_base::openmode mode)
{
    result_file.open(RESULT_FILE_NAME, mode);
    if (!result_file.is_open())
    {
        throw std::runtime_error("txt 파일을 열 수 없습니다.");
    }
}
SSD::SSD() {}

void SSD::Init()
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

void SSD::Read(uint32_t *buffer, uint32_t offset, uint32_t count)
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

void SSD::Write(const uint32_t *buffer, uint32_t offset, uint32_t count)
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