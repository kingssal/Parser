# Parser
프로그래밍언어론 과제


파일을 통해 입력된 프로그래밍이 아래에 제시된 LL(1)문법을 따르는지 여부를 판단하는 파서(parser)를 Recursive descent Parsing 기법을 이용해 작성하고 파싱된 결과를 이용하여 입력된 프로그램 결과를 도출하시오.

문법
<program> → <statements> <statements>→ <statement> | <statement><semi_colon><statements> <statement> → <ident><assignment_op><expression> <expression> → <term><term_tail> <term_tail> → <add_op><term><term_tail> | ε <term> → <factor> <factor_tail> <factor_tail> → <mult_op><factor><factor_tail> | ε <factor> → <left_paren><expression><right_paren> | <ident> | <const> <const> → any decimal numbers <ident> → any names conforming to C identifier rules <assignment_op> → := <semi_colon> → ; <add_operator> → + | - <mult_operator> → * | / <left_paren> → ( <right_paren> → ) 
