#include <bits/stdc++.h>
using namespace std;
int main()
{
	char *s;
	char str[] = "index.html";
	strtok(str, ".");
	char *p = strtok(NULL, ".");
	
	puts(p);
}