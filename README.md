# MES-EX-03
MES Exercise 3.2

This is a simple program to simulate the workings of READ, WRITE and ERASE commands to a SPI Flash Memory (Winbond W25Q80DV).

Currently the program supports a memory table of up to 64KB, which would be 1 Bock of the memory chip. Each block has 16 Sectors of 4KB.

In order to better visualize the operations to memory, it is useful to use a smaller memory table.

The program first creates a memory table in a *.txt file (if the file does not exist). 

Then a READ test is carried out. The program takes the desired address and number of Bytes to read, scans the file and prints to the console.

Afterwards, the WRITE test is done. A test buffer to be written to memory is loaded, and its size and starting address are used by the write function to place data correctly in the memory. Then, the program scans the file again and prints to the console - there it is possible to see the test data was written as expected.

Finally, the ERASE test is made. This function erases a whole sector by placing zeroes on each address of that sector. Once more, the program scans the file and prints to the console.

This version is not comprehensive, but these 3 functions worked fine for several conditions. There’s even a test to check if the Bytes to read exceed the memory addresses, avoiding reading garbage data.
