#include<iostream>
#include<fstream>

using namespace std;

class shopping{
    private:
        int product_code;
        string product_name;
        float price, discount;
    
    public:
        void menu();
        void admin();
        void buyer();
        void list();
        void add();
        void edit();
        void rem();
        void receipt();
};

void shopping :: menu(){
    menu_start:
        int choice;
        string email, password;

        cout << "__________________________________________" << endl;
        cout << "           WELCOME TO SUPERMARKET" << endl;
        cout << "__________________________________________" << endl;
        cout << "           1) Administrator"<<endl;
        cout << "           2) Buyer"<<endl;
        cout << "           3) Exit"<<endl;
        cout << "__________________________________________" << endl;

        cin >> choice;

        switch(choice){
            case 1: {
                cout << "Enter email : ";
                cin >> email;
                cout << "Enter Password : ";
                cin >> password;

                if(email == "1234" && password == "1234"){
                    admin();
                }
                else{
                    cout << "Wrong credentials !!" << endl;
                }
                break;
            }
            case 2 : {
                buyer();
                break;
            }
            case 3 : {
                exit(0);
            }
            default : {
                cout << "Wrong Choice !! Please choose from the given menu only !" << endl;
            }
        }

    goto menu_start;
}

void shopping :: admin(){
    menu_start:
        int choice;
        string email, password;
        cout << endl << endl;

        cout << "--------------- Administrator Menu ----------------" << endl;
        cout << "-----                                         -----" << endl;
        cout << "-------------   1) Add Product      ---------------" << endl;
        cout << "-----                                         -----" << endl;
        cout << "-------------   2) Edit Product     ---------------" << endl;
        cout << "-----                                         -----" << endl;
        cout << "-------------   3) Remove Product   ---------------" << endl;
        cout << "-----                                         -----" << endl;
        cout << "-------------   4) Go Back          ---------------" << endl;
        cout << "-----                                         -----" << endl;
        cout << "---------------------------------------------------" << endl << endl;

        cin >> choice;

        switch(choice){
            case 1 : {
                add();
                break;
            }
            case 2 : {
                edit();
                break;
            }
            case 3 : {
                rem();
                break;
            }
            case 4 : {
                menu();
                break;
            }
            default : {
                cout << "Wrong Choice !! Please choose from the given menu only !" << endl;
            }
        }
    
    goto menu_start;
}

void shopping :: buyer(){
    menu_start:
        int choice;
        string email, password;
        cout << endl << endl;

        cout << "--------------- Buyer Menu ----------------" << endl;
        cout << "-----                                 -----" << endl;
        cout << "-------------   1) Buy Product    ---------" << endl;
        cout << "-----                                 -----" << endl;
        cout << "-------------   2) Go Back        ---------" << endl;
        cout << "-------------------------------------------" << endl << endl;
        
        cin >> choice;

        switch(choice){
            case 1 : {
                receipt();
                break;
            }
            case 2 : {
                menu();
                break;
            }
            default : {
                cout << "Wrong Choice !! Please choose from the given menu only !" << endl;
            }
        }
    
    goto menu_start;
}

void shopping :: add(){
    add_menu : 
        fstream data;
        int c, duplicate=0;
        float p, d;
        string n;

        cout << "Add New Product : "<< endl << endl;
        cout << "Enter Product Code : ";
        cin >> product_code;
        cout << "Enter Product Name : ";
        cin >> product_name;
        cout << "Enter Product Price : ";
        cin >> price;
        cout << "Enter Product Discount : ";
        cin >> discount;

        data.open("database.txt", ios::in);

        if(!data){
            data.open("database.txt", ios::app | ios::out);
            data << product_code << "\t" << product_name << "\t" << price << "\t" << discount << "\n";
            data.close();
        }
        else{
            data >> c >> n >> p >> d;

            while(!data.eof()){
                if(c == product_code){
                    duplicate ++;
                }
                data >> c >> n >> p >> d;
            }
            data.close();

            if(duplicate > 0){
                cout << "Product already exists !!" << endl;
                goto add_menu;
            }
            else{
                data.open("database.txt", ios::app | ios::out);
                data << product_code << "\t" << product_name << "\t" << price << "\t" << discount << "\n";
                data.close();
                cout << "Record Inserted !!";
            }
        }
}

void shopping :: edit(){
    fstream data, data1;
    int code, found=0, c;
    float p, d;
    string n;

    cout << "Edit Product : "<< endl << endl;
    cout << "Enter Product Code : ";
    cin >> code;

    data.open("database.txt", ios::in);
    if(!data){
        cout << "Record Does Not Exist !!" << endl;
    }
    else{
        data1.open("database1.txt", ios::app | ios::out);

        data >> c >> n >> p >> d;

        while(!data.eof()){
            if(c == code){
                cout << "Enter Product New Code : ";
                cin >> product_code;
                cout << "Enter Product Name : ";
                cin >> product_name;
                cout << "Enter Product Price : ";
                cin >> price;
                cout << "Enter Product Discount : ";
                cin >> discount;

                data1 << product_code << "\t" << product_name << "\t" << price << "\t" << discount << "\n";
                cout << "Record Edited" << endl;
                found = 1;
            }
            else{
                data1 << c << "\t" << n << "\t" << p << "\t" << d << "\n";
            }
            data >> c >> n >> p >> d;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(found == 0){
            cout << "Record Not Found !!" << endl;
        }
    }
}
void shopping :: rem(){
    fstream data, data1;
    int c, found=0, code;
    float p, d;
    string n;

    cout << "Edit Product : "<< endl << endl;
    cout << "Enter Product Code : ";
    cin >> code;

    data.open("database.txt", ios::in);
    if(!data){
        cout << "Record Does Not Exist !!" << endl;
    }
    else{
        data1.open("database1.txt", ios::app | ios::out);

        data >> c >> n >> p >> d;

        while(!data.eof()){
            if(c == code){
                cout << "Product Deleted" << endl;
                found = 1;
            }
            else{
                data1 << c << "\t" << n << "\t" << p << "\t" << d << "\n";
            }
            data >> c >> n >> p >> d;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if(found == 0){
            cout << "Product Not Found !!" << endl;
        }
    }
}

void shopping :: list(){
    fstream data;
    data.open("database.txt", ios::in);
    if(!data){
        cout << "Record Does Not Exist !!" << endl;
    }
    else{
        cout << "_________________________________________" << endl;
        cout << "CODE\tNAME\tPRICE\tDISCOUNT" << endl;
        cout << "_________________________________________" << endl;
        data >> product_code >> product_name >> price >> discount;
        while(!data.eof()){
            cout << product_code << "\t" << product_name << "\t" << price << "\t" << discount << endl;
            data >> product_code >> product_name >> price >> discount;
        }
        data.close();
    }
}

void shopping :: receipt(){
    fstream data;
    data.open("database.txt", ios::in);
    if(!data){
        cout << "No Data found !!";
    }
    else{
        list();
    
        struct Product {
            int code, quantity;
            float price, discount;
            string name;
        };
        struct Product products[100];
        char choice = 'n';
        int count = 0;
    
        cout << endl << endl << "-------------- PLEASE PLACE THE ORDER --------------------" << endl << endl;
    
        int pc, found, c;
        float pr, d;
        string n;
        float total = 0;
        do{
            cout << "Enter the product code : ";
            cin >> pc;
            data >> c >> n >> pr >> d;
            found = 0;

            while(!data.eof()){
                if(c == pc){
                    int q;
                    cout << "Enter the quantity : ";
                    cin >> q;
                    struct Product p;
                    p.code = c;
                    p.quantity = q;
                    p.name = n;
                    p.price = pr;
                    p.discount = d;
                    products[count] = p;
                    total = total + (pr - d)*q;
                    count ++;
                    found = 1;
                    break;
                }
                data >> c >> n >> pr >> d;
            }

            if(found == 0){
                cout << "Wrong Product code !! " << endl;
            }

            cout << "Do you want to dd more products ? 'Y' for yes 'N' for no : ";
            cin >> choice;
        }while(choice == 'y');

        data.close();

        cout << "----------------    RECEIPT    ----------------" << endl;
        cout << "CODE\tQTY\tNAME\tPRICE\tDISCOUNT" << endl;
        cout << "-----------------------------------------------" << endl;
        for(int i=0; i<count; i++){
            cout << products[i].code << "\t" << products[i].quantity << "\t"<< products[i].name << "\t"<< products[i].price << "\t"<< products[i].discount << endl;
        }
        cout << "-----------------------------------------------" << endl;
        cout << "TOTAL : " << total << endl;
        cout << "-----------------------------------------------" << endl;
    }
}
int main()
{
    shopping s;
    s.menu();
    return 0;
}