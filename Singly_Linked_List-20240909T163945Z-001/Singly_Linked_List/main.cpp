#include "Singly_Linked_List.h"

//! lệnh chạy, chạy từng lệnh
//^ g++ -o main main.cpp Singly_Linked_List.cpp -I.-std=c++11
//^ ./main file_input -> vd : ./main input.txt

//~ input - check insert and delete -> ./main input.txt
//~ input1 - check Get, IndexOf and Contains -> ./main input1.txt
//~ input2 - check selectionSort, subSingly_Linked_List, reverse -> ./main input2.txt

int main(int argc, char ** argv) {
    string str;
    cout << argv[1] << endl;
    ifstream input(argv[1]);
    Singly_Linked_List list;
    Singly_Linked_List newlist;
    int count = 1;
    while(getline(input, str)){
        stringstream ss(str);
        string signature;
        ss >> signature;
        if(signature == "Insertion")
        {
            int data, index;
            ss >> data >> index;
            list.Insertion(data, index);
            cout << "row " << count << ": ";
            cout << list.Dislay() << '\n';
        }
        else if(signature == "Deletion")
        {
            int index;
            ss  >> index;
            list.Deletion( index);
            cout << "row " << count << ": ";
            cout << list.Dislay() << '\n';
        }
        else if(signature == "Get")
        {
            int index;
            ss  >> index;
            int data = list.Get( index);
            cout << "row " << count << ": ";
            cout << "Data Node " << index <<": " << data << '\n';
        }
        else if(signature == "IndexOf")
        {
            int Data;
            ss  >> Data;
            int index = list.IndexOf( Data);
            cout << "row " << count << ": ";
            cout << "Index Of Data " << Data <<": " << index << '\n';
        }
        else if(signature == "Contains")
        {
            int Data;
            ss  >> Data;
            bool isContains = list.Contains( Data);
            cout << "row " << count << ": ";
            cout << "Contains data " << Data << ": " << (isContains?"true" :"flase")<< '\n';
        }
        else if(signature == "SelecetionSort")
        {
            list.SelecetionSort();
            cout << "row " << count << ": ";
            cout << list.Dislay() << '\n';
        }
        // else if(signature == "MergerSort")
        // {
        //     list.MergerSort();
        //     cout << "row " << count << ": ";
        //     cout << list.Dislay() << '\n';
        // }
        else if(signature == "Concat"){
            //newlist = list.Concat();
        }
        else if(signature == "SubSingly_Linked_List"){
            int from, to;
            ss >> from >> to;
            newlist = list.SubSingly_Linked_List(from, to);
            cout << "row " << count << ": ";
            cout << "newlist :" << newlist.Dislay() << '\n';
        }
        else if (signature == "Reverse"){
            list.Reverse();
            cout << "row " << count << ": ";
            cout << list.Dislay() << '\n';
        }
        count++;
    }

    return 0;
}