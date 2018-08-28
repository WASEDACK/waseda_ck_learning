#include <iostream>

using namespace std;



struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
     ListNode* l3=new ListNode(0);
     ListNode* tail=l3;
    while(l1!=NULL&&l2!=NULL)
    {
    	tail->next=new ListNode((l1->val+l2->val)%10);
    	tail=tail->next;
    	if(l1->val+l2->val<10)
    	{
	    	if(l1->next==NULL&&l2->next!=NULL)
	    		{
	    			l2=l2->next;
	    		    l1->val=0;
	    		}
	    	else if(l2->next==NULL&&l1->next!=NULL)
	    		{
		    		l1=l1->next;
		    		l2->val=0;
	    		}	
	    	else if(l2->next!=NULL&&l1->next!=NULL)
	    		{
	    			l1=l1->next;
	    			l2=l2->next;
	    		}
	    	else 
	    		{
	    			l1=l1->next;
	    			l2=l2->next;
	    		}
	    }
    	else
    	{
    		if(l1->next==NULL&&l2->next!=NULL)
	    		{
	    			l2=l2->next;
	    		    l1->val=1;
	    		}
	    	else if(l2->next==NULL&&l1->next!=NULL)
	    		{
		    		l1=l1->next;
		    		l2->val=1;
	    		}	
	    	else if(l2->next!=NULL&&l1->next!=NULL)
	    		{
	    			l1=l1->next;
	    			l2=l2->next;
	    			l1->val=l1->val+1;
	    		}
	    	else 
	    		{
	    			l1->next=new ListNode(1);
					l1=l1->next;
	    			l2=l2->next;
	    		}

	    		

    	}

    	
    }
    tail=l3->next;
     return tail;
   
    }
};




void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

ListNode* stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

string listNodeToString(ListNode* node) {
    if (node == nullptr) {
        return "[]";
    }

    string result;
    while (node) {
        result += to_string(node->val) + ", ";
        node = node->next;
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
}

int main() {
    string line;
    while (getline(cin, line)) {
        ListNode* l1 = stringToListNode(line);
        getline(cin, line);
        ListNode* l2 = stringToListNode(line);
        
        ListNode* ret = Solution().addTwoNumbers(l1, l2);

        string out = listNodeToString(ret);
        cout << out << endl;
    }
    return 0;
}