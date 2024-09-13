#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // ifstream 클래스의 객체를 바이너리 모드, data.bin 파일로 초기화
    ifstream fin("data.bin", ios::binary);

    // 파일이 열리지 않는 경우
    if(!fin){
        cerr << "파일을 열 수 없습니다." << endl;
    }

    // 파일 사이즈 구하기 => 어차피 4byte면 구할 필요가 있나?
    // seekg : 파일 내에서 위치 이동
    fin.seekg(0, std::ios::end); // 파일 스트림을 파일 끝으로 위치 이동
    size_t size = fin.tellg(); // 파일의 시작부터 현재 위치(파일 끝)까지의 바이트 수를 반환 = 파일의 크기
    fin.seekg(0, std::ios::beg); // 파일 스트림을 다시 시작 위치로 이동 => 파일을 읽을 때 처음부터 읽기 위함

    // 4바이트 정수형 변수 선언
    int result;

    // 이진 모드로 데이터 읽기
    fin.read(reinterpret_cast<char*>(&result), sizeof(result));

    fin.close();

    // 읽은 데이터 출력
    cout << hex <<  result << endl;

    return 0;
}
