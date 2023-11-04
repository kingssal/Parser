#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>

//토큰 타입
enum TokenType {
    IDENTIFIER, //변수명, 함수명과 같은 식별자.
    CONSTANT, //상수 10진수
    ASSIGN_OP, //할당 연산자 :=로 한정
    ADD_OP, //덧셈,뺄셈 연산자
    MULT_OP, //곱셈,나눗셈 연산자
    SEMI_COLON, //세미콜론
    LEFT_PAREN, //왼쪽 괄호
    RIGHT_PAREN, //오른쪽 괄호
    END_OF_FILE, //파일의 끝, 입력 스트림이 끝났음을 나타냄
    ERROR // 오류 표시
};