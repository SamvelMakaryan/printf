#include <iostream>
#include <string>

void put(bool, bool, bool, std::string&);
void parenthes(std::string&);
std::string parser(std::string);
bool isXFake(const std::string&);
bool isYFake(const std::string&);
bool isZFake(const std::string&);
std::string KKNDZ(const std::string&, bool*, bool*, bool*);
std::string KDNDZ(const std::string&, bool*, bool*, bool*);
std::string jegalkin(const std::string&);
std::string deleteingFictives(std::string, bool*, bool*, bool*);
void Not(std::string&);
void And(std::string&);
void Or(std::string&);
void Xor(std::string&);
void Imp(std::string&);
void Nand(std::string&);
void Nor(std::string&);
void Nxor(std::string&);
bool checkParenthese(const std::string&);

int main() {
	bool x[] {0, 0, 0, 0, 1, 1, 1, 1};
	bool y[] {0, 0, 1, 1, 0, 0, 1, 1};
	bool z[] {0, 1, 0, 1, 0, 1, 0, 1};
	std::string s;
	std::string truthVector;
	do {
		std::cout << "Input your function\n";
		getline(std::cin, s);
	} while(!checkParenthese(s));
	s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
	s = '(' + s;
	s += ')';
	for (int i = 0; i < 8; ++i) {
		std::string sCopy(s);
		put(x[i], y[i], z[i], sCopy);	
		parenthes(sCopy);
		truthVector += sCopy;
	}
	std::cout << "\nThe truth vector is\n\t";
	std::cout << truthVector << std::endl;
	bool isXFictive = isXFake(truthVector);
	bool isYFictive = isYFake(truthVector);
	bool isZFictive = isZFake(truthVector);
	std::cout << "\nVariable X is " << (isXFictive ? "significant\n" : "fictious\n"); 
	std::cout << "Variable Y is " << (isYFictive ? "significant\n" : "fictious\n"); 
	std::cout << "Variable Z is " << (isZFictive ? "significant\n" : "fictious\n"); 
	if (!isXFictive && !isYFictive && !isZFictive) {
		std::cout << "\nAll mebers are fictious\n";
	}
	else if (isXFictive && isYFictive && isZFictive) {
		std::cout << "\nAll members are significant\n";
	}
	else {
		std::cout << "\nFunction without fictious\n\t";
		std::cout << deleteingFictives(truthVector, x, y, z) << std::endl;
	}
	std::cout << "\nKKNDZ\n";
	std::cout << KKNDZ(truthVector, x, y, z) << std::endl;
	std::cout << "\nKDNDZ\n";
	std::cout << KDNDZ(truthVector, x, y, z)<< std::endl;
	std::cout << "\npolynomial of Zhegalkin\n";
	std::cout << jegalkin(truthVector) << std::endl;	
}

void put(bool x, bool y, bool z, std::string& s) {
	for (auto& i : s) {
		if (i == 'x') {
			i = x + '0';
		}
		else if (i == 'y') {
			i = y + '0';
		}
		else if (i == 'z') {
			i = z + '0';
		}
	}
}

void parenthes(std::string& s) {
	std::string tmp;
	while (s.find('(') != -1) {
		int pos = s.rfind('(');
		int count = pos;
		while (s[count++] != ')');
		tmp = parser(s.substr(pos + 1, count - pos - 2));
		s.erase(pos, count - pos);
		s.insert(pos, tmp);
	}
}

std::string parser(std::string s) {
	Not(s);
	And(s);
	Or(s);
	Imp(s);
	int i = 0;
	std::string tmp;
	while(s.find('~') != -1 || s.find('/') != -1 || s.find('|') != -1 || s.find('^') != -1) {
		switch(s[i]) {
			case '~':
				tmp = s.substr(i - 1, 3);
				Nxor(tmp);
				s.erase(i - 1, 3);
				s.insert(i - 1, tmp);
				--i;
				break;
			case '/':
				tmp = s.substr(i - 1, 3);
				Nor(tmp);
				s.erase(i - 1, 3);
				s.insert(i - 1, tmp);
				--i;
				break;
			case '|':
				tmp = s.substr(i - 1, 3);
				Nand(tmp);
				s.erase(i - 1, 3);
				s.insert(i - 1, tmp);
				--i;
				break;
			case '^':
				tmp = s.substr(i - 1, 3);
				Xor(tmp);
				s.erase(i - 1, 3);
				s.insert(i - 1, tmp);
				--i;
				break;
		}
		++i;
	}
	return s;
}

void Not(std::string& s) {
	char tmp;
	while (s.find('!') != -1) {
		int pos = s.find('!');
		if (s[pos + 1] == '1') {
			tmp = '0';
		}
		else {
			tmp = '1';
		}
		s.erase(pos, 2);
		s.insert(s.begin() + pos, tmp);
	}
}

void And(std::string& s) {
	char tmp;
	while (s.find('&') != -1) {
		int pos = s.find('&');
		if (s[pos - 1] == '1' && s[pos + 1] == '1') {
			tmp = '1';
		}
		else {
			tmp = '0';
		}
		s.erase(pos - 1 , 3);
		s.insert(s.begin() + pos - 1, tmp);
	}
}

void Or(std::string& s) {
	char tmp;
	while (s.find('v') != -1) {
		int pos = s.find('v');
		if (s[pos - 1] == '0' && s[pos + 1] == '0') {
			tmp = '0';
		}
		else {
			tmp = '1';
		}
		s.erase(pos - 1 , 3);
		s.insert(s.begin() + pos - 1, tmp);
	}
}

void Xor(std::string& s) {
	char tmp;
	while (s.find('^') != -1) {
		int pos = s.find('^');
		if ((s[pos - 1] == '0' && s[pos + 1] == '0') || (s[pos - 1] == '1' && s[pos + 1] == '1')) {
			tmp = '0';
		}
		else {
			tmp = '1';
		}
		s.erase(pos - 1 , 3);
		s.insert(s.begin() + pos - 1, tmp);
	}
}

void Imp(std::string& s) {
	char tmp;
	while (s.find("->") != -1) {
		int pos = s.find("->");
		if (s[pos - 1] == '1' && s[pos + 2] == '0') {
			tmp = '0';
		}
		else {
			tmp = '1';
		}
		s.erase(pos - 1, 4);
		s.insert(s.begin() + pos - 1, tmp);
	}
}

void Nand(std::string& s) {
	char tmp;
	while (s.find('|') != -1) {
		int pos = s.find('|');
		if (s[pos - 1] == '1' && s[pos + 1] == '1') {
			tmp = '0';
		}
		else {
			tmp = '1';
		}
		s.erase(pos - 1, 3);
		s.insert(s.begin() + pos - 1, tmp);
	}
}

void Nxor(std::string& s) {
	char tmp;
	while (s.find('~') != -1) {
		int pos = s.find('~');
		if ((s[pos - 1] == '1' && s[pos + 1] == '1') || (s[pos - 1] == '0' && s[pos + 1] == '0')) {
			tmp = '1';
		}
		else {
			tmp = '0';
		}
		s.erase(pos - 1, 3);
		s.insert(s.begin() + pos - 1, tmp);
	}
} 

void Nor(std::string& s) {
	char tmp;
	while (s.find('/') != -1) {
		int pos = s.find('/');
		if (s[pos - 1] == '0' && s[pos + 1] == '0') {
			tmp = '1';
		}
		else {
			tmp = '0';
		}
		s.erase(pos - 1, 3);
		s.insert(s.begin() + pos - 1, tmp);
	}
}

bool isXFake(const std::string& s) {
	if (s[0] == s[4] && s[1] == s[5] && s[2] == s[6] && s[3] == s[7]) {
		return false;
	}
	return true;
}

bool isYFake(const std::string& s) {
	if (s[0] == s[2] && s[1] == s[3] && s[4] == s[6] && s[5] == s[7]) {
		return false;
	}
	return true;
}

bool isZFake(const std::string& s) {
	if (s[0] == s[1] && s[2] == s[3] && s[4] == s[5] && s[6] == s[7]) {
		return false;
	}
	return true;
}

std::string KKNDZ(const std::string& s, bool* x, bool* y, bool* z) {
	std::string kkndz;
	for (int i = 0; i < 8; ++i) {
		if (s[i] == '0') {
			kkndz += '(';
			kkndz += (x[i] == 0 ? "x" : "!x");
			kkndz += 'v';
			kkndz += (y[i] == 0 ? "y" : "!y");
			kkndz += 'v';
			kkndz += (z[i] == 0 ? "z" : "!z");
			kkndz += ')';
			kkndz += '&';
		}
	}
	kkndz.erase(kkndz.begin() + kkndz.size() - 1);
	return kkndz;
}

std::string KDNDZ(const std::string& s, bool* x, bool* y, bool* z) {
	std::string kdndz;
	for (int i = 0; i < 8; ++i) {
		if (s[i] == '1') {
			kdndz += '(';
			kdndz += (x[i] == 1 ? "x" : "!x");
			kdndz += '&';
			kdndz += (y[i] == 1 ? "y" : "!y");
			kdndz += '&';
			kdndz += (z[i] == 1 ? "z" : "!z");
			kdndz += ')';
			kdndz += 'v';
		}
	}
	kdndz.erase(kdndz.begin() + kdndz.size() - 1);
	return kdndz;
}

std::string deleteingFictives(std::string s, bool* x, bool* y, bool* z) {
	bool isXFict = isXFake(s);
	bool isYFict = isYFake(s);
	bool isZFict = isZFake(s);
	int count = 0;
	std::string index(s);
	for (int i = 0; i < 8; ++i) {
		if (!isXFict && x[i] == 1) {
			index.insert(index.begin() + i + count, '$');
			++count;
			continue;	
		}
		if (!isYFict && y[i] == 1) {
			index.insert(index.begin() + i + count, '$');
			++count;
			continue;
		}
		if (!isZFict && z[i] == 1) {
			index.insert(index.begin() + i + count, '$');
			++count;
			continue;
		}
	}
	while (index.find('$') != -1) {
		index.erase(index.find('$'), 2);
	}
	return index;
}

bool checkParenthese(const std::string& s) {
	int countL = 0;
	int countR = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '(') {
			++countL;
		}
		else if (s[i] == ')') {
			++countR;
		}
	}
	if (countL != countR) {
		std::cout << "Count of '(' doesn't match with ')'\n";
		return false;
	}
	return true;
}

std::string jegalkin(const std::string& s) {
	bool b[8];			 
	std::string formula = "b ^ b&z ^ b&y ^ b&y&z ^ b&x ^ b&x&z ^ b&x&y ^ b&x&y&z";
	b[0] = (int)(s[0] - '0');
	b[1] = b[0] ^ (int)(s[1] - '0');
	b[2] = b[0] ^ (int)(s[2] - '0');
	b[3] = b[0] ^ b[1] ^ b[2] ^ (int)(s[3] - '0');
	b[4] = b[0] ^ (int)(s[4] - '0');
	b[5] = b[0] ^ b[1] ^ b[4] ^ (int)(s[5] - '0');
	b[6] = b[0] ^ b[2] ^ b[4] ^(int)(s[6] - '0');
	b[7] = b[0] ^ b[1] ^ b[2] ^ b[3] ^ b[4] ^ b[5] ^ b[6] ^ (int)(s[7] - '0');
	for (int i = 0 ; i < 8; ++i) {
		int pos = formula.find('b');
		if (!b[i]) {
			if (i == 7) {
				formula.erase(pos, formula.size() - pos - 1);
				continue;
			}
			formula.erase(pos, formula.find('b', pos + 1) - pos);
		}
		else {
			if (i == 0) {
				formula.erase(pos, 1);
				formula = '1' + formula;
				continue;
			}
			formula.erase(pos, 2);
		}
	}
	return formula;
}
