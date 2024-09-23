#include "../header/SSD_class.h"
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <vector>

const std::string SSD::SSD_FILE_NAME = "../memory/nand.txt";
const std::string SSD::RESULT_FILE_NAME = "../result/result.txt";

SSD::SSD() {}

void SSD::open_ssd_file(std::ios_base::openmode mode)
{
    ssd_file.open(SSD_FILE_NAME, mode);
    if (!ssd_file.is_open())
    {
        throw std::runtime_error("SSD 파일을 열 수 없습니다.");
    }
}

void SSD::open_txt_file(std::ios_base::openmode mode)
{
    result_file.open(RESULT_FILE_NAME, mode);
    if (!result_file.is_open())
    {
        throw std::runtime_error("txt 파일을 열 수 없습니다.");
    }
}

void SSD::init()
{
    open_ssd_file(std::ios::out);
    open_txt_file(std::ios::out);
    std::vector<char> buffer(SSD_SIZE, 0);
    ssd_file.write(buffer.data(), SSD_SIZE);
    ssd_file.close();
    result_file.write("", 1);
    result_file.close();
    std::cout << "SSD, nand.txt 초기화 완료\n";
}

void SSD::read(uint32_t *buffer, uint32_t offset, uint32_t count)
{
    if (LBA_SIZE * (offset + count) > SSD_SIZE)
    {
        throw std::out_of_range("읽기 범위가 SSD 크기를 초과합니다.");
    }
    open_ssd_file(std::ios::in);
    ssd_file.seekg(offset * LBA_SIZE);
    ssd_file.read(reinterpret_cast<char *>(buffer), count * LBA_SIZE);
    ssd_file.close();
    open_txt_file(std::ios::out);
    result_file << "0x" << std::hex << std::setw(8)
                << std::setfill('0') << *buffer << std::endl;
    result_file.close();
}

void SSD::write(const uint32_t *buffer, uint32_t offset, uint32_t count)
{
    if (LBA_SIZE * (offset + count) > SSD_SIZE)
    {
        throw std::out_of_range("쓰기 범위가 SSD 크기를 초과합니다.");
    }
    open_ssd_file(std::ios::in | std::ios::out);
    ssd_file.seekp(offset * LBA_SIZE);
    ssd_file.write(reinterpret_cast<const char *>(buffer), count * LBA_SIZE);
    ssd_file.close();
}