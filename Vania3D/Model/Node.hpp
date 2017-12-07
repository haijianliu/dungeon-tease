
#ifndef Node_hpp
#define Node_hpp

template <typename T>
class Node {
public:
	std::string name;
	Node* parent = nullptr;
	std::vector<Node*> children;
	T* data;

	Node() {}

	Node(std::string name) {
		this->name = name;
		this->data = nullptr;
	}

	~Node() {
		if (this->data) delete this->data;
		deleteVector(this->children);
	}
};

#endif /* Node_hpp */
