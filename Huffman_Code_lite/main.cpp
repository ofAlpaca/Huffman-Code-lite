//
//	Algorithms Analysis - Huffman Code v1.1
//	- main.cpp
//
//	Created by ShauShian, Chiang on 2017/06/11.
//	Copyright @ 2017 ShauShian, Chiang. All rights reserved.

#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;
int static num_of_topic;

class Node {
public:
	Node(char _ch, int _fq);
	Node(Node*left, Node*right);
	char ch;
	int fq;
	Node * left_chd;
	Node * right_chd;
};

Node::Node (char _ch, int _fq) {
	ch = _ch;
	fq = _fq;
	left_chd = NULL;
	right_chd = NULL;
}

Node::Node(Node * left, Node * right) {
	ch = '\0';
	fq = left->fq + right->fq;
	left_chd = left;
	right_chd = right;
}

class HuffmanCode {
private:
	string text;
	vector<Node*> hTree;
	map<char, string> codes;

public:
	void insert_to( Node * node ) {
		bool end_flag = true;
		vector<Node*>::iterator it;
		if (hTree.empty()) {
			hTree.push_back(node);
			end_flag = false;
		}

		for (it = hTree.begin(); it != hTree.end(); it++) {
			if ((*it)->fq > node->fq) {	// If the freq of incoming node is smaller than the current node.
				hTree.insert(it, node);
				end_flag = false;
				break;
			}
		}
		if (end_flag) hTree.push_back(node);
	}

	void huffman_encode() {
		Node * newNode;
		while (hTree.size() > 1) { // Until there is only one node.
			newNode = new Node(hTree[0], hTree[1]); // Take the top two smallest node.
			hTree.erase(hTree.begin(), hTree.begin() + 2);
			insert_to(newNode); // Insert a new merged node to the tree.
		}

		make_huffman_code(hTree[0], "");
	}

	void make_huffman_code(Node * root, string code) {
		if (root->left_chd != NULL) {
			code += '0';
			make_huffman_code(root->left_chd, code);
			code.pop_back();
		}

		if (root->right_chd != NULL) {
			code += '1';
			make_huffman_code(root->right_chd, code);
			code.pop_back();
		}

		if (root->left_chd == NULL && root->right_chd == NULL) {
			codes[root->ch] = code;
		}
	}
	
	void huffman_decode(string decode) {
		text = "";
		string tmp = "";
		map<char, string>::iterator it;
		int i = 0, j = 0;
		for (i = 1; i < decode.size(); i++) {
			tmp = decode.substr(j, i);
			for (it = codes.begin(); it != codes.end(); it++) {
				if (it->second == tmp) { // If find the code in the tmp.
					text += it->first;
					j += i;
					i = 1;
					break;
				}
			}
		}
	}

	void print_codes() {
		map<char, string>::iterator it;
		for (it = codes.begin(); it != codes.end(); it++) {
			cout << it->first << " " << it->second << endl;
		}
	}

	void print_decode_text(){
		cout << "\nHuffman Codes #" << num_of_topic << endl;
		print_codes();
		cout << "Decode = " << text << endl << endl;
	}
};

int main() {
	int count = 0;
	num_of_topic = 1;
	char ch;
	int freq;
	string decode_text = "";
	Node * newOne;
	HuffmanCode * c;

	cin >> count;
	while (count != 0) {
		c = new HuffmanCode();;
		for (int i = 0; i < count; i++) {
			cin >> ch >> freq;
			newOne = new Node(ch, freq);
			c->insert_to(newOne);
		}
		cin >> decode_text;

		c->huffman_encode();
		c->huffman_decode(decode_text);
		c->print_decode_text();
		delete c;

		cin >> count;
		num_of_topic++;
	}
	system("pause");
	return 0;
}