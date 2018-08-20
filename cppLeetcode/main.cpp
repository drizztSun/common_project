#include <stdlib.h>

void leetcode();

int main() {


	leetcode();



}




/**
CodingPuzzle 86 87
**/

int removeDuplicate(int* A, int len)
{

	int index = 0;
	for (int i = 0; i < len; i++)
	{
		if (A[index] == A[i]) {
			continue;
		}

		A[++index] = A[i];
	}

	return index + 1;
}


int count = 1;
int removeDuplicate2(int* A, int len)
{

	int index = 0;
	for (int i = 0; i < len; i++)
	{
		if (A[index] == A[i]) {
			if (count == 2)
				continue;

			count++;
		}
		else {
			count = 1;
		}

		A[++index] = A[i];
	}

	return index + 1;
}


/***
*
**/
bool isMatch(const char* pStr, const char* pPatten)
{
	char *s;
	char *start = const_cast<char*>(pStr);
	char *p = const_cast<char*>(pPatten);
	char *pS = p;
	bool isStar = false;

	for (s = start; *s != '\0'; s++, p++)
	{
		switch (*p) {
		case '?':
			break;
		case '*':
		{
			isStar = true;
			start = s;
			pS = p;

			while (*pS == '*') pS++;

			if (pS == '\0')
				break;

			s = start - 1;
			p = pS - 1;
		}
		break;
		default:
		{
			if (*s != *p) {

				if (!isStar)
					return false;

				start++;
				s = start - 1;
				p = pS - 1;
			}
		}
		}
	}


	while (*p == '*')
		p++;

	return *p == '\0';
}
