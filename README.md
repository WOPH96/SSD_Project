# SSD 프로젝트

## Goal

0. git 협업능력 증진
1. 가상 SSD 제작
2. SSD 검증 script 작성

### Result

**세부 규정**

    데이터 범위
    • LBA : 0 ~ 99, 10진수
    • 값 : 항상 0x가 붙으며 10 글자로 표기한다. ( 0x00000000 ~ 0xFFFFFFFF )

    Read 명령어
    • ssd R [LBA]
    • result.txt 에 읽은 값이 적힌다. (기존 데이터는 사라진다.)
    • 한번도 안적은 곳은 0x00000000 으로 읽힌다.

    Write 명령어

    • ssd W [LBA] [값]
    • nand.txt 에 저장한 값이 기록된다

## Language

1. C++
2. Shell script

## Coding Conventions

[구글의 C++ 컨벤션](https://modoocode.com/335)

### 변수명, 클래스 필드 명

**snake_case**

띄어쓰기를 \_ 로 구분, 모두 소문자

### 클래스 명, 함수명

**CamelCase**

대소문자로 띄어쓰기를 구분

### enum 필드

**KEBAB-CASE**

(띄어쓰기를 -로 구분, 모두 대문자)
