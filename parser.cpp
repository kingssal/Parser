//파싱함수 관련 코드
#include "lexer.h"

// 함수 프로토타입 선언
void program();
void statements();
void statement();
void expression();
void term();
void term_tail();
void factor();
void factor_tail();
void match(TokenType expected);


void program(){
    statements();
}

void statements() {
    statement();
    if(next_token == SEMI_COLON){
        match(SEMI_COLON);
        statements();
    }
}
void statement() {
    match(IDENTIFIER);
    match(ASSIGN_OP);
    expression();
}

void expression() {
    term();
    term_tail();
}

void term_tail() {
    if (next_token == ADD_OP) {
        match(ADD_OP);
        term();
        term_tail();
    }
    // ε 경우는 아무것도 하지 않고 반환
}

void term() {
    factor();
    factor_tail();
}

void factor_tail() {
    if (next_token == MULT_OP) {
        match(MULT_OP);
        factor();
        factor_tail();
    }
    // ε 경우는 아무것도 하지 않고 반환
}

void factor() {
    if (next_token == LEFT_PAREN) {
        match(LEFT_PAREN);
        expression();
        match(RIGHT_PAREN);
    } else if (next_token == IDENTIFIER) {
        match(IDENTIFIER);
    } else if (next_token == CONSTANT) {
        match(CONSTANT);
    } else {
        // 오류 처리
    }
}

std::ifstream in;

void match(TokenType expected) {
    if (next_token == expected) {
        // 다음 토큰으로 이동
        lexical(in);
    } else {
        // 오류 처리
    }
}

int main() {
    // 파일을 열고, 입력 스트림을 초기화
    in.open("input.txt");
    if (!in) {
        std::cerr << "File could not be opened." << std::endl;
        return 1;
    }

    // 어휘 분석기와 파서를 초기화하고 시작
    lexical(in); // 첫 번째 토큰을 가져옴
    program();   // 파싱을 시작

    in.close();  // 파일 스트림을 닫음
    return 0;
}