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

//global variables
TokenType next_token;
std::string token_string;

//스트링이 숫자인지 확인하기 위한 함수
bool isNumber(const std::string& str){
    for(char const &c : str) {
        if(std::isdigit(c)==0){
            return false;
        }
    }
    return true;
}

//leximal analyzer function
