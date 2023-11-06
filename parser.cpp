//파싱함수 관련 코드
#include "lexer.h"
#include <map>
#include <string>
#include <iostream>

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

// 전역 변수로 심볼 테이블과 오류 카운트를 추가합니다.
std::map<std::string, int> symbolTable;
int identifierCount = 0;
int constantCount = 0;
int operatorCount = 0;
bool hasError = false;

int errorCount = 0;


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
        if (expected == IDENTIFIER) {
            identifierCount++;
            // 변수 이름을 심볼 테이블에 추가하거나 업데이트
            // 현재는 0으로 초기화하지만, 실제 값으로 업데이트해야 할 수 있습니다.
            symbolTable[token_string] = 0;
        } else if (expected == CONSTANT) {
            constantCount++;
        } else if (expected == ADD_OP || expected == MULT_OP || expected == ASSIGN_OP) {
            operatorCount++;
        }
        // 다음 토큰으로 이동
        lexical(in);
    } else {
        // 오류 처리
        std::cout << "Error: expected token " << expected << " but found " << next_token << std::endl;
        hasError = true;
    }
}




// 오류 메시지를 출력하고 오류 카운트를 증가시키는 함수
void error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    ++errorCount;
}

// 오류가 발생했을 때 복구를 시도하는 함수
void recover() {
    // 복구 로직을 구현합니다. 예를 들어, 세미콜론을 찾을 때까지 토큰을 건너뛰는 등의 방법이 있습니다.
    while (next_token != SEMI_COLON && next_token != END_OF_FILE) {
        lexical(in); // 다음 토큰으로 이동
    }
    // 세미콜론을 찾았다면, 파싱을 계속하기 위해 건너뛰고 다음 토큰으로 이동합니다.
    if (next_token == SEMI_COLON) {
        lexical(in); // 다음 토큰으로 이동
    }
}


// 변수를 심볼 테이블에 추가하거나 업데이트하는 함수입니다.
void updateSymbolTable(const std::string& identifier, int value) {
    symbolTable[identifier] = value;
}

// 심볼 테이블에서 변수의 값을 조회하는 함수입니다.
int getValueFromSymbolTable(const std::string& identifier) {
    if (symbolTable.find(identifier) != symbolTable.end()) {
        return symbolTable[identifier];
    } else {
        std::cerr << "Error: Variable " << identifier << " not defined." << std::endl;
        return 0; // 오류가 발생한 경우 기본값으로 0을 반환합니다.
    }
}

// 심볼 테이블의 내용을 출력하는 함수입니다.
void printSymbolTable() {
    std::cout << "Symbol Table:" << std::endl;
    for (const auto& entry : symbolTable) {
        std::cout << entry.first << " = " << entry.second << std::endl;
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
    // 토큰 개수 출력
    std::cout << "ID:" << identifierCount << "; CONST:" << constantCount << "; OP:" << operatorCount << ";" << std::endl;

    // 파싱 결과 출력
    if (hasError) {
        std::cout << "Parsing Result: (ERROR)" << std::endl;
    } else {
        // 경고가 있는 경우 (WARNING)을 출력할 수 있습니다.
        std::cout << "Parsing Result: (OK)" << std::endl;
    }

    // 심볼 테이블 결과 출력
    std::cout << "Result ==> ";
    for (const auto& entry : symbolTable) {
        std::cout << entry.first << ":" << entry.second << ";";
    }
    std::cout << std::endl;
    return 0;
}