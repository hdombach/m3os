#include "node.hpp"


//These are not nodes that are helpful for abstracting away the defualt thingies.

class DefCharNode: public DefStructNode {
	DefCharNode();

	virtual operator string() const;

	virtual int getAllocatedSize();
};

class DefShortNode: public DefStructNode {
	DefShortNode();
};

class DefIntNode: public DefStructNode {
	DefIntNode();

	virtual operator string() const;

	virtual int getAllocatedSize();
};

class DefLongNode: public DefStructNode {
	DefLongNode();
	
	virtual operator string() const;

	virtual int getAllocatedSize();
};

class DefFloatNode: public DefStructNode {
	DefFloatNode();

	virtual operator string() const;

	virtual int getAllocatedSize();
};

class DefDoubleNode: public DefStructNode {
	DefDoubleNode();

	virtual operator string() const;

	virtual int getAllocatedSize();
};
