#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>



//토큰 타입
enum TokenType {
    IDENTIFIER, //변수명, 함수명과 같은 식별자. 0
    CONSTANT, //상수 10진수. 1
    ASSIGN_OP, //할당 연산자 :=로 한정. 2
    ADD_OP, //덧셈,뺄셈 연산자 3
    MULT_OP, //곱셈,나눗셈 연산자 4
    SEMI_COLON, //세미콜론 5
    LEFT_PAREN, //왼쪽 괄호 6 
    RIGHT_PAREN, //오른쪽 괄호7 
    END_OF_FILE, //파일의 끝, 입력 스트림이 끝났음을 나타냄 8
    ERROR // 오류 표시 9
};

//어휘 분석기의 상태를 나타내는 열거형
enum LexerState{
    START,
    IN_ASSIGN,
    IN_COMMENT,
    IN_NUM,
    IN_ID,
    DONE
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

//lexical analyzer function
void lexical(std::istream& in) {
    char ch;
    token_string.clear();
    
    //공백을 건너뛰기
    while(std::isspace(in.peek())) in.get();

    //파일 끝에 오면 끝내기
    if(in.eof()){
        next_token = END_OF_FILE;
        return;
    }

    ch = in.get();

    //identifier인지 확인
    if(std::isalpha(ch)){
        token_string = ch;
        while(std::isalnum(in.peek())){
            ch = in.get();
            token_string += ch;
        }
        next_token = IDENTIFIER;
    }
    
    //constants인지 확인
    else if(std::isdigit(ch)){
        token_string = ch;
        while(std::isdigit(in.peek())){
            ch = in.get();
            token_string += ch;
        }
        next_token = CONSTANT;
    }

    //assignment op인지 확인
    else if(ch == ':'){
        if(in.peek()=='='){
            in.get();
            next_token = ASSIGN_OP;
            token_string = ":=";
        } else {
            next_token = ERROR;
            token_string = ch;
        }
    }
    //나머지 op나 심볼들
    else{
        switch (ch)
        {
        case '+':
            next_token = ADD_OP;
            break;
        case '-':
            next_token = ADD_OP;
            break;
        case '*':
            next_token = MULT_OP;
            break;
        case '/':
            next_token = MULT_OP;
            break;
        case ';':
            next_token = SEMI_COLON;
            break;
        case '(':
            next_token = LEFT_PAREN;
            break;
        case ')':
            next_token = RIGHT_PAREN;
            break;
        default:
            next_token = ERROR;
            break;
        }
        token_string = ch;
    }
}

// int main() {
//     std::ifstream file("input.txt");
//     if (!file) {
//         std::cerr << "File cannot be opened.\n";
//         return 1;
//     }

//     while (!file.eof()) {
//         lexical(file);
//         std::cout << "Token: " << token_string << ", Type: " << next_token << std::endl;
//     }

//     return 0;
// }
