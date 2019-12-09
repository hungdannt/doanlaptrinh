#include "DBhelper.h"
#include <iostream>
using namespace std;
char SQLQuery[] = "SELECT * FROM student";
void DBhelper::setup() {
    SQLEnvHandle = NULL; 
	SQLHANDLE SQLConnectionHandle = NULL;
	SQLHANDLE SQLStatementHandle = NULL;
	SQLRETURN retCode = 0;
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			close();

	if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govervn aspects of environments
			close();

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			close();
	if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			close();

	switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=myDB; UID=myID; PWD=myPW;", SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
		// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;

		case SQL_SUCCESS_WITH_INFO:
			break;
			
		case SQL_INVALID_HANDLE:
			cout << "Could not connect to SQL Server";
			cout << "\n";
			close();
			break;

	    case SQL_ERROR:
			cout << "Could not connect to SQL Server";
			cout << "\n";
			close();
			break;

		default:
			break;
	}
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
	 	close();

}
void DBhelper::execute() {
 		//output
	cout << "\n";
	cout << "Executing T-SQL query...";
	cout << "\n";
	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS)) {
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {

		char name[64];
		char age[64];
		while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {

			SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &name, sizeof(name), NULL);
			SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &age, sizeof(name), NULL);
			//display query result
			cout << name << " " << age << endl;
		}
	}
}



void DBhelper::close() {
	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	getchar();
}
 

