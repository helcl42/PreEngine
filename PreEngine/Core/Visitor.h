#ifndef VISITOR_H
#define VISITOR_H


template <class VisitableType>
class IVisitor
{
public:
	virtual void Visit(VisitableType* visitable) = 0;

public:
	virtual ~IVisitor() {}
};

template <class VisitableType>
class IVisitable
{
public:
	template <typename VisitorType>
	void Accept(VisitorType* visitor)
	{
		visitor->Visit(static_cast<VisitableType*>(this));
	}

public:
	virtual ~IVisitable() {}
};

//////////////////////////////////////////////////
// Usage
//////////////////////////////////////////////////

/*class Visitable1 : public IVisitable<Visitable1>
{
};

class Visitable2 : public IVisitable<Visitable2>
{
};

class Visitor : public IVisitor<Visitable1>, public IVisitor<Visitable2>
{
public:
	void Visit(Visitable1* c)
	{
		std::cout << "1" << std::endl;
	}
	void Visit(Visitable2* c)
	{
		std::cout << "2" << std::endl;
	}

public:
	virtual ~Visitor() {}
};


// Client
int main(int argc, char** argv)
{
	Visitor visitor;
	Visitable1 visitable1;
	Visitable2 visitable2;

	visitable1.Accept<Visitor>(&visitor);
	visitable2.Accept<Visitor>(&visitor);
}*/

#endif