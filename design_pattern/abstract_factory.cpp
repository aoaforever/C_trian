//抽象工厂类，说白了就是工厂的工厂。大工厂管理很多小工厂。主函数调用大工厂来获得各个小工厂的对象。
//https://www.runoob.com/design-pattern/abstract-factory-pattern.html
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


class Color{
public:
    virtual void fill() =0;
};

class Red : public Color{
public:
    void fill(){
        cout<<"Red::fill()"<<endl;
    }
};

class Green : public Color{
public:
    void fill(){
        cout<<"Green::fill()"<<endl;
    }
};


//抽象工厂类
class AbstractFactory{
public:
    virtual Color* getColor(string color)=0;
    virtual Shape* getShape(string shape)=0;
};

class ShapeFactory: public AbstractFactory{
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
    Color* getColor(string color){
        return nullptr;
    }
};

class ColorFactory: public AbstractFactory{
public:
    Color* getColor(string colortype){
        if(colortype.empty()){
            return nullptr;
        }
        if(colortype=="RED"){
            return new Red();
        }
        else if(colortype=="GREEN"){
            return new Green();
        }
        return nullptr;
    }

    Shape* getShape(string shape){
        return nullptr;
    }
};


//创建一个工厂创造器、生成器类，通过传递形状或颜色信息来获取工厂
class FactoryProducer{
public:
    static AbstractFactory* getFactory(string choice){
        if(choice=="SHAPE"){
            return new ShapeFactory();
        }
        else if(choice=="COLOR"){
            return new ColorFactory();
        }
        return nullptr;
    }
};

int main(){
    //通过FactoryProducer获取AbstractFactory,通过传递类型信息来获取实体类的对象
    AbstractFactory* sf = FactoryProducer::getFactory("SHAPE");
    Shape* s1 = sf->getShape("RECTANGLE");
    s1->draw();

    Shape* s2 = sf->getShape("SQUARE");
    s2->draw();

    AbstractFactory* cf = FactoryProducer::getFactory("COLOR");
    Color* c1 = cf->getColor("RED");
    c1->fill();

    Color* c2 = cf->getColor("GREEN");
    c2->fill();
    return 0;
}