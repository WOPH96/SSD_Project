#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // 파일 이름과 이진 모드로 파일을 엽니다.
    ifstream inFile("data.bin", ios::binary);
    
    if (!inFile) {
        cerr << "파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    // 파일의 크기를 얻기 위해 끝으로 이동한 후 파일 크기를 계산합니다.
    inFile.seekg(0, ios::end);
    size_t size = inFile.tellg();
    inFile.seekg(0, ios::beg);

    // 파일 크기에 맞는 배열 생성
    int* numbers = new int[size / sizeof(int)];

    // 이진 모드로 데이터 읽기
    inFile.read(reinterpret_cast<char*>(numbers), size);

    // 읽은 데이터 출력
    for (size_t i = 0; i < size / sizeof(int); ++i) {
        cout << hex <<numbers[i] << " ";
    }
    cout << endl;

    // 동적 메모리 해제 및 파일 닫기
    delete[] numbers;
    inFile.close();

    return 0;
}
