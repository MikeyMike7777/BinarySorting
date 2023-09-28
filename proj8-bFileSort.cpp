/* file: proj8-bFileSort.cpp
* author: Michael Mathews
* course: CSI 1440
* assignment: project 8
* due date: 11/8/2021
*/

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    //uses initially empty file, sortedInts,
    int X, len, count = 0;
    bool done = false;
    fstream file;

    //open file
    file.open("sortedInts", ios::binary | ios::in | ios::out);

    //make sure file is open
    if (!file) {
        cerr << "Bad";
        return 1;
    }

    //outputs list of stored integers to screen

    //go to end of file
    file.seekg(0, ios::end);
    //count how many bytes
    len = file.tellg();

    //declare array
    int* data = new int[(len/4 + 4)];

    //read integer and print
    for (int i = 0, j = 0; i < len; i+=sizeof(int), j++) {
        //read int every 4th
        file.seekg(i);
        file.read((char*) &data[j], sizeof(int));
        //print each element
        cout << data[j] << " ";
        //keep track of size of array
        count++;
    }
    cout << endl;


    //asks user to enter new integer X
    cout << "Please enter a new integer" << endl;
    cin >> X;

    if(data[count-1] <= X) {
        data[count] = X;
        file.seekp(count*sizeof(int), ios::beg);
        file.write((char*) &data[count], sizeof(int));
    }
    else {
        int i = count-1;
        while(!done){
            //if first element
            if(i == -1) {
                i++;
                done = true;
            }
            //if greater than number
            else if(data[i] > X) {
                data[i+1] = data[i];
                i--;
            }
            //if less than or equal to number
            else {
                done = true;
                i++;
            }
        }

        data[i] = X;

        //rewrite data to file starting from new number
        while(i <= count) {
            file.seekp(i*sizeof(int), ios::beg);
            file.write((char*) &data[i], sizeof(int));
            i++;
        }
    }

    delete [] data;

    file.close();

    return 0;
}
