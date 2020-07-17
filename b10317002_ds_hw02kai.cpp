// B10317002_DS_HW02.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

char opr[] = { '(', '+', '-', '*', '/' };
int prio[] = { 0, 1, 1, 2, 2 };
int layernow = -1;
int PopStart = 0;
int PushStart = 0;
int inlength = 0;
int OprUse = 0;
char infix[100] = { '\0' };
char postfix[100] = { '\0' };
char stack[100] = { '\0' };
int	 PrioStack[100] = { 0 };
void Infix_To_Postfix();
void pushch();


int _tmain(int argc, _TCHAR* argv[])
{
	char regis = '0';
	cout << "Enter Infix Expression:";

	//-------將輸入內容存入infix陣列中-------------------------------------------
	for (int i = 0; i < 100; i++)	{
		cin.get(regis);
		if (regis == '\n') i = 1000;
		else{
			infix[i] = regis;
			inlength++;
			for (int u = 1; u < 5; u++){
				if (regis == opr[u]){
					i++;
					infix[i] = ' ';
					inlength++;
				}
			}
		}
	}


	Infix_To_Postfix();

	for (int w = 0; w < PopStart; w++){
		cout << postfix[w];
	}
	system("PAUSE");
	return 0;
}




void push(){
	if ((layernow == -1) || (infix[PushStart] == '(') || (PrioStack[layernow + 1] > PrioStack[layernow])){
		layernow++;
		stack[layernow] = infix[PushStart];
		PushStart++;
	}
	else {
		PrioStack[layernow + 1] = 0;
		PrioStack[layernow] = prio[OprUse];
		pushch();
	}

}


void pop(){
	bool conti = 1;
	if (layernow == -1) conti = 0;
	while (conti){
		postfix[PopStart] = stack[layernow];
		stack[layernow] = NULL;
		PrioStack[layernow] = 0;
		layernow--;
		PopStart++;

		if (stack[layernow] == '('){
			stack[layernow] = NULL;
			PrioStack[layernow] = 0;
			layernow--;
			conti = 0;
		}
		else if (layernow == -1){
			conti = 0;
		}
	}
}

void pushch(){
	postfix[PopStart] = stack[layernow];
	stack[layernow] = infix[PushStart];
	PopStart++;
	PushStart++;
	if (PrioStack[layernow] == PrioStack[layernow - 1]){
		PrioStack[layernow] = 0;
		layernow--;
		postfix[PopStart] = stack[layernow];
		stack[layernow] = stack[layernow + 1];
		stack[layernow + 1] = NULL;
		PopStart++;
	}

}


void Infix_To_Postfix(){
	bool NeedPush = 0;
	for (int z = 0; z < inlength; z++){
		NeedPush = 0;

		for (int k = 0; k < 5; k++){
			if (infix[PushStart] == opr[k]){
				NeedPush = 1;
				OprUse = k;
			}
		}
		if (NeedPush){
			PrioStack[layernow + 1] = prio[OprUse];
			push();

		}
		else if (infix[PushStart] == ')'){
			pop();
			PushStart++;
		}
		else{
			postfix[PopStart] = infix[PushStart];
			PopStart++;
			PushStart++;
		}


		if (z == (inlength - 1)) pop();



	}
}

