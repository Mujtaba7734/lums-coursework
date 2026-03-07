#include <iostream>
using namespace std;


void addProduct(string inventory[100],string order[100], int inv_amount[100], int order_amount[], int  &no_of_items, int &no_of_orders)
{
    string name;
    int index = -1;
    cout << "----------------------------------------------" << endl;
    cout << "              ADD A NEW PRODUCT               " << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Enter product type: ";
    cin >> name;
    for (int i=0; i < no_of_items; i++)
    {
        if (inventory[i] == name)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        inventory[no_of_items] = name;
        cout << "Enter amount: ";
        cin >> inv_amount[no_of_items];
        while (inv_amount[no_of_items] <= 0)
        {
            cout << "Invalid Amount. Enter Amount again";
            cin >> inv_amount[no_of_items];
        }        
        no_of_items++;
    }
    else
    {
        cout << "Enter amount: ";
        int newamount;
        cin >> newamount;
        while (newamount <= 0)
        {
            cout << "Invalid Amount. Enter Amount again";
            cin >> newamount;
        }
        inv_amount[index] += newamount;
    }
    cout << "Product Added to Inventory." << endl;
}

void placeOrder(string inventory[100],string order[100], int inv_amount[100], int order_amount[], int  &no_of_items, int &no_of_orders)
{
    cout << "----------------------------------------------" << endl;
    cout << "              PLACE A NEW ORDER               " << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Enter order type: ";
    cin >> order[no_of_orders];
    bool found = false;
    while (!found)
    {
        for (int i=0; i < no_of_items; i++)
        {
            if (order[no_of_orders] == inventory[i])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Wrong order:" << endl;
            cin >> order[no_of_orders];
        }
    }
    cout << "Enter amount: ";
    cin >> order_amount[no_of_orders];
    while (order_amount[no_of_orders] <= 0)
    {
        cout << "Invalid Amount, Enter again: ";
        cin >> order_amount[no_of_orders];
    }
    no_of_orders++;
    cout << "Order Recorded. " << endl;
}

void updateProduct(string inventory[100],string order[100], int inv_amount[100], int order_amount[], int  &no_of_items, int &no_of_orders)
{
    string name, new_name;
    int index = -1;
    cout << "----------------------------------------------" << endl;
    cout << "             UPDATE PRODUCT TYPE              " << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Enter current product type: ";
    cin >> name;
    for (int i=0; i < no_of_items; i++)
    {
        if (inventory[i] == name)
        {
            index = i;
            break;
        }
    } 
    if (index == -1)
    {
        cout << "Product not found" << endl;
        return;
    }
    cout << "Enter new product type: ";
    cin >> new_name;
    for (int i =0; i < no_of_items; i++)
    {
        if (inventory[i] == new_name)
        {
            inv_amount[i] += inv_amount[index];
            inventory[index] = "";
            for (int i = index; i < no_of_items; i++)
            {
                string temp_name = inventory[i];
                inventory[i] = inventory[i+1];
                inventory[i+1] = temp_name;
                int temp = inv_amount[i];
                inv_amount[i] = inv_amount[i+1];
                inv_amount[i+1] = temp;
            }
            no_of_items--;
            cout << "Product Type Updated Successfully" << endl;
            return;
        }
    }
    inventory[index] = new_name;
    cout << endl;
    cout << "Product Type Updated Successfully" << endl;
}

void updateOrder(string inventory[100],string order[100], int inv_amount[100], int order_amount[], int  &no_of_items, int &no_of_orders)
{
    string name, new_name;
    int index = -1;
    cout << "----------------------------------------------" << endl;
    cout << "             UPDATE ORDER TYPE              " << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Enter current order type: ";
    cin >> name;
    for (int i=0; i < no_of_orders; i++)
    {
        if (order[i] == name)
        {
            index = i;
            break;
        }
    } 
    if (index == -1)
    {
        cout << "Order Name not found" << endl;
        return;
    }
    cout << "Enter new order type: ";
    cin >> new_name;
    order[index] = new_name;
    cout << endl;
    cout << "Order Type Updated Successfully" << endl;
}

void completeOrder(string inventory[100],string order[100], int inv_amount[100], int order_amount[], int  &no_of_items, int &no_of_orders)
{
    cout << "----------------------------------------------" << endl;
    cout << "            FULFILL EARLIEST ORDER            " << endl;
    cout << "----------------------------------------------" << endl;
    cout << " Processing the earliest pending order... " << endl << endl << endl;
    int index = -1;
    cout << endl;
    for (int i=0; i <no_of_items; i++)
    {
        if (inventory[i] == order[0])
        {
            index = i;
            break;
        }
    }
    
    if (index == -1)
    {
        cout << "Cannot fulfill the order for " << order_amount[0] << " " << order[0] << " due to insufficent inventory." << endl;
        return;
    }
    if (inv_amount[index] == 0)
    {
        cout << "Cannot fulfill the order for " << order_amount[0] << " " << order[0] << " due to insufficent inventory." << endl;
        return;
    }
    if (inv_amount[index] == order_amount[0])
    {
        cout << "Order for " << order_amount[0] << " " << order[0] << " completely fulfilled and product" << endl;
        cout << "depleted from inventory." << endl;
        order[0] = "";
        inventory[index] = "";
        order_amount[0] = 0;
        inv_amount[index] = 0;
        for (int i = index; i < no_of_items; i++)
        {
            string temp_name = inventory[i];
            inventory[i] = inventory[i+1];
            inventory[i + 1] = temp_name;
            int temp = inv_amount[i];
            inv_amount[i] = inv_amount[i+1];
            inv_amount[i + 1] = temp;
        }
        no_of_items--;
        for (int i = 0; i < no_of_orders; i++)
        {
            string temp_name = order[i];
            order[i] = order[i+1];
            order[i+1] = temp_name;
            int temp = order_amount[i];
            order_amount[i] = order_amount[i+1];
            order_amount[i+1] = temp;
        }
        no_of_orders--;
    }
    else if (inv_amount[index] < order_amount[0])
    {
        cout << "Order for " << inv_amount[index] << " " << order[0] << " partially fulfilled, " << (order_amount[0] - inv_amount[index]) << " still needed. " << endl;
        order_amount[0] -= inv_amount[index];
        inv_amount[index] = 0;
        if (inv_amount[index] == 0)
        {
            for (int i = 0; i < no_of_items; i++)
            {
                string temp_name = inventory[i];
                inventory[i] = inventory[i+1];
                inventory[i+1] = temp_name;
                int temp = inv_amount[i];
                inv_amount[i] = inv_amount[i+1];
                inv_amount[i+1] = temp;
            }
            no_of_items--;

        }
    }
    else
    {
        cout << "Order for " << order_amount[0] << " " << order[0] << " completely fulfilled. ";
        inv_amount[index] -= order_amount[0];
        for (int i = 0; i < no_of_orders; i++)
        {
            string temp_name = order[i];
            order[i] = order[i+1];
            order[i+1] = temp_name;
            int temp = order_amount[i];
            order_amount[i] = order_amount[i+1];
            order_amount[i+1] = temp;
        }
        no_of_orders--;

        if (inv_amount[index] == 0)
        {
            for (int i = 0; i < no_of_items; i++)
            {
                string temp_name = inventory[i];
                inventory[i] = inventory[i+1];
                inventory[i+1] = temp_name;
                int temp = inv_amount[i];
                inv_amount[i] = inv_amount[i+1];
                inv_amount[i+1] = temp;
            }
            no_of_items--;

        }
    }
}     


void printReport(string inventory[100],string order[100], int inv_amount[100], int order_amount[], int  &no_of_items, int &no_of_orders)
{
    cout << "----------------------------------------------" << endl;
    cout << "        CURRENT INVENTORY & ORDERS            " << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl << endl;
    cout << "Current Inventory: " << endl;
    for (int i=0; i < no_of_items; i++)
    {
        cout << "Product Type: " << inventory[i] << ", Amount: " << inv_amount[i] << endl;
    } 
    cout << endl << endl;
    cout << "Outstanding Orders: " << endl;
    for (int i=0; i < no_of_orders; i++)
    {
        cout << "Order Type: " << order[i] << ", Amount: " << order_amount[i] << endl;
    }
}

int main()
{
    string inventory[100];
    int inv_amount[100];
    string order[100];
    int order_amount[100];
    int choice = 0;
    int no_of_items = 0, no_of_orders = 0;

    while (choice != 7)
    {
        cout << "==============================================" << endl;
        cout << "         WHOLESALE WAREHOUSE SYSTEM           " << endl;
        cout << "==============================================" << endl;
        cout << "           Inventory & Order Management       " << endl;
        cout << "----------------------------------------------" << endl;
        cout << "  1.  Enter a New Product" << endl;
        cout << "  2.  Place an Order" << endl;
        cout << "  3.  Update Product Type" << endl;
        cout << "  4.  Update Order Type" << endl;
        cout << "  5.  Fulfill the Earliest Order" << endl;
        cout << "  6.  Print Status Report" << endl;
        cout << "  7️.  Exit the Program" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "   Please enter your choice (1-7): ";
        cin >> choice;
        while ((choice < 1) || (choice > 7))
        {
            cout << "Invalid Choice, Enter again: ";
            cin >> choice;
        }
        switch(choice)
        {
            case 1: addProduct(inventory, order, inv_amount, order_amount, no_of_items, no_of_orders); break;
            case 2: placeOrder(inventory, order, inv_amount, order_amount, no_of_items, no_of_orders); break;
            case 3: updateProduct(inventory, order, inv_amount, order_amount, no_of_items, no_of_orders); break;
            case 4: updateOrder(inventory, order, inv_amount, order_amount, no_of_items, no_of_orders); break;
            case 5: completeOrder(inventory, order, inv_amount, order_amount, no_of_items, no_of_orders); break;
            case 6: printReport(inventory, order, inv_amount, order_amount, no_of_items, no_of_orders); break;
            case 7:
            cout << "==============================================" << endl;
            cout << "       THANK YOU FOR USING THE SYSTEM!        " << endl;
            cout << "             See you next time!               " << endl;
            cout << "==============================================" << endl;
            return 0;
        }
        cout << endl << endl;
    }
}