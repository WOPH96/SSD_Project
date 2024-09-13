#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // 파일 이름과 이진 모드로 파일을 엽니다.
    ofstream outFile("data.bin", ios::binary);
    
    if (!outFile) {
        cerr << "파일을 열 수 없습니다." << endl;
        return 1;
    }

    // 예제 데이터
    int input;
    cin >> hex >> input;

    // 이진 모드로 데이터 쓰기
    outFile.write(reinterpret_cast<char*>(&input), sizeof(input)); // char*(문자열)로 타입캐스팅을 한 후에 write

    // 파일 닫기
    outFile.close();

    std::cout << "데이터가 파일에 성공적으로 기록되었습니다." << std::endl;

    return 0;
}
