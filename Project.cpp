#include <iostream>//for plain input and output
#include <fstream>//for file handling purposes
#include <string>//for string related functionalities
#include <sstream>//for reading records from csv file
#include <stdlib.h>
#include<stack>//for explicit stack working
//#include<conio.h>//for clearing out console
using namespace std;
class Node
{
public:
    // each node is treated like a single contact person
    string number;
    string firstName;
    string lastName;
    string address;
    string email;
    bool favourite;
    Node* left;
    Node* right;
    void setFavourite(Node* ptr)
    {
        cout << "Would you want to add this contact to your favourites contact list? (0 for No or 1 for Yes) ";
        cin >> favourite;
        if (favourite == 1)
        {
            fstream w;
            w.open("Favourites.csv", ios::app);
            w << ptr->firstName << "," << ptr->lastName << "," << ptr->number << "," << ptr->address << "," << ptr->email << "\n";
            cout << endl
            << ptr->number << " added to your list of favourites.";
            w.close();
        }
    }
    bool checkNumber(string no){
        for(int i=0;i<no.length();++i){
            if((no[i]<'0')||(no[i]>'9'))
            return false;
        }
        return true;
    }
    Node()
    {
        fstream fout;
        fout.open("Record.csv", ios::out | ios::app);
        left = right = NULL;
        cout << "Enter first and last name, number, address and email: ";
        fflush(stdin);
        cin >> firstName;
        cin >> lastName;
        cin >> number;
        bool hold=checkNumber(number);
        while(hold==false){
            cout<<endl<<"Enter a valid number: ";
            cin>>number;
            hold=checkNumber(number);
        }
        cin >> address;
        cin >> email;
        setFavourite(this);
        fout << firstName << "," << lastName << "," << number << "," << address << "," << email << "\n";
        fout.close();
    }
    Node(string arr[])
    {
        left = right = NULL;
        firstName = arr[0];
        lastName = arr[1];
        number = arr[2];
        address = arr[3];
        email = arr[4];
    }
    void setFName(string arr)
    {
        firstName = arr;
    }
    void setlName(string arr)
    {
        lastName = arr;
    }
    void setNo(string arr)
    {
        number = arr;
    }
    void setAdd(string arr)
    {
        address = arr;
    }
    void setEmail(string arr)
    {
        email = arr;
    }
};
class Phone
{
private:
    string lowercase(string arr)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] >= 'A' && arr[i] <= 'Z')
            {
                arr[i] = arr[i] + 32;
            }
        }
        return arr;
    }
    Node* minvaluenode(Node* node)
    {
        Node* current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

public:
    Node* root;
    string line, cell;
    stringstream lineStream;
    Phone()
    {
        root = NULL;
    }
    void addContact()
    {
        fflush(stdin);
        system("CLS");
        Node* newnode = new Node();
    }
    Node* constructBST(Node* root, Node* NW)
    {
        if (root == NULL)
            root = NW;
        else{    
		int s1, s2;
        char* name1, * name2;
        s1 = root->firstName.length();
        s2 = NW->firstName.length();
        name1 = new char[s1 + 1];
        strcpy(name1, root->firstName.c_str());
        name2 = new char[s2 + 1];
        strcpy(name2, NW->firstName.c_str());
        if ((strcmp(name2, name1) < 0))
            root->left = constructBST(root->left, NW);
        else if (strcmp(name2, name1) > 0)
            root->right = constructBST(root->right, NW);
        else{
            strcpy(name1, root->lastName.c_str());
            strcpy(name2, NW->lastName.c_str());
            if(strcmp(name2, name1) < 0)
            root->left=constructBST(root->left,NW);
            else if(strcmp(name2, name1) > 0)
            root->right=constructBST(root->right,NW);
        }
        }
        return root;
    }
    void buildBST2(Node *r,char option)
    {
        int i = 0, count = 0;
        char name[] = { "Record.csv" };
        if (remove(name) == 0)
        {
            cout << endl;
            if(option=='m')
            cout << "modified"<<endl;
            else
            cout << "deleted"<<endl;
            cout << endl;
        }
        if(r!=NULL){
        fstream fout;
        fout.open("Record.csv", ios::out);
        stack<Node*> nodeStack;
        nodeStack.push(root);
        while (nodeStack.empty() == false) {
            Node* node = nodeStack.top();
            fout << node->firstName << "," << node->lastName << "," << node->number << "," << node->address << "," << node->email << "\n";
            nodeStack.pop();
            if (node->right)
                nodeStack.push(node->right);
            if (node->left)
                nodeStack.push(node->left);
        }
    }
    }
    void buildBST()
    {
        int i = 0, count = 0;
        fstream fin;
        fin.open("Record.csv", ios::in);
        string array2[5];
        while (getline(fin, line))
        {
            lineStream.clear();
            lineStream.str(line); // reads only the current row and saved in line
            while (getline(lineStream, array2[i], ','))
            {
                if (count == 0)
                {
                    break;
                } // this escapes the first row as in first record which is always root
                ++i;
                // reads the row and saves each field in the array
            }
            if (count == 0)
            {
                ++count;
                continue;
            }// this makes sure that after escaping the first row, it jumps to the second row from here
            Node* temp = new Node(array2);
            // new node created that stores current row record
            constructBST(root, temp);      // creates the actual BST
            i = 0;
        }
        fin.close();
    }
    void modifyContact(string arr, Node* r, string arr2)
    {
        int choice;
        string temp;
        if (r == NULL)
            return;
        if ((r->firstName == arr)&&(r->lastName==arr2))
        { // pre-order traversal
        backToChoices2:
            cout << endl
                << "What would you like to change (1 for first name, 2 for last name, 3 for cell number, 4 for address or 5 for email): ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << endl
                    << "Enter new first name: ";
                cin >> temp;
                r->setFName(temp);
                break;
            case 2:
                cout << endl
                    << "Enter new last name: ";
                cin >> temp;
                r->setlName(temp);
                break;
            case 3:
                cout << endl
                    << "Enter new cell number: ";
                cin >> temp;
                r->setNo(temp);
                break;
            case 4:
                cout << endl
                    << "Enter new address: ";
                cin >> temp;
                r->setAdd(temp);
                break;
            case 5:
                cout << endl
                    << "Enter new email ID: ";
                cin >> temp;
                r->setEmail(temp);
                break;
            default:
                cout << endl
                    << "Invalid choice. Please enter correct choice: ";
                cin >> choice;
                goto backToChoices2;
            }
            int hold=delete_Favourites(arr,arr2);
            if(hold==1){//only if the contact is also present in the favourites.csv
            fstream fout;
            fout.open("Favourites.csv",ios::out|ios::app);
            fout<<r->firstName<<","<<r->lastName<<","<<r->number<<","<<r->address<<","<<r->email<<endl;
            fout.close();
        }
        }
        modifyContact(arr, r->left,arr2);
        modifyContact(arr, r->right,arr2);
    }
    void viewFavourites()
    {
        cout << "First Name | "
            << "\t"
            << "Last Name | "
            << "\t"
            << "   No. | "
            << "\t\t"
            << "Address | "
            << "\t\t"
            << "Email " << endl
            <<"-------------------------------------------------------------------------------------------------"<<endl;
        fstream fin;
        fin.open("Favourites.csv", ios::in);
        while (getline(fin, line))
        {
            lineStream.clear();
            lineStream.str(line);
            while (getline(lineStream, cell, ','))
                cout << cell << "\t\t";
            cout << endl;
        }
        fin.close();
    }
    void searchContact(Node* r, string arr)
    {
        static int temp = 0;
            if (root == NULL)
            return;
        stack<Node*> nodeStack;
        nodeStack.push(r);
        while (nodeStack.empty() == false) {
            Node* node = nodeStack.top();
            if (lowercase(node->firstName) == lowercase(arr))
            {
                ++temp;
                cout << "---------------------------------------------"<<endl
                <<"First Name: " << node->firstName << endl
                    << "Last Name: " << node->lastName << endl
                    << "Cell No. " << node->number << endl
                    << "Address: " << node->address << endl
                    << "Email: " << node->email<<endl
                    <<"---------------------------------------------";
            }
            nodeStack.pop();
            if (node->right!=NULL)
                nodeStack.push(node->right);
            if (node->left!=NULL)
                nodeStack.push(node->left);
        }
        if(temp==0)
        cout<<endl<<"No such contact exists.";
    }
    void viewAllContacts(Node* r)
    {
        if (r == NULL)
            return;
        viewAllContacts(r->left);
        cout << endl
            << r->firstName << " " << r->lastName;
        viewAllContacts(r->right);
    }
    int delete_Favourites(string name, string lname)
    {
        int count, i, j = 0;
        fstream fin, fout;
        fin.open("Favourites.csv", ios::in);
        fout.open("Favouritesnew.csv", ios::out);
        string line, word;
        string row[5];
        // Check if this record exists
        // If exists, leave it and
        // add all other data to the new file
        while (!fin.eof())
        {
            getline(fin, line);
            lineStream.clear();
            lineStream.str(line);
            j = 0;
            while (getline(lineStream, word, ','))
            {
                row[j] = word;
                j++;
            }
            string name1 = (row[0]);
            string name2 = (row[1]);
            // writing all records,
            // except the record to be deleted,
            if (name1 == name && name2 == lname)
            {
                count = 1;
            }
            else
            {
                if (!fin.eof())
                {
                    for (i = 0; i < 5 - 1; i++)
                    {
                        fout << row[i] << ",";
                    }
                    fout << row[5 - 1] << "\n";
                }
            }
            if (fin.eof())
                break;
        }
        fin.close();
        fout.close();
        // removing the existing file
        remove("Favourites.csv");
        // renaming the new file with the existing file name
        rename("Favouritesnew.csv", "Favourites.csv");
        return count;
    }
    Node* deleteContact(Node* r, string name,string lname)
    {
        if (r == NULL)
            return NULL;
        int s, s1;
        char* name1, * name2;
        s = r->firstName.length();
        s1 = name.length();
        name1 = new char[s + 1];//root->firstname
        strcpy(name1, r->firstName.c_str());
        name2 = new char[s1 + 1];//user entered name
        strcpy(name2, name.c_str());
        if (strcmp(name2, name1) < 0)
            r->left = deleteContact(r->left, name2,lname);
        else if (strcmp(name2, name1) > 0)
            r->right = deleteContact(r->right, name2,lname);
        else {
            s = r->lastName.length();
            name1 = new char[s + 1];//root->lastName
        s1 = lname.length();
        name2 = new char[s1 + 1];//user entered last name
        strcpy(name1, r->lastName.c_str());
        strcpy(name2, lname.c_str());
        if(strcmp(name1, name2)==0){
            if (r->left == NULL) {
                Node* temp = r->right;
                delete r;
                return temp;
            }
            else if (r->right == NULL) {
                Node* temp = r->left;
                delete r;
                return temp;
            }
            else {
                Node* temp = minvaluenode(r->right);
                r->firstName = temp->firstName;
                r->lastName = temp->lastName;
                r->number = temp->number;
                r->address = temp->address;
                r->email = temp->email;
                r->right = deleteContact(r->right, temp->firstName,temp->lastName);
            }
        }
        else{
            deleteContact(r->left,name,lname);
            deleteContact(r->right,name,lname);
        }
        }
        return r;
    }
    void directory()
    {
        fstream fout;
        string arr,arr2;
        backToChoices:
        fout.open("Record.csv", ios::in);
        char decision = 'y', choice;
        int i = 0,alert=0;
        string *array2=new string[5];
        getline(fout, line, '\n');
            lineStream.clear();
            lineStream.str(line);
            // first record of file is goig to be root
            while (getline(lineStream, array2[i], ','))
            {
                ++i;
            }
        root = new Node(array2); // root node created
        fout.close();
        buildBST();
        cout << endl
            << "\t\t\tWelcome to the Main Menu" << endl;
        cout << endl
            << "#*********************************************************************#" << endl
            << endl;
        cout << "1. Add contact" << endl
            << "2. Modify contact" << endl
            << "3. Delete contact" << endl
            << "4. Search contact" << endl
            << "5. View favourites" << endl
            << "6. View all contacts" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case '1':
            addContact();
            buildBST();
            break;
        case '2':
        system("CLS");
            cout << endl
                << "Enter the first name of the contact person: ";
            cin >> arr;
            cout<<endl<<"Enter the last name of the contact person: ";
            cin>>arr2;
            modifyContact(arr, root,arr2);
            buildBST2(root,'m');
            break;
        case '3':
        system("CLS");
            cout << endl
                << "Enter the first name of the contact person: ";
            cin >> arr;
            cout<<endl<<"Enter the last name of the contact person: ";
            cin>>arr2;
            root=deleteContact(root, arr,arr2);
            buildBST2(root,'d');
            delete_Favourites(arr,arr2);
            delete[] array2;
            break;
        case '4':
        system("CLS");
            cout << endl
                << "Enter the first name of the contact person: ";
            cin >> arr;
            searchContact(root, arr);
            system("CLS");
            break;
        case '5':
        system("CLS");
            viewFavourites();
            break;
        case '6':
        system("CLS");
        cout<<"---------------------------------------";
        viewAllContacts(root);
        cout<<endl<<"---------------------------------------"<<endl;
        break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
        cout << endl
            << "Want to continue performing actions (y/n): ";
        cin >> decision;
        if (decision == 'y') {
            system("CLS");
            goto backToChoices;
        }
        else {
            exit(0);
        }
    }
};
int main()
{
    Phone obj;//a mobile exists
    obj.directory();//a user only clicks the icon and rest of the functions of a phone are carried out by the application
}