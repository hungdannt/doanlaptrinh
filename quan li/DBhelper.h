#pragma once
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include "Student.h"
class DBhelper 
{
    SQLHANDLE SQLEnvHandle ;
    SQLHANDLE SQLConnectionHandle;
    SQLHANDLE SQLStatementHandle;
    SQLRETURN retCode;
    SQLCHAR retconstring[1024];
public:
    void setup();
    void execute();
    Student* getStudents();
    void close();

};
