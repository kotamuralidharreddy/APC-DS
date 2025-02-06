# APC-DS
 Arbitrary-precision arithmetic, also called big-num arithmetic, multiple precision arithmetic, or sometimes infinite-precision arithmetic, indicates that calculations are performed on numbers whose digits of precision are limited only by the available memory of the host system.
Some example applications include: 

A common application is public-key cryptography, whose algorithms commonly employ arithmetic with integers having hundreds of digits.
Arbitrary precision arithmetic is also used to compute fundamental mathematical constants such as π to millions or more digits.
The goal of this project is to implement various mathematical operations of given two big numbers by storing in an Abstract Data Type (ADT) like linked list.

 

Data Structres Projects Explore the intersection of data structures and arithmetic with our projects and extend your skills through our calculator project in C. For our implementation following mathematical operations are considered: 

Addition (+)
Subtraction (-)
Multiplication (*)
Division (/)
Modulus (%)
Power (^)
Given the two big numbers it has to be sliced and stored across different nodes of the linked list. Depending on the type of operation performed it should create a result linked list and stored the output. It should also take care of printing the given output from the newly crated output list. Appropriate handling of specific things (ex: carry forward) need to be taken care during implementation. All operations should work for integer numbers and also for numbers with decimal point. Slice the numbers according to sizeof(int), should be portable across different machines.

During the implementation special care need to be taken for handling zero inputs by reducing the work and optimizing the program. Similar to zero input, there can be multiple corner cases / optimization opportunities, which need to be taken care appropriately. If any one of the given input number is zero, the following Algorithm can be applied. 

If Num1 = 0 and Num2 = x, then directly print Num2 as output.
If Num1 = x and Num2 = 0, then directly print Num1 as output.
If Num1 = 0 and Num2 = 0, then directly print 0 as output
