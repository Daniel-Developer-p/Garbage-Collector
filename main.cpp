#include<memory>
#include<new>
 
class Parent {
    public:
        virtual~Parent(){}
};
 
class SomeObject {
    public:
        virtual~SomeObject(){}
};
 
class Child : public SomeObject, public Parent {
    public:
};
 
int main()
{
    //delete без проблем удаляет объект Child по Parent* указателю
    Parent*object=new Child;
    delete object;
 
    std::allocator<Parent> parentAllocator;
    std::allocator<Child> childAllocator;
 
    //создаем массив разномастных потомков Parent.
    //Информация о реальном типе полиморфного объекта теряется
    Parent*array[2]={new (parentAllocator.allocate(1)) Parent,
                     new (childAllocator.allocate(1)) Child};
    //опять пытаемся удалить объект Child по Parent* указателю. Опс, программа падает
    parentAllocator.deallocate(array[1],1);
    return 0;
}
