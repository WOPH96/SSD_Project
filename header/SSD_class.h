#ifndef __SSD_CLASS_H__
#define __SSD_CLASS_H__

#include <string>
#include <fstream>
#include <cstdint>

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

    void OpenSSDFile(std::ios_base::openmode mode);
    void OpentxtFile(std::ios_base::openmode mode);

public:
    SSD();
    void Init();
    void Read(uint32_t *buffer, uint32_t offset, uint32_t count = 1);
    void Write(const uint32_t *buffer, uint32_t offset, uint32_t count = 1);
};

#endif