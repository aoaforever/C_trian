#include <string>
#include <iostream>

using namespace std;

class Shape{
public:
    virtual void draw() = 0;
};

class Rectangle :public Shape{
public:
    void draw() override {
        cout<<"Rectangle::draw()"<<endl;
    }
};

class Square: public Shape{
public:
    void draw() override{
        cout<<"Square::draw()"<<endl;
    }
};

class ShapeFactory{
public:
    Shape* getShape(string shapetype){
        if(shapetype.empty()){
            return nullptr;
        }
        if(shapetype=="RECTANGLE"){
            return new Rectangle();
        }
        else if(shapetype=="SQUARE"){
            return new Square();
        }
        return nullptr;
    }
};

int main(){
    ShapeFactory f;
    Shape* s = f.getShape("SQUARE");
    // if(s==nullptr) {
    //     cout<<"nullptr"<<endl;
    //     return 0;
    // }
    // Shape * c = new Shape();
    // c->draw();
    s->draw();
    Rectangle* ss = dynamic_cast<Rectangle*>(s);
    ss->draw();

    return 0;
}