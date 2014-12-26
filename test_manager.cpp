#include "manager.hpp"
#include <vector>
#include <iostream>

int main() {
    try {
    Manager manager;
    std::vector<Type> types;
    Type type(TYPE_INT, false, 4, "id");
    types.push_back(type);
    manager.CreateTable("test", types); 

    std::vector<Object> objects;
    std::vector<std::vector<Object>> obj_vec;
    int id = 4;
    Object object(&id, 4, TYPE_INT, true);
    objects.push_back(object);
    obj_vec.push_back(objects);
    std::string str = "test";
    manager.Insert(str, obj_vec);

    TableDesc desc;
    desc.colSize = 1;
    desc.colType[0] = type;
    ReadExpr lexpr("test", "id");
    Table* table = manager.getTable("test", false);
    lexpr.Use("test", "", &desc, NULL); 
    LiteralManager lmanager;
    Object obj = lmanager.GetInt(4);
    LiteralExpr rexpr(obj);
    Condition cond;
    cond.l = &lexpr;
    cond.r = &rexpr;
    cond.op = op_eq;
    std::vector<Condition> conds;
    conds.push_back(cond);
    manager.Update(str, conds, lexpr, obj);  

    manager.Select("test", "", conds);

    manager.Delete("test", conds);

    } catch (const char* ex) {
        std::cout << ex << std::endl;
    }
}
