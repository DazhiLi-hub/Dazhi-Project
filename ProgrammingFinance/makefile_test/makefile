CMP=g++
CMP_para=-Wall -g
Main_N=1_mainPgm.cpp

main: main.o Employee.o CommissionEmployee.o SalariedEmployee.o BasePlusCommissionEmployee.o
	$(CMP) $(CMP_para) -o main main.o Employee.o CommissionEmployee.o SalariedEmployee.o BasePlusCommissionEmployee.o

main.o: $(Main_N) Employee.h CommissionEmployee.h SalariedEmployee.h BasePlusCommissionEmployee.h
	$(CMP) $(CMP_para) -c -o main.o $(Main_N)

BasePlusCommissionEmployee.o: BasePlusCommissionEmployee.cpp CommissionEmployee.h Employee.h
	$(CMP) $(CMP_para) -c -o BasePlusCommissionEmployee.o  BasePlusCommissionEmployee.cpp

CommissionEmployee.o: CommissionEmployee.cpp Employee.h
	$(CMP) $(CMP_para) -c -o CommissionEmployee.o CommissionEmployee.cpp

SalariedEmployee.o: SalariedEmployee.cpp Employee.h
	$(CMP) $(CMP_para) -c -o SalariedEmployee.o SalariedEmployee.cpp

Employee.o: Employee.cpp
	$(CMP) $(CMP_para) -c -o Employee.o Employee.cpp

clean:
	rm *.o main
