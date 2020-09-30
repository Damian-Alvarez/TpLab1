#ifndef ARRAYEMPLOYEES_H_INCLUDED
#define ARRAYEMPLOYEES_H_INCLUDED

typedef struct{

int id;
char name[51];
char lastName[51];
float salary;
int sector;
int isEmpty;

}sEmployee;

int initEmployees(sEmployee listEmployees[], int len);
int mostrarUnEmpleado(sEmployee listEmployees[], int len, int index);
int printEmployees(sEmployee listEmployees[], int len);
int buscarLibre(sEmployee listEmployees[], int len);
int addEmployees(sEmployee listEmployees[], int len, int id, char* name, char* lastName, float salary, int sector);
int altaEmpleados(sEmployee listEmployees[], int len);
int findEmployeeById(sEmployee listEmployees[], int len, int id);
int modificarEmpleado(sEmployee listEmployees[], int len);
int removeEmployee(sEmployee listEmployees[], int len, int id);
int borrarEmpleado(sEmployee listEmployees[], int len);
void swapEmployee(sEmployee listEmployees [], int i);
int sortEmployees(sEmployee listEmployees[], int len, int order);
int cantidadEmpleadosQueSuperanElPromedio(sEmployee listEmployees[], int len, float promedioSalarios);
int totalYPromedioSalariosEmpleados(sEmployee listEmployees[], int len);


#endif
