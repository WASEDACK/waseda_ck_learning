#include <iostream>

class Solution {
public:
    string longestPalindrome(string s) {
   int length=s.size();
    if(length<=1)return s;
        bool J[length][length];
for(int x=0;x<length;x++){
    for(int y=0;y<length;y++)
        J[x][y]=0;
}
        int left ,right;
        left=right=0;
        
       for(int i=0;i<length;i++)
        {  J[i][i]=true;
         
            
        }
          for(int i=1;i<length;i++)
        {  J[i][i-1]=true;
         
            
        }
        for(int k=2;k<=length;k++){
            for(int m=0;m<=length-k;m++)
            {
                if(s[m]==s[m+k-1]&&J[m+1][m+k-2]==true)
                {
                    J[m][m+k-1]=true;
                    left=m;
                    right=m+k-1;

                }
            }

        }
        return s.substr(left,right-left+1);


    }
};

string stringToString(string input) {
    assert(input.length() >= 2);
    string result;
    for (int i = 1; i < input.length() -1; i++) {
        char currentChar = input[i];
        if (input[i] == '\\') {
            char nextChar = input[i+1];
            switch (nextChar) {
                case '\"': result.push_back('\"'); break;
                case '/' : result.push_back('/'); break;
                case '\\': result.push_back('\\'); break;
                case 'b' : result.push_back('\b'); break;
                case 'f' : result.push_back('\f'); break;
                case 'r' : result.push_back('\r'); break;
                case 'n' : result.push_back('\n'); break;
                case 't' : result.push_back('\t'); break;
                default: break;
            }
            i++;
        } else {
          result.push_back(currentChar);
        }
    }
    return result;
}

int main() {
    string line;
    while (getline(cin, line)) {
        string s = stringToString(line);
        
        string ret = Solution().longestPalindrome(s);

        string out = (ret);
        cout << out << endl;
    }
    return 0;
}