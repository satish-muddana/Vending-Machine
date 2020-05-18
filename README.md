# Vending-Machine

## Introduction: ##
This project contains the working code of a console appliction with the mock behavior of a vending machine that lets the users to add, view and buy products.

## Functionalities: ##

The functionalities depend of the type of the users. There are two types of Users for this sytem.

#### Customer: ####
The Customer can do the following things.

* View List of Available Products: Users can view the list of available products and details of each product like name, price and quantity.
* Add Items to the Cart: Users can add the list of products to the cart.
* View the Cart: Users can view the list of products that are added to the cart.
* Remove Items from the Cart: Users can remove the products that are added to the cart.
* Checkout Cart: Users can checkout the cart with the required products for the payment.
* Enter the Cash: Users can enter the cash with multiple denominations for payment.
* Buy the Products: Users can take the products from the machine if the payment is successful.
* Collect the Change: Users can collect the change if he pays extra cash.
* Cancel the Transaction: Users can cancel the transaction at any point of time.

#### Admin: ####
The Admin can do the following things.

* Add Products to the Vending Machine: Admin can add new products to the machine and update the information of existing products.
* Remove Products From the Machine: Admin can remove the products from the vending machine to make space for the new products.
* View the Products: Admin can view all the products and its details.
* Add Cash: Admin can add cash and denominations for processing the change.
* Remove Cash: Admin can take out the cash from the machine.
* Reset: Admin can reset the system at any time to its default state.


## Design: ##

### Classes: ###

#### Vending Machine #### 
This is a Driver class. This class has access to all the other classes and interact with one another to achieve the functionality of the vending machine. All the functions that are exposed to the end user are handled in this class.

#### Product Catalog #### 
This is a catalog for all the products inside the Vending Machine. It maintains the count of each product inside the vending machine and is responsible for managing all the products.

#### Cart #### 
This class manages all the list of products that are added to the cart by the customer for checking out.

#### Denomination Catalog #### 
This is a catalog for all the denominations and its types inside the Vending Machine. It maintains the count of each denomination, it's value and is responsible for managing all the cash.

#### Product #### 
This class stores the information and details of each product like name, price and Id.



